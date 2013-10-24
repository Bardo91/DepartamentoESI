/*
 * ExtendedKalmanFilter.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: pablo
 */

#include <ExtendedKalmanFilter.h>

using namespace cv;

namespace sysctrl {

void ExtendedKalmanFilter::init(Mat Q, Mat R, cv::Vec Xi) {
	this->Q = Q;
	this->R = R;
	this->Xak = Xi;

}

} /* namespace ccss */
