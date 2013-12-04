////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extended Kalman Filter applied to Stereo Vision

#ifndef _VISUAL_TRACKING_UI_STEREOVISIONEKF_H_
#define _VISUAL_TRACKING_UI_STEREOVISIONEKF_H_

#include <ComputerVisionLibraries/Positioning/Camera.h>

#include <opencv/cv.h>

namespace vision {
	namespace tracking{

		class StereoVisionEKF {
		public:
			StereoVisionEKF();
			StereoVisionEKF(const cv::Mat& _Q, const cv::Mat& _R, const cv::Mat& _x0, position::Camera& _cam1, position::Camera& _cam2);
			
			void init(const cv::Mat& _Q, const cv::Mat& _R, const cv::Mat& _x0,const vision::position::Camera& _cam1,const vision::position::Camera& _cam2);

		private:
			void updateJf();
			void updateJh_and_hZk();

			void forecastStep();
			void filterStep(const cv::Mat&);

		public:
			void updateCameraPos(const cv::Mat& _pos1, const cv::Mat& _pos2, const cv::Mat& _ori1, const cv::Mat& _ori2);
			void updateIncT(const double& _incT);

			void stepEKF(const cv::Mat&);

			void getStateVector(cv::Mat&) const;

		private:
			cv::Mat Xfk, Xak, K, Jf, Jh, P, Q, R, h_Zk;
			double incT;

			vision::position::Camera cam1, cam2;

		};
	} // namespace tracking
} // namespace vision

#endif // _VISUAL_TRACKING_UI_STEREOVISIONEKF_H_ 
