/*
 * StereoVisionEKF.cpp
 *
 *  Created on: Oct 25, 2013
 *      Author: pablo
 */

#include <StereoVisionEKF.h>

using namespace sysctrl::visionctrl;
using namespace cv;
using namespace std;

namespace sysctrl {

void StereoVisionEKF::updateJf() {
	// On this case of linear function, Jf is very simple.
	Jf = Mat::eye(6, 6, CV_64F);
	Jf.ptr<double>(0)[3] = incT;
	Jf.ptr<double>(1)[4] = incT;
	Jf.ptr<double>(2)[5] = incT;
}

void StereoVisionEKF::updateJh() {
	// Coordinates related to cameras C1 & C2
	double PYc1, PXc1, PZc1, PYc2, PXc2, PZc2;
	Mat Pc1, Pc2;
	Mat P =
			(Mat_<double>(3, 1) << Xfk.ptr<double>(0)[0], Xfk.ptr<double>(1)[0], Xfk.ptr<
					double>(2)[0]);
	Mat C1 = (Mat_<double>(3, 1) << cam1.pos[0], cam1.pos[1], cam1.pos[2]);
	Mat C2 = (Mat_<double>(3, 1) << cam2.pos[0], cam2.pos[1], cam2.pos[2]);

	Pc1 = cam1.ori * (P - C1);
	Pc2 = cam2.ori * (P - C2);

	PYc1 = Pc1.ptr<double>(0)[0];
	PYc2 = Pc2.ptr<double>(0)[0];
	PXc1 = Pc1.ptr<double>(1)[0];
	PXc2 = Pc2.ptr<double>(1)[0];
	PZc1 = Pc1.ptr<double>(2)[0];
	PZc2 = Pc2.ptr<double>(2)[0];

	assert(PZc1 != 0.0); // The tracked object cannot be at the same plane where the cameras are.

	// Calculate Jacobian of h(.)
	double *ptr = Jh.ptr<double>(0);

	double *ptrOri0 = cam1.ori.ptr<double>(0);
	double *ptrOri1 = cam1.ori.ptr<double>(1);
	double *ptrOri2 = cam1.ori.ptr<double>(2);

	ptr[0] = cam1.alphaX * (ptrOri0[0] * PZc1 - ptrOri2[0] * PXc1) / PZc1
			/ PZc1;
	ptr[1] = cam1.alphaX * (ptrOri0[1] * PZc1 - ptrOri2[1] * PXc1) / PZc1
			/ PZc1;
	ptr[2] = cam1.alphaX * (ptrOri0[2] * PZc1 - ptrOri2[2] * PXc1) / PZc1
			/ PZc1;
	ptr[3] = 0;
	ptr[4] = 0;
	ptr[5] = 0;

	ptr = Jh.ptr<double>(1);
	ptr[0] = cam1.alphaX * (ptrOri1[0] * PZc1 - ptrOri2[0] * PYc1) / PZc1
			/ PZc1;
	ptr[1] = cam1.alphaX * (ptrOri1[1] * PZc1 - ptrOri2[1] * PYc1) / PZc1
			/ PZc1;
	ptr[2] = cam1.alphaX * (ptrOri1[2] * PZc1 - ptrOri2[2] * PYc1) / PZc1
			/ PZc1;
	ptr[3] = 0;
	ptr[4] = 0;
	ptr[5] = 0;

	ptrOri0 = cam2.ori.ptr<double>(0);
	ptrOri1 = cam2.ori.ptr<double>(1);
	ptrOri2 = cam2.ori.ptr<double>(2);
	ptr = Jh.ptr<double>(2);
	ptr[0] = cam2.alphaX * (ptrOri0[0] * PZc2 - ptrOri2[0] * PXc2) / PZc2
			/ PZc2;
	ptr[1] = cam2.alphaX * (ptrOri0[1] * PZc2 - ptrOri2[1] * PXc2) / PZc2
			/ PZc2;
	ptr[2] = cam2.alphaX * (ptrOri0[2] * PZc2 - ptrOri2[2] * PXc2) / PZc2
			/ PZc2;
	ptr[3] = 0;
	ptr[4] = 0;
	ptr[5] = 0;

	ptr = Jh.ptr<double>(3);
	ptr[0] = cam2.alphaX * (ptrOri1[0] * PZc2 - ptrOri2[0] * PYc2) / PZc2
			/ PZc2;
	ptr[1] = cam2.alphaX * (ptrOri1[1] * PZc2 - ptrOri2[1] * PYc2) / PZc2
			/ PZc2;
	ptr[2] = cam2.alphaX * (ptrOri1[2] * PZc2 - ptrOri2[2] * PYc2) / PZc2
			/ PZc2;
	ptr[3] = 0;
	ptr[4] = 0;
	ptr[5] = 0;
}

//------------------------------------------------------------(Mat *X, Mat *Zk, camera cam1,camera cam2)
void StereoVisionEKF::fromSystemState2ObservationState(Mat& h_Zk) {
	// Calculate coordinate points related to cameras
	double PYc1, PXc1, PZc1, PYc2, PXc2, PZc2;
	Mat Pc1, Pc2;
	Mat P =
			(Mat_<double>(3, 1) << Xfk.ptr<double>(0)[0], Xfk.ptr<double>(1)[0], Xfk.ptr<
					double>(2)[0]);
	Mat C1 = (Mat_<double>(3, 1) << cam1.pos[0], cam1.pos[1], cam1.pos[2]);
	Mat C2 = (Mat_<double>(3, 1) << cam2.pos[0], cam2.pos[1], cam2.pos[2]);

	Pc1 = cam1.ori * (P - C1);
	Pc2 = cam2.ori * (P - C2);
	PYc1 = Pc1.ptr<double>(0)[0];
	PYc2 = Pc2.ptr<double>(0)[0];
	PXc1 = Pc1.ptr<double>(1)[0];
	PXc2 = Pc2.ptr<double>(1)[0];
	PZc1 = Pc1.ptr<double>(2)[0];
	PZc2 = Pc2.ptr<double>(2)[0];

	// Calculate observation state variables.

	h_Zk.ptr<double>(0)[0] = cam1.alphaX * PXc1 / PZc1;
	h_Zk.ptr<double>(1)[0] = cam1.alphaX * PYc1 / PZc1;
	h_Zk.ptr<double>(2)[0] = cam2.alphaX * PXc2 / PZc2;
	h_Zk.ptr<double>(3)[0] = cam2.alphaX * PYc2 / PZc2;

	cout << "Zk = " << Zk << endl;
	cout << "H_Zk = " << h_Zk << endl;

	waitKey();
}

StereoVisionEKF::StereoVisionEKF(const camera& camera1, const camera& camera2,
		const Mat& Q, const Mat& R, const cv::Mat& Xi) :
		ExtendedKalmanFilter(Q, R, Xi) {

	Xfk.create(6, 1, CV_64F);
	Xak.create(6, 1, CV_64F);
	P.create(6, 6, CV_64F);
	Jf.create(6, 6, CV_64F);
	Jh.create(4, 6, CV_64F);
	K.create(6, 4, CV_64F);
	Zk.create(4, 1, CV_64F);
	incT = 0;
	init(Q, R, Xi);
}

StereoVisionEKF::~StereoVisionEKF() {
	Xfk.release();
	Xak.release();
	P.release();
	Jf.release();
	Jh.release();
	Q.release();
	R.release();
	K.release();
	Zk.release();
}

void StereoVisionEKF::updateZk(const Mat& Zk) {
	Zk.copyTo(this->Zk);
}

void StereoVisionEKF::updateincT(const double& incT) {
	this->incT = incT;
}

void StereoVisionEKF::updateCameras(const camera& camera1,
		const camera& camera2) {
	cam1 = camera1;
	cam2 = camera2;
}

} /* namespace sysctrl */
