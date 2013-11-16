////////////////////////////////////////////////////////////////////////////////
//	Single Camera Ground Tracking - Extended Kalman Filter
//		Author: Pablo Ramón Soria
//		Date: 2013/11/02
////////////////////////////////////////////////////////////////////////////////
// Extended Kalman filter applied to single camara ground tracking


#include "GroundTrackingEKF.h"
#include "CameraDataEKF.h"

#include <opencv/cv.h>

using namespace sysctrl;
using namespace cv;

GroundTrackingEKF::GroundTrackingEKF(const Mat& _Q, const Mat& _R, const Mat& _x0){
	Q = _Q;
	R = _R;
	Xak = _x0;
	P = Mat::eye(6,6,CV_64F);
	h_Zk = Mat::zeros(2,1,CV_64F);
	Jh = Mat::zeros(2,6,CV_64F);
	Jf = Mat::zeros(6,6,CV_64F);

	incT = 0;

	cam = camera(alphaX, alphaY, gammaSkew, u0, v0, distortionMat,
			projectionMat);

	//The rest of variables needn't to be initialized
}


void GroundTrackingEKF::updateCameraPos(const Mat& _C, const Mat& _ori){
	cam.pos = _C;
	cam.ori = _ori;

}

void GroundTrackingEKF::updateIncT(const double& _incT){
	incT = _incT;
}

void GroundTrackingEKF::updateJf(){
	Jf =
			(Mat_<double>(6, 6) << 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, incT, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
}

void GroundTrackingEKF::updateJh_and_hZk(){
	double * R = (double*) cam.ori.data;

	double f = cam.alphaX;

	Mat point = Xfk(Range(0, 3), Range::all());

	Mat Pc = cam.ori.t() * (point - cam.pos);

	double* pcdata = (double*) Pc.data;

	double PXc = pcdata[0];
	double PYc = pcdata[1];
	double PZc = pcdata[2];

	// updating h_Zk

	double * hzkdata = (double*) h_Zk.data;

	hzkdata[0] = -f * PYc / PZc;
	hzkdata[1] = -f * PXc / PZc;

	// Updating Jh

	double * dataJh = (double*) Jh.data;
	dataJh[0] = f *R[3 * 0 + 0];
	dataJh[1] = f *R[3 * 1 + 0];
	dataJh[2] = f *R[3 * 2 + 0];

	dataJh[6] = f *R[3 * 0 + 1];
	dataJh[7] = f *R[3 * 1 + 1];
	dataJh[8] = f *R[3 * 2 + 1];

	dataJh[3] = dataJh[4] = dataJh[5] = dataJh[9] = dataJh[10] = dataJh[11] = 0;
}

void GroundTrackingEKF::forecastStep(){
	updateJf();

	Xfk = Jf*Xak;
	P = Jf*P*Jf.t() + Q;
}

void GroundTrackingEKF::filterStep(const Mat& Zk) {
	updateJh_and_hZk();

	K = P * Jh.t() * (Jh * P * Jh.t() + R).inv();

	P = (Mat::eye(6, 6, CV_64F) - K * Jh);

	Xak = Xfk + K * (Zk - h_Zk);

}

void GroundTrackingEKF::stepEKF(const Mat& Zk) {
	forecastStep();
	filterStep(Zk);
}

void GroundTrackingEKF::getStateVector(Mat& Xak_) const {
	Xak_ = Xak;
}