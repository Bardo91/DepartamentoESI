/*
 * StereoVisionEKF.h
 *
 *  Created on: Oct 25, 2013
 *      Author: pablo
 */

#ifndef STEREOVISIONEKF_H_
#define STEREOVISIONEKF_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <ExtendedKalmanFilter.h>

namespace sysctrl {

namespace visionctrl {
struct camera {
	double pos[3]; // Position vector [x, y, z].
	cv::Mat ori; // Inverse of orientation matix

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
	}

	camera(double x, double y, double z, const cv::Mat& _ori, double _alphaX,
			double _alphaY, double _gammaSkew, double _u0, double _v0,
			const cv::Mat& _disMat, const cv::Mat& _projMat) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		ori = _ori;
		alphaX = _alphaX;
		alphaY = _alphaY;
		gammaSkew = _gammaSkew;
		u0 = _u0;
		v0 = _v0;
		distortionMat = _disMat;
		projectionMat = _projMat;
	}

};
}

class StereoVisionEKF: public ExtendedKalmanFilter {

	visionctrl::camera cam1, cam2;

	double incT;

	virtual void updateJf();
	virtual void updateJh();

	virtual void fromSystemState2ObservationState(cv::Mat& h_Zk);

public:
	StereoVisionEKF(const visionctrl::camera&, const visionctrl::camera&,
			const cv::Mat&, const cv::Mat&, const cv::Mat&);
	~StereoVisionEKF();

	void updateZk(const cv::Mat&);
	void updateincT(const double&);
	void updateCameras(const visionctrl::camera&, const visionctrl::camera&);
};

} /* namespace sysctrl */

#endif /* STEREOVISIONEKF_H_ */
