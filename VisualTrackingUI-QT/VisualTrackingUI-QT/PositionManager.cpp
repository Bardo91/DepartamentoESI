////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#include "PositionManager.h"
#include "ComputerVisionLibraries/Positioning/Camera.h"
using namespace cv;

namespace vision{
	PositionManager::PositionManager(){
		cam1 = new position::Camera();
		cam2 = new position::Camera();
	}

	PositionManager::~PositionManager(){
		delete cam1, cam2;
	}

	int PositionManager::configureCams(string& _filePath){
		if (cam1->loadPropertiesFromFile(_filePath) != 0 ||cam2->loadPropertiesFromFile(_filePath) != 0)
			return -1;

		return 0;
	}
	
} // namespace vision
