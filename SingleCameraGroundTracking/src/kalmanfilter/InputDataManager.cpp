/*
 * InputDataManager.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: pablo
 */

#include <InputDataManager.h>

using namespace std;
using namespace sysctrl;
using namespace ccss;
using namespace cv;

namespace sysctrl {

InputDataManager::InputDataManager(string pathName, string imageNameFormat1,
		string imageNameFormat2, int width, int height, string dataPathName_) {

	imagAc1 = ImageAcquisitor(pathName, imageNameFormat1, width, height);
	imagAc2 = ImageAcquisitor(pathName, imageNameFormat2, width, height);
	inputMethod = imagAc1.getInputMethod();

	vicon.changePath(dataPathName_);

	currentFrame = 0;

}

InputDataManager::InputDataManager(int dev1, int dev2, int width, int height) {
	imagAc1 = ImageAcquisitor(dev1, width, height);
	imagAc2 = ImageAcquisitor(dev2, width, height);
	inputMethod = imagAc1.getInputMethod();

	currentFrame = 0;

}

void InputDataManager::updateFrame() {
	imagAc1.updateFrame(currentFrame);
	imagAc2.updateFrame(currentFrame);
}

void InputDataManager::getFrames(Mat& frame1, Mat& frame2) {
	imagAc1.getFrame(frame1);
	imagAc2.getFrame(frame2);
}

void InputDataManager::changeViconPath(string path) {
	vicon.changePath(path);
}

void InputDataManager::getNextCamPos(camera& cam1, camera& cam2, double& incT) {
	if (inputMethod)
		vicon.getNextViconData(cam1, cam2, incT);
	else {
		cam1.pos = (Mat_<double>(3, 1) << 0, 0, 0);
		cam2.pos = (Mat_<double>(3, 1) << 0, -0.16, 0);

		cam1.ori = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
		cam2.ori = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
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
		string imageNameFormat2, int width, int height, string dataPathName_) {

	imagAc1 = ImageAcquisitor(pathName, imageNameFormat1, width, height);
	imagAc2 = ImageAcquisitor(pathName, imageNameFormat2, width, height);
	inputMethod = imagAc1.getInputMethod();

	vicon.changePath(dataPathName_);

	currentFrame = 0;

}

void InputDataManager::changeMethod(int dev1, int dev2, int width, int height) {
	imagAc1 = ImageAcquisitor(dev1, width, height);
	imagAc2 = ImageAcquisitor(dev2, width, height);
	inputMethod = imagAc1.getInputMethod();

	currentFrame = 0;

}

} /* namespace sysctrl */
