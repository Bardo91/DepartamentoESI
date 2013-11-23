////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 

#include "ObjectGeo.h"

#include <opencv/cv.h>

using namespace cv;

namespace vision{
	namespace position{
		//--------------------------------------------------------------------
		void ObjectGeo::setPosition(const Mat& _position){
			_position.copyTo(position);
		}

		//--------------------------------------------------------------------
		void ObjectGeo::setOrientation(const Mat& _orientation){
			_orientation.copyTo(orientation);
		}

		//--------------------------------------------------------------------
		void ObjectGeo::getPosition(Mat& _position) const{
			position.copyTo(_position);
		}

		//--------------------------------------------------------------------
		void ObjectGeo::getOrientation(Mat& _orientation) const{
			orientation.copyTo(_orientation);
		}

		//--------------------------------------------------------------------

	} // namespace position
} // namespace vision