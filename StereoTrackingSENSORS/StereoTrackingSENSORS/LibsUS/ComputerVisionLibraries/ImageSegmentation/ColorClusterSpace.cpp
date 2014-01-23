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

namespace vision {
	namespace segmentation {
		ColorClusterSpace::ColorClusterSpace(int _n, uint8_t *_AClass, uint8_t *_BClass,
				uint8_t *_CClass, const c3i *_colors) {

			AClass = new uint8_t[_n];
			BClass = new uint8_t[_n];
			CClass = new uint8_t[_n];
			clusters = new c3i[8];
			size = _n;

			for (int i = 0; i < _n; i++) {
				AClass[i] = _AClass[i];
				BClass[i] = _BClass[i];
				CClass[i] = _CClass[i];
				if (i < 8)
					clusters[i] = _colors[i];
			}
		}

		ColorClusterSpace::~ColorClusterSpace() {
			delete[] AClass;
			delete[] BClass;
			delete[] CClass;
			delete[] clusters;

		}
	} // namespace segmentation
} // namespace vision
