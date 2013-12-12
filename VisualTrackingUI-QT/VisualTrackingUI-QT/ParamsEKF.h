////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extended Kalman Filter parameters

#ifndef CAMERADATAEKF_H_
#define CAMERADATAEKF_H_

#include <opencv/cv.h>

using namespace cv;

// Adjust matrixes:
namespace vision{
	static const Mat matQ =
			(Mat_<double>(6, 6) <<	0.05, 0, 0, 0, 0, 0, 
									0, 0.05, 0, 0, 0, 0, 
									0, 0, 0.05, 0, 0, 0, 
									0, 0, 0, 0.05, 0, 0, 
									0, 0, 0, 0, 0.05, 0, 
									0, 0, 0, 0, 0, 0.05);
	static const Mat matR =
			(Mat_<double>(4, 4) <<	0.1, 0, 0, 0, 
									0, 0.1, 0, 0, 
									0, 0, 0.1, 0, 
									0, 0, 0, 0.1);

	static const Mat x0 =
			(Mat_<double>(6, 1) <<	8,//0, 
									12,//0, 
									0,//0, 
									0,//0, 
									0,//0, 
									0);//0);

	static const Mat I = (Mat_<double>(6,6) <<	1, 0, 0, 0, 0, 0,
										0, 1, 0, 0, 0, 0,
										0, 0, 1, 0, 0, 0,
										0, 0, 0, 1, 0, 0,
										0, 0, 0, 0, 1, 0,
										0, 0, 0, 0, 0, 1);
} // namespace vision
#endif