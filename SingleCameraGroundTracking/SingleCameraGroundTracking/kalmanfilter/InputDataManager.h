/*
 * InputDataManager.h
 *
 *  Created on: Nov 2, 2013
 *      Author: pablo
 */

#ifndef INPUTDATAMANAGER_H_
#define INPUTDATAMANAGER_H_

#include <acquisition/ImageAcquisitor.h>
#include <kalmanfilter/ViconDataAcquisitor.h>

namespace sysctrl {

class InputDataManager {
	ccss::ImageAcquisitor imagAc;

	sysctrl::ViconDataAcquisitor vicon;

	int inputMethod;

	int currentFrame;

public:
	InputDataManager(std::string, std::string, int, int, std::string);
	InputDataManager(int, int, int);

	void updateFrame();

	void getFrame(cv::Mat&);

	void changeViconPath(std::string);
	void getNextCamPos(sysctrl::camera&, double&);

	void updateCurrentFrame();

	int getInputMethod();

	void changeMethod(std::string, std::string, int, int, std::string);

	void changeMethod(int, int, int);
};

} /* namespace sysctrl */

#endif /* INPUTDATAMANAGER_H_ */
