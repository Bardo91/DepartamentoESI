////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#ifndef _VISUAL_TRACKING_UI_OBJECT_GEO_H_
#define _VISUAL_TRACKING_UI_OBJECT_GEO_H_

#include <opencv/cv.h>

namespace vision{
	namespace position{
		enum eOriType {eEulerAngles, eQuaternaries};
		enum ePosType {eCartesian, ePolar, eSphere};

		class ObjectGeo{ // Class that arrange and manage geometrical information of an object
		public:
			ObjectGeo();
		
		public:
			void setPosition(const cv::Mat& _position);
			void setOrientation(const cv::Mat& _orientation);

			void getPosition(cv::Mat& _position) const;
			void getOrientation(cv::Mat& _orientation) const;

		private:
			eOriType oriType;
			cv::Mat position;
			cv::Mat orientation;
		}; // class ObjectGeo
	} // namespace position
} // namespace vision


#endif //_VISUAL_TRACKING_UI_OBJECT_GEO_H_