/*
 * SegmentedObject.h
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#ifndef SEGMENTEDOBJECT_H_
#define SEGMENTEDOBJECT_H_

#include <opencv/cv.h>

#include <algorithm>    // std::sort
#include <vector>       // std::vector

namespace ccss {

struct LineObjRLE {
	unsigned int i;
	unsigned int js;
	unsigned int je;
	unsigned int size;
	int color;
	struct LineObjRLE *parent;
	int iObj;
};

class SegmentedObject {
	std::vector<LineObjRLE> obj;

	cv::Point2d upperLeft, downRight; // Border pixels
	int color;
	uint size;

public:
	SegmentedObject(LineObjRLE ini);

	void addLineObjRLE(LineObjRLE);
	void addRLEFamily(SegmentedObject&);

	int getLines();
	LineObjRLE getRLEObj(int);
	cv::Point2d getUpperLeft();
	cv::Point2d getDownRight();
	unsigned int getColor();
	unsigned int getSize();
	unsigned int getBBSize();
	cv::Point2d getCentroid();

	void sortObj();
};

} /* namespace ccss */

#endif /* SEGMENTEDOBJECT_H_ */
