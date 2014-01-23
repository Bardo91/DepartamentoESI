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
#include <fstream>
#include <vector>

namespace vision{
	class PositionManager{
	public:
		PositionManager();
		~PositionManager();
	

	public:
		int configureCams(std::string& _filePath); // both cams are supposed to have same properties.

		int preparePositioner(std::string& _posFilePath, bool _isFixed);

		void closeStream();

		int updatePosAndTime();

		void getCameraPosAndTime(position::Camera& _cam1, position::Camera& _cam2, double& _time) const;
		position::Camera getCamera(int _cam);

		double getTime();

	private:
		void getNextLine(std::vector<std::string>& _splittedString);
		
		void updatePos(const std::vector<std::string>& _splittedString);
		void updateTime(const std::vector<std::string>& _splittedString);

	private:
		int posMethod; // 0 from file ;  1 from vicon
		bool isFixed, isFirstPos;

		position::Camera *cam1, *cam2;
		double refTime; // Reference of time when the application started
		double currentTime;

		int idObj1, idObj2;
		std::ifstream posFile;

	}; // class PositionManager
} // namespace vision


#endif //_VISUAL_TRACKING_UI_POSITION_MANAGER_H_
