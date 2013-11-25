////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#include "PositionManager.h"
#include "ComputerVisionLibraries/Positioning/Camera.h"


using namespace cv;
using namespace std;
using namespace vision::position;

namespace vision{
	//------------------------------------------------------------------------
	PositionManager::PositionManager(){
		cam1 = new position::Camera();
		cam2 = new position::Camera();
	}

	//------------------------------------------------------------------------
	PositionManager::~PositionManager(){
		delete cam1, cam2;
	}

	//------------------------------------------------------------------------
	int PositionManager::configureCams(string& _filePath){
		if (cam1->loadPropertiesFromFile(_filePath) != 0 ||cam2->loadPropertiesFromFile(_filePath) != 0)
			return -1;

		return 0;
	}

	//------------------------------------------------------------------------
	int PositionManager::initTimer(){
		if(!STime::isInitialized())
			STime::init();
		timer = STime::get();
		timer->update();
		refTime = timer->frameTime();

		return timer == nullptr ? -1 : 0;
	}

	//------------------------------------------------------------------------
	int PositionManager::preparePositioner(string& _posFilePath, bool _isFixed){
		int errors = 0;
		errors += initTimer();
		posFile.open(_posFilePath);
		
		isFixed = _isFixed;

		if(!posFile.is_open() || errors < 0)
			return -1;
		
		return 0;
	}
	
	//------------------------------------------------------------------------
	int PositionManager::updatePosAndTime(){
		string line;
		int colCounter = 0;
		int init = 0;
		vector<string> splittedString;
		int counter = 0;

		getline(posFile, line);
		colCounter = line.size();

				

		for (int i = 0; i < colCounter; i++) {
			if (((int) line.at(i)) == 9) {
				splittedString.push_back(line.substr(init, i - init + 1));
				init = i + 1;
				counter++;
			}
		}
		

		// assigning values
		if(isFixed){
			timer->update();
			currentTime = timer->frameTime(); // 666 TODO: if fixed, only read one line, etc...
		}else
			currentTime = atof(splittedString.at(0).c_str());

		// Update Cameras
			double a = atof(splittedString.at(10).c_str()); // alpha, beta, gamma.
			double b = atof(splittedString.at(11).c_str());
			double c = atof(splittedString.at(12).c_str()); 

			cam1->setPosition((Mat_<double>(3, 1) << atof(splittedString.at(7).c_str()), atof(splittedString.at(8).c_str()), atof(splittedString.at(9).c_str())));

			cam1->setOrientation(obtainRotationMatrix(a, b, c));

			cam2->setPosition((Mat_<double>(3, 1) << atof(splittedString.at(13).c_str()), atof(splittedString.at(14).c_str()), atof(splittedString.at(15).c_str())));

			a = atof(splittedString.at(16).c_str()); // alpha, beta, gamma.
			b = atof(splittedString.at(17).c_str());
			c = atof(splittedString.at(18).c_str()); 

			cam2->setOrientation(obtainRotationMatrix(a, b, c));

			return 0;
	}

	//------------------------------------------------------------------------
	void PositionManager::getCameraAndTime(position::Camera& _cam1, position::Camera& _cam2, TReal& _time) const{
		_cam1.setPosition(cam1->getPosition());
		_cam1.setOrientation(cam1->getOrientation());
		_cam2.setPosition(cam2->getPosition());
		_cam2.setOrientation(cam2->getOrientation());
		
	}
} // namespace vision
