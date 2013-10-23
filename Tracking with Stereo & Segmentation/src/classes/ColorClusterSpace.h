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

#ifndef COLORCLUSTERSPACE_H_
#define COLORCLUSTERSPACE_H_
#endif

#define LOG2 0.3010299957

#ifndef COLOR_SPACE
#define COLOR_SPACE 0  // Types 0-HSV ; 1-RGB ; ...
#endif

namespace ccss {

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct color3int {
	uint a, b, c;
} c3i;

class ColorClusterSpace {
	uchar AClass[8];
	uchar BClass[8];
	uchar CClass[8];
	c3i clusters[8];
public:
	ColorClusterSpace(uchar*, uchar*, uchar*, c3i *);

	int whichColor(c3i); // Return between 0 and 255
};

} /* namespace ccs  is an abreviature of Color Cluster Space Segmentation*/
