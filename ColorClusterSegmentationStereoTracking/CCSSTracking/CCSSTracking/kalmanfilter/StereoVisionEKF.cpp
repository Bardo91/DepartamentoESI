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
	cam2 = camera(alphaX, alphaY, gammaSkew, u0, v0, distortionMat,
			projectionMat);

	//The rest of variables needn't to be initialized
}

void StereoVisionEKF::updateCameraPos(const cv::Mat& C1, const cv::Mat& C2,
		const cv::Mat& ori1, const cv::Mat& ori2) {

	cam1.pos = C1;
	cam2.pos = C2;
	cam1.ori = ori1;
	cam2.ori = ori2;

}

void StereoVisionEKF::updateIncT(const double& incT_) {
	incT = incT_;
}

void StereoVisionEKF::updateJf() {
	Jf =
			(Mat_<double>(6, 6) << 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
}
void StereoVisionEKF::updateJh_and_hZk() {
	double * R1 = (double*) cam1.ori.data;
	double * R2 = (double*) cam2.ori.data;

	double f = cam1.alphaX;

	Mat point = Xfk(Range(0, 3), Range::all());

	Mat Pc1 = cam1.ori.t() * (point - cam1.pos);
	Mat Pc2 = cam2.ori.t() * (point - cam2.pos);

	double* pc1data = (double*) Pc1.data;
	double* pc2data = (double*) Pc2.data;

	double PXc1 = pc1data[0];
	double PYc1 = pc1data[1];
	double PZc1 = pc1data[2];
	double PXc2 = pc2data[0];
	double PYc2 = pc2data[1];
	double PZc2 = pc2data[2];

	// updating h_Zk

	double * hzkdata = (double*) h_Zk.data;

	hzkdata[0] = f * PYc1 / PZc1;
	hzkdata[1] = f * PXc1 / PZc1;
	hzkdata[2] = f * PYc2 / PZc2;
	hzkdata[3] = f * PXc2 / PZc2;
	//

	double * dataJh = (double*) Jh.data;

	dataJh[0] = f * (R1[3 * 0 + 1] * PZc1 - R1[3 * 0 + 2] * PYc1) / PZc1 / PZc1;
	dataJh[1] = f * (R1[3 * 1 + 1] * PZc1 - R1[3 * 1 + 2] * PYc1) / PZc1 / PZc1;
	dataJh[2] = f * (R1[3 * 2 + 1] * PZc1 - R1[3 * 2 + 2] * PYc1) / PZc1 / PZc1;

	dataJh[6] = f * (R1[3 * 0 + 0] * PZc1 - R1[3 * 0 + 2] * PXc1) / PZc1 / PZc1;
	dataJh[7] = f * (R1[3 * 1 + 0] * PZc1 - R1[3 * 1 + 2] * PXc1) / PZc1 / PZc1;
	dataJh[8] = f * (R1[3 * 2 + 0] * PZc1 - R1[3 * 2 + 2] * PXc1) / PZc1 / PZc1;

	dataJh[12] = f * (R2[3 * 0 + 1] * PZc2 - R2[3 * 0 + 2] * PYc2) / PZc2
			/ PZc2;
	dataJh[13] = f * (R2[3 * 1 + 1] * PZc2 - R2[3 * 1 + 2] * PYc2) / PZc2
			/ PZc2;
	dataJh[14] = f * (R2[3 * 2 + 1] * PZc2 - R2[3 * 2 + 2] * PYc2) / PZc2
			/ PZc2;

	dataJh[18] = f * (R2[3 * 0 + 0] * PZc2 - R2[3 * 0 + 2] * PXc2) / PZc2
			/ PZc2;
	dataJh[19] = f * (R2[3 * 1 + 0] * PZc2 - R2[3 * 1 + 2] * PXc2) / PZc2
			/ PZc2;
	dataJh[20] = f * (R2[3 * 2 + 0] * PZc2 - R2[3 * 2 + 2] * PXc2) / PZc2
			/ PZc2;

	dataJh[3] = dataJh[4] = dataJh[5] = dataJh[9] = dataJh[10] = dataJh[11] =
			dataJh[15] = dataJh[16] = dataJh[17] = dataJh[21] = dataJh[22] =
					dataJh[23] = 0;

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

	/*cout << "K = " << K << endl;
	 cout << "P = " << P << endl;
	 cout << "Jh = " << Jh << endl;
	 cout << "Xfk = " << Xfk << endl;
	 cout << "Xak = " << Xak << endl;
	 cout << "Zk = " << Zk << endl;
	 cout << "hZk = " << h_Zk << endl << "--------------------" << endl;

	 waitKey();*/

}

void StereoVisionEKF::stepEKF(const Mat& Zk) {
	forecastStep();
	filterStep(Zk);
}

void StereoVisionEKF::getStateVector(Mat& Xak_) const {
	Xak_ = Xak;
}

} /* namespace sysctrl */
