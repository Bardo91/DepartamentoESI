/*
 * SegmentateImage.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#include <SegmentateImage.h>
#include <opencv/highgui.h>

#include <ColorSpaceHSV8.h>

using namespace cv;
using namespace ccss;
namespace ccss {
void segmentateImage(Mat& frame1, Mat& frame2, ColorClusterSpace& CS,
		vector<SegmentedObject>& objs1, vector<vector<LineObjRLE> >& aRLE1,
		vector<SegmentedObject>& objs2, vector<vector<LineObjRLE> >& aRLE2) {

	int n = frame1.channels(); // Count the number of image's channels to use the pointer

	int color1;
	int color2;
	short int js1 = 0, js2 = 0, colorRLE1 = -1, colorRLE2 = -1; // Variables for RLE encode
	for (int i = 0; i < frame1.rows; i++) {
		uchar* ptr1 = frame1.ptr<uchar>(i); // Pointer to i row
		uchar* ptr2 = frame2.ptr<uchar>(i); // Pointer to i row
		vector<LineObjRLE> temp1;
		vector<LineObjRLE> temp2;
		for (int j = 0; j < frame1.cols; j++) {
			// Proximate the color to a cluster
			//First Camera ---------------------------------------------------------------
			c3i auxCol1;
			auxCol1.a = ptr1[n * j];
			auxCol1.b = ptr1[n * j + 1];
			auxCol1.c = ptr1[n * j + 2];
			color1 = CS.whichColor(auxCol1);

			// RLE encoding
			if (j == 0) {
				colorRLE1 = color1;
				js1 = 0;
			} else {
				if (j == frame1.cols - 1) {
					LineObjRLE aux;
					aux.i = i;
					aux.js = js1;
					aux.je = j;
					aux.size = j - js1;
					aux.color = colorRLE1;
					aux.parent = NULL;
					aux.iObj = -1;

					temp1.push_back(aux);
				} else if (color1 != colorRLE1) {
					LineObjRLE aux;
					aux.i = i;
					aux.js = js1;
					aux.je = j;
					aux.size = j - js1;
					aux.color = colorRLE1;
					aux.parent = NULL;
					aux.iObj = -1;

					temp1.push_back(aux);
					colorRLE1 = color1;
					js1 = j;
				}
			}

			// Change the color (Possible improve assigning directly the BGR color instead of using imageHSV2BGR)

			ptr1[n * j] = CS.clusters[color1].a;
			ptr1[n * j + 1] = CS.clusters[color1].b;
			ptr1[n * j + 2] = CS.clusters[color1].c;

			// Second Camera ---------------------------------------------------------------

			c3i auxCol2;
			auxCol2.a = ptr2[n * j];
			auxCol2.b = ptr2[n * j + 1];
			auxCol2.c = ptr2[n * j + 2];
			color2 = CS.whichColor(auxCol2);

			if (j == 0) {
				colorRLE2 = color2;
				js2 = 0;
			} else {
				if (j == frame2.cols - 1) {
					LineObjRLE aux;
					aux.i = i;
					aux.js = js2;
					aux.je = j;
					aux.size = j - js2;
					aux.color = colorRLE2;
					aux.parent = NULL;
					aux.iObj = -1;
					temp2.push_back(aux);
				} else if (color2 != colorRLE2) {
					LineObjRLE aux;
					aux.i = i;
					aux.js = js2;
					aux.je = j;
					aux.size = j - js2;
					aux.color = colorRLE2;
					aux.parent = NULL;
					aux.iObj = -1;

					temp2.push_back(aux);
					colorRLE2 = color2;
					js2 = j;
				}
			}

			ptr2[n * j] = CS.clusters[color2].a;
			ptr2[n * j + 1] = CS.clusters[color2].b;
			ptr2[n * j + 2] = CS.clusters[color2].c;

		}

		aRLE1.push_back(temp1);
		aRLE2.push_back(temp2);

		if (i) { // Except the first line that can't be child of any object (only parent) start joining objects grouped in LineObjRLE variables
			// First Camera ---------------------------------------------------------------
			unsigned int j = 0, jp = 0; // Pointer to current and previous LineObjRLE
			unsigned int pp = aRLE1[i - 1][jp].size, pc = aRLE1[i][j].size; // Pointer to previous and current col
			while (1) {
				// Connecting
				if (!(aRLE1[i - 1][jp].color == -1 || aRLE1[i][j].color == -1)) {
					if (aRLE1[i - 1][jp].color == aRLE1[i][j].color
							&& aRLE1[i - 1][jp].je >= aRLE1[i][j].js
							&& aRLE1[i - 1][jp].js <= aRLE1[i][j].je) {

						if (aRLE1[i][j].parent == NULL) { // Solve overlap problem checking parent
							if (aRLE1[i - 1][jp].parent != NULL) { // Another parent
								aRLE1[i][j].parent = aRLE1[i - 1][jp].parent;
							} else {
								// Is first parent
								aRLE1[i][j].parent = &(aRLE1[i - 1][jp]);
							}
						} else { //In case of overlap
							if (aRLE1[i - 1][jp].parent != NULL) { // New family
								if (aRLE1[i - 1][jp].parent
										!= aRLE1[i][j].parent) {
									aRLE1[i - 1][jp].parent->parent =
											aRLE1[i][j].parent;
								}

							} else {
								// Orphan
								aRLE1[i - 1][jp].parent = aRLE1[i][j].parent;
							}
						}
					}
				}
				if (j >= aRLE1[i].size() - 1 && jp >= aRLE1[i - 1].size() - 1)
					break;
				if (pp > pc) {
					j++;
					pc += aRLE1[i][j].size;
				} else if (pp <= pc) {
					jp++;
					pp += aRLE1[i - 1][jp].size;
				}
			}
			// Second Camera ---------------------------------------------------------------
			j = 0, jp = 0; // Pointer to current and previous LineObjRLE
			pp = aRLE2[i - 1][jp].size, pc = aRLE2[i][j].size; // Pointer to previous and current col
			while (1) {
				// Connecting
				if (!(aRLE2[i - 1][jp].color == -1 || aRLE2[i][j].color == -1)) {
					if (aRLE2[i - 1][jp].color == aRLE2[i][j].color
							&& aRLE2[i - 1][jp].je >= aRLE2[i][j].js
							&& aRLE2[i - 1][jp].js <= aRLE2[i][j].je) {

						if (aRLE2[i][j].parent == NULL) { // Solve overlap problem checking parent
							if (aRLE2[i - 1][jp].parent != NULL) { // Another parent
								aRLE2[i][j].parent = aRLE2[i - 1][jp].parent;
							} else {
								// Is first parent
								aRLE2[i][j].parent = &(aRLE2[i - 1][jp]);
							}
						} else { //In case of overlap
							if (aRLE2[i - 1][jp].parent != NULL) { // New family
								if (aRLE2[i - 1][jp].parent
										!= aRLE2[i][j].parent) {
									aRLE2[i - 1][jp].parent->parent =
											aRLE2[i][j].parent;
								}

							} else {
								// Orphan
								aRLE2[i - 1][jp].parent = aRLE2[i][j].parent;
							}
						}
					}
				}
				if (j >= aRLE2[i].size() - 1 && jp >= aRLE2[i - 1].size() - 1)
					break;
				if (pp > pc) {
					j++;
					pc += aRLE2[i][j].size;
				} else if (pp <= pc) {
					jp++;
					pp += aRLE2[i - 1][jp].size;
				}
			}
		}

	}
	// First Camera ---------------------------------------------------------------
	//Re-assign parents due to overlap
	for (unsigned int i = 0; i < aRLE1.size(); i++) {
		for (unsigned int j = 0; j < aRLE1[i].size(); j++) {
			if (aRLE1[i][j].parent != NULL) {
				LineObjRLE auxRLE = *aRLE1[i][j].parent;

				int loopAvoider = 0; // Need to be checked if image size is larger than 320x240. If possible check the origin of loops
				while (auxRLE.parent != NULL && loopAvoider < 30) {
					aRLE1[i][j].parent = auxRLE.parent;
					auxRLE = *auxRLE.parent;
					loopAvoider++;
				}

				if (aRLE1[i][j].parent->iObj == -1) {
					aRLE1[i][j].parent->iObj = objs1.size();
					SegmentedObject obj(*aRLE1[i][j].parent);
					objs1.push_back(obj);
				}
			}
		}
	}
	for (unsigned int i = 0; i < aRLE1.size(); i++) {
		for (unsigned int j = 0; j < aRLE1[i].size(); j++) {
			if (aRLE1[i][j].parent != NULL) {
				objs1[aRLE1[i][j].parent->iObj].addLineObjRLE(aRLE1[i][j]);
			}
		}
	}
	// Second Camera ---------------------------------------------------------------
	for (unsigned int i = 0; i < aRLE2.size(); i++) {
		for (unsigned int j = 0; j < aRLE2[i].size(); j++) {
			if (aRLE2[i][j].parent != NULL) {
				LineObjRLE auxRLE = *aRLE2[i][j].parent;

				int loopAvoider = 0; // Need to be checked if image size is larger than 320x240. If possible check the origin of loops
				while (auxRLE.parent != NULL && loopAvoider < 30) {
					aRLE2[i][j].parent = auxRLE.parent;
					auxRLE = *auxRLE.parent;
					loopAvoider++;
				}

				if (aRLE2[i][j].parent->iObj == -1) {
					aRLE2[i][j].parent->iObj = objs2.size();
					SegmentedObject obj(*aRLE2[i][j].parent);
					objs2.push_back(obj);
				}
			}
		}
	}
	for (unsigned int i = 0; i < aRLE2.size(); i++) {
		for (unsigned int j = 0; j < aRLE2[i].size(); j++) {
			if (aRLE2[i][j].parent != NULL) {
				objs2[aRLE2[i][j].parent->iObj].addLineObjRLE(aRLE2[i][j]);
			}
		}
	}
}

}
