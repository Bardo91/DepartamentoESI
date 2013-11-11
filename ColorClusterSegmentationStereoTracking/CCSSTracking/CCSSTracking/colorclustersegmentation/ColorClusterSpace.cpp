////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/10/22
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Color Cluster Space
//		Here is defined the limits of every color and functions to truncate colors.

#include "ColorClusterSpace.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <cmath>

namespace ccss {

ColorClusterSpace::ColorClusterSpace(int n, uint8_t *AClass, uint8_t *BClass,
		uint8_t *CClass, const c3i *colors) {

	this->AClass = new uint8_t[n];
	this->BClass = new uint8_t[n];
	this->CClass = new uint8_t[n];
	clusters = new c3i[8];
	size = n;

	for (int i = 0; i < n; i++) {
		this->AClass[i] = AClass[i];
		this->BClass[i] = BClass[i];
		this->CClass[i] = CClass[i];
		if (i < 8)
			clusters[i] = colors[i];
	}
}

ColorClusterSpace::~ColorClusterSpace() {
	delete[] AClass;
	delete[] BClass;
	delete[] CClass;
	delete[] clusters;

}

int ColorClusterSpace::whichColor(c3i& color) { // If Opencv gives YCrCb values between 0 and 255
	int i = 0, j = int(floor(color.b / 255.0 * (size - 1))), k = int(floor(color.c / 255.0 * (size - 1)));

	i = int(floor(color.a / (COLOR_SPACE == 0 ? 180.0 : 255.0) * (size - 1)));

	int res = AClass[i] & BClass[j] & CClass[k]; //Supposing that colors are not over-layed there's only one possible solution and log2(x) returns an integer /

	int aux = 0;

	if (!res)
		return -1;

	while (!(res & 0x01)) {
		res = res >> 1;
		aux += 1;
	}

	return aux;
}

}/* namespace ccs  is an abreviature of Color Cluster Space Segmentation*/
