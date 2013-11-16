/*
 * SegmentateImage.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#include "SegmentateImage.h"
#include <opencv/highgui.h>

#include "ColorSpaceHSV8.h"

using namespace cv;
using namespace ccss;
namespace ccss {
void segmentateImage(Mat& frame, ColorClusterSpace& CS,
		vector<SegmentedObject>& objs, vector<vector<LineObjRLE> >& aRLE) {

	int n = frame.channels(); // Count the number of image's channels to use the pointer

	int color;

	short int js1 = 0, colorRLE = -1; // Variables for RLE encode
	for (int i = 0; i < frame.rows; i++) {
		uchar* ptr = frame.ptr<uchar>(i); // Pointer to i row

		vector<LineObjRLE> temp1;

		for (int j = 0; j < frame.cols; j++) {
			// Proximate the color to a cluster
			//First Camera ---------------------------------------------------------------
			c3i auxCol;
			auxCol.a = ptr[n * j];
			auxCol.b = ptr[n * j + 1];
			auxCol.c = ptr[n * j + 2];
			color = CS.whichColor(auxCol);

			// RLE encoding
			if (j == 0) {
				colorRLE = color;
				js1 = 0;
			} else {
				if (j == frame.cols - 1) {
					LineObjRLE aux;
					aux.i = i;
					aux.js = js1;
					aux.je = j;
					aux.size = j - js1;
					aux.color = colorRLE;
					aux.parent = NULL;
					aux.iObj = -1;

					temp1.push_back(aux);
				} else if (color != colorRLE) {
					LineObjRLE aux;
					aux.i = i;
					aux.js = js1;
					aux.je = j;
					aux.size = j - js1;
					aux.color = colorRLE;
					aux.parent = NULL;
					aux.iObj = -1;

					temp1.push_back(aux);
					colorRLE = color;
					js1 = j;
				}
			}

			// Change the color (Possible improve assigning directly the BGR color instead of using imageHSV2BGR)

			if (color == -1) {
				ptr[n * j] = CS.clusters[0].a;
				ptr[n * j + 1] = CS.clusters[0].b;
				ptr[n * j + 2] = CS.clusters[0].c;
			} else {
				ptr[n * j] = CS.clusters[color].a;
				ptr[n * j + 1] = CS.clusters[color].b;
				ptr[n * j + 2] = CS.clusters[color].c;
			}

		}

		aRLE.push_back(temp1);

		if (i) { // Except the first line that can't be child of any object (only parent) start joining objects grouped in LineObjRLE variables
			unsigned int j = 0, jp = 0; // Pointer to current and previous LineObjRLE
			unsigned int pp = aRLE[i - 1][jp].size, pc = aRLE[i][j].size; // Pointer to previous and current col
			while (1) {
				// Connecting
				if (!(aRLE[i - 1][jp].color == -1 || aRLE[i][j].color == -1)) {
					if (aRLE[i - 1][jp].color == aRLE[i][j].color
							&& aRLE[i - 1][jp].je >= aRLE[i][j].js
							&& aRLE[i - 1][jp].js <= aRLE[i][j].je) {

						if (aRLE[i][j].parent == NULL) { // Solve overlap problem checking parent
							if (aRLE[i - 1][jp].parent != NULL) { // Another parent
								aRLE[i][j].parent = aRLE[i - 1][jp].parent;
							} else {
								// Is first parent
								aRLE[i][j].parent = &(aRLE[i - 1][jp]);
							}
						} else { //In case of overlap
							if (aRLE[i - 1][jp].parent != NULL) { // New family
								if (aRLE[i - 1][jp].parent
										!= aRLE[i][j].parent) {
									aRLE[i - 1][jp].parent->parent =
											aRLE[i][j].parent;
								}

							} else {
								// Orphan
								aRLE[i - 1][jp].parent = aRLE[i][j].parent;
							}
						}
					}
				}
				if (j >= aRLE[i].size() - 1 && jp >= aRLE[i - 1].size() - 1)
					break;
				if (pp > pc) {
					j++;
					pc += aRLE[i][j].size;
				} else if (pp <= pc) {
					jp++;
					pp += aRLE[i - 1][jp].size;
				}
			}
		}

	}
	//Re-assign parents due to overlap
	for (unsigned int i = 0; i < aRLE.size(); i++) {
		for (unsigned int j = 0; j < aRLE[i].size(); j++) {
			if (aRLE[i][j].parent != NULL) {
				LineObjRLE auxRLE = *aRLE[i][j].parent;

				int loopAvoider = 0; // Need to be checked if image size is larger than 320x240. If possible check the origin of loops
				while (auxRLE.parent != NULL && loopAvoider < 30) {
					aRLE[i][j].parent = auxRLE.parent;
					auxRLE = *auxRLE.parent;
					loopAvoider++;
				}

				if (aRLE[i][j].parent->iObj == -1) {
					aRLE[i][j].parent->iObj = objs.size();
					SegmentedObject obj(*aRLE[i][j].parent);
					objs.push_back(obj);
				}
			}
		}
	}
	for (unsigned int i = 0; i < aRLE.size(); i++) {
		for (unsigned int j = 0; j < aRLE[i].size(); j++) {
			if (aRLE[i][j].parent != NULL) {
				objs[aRLE[i][j].parent->iObj].addLineObjRLE(aRLE[i][j]);
			}
		}
	}
}

}
