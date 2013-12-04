////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#ifndef _VISUAL_TRACKING_UI_POSITION_MANAGER_H_
#define _VISUAL_TRACKING_UI_POSITION_MANAGER_H_

#include "ComputerVisionLibraries/Positioning/Camera.h"
#include "ComputerVisionLibraries/Timing/time.h"

#include <opencv/cv.h>
#include <string>
#include <fstream>
#include <vector>

namespace vision{
	class PositionManager{
	public:
		PositionManager();
		~PositionManager();
	
	private:
		int initTimer();

	public:
		int configureCams(std::string& _filePath); // both cams are supposed to have same properties.

		int preparePositioner(std::string& _posFilePath, bool _isFixed);
		int preparePositioner(/*vicon stream*/);

		void closeStream();

		int updatePosAndTime();

		void getCameraPosAndTime(position::Camera& _cam1, position::Camera& _cam2, TReal& _time) const;
		position::Camera getCamera(int _cam);
	private:
		void getNextLine(std::vector<std::string>& _splittedString);
		
		void updatePos(const std::vector<std::string>& _splittedString);
		void updateTime(const std::vector<std::string>& _splittedString);
		void updateTime();

	private:
		int posMethod; // 0 from file ;  1 from vicon
		bool isFixed, isFirstPos;

		position::Camera *cam1, *cam2;
		STime *timer;
		TReal refTime; // Reference of time when the application started
		TReal currentTime;

		std::ifstream posFile;

	}; // class PositionManager
} // namespace vision


#endif //_VISUAL_TRACKING_UI_POSITION_MANAGER_H_
