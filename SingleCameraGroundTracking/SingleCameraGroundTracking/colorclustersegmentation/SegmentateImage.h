/*
 * SegmentateImage.h
 *
 *  Created on: Oct 28, 2013
 *      Author: pablo
 */

#ifndef SEGMENTATEIMAGE_H_
#define SEGMENTATEIMAGE_H_

#include <opencv/cv.h>
#include <string>

#include "SegmentedObject.h"
#include "ColorClusterSpace.h"

namespace ccss {

void segmentateImage(cv::Mat& frame1, ColorClusterSpace& CS,
		std::vector<SegmentedObject>& objs1,
		std::vector<std::vector<LineObjRLE> >& aRLE1);

}

#endif /* SEGMENTATEIMAGE_H_ */
