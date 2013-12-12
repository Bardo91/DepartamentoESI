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
		Mat obtainRotationMatrix(double a, double b, double c){
			Mat Rx = (Mat_<double>(3, 3) << 1, 0, 0, 0, cos(a), -sin(a), 0, sin(a), cos(a));

			Mat Ry = (Mat_<double>(3, 3) << cos(b), 0, sin(b), 0, 1, 0, -sin(b), 0, cos(b));

			Mat Rz = (Mat_<double>(3, 3) << cos(c), -sin(c), 0, sin(c), cos(c), 0, 0, 0, 1);

			return Rz * Ry * Rx;

			/*return (Mat_<double>(3,3) <<	cos(c)*cos(b),	cos(c)*sin(b)*sin(a)-sin(c)*cos(a),		cos(c)*sin(b)*cos(a)+sin(c)*sin(a),
											sin(c)*cos(b),	sin(c)*sin(b)*sin(a)+cos(c)*cos(a),		sin(c)*sin(b)*cos(a)-sin(a)*cos(c),
											-sin(b),		cos(b)*sin(a),							cos(b)*cos(a));*/
		}

		//--------------------------------------------------------------------
		ObjectGeo::ObjectGeo(){
			oriType = eEulerAngles;
		}

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
		Mat ObjectGeo::getPosition() const{
			return position;
		}

		//--------------------------------------------------------------------
		void ObjectGeo::getOrientation(Mat& _orientation) const{
			orientation.copyTo(_orientation);
		}

		//--------------------------------------------------------------------
		Mat ObjectGeo::getOrientation() const{
			return orientation;
		}

		//--------------------------------------------------------------------

	} // namespace position
} // namespace vision