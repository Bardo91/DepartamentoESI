////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#ifndef _VISUAL_TRACKING_UI_POSITION_MANAGER_H_
#define _VISUAL_TRACKING_UI_POSITION_MANAGER_H_

#include "ComputerVisionLibraries/Positioning/Camera.h"

#include <opencv/cv.h>
#include <string>

namespace vision{
	class PositionManager{
	public:
		PositionManager();
		~PositionManager();
	
	public:
		int configureCams(std::string& _filePath); // both cams are supposed to have same properties.

	private:
		position::Camera *cam1, *cam2;
	}; // class PositionManager
} // namespace vision


#endif //_VISUAL_TRACKING_UI_POSITION_MANAGER_H_
