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
		vicon = new iofunctions::Vicon();
	}

	//------------------------------------------------------------------------
	PositionManager::~PositionManager(){
		vicon->disconnect();
		delete cam1, cam2, vicon;
		posFile.close();
		STime::end();
	}

	//------------------------------------------------------------------------
	int PositionManager::configureCams(string& _filePath){
		int errors = 0;
		errors += cam1->loadPropertiesFromFile(_filePath);
		errors += cam2->loadPropertiesFromFile(_filePath);
		if(errors < 0)
			return -1;

		return 0;
	}

	//------------------------------------------------------------------------
	int PositionManager::initTimer(){
		if(!STime::isInitialized())
			STime::init();
		timer = STime::get();
		refTime = timer->frameTime();

		return timer == nullptr ? -1 : 0;
	}

	//------------------------------------------------------------------------
	int PositionManager::preparePositioner(string& _posFilePath, bool _isFixed){
		posMethod = 0;
		int errors = 0;
		errors += initTimer();
		posFile.open(_posFilePath); // Is only open 1st time.
		
		isFixed = _isFixed;
		isFirstPos = true;
		if(!posFile.is_open() || !posFile.good() || errors < 0)
			return -1;
		
		return 0;
	}
	//------------------------------------------------------------------------
	int PositionManager::preparePositionerFromVicon(int _idObj1, int _idObj2){
		posMethod = 1;

		vicon->connect();
		idObj1 = _idObj1;
		idObj2 = _idObj2;

		return 0;
	}

	//------------------------------------------------------------------------
	void PositionManager::closeStream(){
		if(posMethod){
			// 666 TODO: close vicon streaming
		}else{
			if(posFile != 0)
				posFile.close();
		}
	}
	//------------------------------------------------------------------------
	void PositionManager::getNextLine(vector<string>& _splittedString){
		string line;
		int colCounter = 0;
		int init = 0;
		int counter = 0;

		getline(posFile, line);
		colCounter = line.size();

		assert(colCounter > 0);
				

		for (int i = 0; i < colCounter; i++) {
			if (((int) line.at(i)) == 9) {
				_splittedString.push_back(line.substr(init, i - init + 1));
				init = i + 1;
				counter++;
			}
		}
	}
	//------------------------------------------------------------------------
	void PositionManager::updatePos(const vector<string>& _splittedString){
		double a = atof(_splittedString.at(10).c_str()); // alpha, beta, gamma.
		double b = atof(_splittedString.at(11).c_str());
		double c = atof(_splittedString.at(12).c_str()); 

		cam1->setPosition((Mat_<double>(3, 1) << atof(_splittedString.at(7).c_str()), atof(_splittedString.at(8).c_str()), atof(_splittedString.at(9).c_str())));

		cam1->setOrientation(obtainRotationMatrix(a, b, c));

		cam2->setPosition((Mat_<double>(3, 1) << atof(_splittedString.at(13).c_str()), atof(_splittedString.at(14).c_str()), atof(_splittedString.at(15).c_str())));

		a = atof(_splittedString.at(16).c_str()); // alpha, beta, gamma.
		b = atof(_splittedString.at(17).c_str());
		c = atof(_splittedString.at(18).c_str()); 

		cam2->setOrientation(obtainRotationMatrix(a, b, c));
	}

	//------------------------------------------------------------------------
	void PositionManager::updateTime(const vector<string>& _splittedString){
		currentTime = atof(_splittedString.at(0).c_str());
	}
	//------------------------------------------------------------------------
	void PositionManager::updateTime(){
		currentTime = timer->frameTime();

	}

	//------------------------------------------------------------------------
	int PositionManager::updatePosAndTime(){
		// 666 TODO: Cambiar, no es elegante...
		if(posMethod == 1){
			Mat p1,p2,o1,o2;
			// First get info from vicon stream and then save information in order to synchronize as fast as possible.
			currentTime = vicon->getTime();
			vicon->getPosition(idObj1, p1);
			vicon->getPosition(idObj2, p2);
			vicon->getOrientation(idObj1, o1);
			vicon->getOrientation(idObj2, o2);
			
			cam1->setPosition(p1);			
			cam2->setPosition(p2);			
			cam1->setOrientation(o1);			
			cam2->setOrientation(o2);
			
		}else{
			vector<string> splittedString;
		
			if(isFirstPos){ 
				getNextLine(splittedString);
			}

			if(isFixed){
				updateTime();
				if(isFirstPos){
					updatePos(splittedString);
					isFirstPos = false;
				}
			} else{
				updateTime(splittedString);
				updatePos(splittedString);
			}
		}
		return 0;
	}

	//------------------------------------------------------------------------
	void PositionManager::getCameraPosAndTime(position::Camera& _cam1, position::Camera& _cam2, double& _time) const{
		_cam1.setPosition(cam1->getPosition());
		_cam1.setOrientation(cam1->getOrientation());
		_cam2.setPosition(cam2->getPosition());
		_cam2.setOrientation(cam2->getOrientation());
		_time = currentTime;
	}

	//------------------------------------------------------------------------
	Camera PositionManager::getCamera(int _cam){
		if(_cam == 1)
			return *cam1;
		else if(_cam == 2)
			return *cam2;
		return *cam1;
	}

	//------------------------------------------------------------------------

} // namespace vision
