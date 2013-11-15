////////////////////////////////////////////////////////////////////////////////
//	Single Camera Ground Tracking - Extended Kalman Filter
//		Author: Pablo Ramón Soria
//		Date: 2013/11/02
////////////////////////////////////////////////////////////////////////////////
// Extended Kalman filter applied to single camara ground tracking

#ifndef GROUNDTRACKING_H_
#define GROUNDTRACKING_H_

#include <opencv\cv.h>

namespace sysctrl{

	struct camera {
	cv::Mat pos; // Position vector [x, y, z].
	cv::Mat ori; // Orientation matrix

	//Focal length in term of pixels related to width and height.
	double alphaX; //alphaX = f * mx.
	double alphaY; //alphaY = f * my.

	//Skew coefficient between the x and the y axis
	double gammaSkew;

	// Principal point (Ideally in the center of the image, in term of 1).
	double u0;
	double v0;

	cv::Mat distortionMat;
	cv::Mat projectionMat;

	camera() {
		u0 = v0 = gammaSkew = alphaX = alphaY = 0;
	}

	camera(double _alphaX, double _alphaY, double _gammaSkew, double _u0,
			double _v0, const cv::Mat& _disMat, const cv::Mat& _projMat) {
		alphaX = _alphaX;
		alphaY = _alphaY;
		gammaSkew = _gammaSkew;
		u0 = _u0;
		v0 = _v0;
		distortionMat = _disMat;
		projectionMat = _projMat;
	}

};



class GroundTrackingEKF{
public:
	GroundTrackingEKF(const cv::Mat&, const cv::Mat&, const cv::Mat&);
	~GroundTrackingEKF();

	void updateCameraPos(const cv::Mat&, const cv::Mat&);
	void updateIncT(const double&);

	void updateJf();
	void updateJh_and_hZk();

	void forecastStep();
	void filterStep(const cv::Mat&);

	void stepEKF(const cv::Mat&);

	void getStateVector(cv::Mat&) const;

private:
	cv::Mat Xfk, Xak, K, Jf, Jh, P, Q, R, h_Zk;
	double incT;

	camera cam1, cam2;


};

} // namespace sysctrl


#endif // GROUNDTRACKING_H_