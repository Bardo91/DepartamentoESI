/*
 * ViconDataAcquisitor.h
 *
 *  Created on: Oct 26, 2013
 *      Author: pablo
 */

#ifndef VICONDATAACQUISITOR_H_
#define VICONDATAACQUISITOR_H_

#include <string>
#include <iostream>
#include <fstream>

#include <StereoVisionEKF.h>
#include <opencv/cv.h>

namespace ccss {

class ViconDataAcquisitor {
	std::string dataPathName;
	std::ifstream viconFile;
public:

	void changePath(std::string);
	void init();
	int getNextViconData(sysctrl::visionctrl::camera& cam1,
			sysctrl::visionctrl::camera& cam2, int& incT);
};

} /* namespace ccss*/

#endif /* VICONDATAACQUISITOR_H_ */
