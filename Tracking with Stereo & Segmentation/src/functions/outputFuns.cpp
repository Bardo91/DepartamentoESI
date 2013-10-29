/*
 * outputFuns.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: pablo
 */

#include <outputFuns.h>

using namespace cv;

namespace ccss {

void highlighObjs(std::vector<SegmentedObject>& objs, cv::Mat ori,
		unsigned int sizeThreshold) {
	for (unsigned int i = 0; i < objs.size(); i++) {
		if (objs[i].getSize() > sizeThreshold) {
			Point p1 = Point(objs[i].getUpperLeft().x,
					objs[i].getUpperLeft().y);
			Point p2 = Point(objs[i].getDownRight().x,
					objs[i].getDownRight().y);

			rectangle(ori, p1, p2, Scalar(0, 0, 0), 1);

			circle(ori, Point(objs[i].getCentroid().x, objs[i].getCentroid().y),
					2, Scalar(255, 255, 255));
		}
	}
}

}  // namespace ccss

