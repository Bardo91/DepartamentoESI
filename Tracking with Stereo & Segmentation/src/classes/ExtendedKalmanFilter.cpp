/*
 * ExtendedKalmanFilter.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: pablo
 */

#include <ExtendedKalmanFilter.h>

using namespace cv;
using namespace std;

namespace sysctrl {

void ExtendedKalmanFilter::init(const Mat& Q, const Mat& R, const cv::Mat& Xi) {
	this->Q = Q;
	this->R = R;
	this->Xak.ptr<double>(0)[0] = Xi.ptr<double>(0)[0];
	this->Xak.ptr<double>(1)[0] = Xi.ptr<double>(1)[0];
	this->Xak.ptr<double>(2)[0] = Xi.ptr<double>(2)[0];
	this->Xak.ptr<double>(3)[0] = 0;
	this->Xak.ptr<double>(4)[0] = 0;
	this->Xak.ptr<double>(5)[0] = 0;

	P = Mat::eye(6, 6, CV_64F);

}

void ExtendedKalmanFilter::forecastStep() {
	updateJf();
	Xfk = Jf * Xak;
	P = Jf * P * Jf.t() + Q;
}

void ExtendedKalmanFilter::filterStep() {
	updateJh();
	K = P * Jh.t() * ((Jh * P * Jh.t() + R).inv());
	Mat I = Mat::eye(6, 6, CV_64F);
	P = (I - K * Jh) * P;
	Mat h_Zk(4, 1, CV_64F);
	fromSystemState2ObservationState(h_Zk);

	Xak = Xfk + K * (Zk - h_Zk);
}

ExtendedKalmanFilter::ExtendedKalmanFilter(const cv::Mat& Q, const cv::Mat& R,
		const cv::Mat& Xi) {

}

ExtendedKalmanFilter::~ExtendedKalmanFilter() {

}

void ExtendedKalmanFilter::EKFStep() {
	forecastStep();
	filterStep();

}

void ExtendedKalmanFilter::getStateVector(Mat& state) const {
	Xak.copyTo(state);
}

} /* namespace ccss */
