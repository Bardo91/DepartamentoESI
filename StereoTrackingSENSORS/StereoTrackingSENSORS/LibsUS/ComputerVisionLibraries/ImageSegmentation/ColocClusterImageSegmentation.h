////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/23
////////////////////////////////////////////////////////////////////////////////
// Color cluster segmentation algorithm.

#ifndef _VISUAL_TRACKING_UI_SEGMENTATEIMAGE_H_
#define _VISUAL_TRACKING_UI_SEGMENTATEIMAGE_H_

#include "ColorClusterSpace.h"
#include <SimpleObject.h>

#include <opencv/cv.h>
#include <string>


namespace vision {
	namespace segmentation {
		// Unique frame color cluster segmentation.
		int ColorClusterImageSegmentation(cv::Mat& _frame, ColorClusterSpace& _CS, uint16_t _threshold, std::vector<SimpleObject>& _objects);
		
		// Pair frames color cluster segmentation. Better that execute a couple times the previous algorithm, because reuse loops for both frames.
		int ColorClusterImageSegmentation(cv::Mat& _frame1, cv::Mat& _frame2, ColorClusterSpace& _CS, uint16_t _threshold, std::vector<SimpleObject>& _objects1, std::vector<SimpleObject>& _objects2);
		
	} // namespace segmentation
} // namespace vision


#endif // _VISUAL_TRACKING_UI_SEGMENTATEIMAGE_H_
