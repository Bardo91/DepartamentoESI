/*
 * CameraDataEKF.h
 *
 *  Created on: Oct 28, 2013
 *      Author: pablo
 */

#ifndef CAMERADATAEKF_H_
#define CAMERADATAEKF_H_

#include <opencv/cv.h>
#include <StereoVisionEKF.h>

using namespace cv;
using namespace std;

// Adjust matrixes:
const Mat matQ =
		(Mat_<double>(6, 6) << 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0, 0.05);
const Mat matR =
		(Mat_<double>(4, 4) << 0.1, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0.1);

//Parameters obtained by ROS mono-camera calibration module for Logitech c525:
//Focal length in term of pixels related to width and height.
const double alphaX = 834.964910; //alphaX = f * mx.
const double alphaY = 834.091275; //alphaY = f * my.

//Skew coefficient between the x and the y axis
const double gammaSkew = 0.0;

// Principal point (Ideally in the center of the image, in term of 1).
const double u0 = 268.591572 / 480.0;
const double v0 = 324.159142 / 640.0;

const Mat distortionMat =
		(Mat_<double>(5, 1) << 0.123201, -0.049532, 0.030087, -0.020951, 0.000000);

const Mat projectionMat =
		(Mat_<double>(3, 4) << 852.964478, 0.000000, 262.131568, 0.000000, 0.000000, 846.645447, 329.710386, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000);

#endif /* CAMERADATAEKF_H_ */
