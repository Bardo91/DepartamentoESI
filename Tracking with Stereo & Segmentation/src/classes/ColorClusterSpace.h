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

#ifndef COLORCLUSTERSPACE_H_
#define COLORCLUSTERSPACE_H_

#define LOG2 0.3010299957

#ifndef COLOR_SPACE
#define COLOR_SPACE 0  // Types 0-HSV ; 1-RGB ; ...
#endif

namespace ccss {

typedef unsigned int uint;

typedef struct color3int {
	uint a, b, c;
} c3i;

class ColorClusterSpace {
	uint8_t AClass[8];
	uint8_t BClass[8];
	uint8_t CClass[8];
public:
	c3i clusters[8];
	ColorClusterSpace();
	ColorClusterSpace(int, uint8_t*, uint8_t*, uint8_t*, const c3i *);

	int whichColor(c3i); // Return between 0 and 255
};

} /* namespace ccs  is an abreviature of Color Cluster Space Segmentation*/
#endif
