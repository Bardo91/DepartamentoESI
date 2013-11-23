////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 

#include "Camera.h"

#include <opencv/cv.h>
#include <cassert>

using namespace cv;

namespace vision{
	namespace position{
		//--------------------------------------------------------------------
		int Camera::loadPropertiesFromFile(string _filePath){
			// 666 TODO: implement function.

			return 0;
		}

		//--------------------------------------------------------------------
		int Camera::preparePositionFile(){
			// 666 TODO: implement function.
			
			return 0;
		}

		//--------------------------------------------------------------------
		int Camera::startViconConnection(){
			// 666 TODO: implement function.
			
			return 0;
		}

		//--------------------------------------------------------------------
		int Camera::init(){
			// 666 TODO: implement function.
			
			return 0;
		}

		//--------------------------------------------------------------------
		double Camera::getFocalLenght() const{
			return focalLenght;
		}

		//--------------------------------------------------------------------
		int Camera::fixDistorsion(Mat& _frame) const{
			if(distorsionCoef == 0 || projectionCoef == 0)
				return -1;
			assert(_frame.rows != 0);
			// 666 TODO: implement function.

			return 0;
		}

	} // namespace position
} // namespace vision
