/*
 * SegmentededObject.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#include <SegmentedObject.h>

namespace ccss {

SegmentedObject::SegmentedObject(LineObjRLE ini) {
	upperLeft.x = 9999;
	downRight.x = 0;
	upperLeft.y = 9999;
	downRight.y = 0;
	size = 0;
	color = ini.color;
	addLineObjRLE(ini);

}

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

bool sortFunction(LineObjRLE a, LineObjRLE b) {
	return a.i < b.i || (a.i == b.i && a.je < b.js) ? true : false;
}

void SegmentedObject::sortObj() {
	std::sort(obj.begin(), obj.end(), sortFunction);
}

} /* namespace ccss */

