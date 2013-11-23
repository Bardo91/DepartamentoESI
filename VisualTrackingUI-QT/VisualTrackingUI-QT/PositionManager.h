////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#ifndef _VISUAL_TRACKING_UI_POSITION_MANAGER_H_
#define _VISUAL_TRACKING_UI_POSITION_MANAGER_H_

#include "ComputerVisionLibraries/Positioning/Camera.h"

#include <opencv/cv.h>

namespace vision{
	namespace position{
		class PositionManager{
		public:

		private:
			Camera cam1, cam2;
		}; // class PositionManager
	} // namespace position
} // namespace vision


#endif //_VISUAL_TRACKING_UI_POSITION_MANAGER_H_
