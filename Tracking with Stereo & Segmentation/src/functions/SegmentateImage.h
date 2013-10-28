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

#include <SegmentedObject.h>
#include <ColorClusterSpace.h>

namespace ccss {

void segmentateImage(cv::Mat& frame1, cv::Mat& frame2, ColorClusterSpace& CS,
		std::vector<SegmentedObject>& objs1,
		std::vector<std::vector<LineObjRLE> >& aRLE1,
		std::vector<SegmentedObject>& objs2,
		std::vector<std::vector<LineObjRLE> >& aRLE2);

}

#endif /* SEGMENTATEIMAGE_H_ */
