/*
 * StereoVisionEKF.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: pablo
 */

#include "StereoVisionEKF.h"
#include "CameraDataEKF.h"

#include "opencv/cv.h"
#include "opencv/highgui.h"

using namespace cv;

namespace sysctrl {

StereoVisionEKF::StereoVisionEKF(const Mat& Q_, const Mat& R_, const Mat& x0_) {

	Q = Q_;
	R = R_;
	Xak = x0_;
	P = Mat::eye(6, 6, CV_64F);
	h_Zk = Mat::zeros(4, 1, CV_64F);
	Jh = Mat::zeros(4, 6, CV_64F);
	Jf = Mat::zeros(6, 6, CV_64F);

	incT = 0;

	cam1 = camera(alphaX, alphaY, gammaSkew, u0, v0, distortionMat,
			projectionMat);

	//The rest of variables needn't to be initialized
}

StereoVisionEKF::~StereoVisionEKF() {
	Q.deallocate();
	R.deallocate();
	Xfk.deallocate();
	Xak.deallocate();
	P.deallocate();
	K.deallocate();
	Jf.deallocate();
	Jh.deallocate();
}

void StereoVisionEKF::updateCameraPos(const cv::Mat& C1, const cv::Mat& ori1) {
	cam1.pos = C1;
	cam1.ori = ori1;

}

void StereoVisionEKF::updateIncT(const double& incT_) {
	incT = incT_;
}

void StereoVisionEKF::updateJf() {
	Jf =
			(Mat_<double>(6, 6) << 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
}
void StereoVisionEKF::updateJh_and_hZk() {
////////////--------------------------------------------------------
}
void StereoVisionEKF::forecastStep() {
	updateJf();

	Xfk = Jf * Xak;

	P = Jf * P * Jf.t() + Q;

}

void StereoVisionEKF::filterStep(const Mat& Zk) {
	updateJh_and_hZk();

	K = P * Jh.t() * (Jh * P * Jh.t() + R).inv();

	P = (Mat::eye(6, 6, CV_64F) - K * Jh);

	Xak = Xfk + K * (Zk - h_Zk);

}

void StereoVisionEKF::stepEKF(const Mat& Zk) {
	forecastStep();
	filterStep(Zk);
}

void StereoVisionEKF::getStateVector(Mat& Xak_) const {
	Xak_ = Xak;
}

} /* namespace sysctrl */
