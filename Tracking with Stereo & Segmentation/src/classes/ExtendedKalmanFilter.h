/*
 * ExtendedKalmanFilter.h
 *
 *  Created on: Oct 24, 2013
 *      Author: pablo
 */

#ifndef EXTENDEDKALMANFILTER_H_
#define EXTENDEDKALMANFILTER_H_

#include <opencv/cv.hpp>

namespace sysctrl {

class ExtendedKalmanFilter {
	cv::Mat Xfk, Xak, P, Jf, Jh, Q, K, R, Zk;

	void init(cv::Mat, cv::Mat, cv::Vec); // Initialize the algorithm

	void updateJf(cv::Mat);
	void updateJh(cv::Mat);

	void forecastStep(double);
	void filterStep();

	void systemStateFunctionUpdate();

public:
	ExtendedKalmanFilter(); //Constructor
	ExtendedKalmanFilter();

	void EKFStep(); // Execute a EKF step
	void getStateVector(); // Get the current state vector

};

} /* namespace sysctrl */

#endif /* EXTENDEDKALMANFILTER_H_ */
