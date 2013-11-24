////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#ifndef _VISUAL_TRACKING_UI_POSITION_MANAGER_H_
#define _VISUAL_TRACKING_UI_POSITION_MANAGER_H_

#include "ComputerVisionLibraries/Positioning/Camera.h"
#include "ComputerVisionLibraries/Timing/time.h"

#include <opencv/cv.h>
#include <string>

namespace vision{
	class PositionManager{
	public:
		PositionManager();
		~PositionManager();
	
	private:
		int configureCams(std::string& _filePath); // both cams are supposed to have same properties.
		int initTimer();

	public:
		int preparePositioner(std::string& _filePath, int _acquisitionMethod);

	private:
		position::Camera *cam1, *cam2;
		STime *timer;
		TReal refTime; // Reference of time when the application started
	}; // class PositionManager
} // namespace vision


#endif //_VISUAL_TRACKING_UI_POSITION_MANAGER_H_
