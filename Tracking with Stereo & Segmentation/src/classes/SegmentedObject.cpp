/*
 * SegmentededObject.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#include <SegmentedObject.h>

namespace ccss {

void SegmentedObject::addLineObjRLE(LineObjRLE aux) {
	obj.push_back(aux);

	if (upperLeft.y > aux.i)
		upperLeft.y = aux.i;
	if (upperLeft.x > aux.js)
		upperLeft.x = aux.js;
	if (downRight.y < aux.i)
		downRight.y = aux.i;
	if (downRight.x < aux.je)
		downRight.x = aux.je;
	size += aux.size + 1;
}

void SegmentedObject::addRLEFamily(SegmentedObject& family) {
	for (int k = 0; k < family.getLines(); k++) {
		LineObjRLE aux = family.getRLEObj(k);
		obj.push_back(aux);
		if (upperLeft.y > aux.i)
			upperLeft.y = aux.i;
		if (upperLeft.x > aux.js)
			upperLeft.x = aux.js;
		if (downRight.y < aux.i)
			downRight.y = aux.i;
		if (downRight.x < aux.je)
			downRight.x = aux.je;
		size += aux.size + 1;
	}
}

int SegmentedObject::getLines() {
	return obj.size();
}

LineObjRLE SegmentedObject::getRLEObj(int k) {
	return obj[k];
}

cv::Point2d SegmentedObject::getUpperLeft() {
	return upperLeft;
}

cv::Point2d SegmentedObject::getDownRight() {
	return downRight;
}

unsigned int SegmentedObject::getColor() {
	return color;
}

unsigned int SegmentedObject::getSize() {
	return size;
}

unsigned int SegmentedObject::getBBSize() {
	return (downRight.x - upperLeft.x) * (downRight.y - upperLeft.y);
}

cv::Point2d SegmentedObject::getCentroid() {
	return cv::Point((upperLeft.x + downRight.x) / 2,
			(upperLeft.y + downRight.y) / 2);
}

} /* namespace ccss */

