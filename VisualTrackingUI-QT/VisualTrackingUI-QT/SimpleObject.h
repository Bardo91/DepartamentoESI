////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/11/19
////////////////////////////////////////////////////////////////////////////////
// SimpleObject

#ifndef _VISUAL_TRACKING_UI_SIMPLE_OBJECT_H_
#define _VISUAL_TRACKING_UI_SIMPLE_OBJECT_H_

#include <opencv/cv.h>

namespace vision{

	struct SimpleObject{
		cv::Point2d upperLeft; // Margins of the object.
		cv::Point2d downRight;
		cv::Point2d centroid; // Geometrical Centroid of object.
		unsigned int size; // Number of pixels of the objec.

		int color; // This variable might not be used (Depend on Color Segmentation Algorithm).

	};

}

#endif //_VISUAL_TRACKING_UI_SIMPLE_OBJECT_H_

