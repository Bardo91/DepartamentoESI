/*
 * ExtendedKalmanFilter.h
 *
 *  Created on: Oct 24, 2013
 *      Author: pablo
 */

#ifndef EXTENDEDKALMANFILTER_H_
#define EXTENDEDKALMANFILTER_H_

#include <opencv/cv.hpp>
#include <opencv/highgui.h>

namespace sysctrl {

class ExtendedKalmanFilter {
	cv::Mat Xfk, Xak, P, Jf, Jh, Q, K, R, Zk;

	void init(const cv::Mat&, const cv::Mat&, const cv::Vec&); // Initialize the algorithm

	void forecastStep();
	void filterStep();

	virtual void updateJf() =0;
	virtual void updateJh() =0;

	virtual void fromSystemState2ObservationState(cv::Mat&) =0;

public:
	ExtendedKalmanFilter(const cv::Mat&, const cv::Mat&, const cv::Vec&); //Constructor
	virtual ~ExtendedKalmanFilter() =0;

	void EKFStep(); // Execute a EKF step
	void getStateVector(const cv::Mat&) const; // Get the current state vector

};

// Inline functions.

} /* namespace sysctrl */

#endif /* EXTENDEDKALMANFILTER_H_ */
