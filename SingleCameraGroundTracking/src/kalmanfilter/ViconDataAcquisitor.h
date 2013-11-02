/*
 * ViconDataAcquisitor.h
 *
 *  Created on: Nov 2, 2013
 *      Author: pablo
 */

#ifndef VICONDATAACQUISITOR_H_
#define VICONDATAACQUISITOR_H_

#include <string>
#include <iostream>
#include <fstream>

#include <StereoVisionEKF.h>

namespace sysctrl {

class ViconDataAcquisitor {
	std::string dataPathName;
	std::ifstream viconFile;
public:

	void changePath(std::string);
	void init();
	int getNextViconData(sysctrl::camera&, sysctrl::camera&, double&);
};

} /* namespace sysctrl */

#endif /* VICONDATAACQUISITOR_H_ */
