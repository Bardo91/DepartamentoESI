/*
 * InputDataManager.h
 *
 *  Created on: Nov 2, 2013
 *      Author: pablo
 */

#ifndef INPUTDATAMANAGER_H_
#define INPUTDATAMANAGER_H_

#include <ImageAcquisitor.h>
#include <ViconDataAcquisitor.h>

namespace sysctrl {

class InputDataManager {
	ccss::ImageAcquisitor imagAc1;
	ccss::ImageAcquisitor imagAc2;

	sysctrl::ViconDataAcquisitor vicon;

	int inputMethod;

	int currentFrame;

public:
	InputDataManager(std::string, std::string, std::string, int, int,
			std::string);
	InputDataManager(int, int, int, int);

	void updateFrame();

	void getFrames(cv::Mat&, cv::Mat&);

	void changeViconPath(std::string);
	void getNextCamPos(sysctrl::camera&, sysctrl::camera&, double&);

	void updateCurrentFrame();

	int getInputMethod();

	void changeMethod(std::string, std::string, std::string, int, int,
			std::string);

	void changeMethod(int, int, int, int);
};

} /* namespace sysctrl */

#endif /* INPUTDATAMANAGER_H_ */
