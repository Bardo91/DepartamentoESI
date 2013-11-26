////////////////////////////////////////////////////////////////////////////////
//	Single Camera Ground Tracking - Extended Kalman Filter
//		
//		Author: Pablo Ramón Soria
//		Date: 2013/11/02
//
////////////////////////////////////////////////////////////////////////////////
// Extended Kalman filter applied to single camara ground tracking

#ifndef _VISUAL_TRACKING_UI_GROUNDTRACKING_H_
#define _VISUAL_TRACKING_UI_GROUNDTRACKING_H_

#include <ComputerVisionLibraries/Positioning/Camera.h>

#include <opencv\cv.h>

namespace vision{
	namespace tracking {
		class GroundTrackingEKF{
		public:
			GroundTrackingEKF();
			GroundTrackingEKF(const cv::Mat& _Q, const cv::Mat& _R, const cv::Mat& _x0, vision::position::Camera _cam);

			void init(const cv::Mat& _Q, const cv::Mat& _R, const cv::Mat& _x0, vision::position::Camera _cam);
		
		private:
			void forecastStep();
			void filterStep(const cv::Mat&);

			void updateJf();
			void updateJh_and_hZk();

		public:
			void stepEKF(const cv::Mat&);

			void getStateVector(cv::Mat&) const;

			void updateCameraPos(const cv::Mat&, const cv::Mat&);
			void updateIncT(const double&);
		
		private:
			cv::Mat Xfk, Xak, K, Jf, Jh, P, Q, R, h_Zk;
			double incT;

			vision::position::Camera cam;


		};
	} // namespace tracking
} // namespace sysctrl


#endif // _VISUAL_TRACKING_UI_GROUNDTRACKING_H_