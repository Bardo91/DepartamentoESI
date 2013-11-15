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

	imagAc1 = ImageAcquisitor(pathName, imageNameFormat1, width, height);
	inputMethod = imagAc1.getInputMethod();

	vicon.changePath(dataPathName_);

	currentFrame = 0;

}

InputDataManager::InputDataManager(int dev1, int width, int height) {
	imagAc1 = ImageAcquisitor(dev1, width, height);
	inputMethod = imagAc1.getInputMethod();

	currentFrame = 0;

}

void InputDataManager::updateFrame() {
	imagAc1.updateFrame(currentFrame);
}

void InputDataManager::getFrame(Mat& frame1) {
	imagAc1.getFrame(frame1);
}

void InputDataManager::changeViconPath(string path) {
	vicon.changePath(path);
}

void InputDataManager::getNextCamPos(camera& cam1, double& incT) {
	if (inputMethod)
		vicon.getNextViconData(cam1, incT);
	else {
		cam1.pos = (Mat_<double>(3, 1) << 0, 0, 0);

		cam1.ori = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);

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

	imagAc1 = ImageAcquisitor(pathName, imageNameFormat1, width, height);
	inputMethod = imagAc1.getInputMethod();

	vicon.changePath(dataPathName_);

	currentFrame = 0;

}

void InputDataManager::changeMethod(int dev1, int width, int height) {
	imagAc1 = ImageAcquisitor(dev1, width, height);
	inputMethod = imagAc1.getInputMethod();

	currentFrame = 0;

}

} /* namespace sysctrl */
