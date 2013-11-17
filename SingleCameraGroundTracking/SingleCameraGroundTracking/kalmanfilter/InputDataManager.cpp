////////////////////////////////////////////////////////////////////////////////
//	Single Camera Ground Tracking - Extended Kalman Filter
//		Author: Pablo Ramón Soria
//		Date: 2013/11/02
////////////////////////////////////////////////////////////////////////////////
// Input data manager

#include <kalmanfilter/InputDataManager.h>

using namespace std;
using namespace sysctrl;
using namespace ccss;
using namespace cv;

namespace sysctrl {

InputDataManager::InputDataManager(string pathName, string imageNameFormat1,
		int width, int height, string dataPathName_) {

	imagAc = ImageAcquisitor(pathName, imageNameFormat1, width, height);
	inputMethod = imagAc.getInputMethod();

	vicon.changePath(dataPathName_);

	currentFrame = 0;

}

InputDataManager::InputDataManager(int dev1, int width, int height) {
	imagAc = ImageAcquisitor(dev1, width, height);
	inputMethod = imagAc.getInputMethod();

	currentFrame = 0;

}

void InputDataManager::updateFrame() {
	imagAc.updateFrame(currentFrame);
}

void InputDataManager::getFrame(Mat& frame1) {
	imagAc.getFrame(frame1);
}

void InputDataManager::changeViconPath(string path) {
	vicon.changePath(path);
}

void InputDataManager::getNextCamPos(camera& cam, double& incT) {
	if (inputMethod)
		vicon.getNextViconData(cam, incT);
	else {
		// 666 TODO: change for voluble pos and rot.
		cam.updatePos(0,0,0);
		cam.updateRot(0,20.f*3.141592/180.f,0);

		incT = -1;

	}
}

void InputDataManager::updateCurrentFrame() {
	currentFrame += 1;
}

int InputDataManager::getInputMethod() {
	return inputMethod;
}

void InputDataManager::changeMethod(string pathName, string imageNameFormat1,
		int width, int height, string dataPathName_) {

	imagAc = ImageAcquisitor(pathName, imageNameFormat1, width, height);
	inputMethod = imagAc.getInputMethod();

	vicon.changePath(dataPathName_);

	currentFrame = 0;

}

void InputDataManager::changeMethod(int dev1, int width, int height) {
	imagAc = ImageAcquisitor(dev1, width, height);
	inputMethod = imagAc.getInputMethod();

	currentFrame = 0;

}

} /* namespace sysctrl */
