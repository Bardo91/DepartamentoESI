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

bool sortFunction(LineObjRLE a, LineObjRLE b) {
	return a.i < b.i || (a.i == b.i && a.je < b.js) ? true : false;
}

class SegmentedObject {
	std::vector<LineObjRLE> obj;

	cv::Point2d upperLeft, downRight; // Border pixels
	int color;
	uint size;

public:
	SegmentedObject();

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

	void sortObj() {
		std::sort(obj.begin(), obj.end(), sortFunction);
	}
};

} /* namespace ccss */

#endif /* SEGMENTEDOBJECT_H_ */
