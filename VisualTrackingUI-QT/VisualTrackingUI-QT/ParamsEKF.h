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
const Mat matQ =
		(Mat_<double>(6, 6) << 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05);
const Mat matR =
		(Mat_<double>(4, 4) << 0.1, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0.1);

const Mat x0 =
		(Mat_<double>(6, 1) << 0, 0, 0, 0, 0, 0);


#endif