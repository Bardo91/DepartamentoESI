////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/19
////////////////////////////////////////////////////////////////////////////////
// 

#ifndef _VISUAL_TRACKING_UI_POSITION_MANAGER_H_
#define _VISUAL_TRACKING_UI_POSITION_MANAGER_H_

namespace vision{
	namespace position{
		class ObjectGeo{
		public:

		private:
			cv::Mat position;
			cv::Mat orientation;
		};

		class camera : ObjectGeo{
		public:

		private:
			double focalLenght;
			double *distorsionMat;
		};

		class PositionManager{

		}; // Position Manager
	} //namespace position
} // namespace vision


#endif // _VISUAL_TRACKING_UI_POSITION_MANAGER_H_