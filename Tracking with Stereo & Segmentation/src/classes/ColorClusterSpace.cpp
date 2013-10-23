/*
 * ColorClusterSpace.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: pablo
 */

#include <ColorClusterSpace.h>

namespace ccss {

ColorClusterSpace::ColorClusterSpace(int n, uint8_t* AClass, uint8_t* BClass,
		uint8_t* CClass, c3i* colors) {
	for (uint i = 0; i < n; i++) {
		this->AClass[i] = AClass[i];
		this->BClass[i] = BClass[i];
		this->CClass[i] = CClass[i];
	}
}

int ColorClusterSpace::whichColor(c3i color) { // If Opencv gives YCrCb values between 0 and 255
	int i = 0, j = round(color.b / 255.0 * 8), k = round(color.c / 255.0 * 8);

	i = round(color.a / (COLOR_SPACE == 0 ? 180.0 : 255.0) * 8);

	int res = AClass[i] & BClass[j] & CClass[k]; //Supposing that colors are not over-layed there's only one possible solution and log2(x) returns an integer /

	return res != 0 ? log(double(res)) / LOG2 : -1;
}

}/* namespace ccs  is an abreviature of Color Cluster Space Segmentation*/
