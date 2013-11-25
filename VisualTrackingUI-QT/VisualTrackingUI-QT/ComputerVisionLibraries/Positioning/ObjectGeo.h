////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
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

		cv::Mat obtainRotationMatrix(double a, double b, double c);


		class ObjectGeo{ // Class that arrange and manage geometrical information of an object
		public:
			ObjectGeo();
		
		public:
			void setPosition(const cv::Mat& _position);
			void setOrientation(const cv::Mat& _orientation);

			void getPosition(cv::Mat& _position) const;
			cv::Mat getPosition() const;
			void getOrientation(cv::Mat& _orientation) const;
			cv::Mat getOrientation() const;

		private:
			eOriType oriType;
			cv::Mat position;
			cv::Mat orientation;
		}; // class ObjectGeo
	} // namespace position
} // namespace vision


#endif //_VISUAL_TRACKING_UI_OBJECT_GEO_H_