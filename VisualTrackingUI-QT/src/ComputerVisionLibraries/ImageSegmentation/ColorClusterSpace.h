/*
 * ColorClusterSpace.h
 *
 *  Created on: Oct 22, 2013
 *      Author: Pablo Ramón Soria
 *
 *      In this header are defined the classes and functions used on ImageClusterSegmentation
 *		algorithm.
 *
 */

#include <math.h>
#include <stdint.h>
#include <string>

#ifndef _VISUAL_TRACKING_UI_COLORCLUSTERSPACE_H_
#define _VISUAL_TRACKING_UI_COLORCLUSTERSPACE_H_

#define LOG2 0.3010299957

namespace vision {
	namespace segmentation {
		typedef unsigned int uint;

		typedef struct color3int {
			uint a, b, c;
		} c3i;

		class ColorClusterSpace {
			uint8_t *AClass;
			uint8_t *BClass;
			uint8_t *CClass;
		public:
			int size;
			c3i *clusters;
			ColorClusterSpace(int, uint8_t *, uint8_t *, uint8_t *, const c3i *);
			~ColorClusterSpace();

			int whichColor(c3i&); // Return between 0 and 255
		};


		inline int ColorClusterSpace::whichColor(c3i& color) { // If Opencv gives YCrCb values between 0 and 255
			int i = 0, j = int(floor(color.b / 255.0 * (size - 1))), k = int(floor(color.c / 255.0 * (size - 1)));

			i = int(floor(color.a / 180.0 * (size - 1)));

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

		// OTHER FUNCTIONS 
		//666 TODO: change place
		ColorClusterSpace *CreateHSVCS_8c(int MaskH, int MaskS, int MaskV);
		int bin2dec(std::string bin);

	} // namespace segmentation.
} // namespace vision.
#endif // _VISUAL_TRACKING_UI_COLORCLUSTERSPACE_H_
