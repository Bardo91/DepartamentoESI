/*
 * ColorClusterSpace.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: pablo
 */

#include "ColorClusterSpace.h"

namespace ccss {

ColorClusterSpace::ColorClusterSpace(uchar* AClass, uchar* BClass,
		uchar* CClass, c3i* colors) {
	for (uint i = 0; i < 8; i++) {
		this->AClass[i] = AClass[i];
		this->BClass[i] = BClass[i];
		this->CClass[i] = CClass[i];
	}
}

int ColorClusterSpace::whichColor(c3i color) { // If Opencv gives YCrCb values between 0 and 255
	int i = 0, j = 0, k = 0;
	if (COLOR_SPACE)
		i = round(color.a / 255.0 * 8), j = round(color.b / 255.0 * 8), k =
				round(color.c / 255.0 * 8);
	else
		i = round(color.a / 180.0 * 8), j = round(color.b / 255.0 * 8), k =
				round(color.c / 255.0 * 8);
	int res = AClass[i] & BClass[j] & CClass[k]; //Supposing that colors are not over-layed there's only one possible solution and log2(x) returns an integer /

	return res != 0 ? log(double(res)) / LOG2 : -1;
}

}/* namespace ccs  is an abreviature of Color Cluster Space Segmentation*/
