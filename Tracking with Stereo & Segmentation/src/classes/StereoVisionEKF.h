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
	const double alphaX; //alphaX = f * mx.
	const double alphaY; //alphaY = f * my.

	//Skew coefficient between the x and the y axis
	const double gammaSkew;

	// Principal point (Ideally in the center of the image, in term of 1).
	const double u0;
	const double v0;

	const cv::Mat distortionMat;
	const cv::Mat projectionMat;

};
}

class StereoVisionEKF: public ExtendedKalmanFilter {

	visionctrl::camera cam1, cam2;

	double incT;

	void updateJf();
	void updateJh();

	void fromSystemState2ObservationState(cv::Mat& h_Zk);

public:
	StereoVisionEKF(const visionctrl::camera&, const visionctrl::camera&,
			const cv::Mat&, const cv::Mat&, const cv::Mat&);
	~StereoVisionEKF();

	void updateincT(const double&);
	void updateCameras(const visionctrl::camera&, const visionctrl::camera&);
};

} /* namespace sysctrl */

#endif /* STEREOVISIONEKF_H_ */
