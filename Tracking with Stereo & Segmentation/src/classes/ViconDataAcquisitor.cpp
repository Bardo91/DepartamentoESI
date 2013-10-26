/*
 * ViconDataAcquisitor.cpp
 *
 *  Created on: Oct 26, 2013
 *      Author: pablo
 */

#include <ViconDataAcquisitor.h>

#include <string>
#include <opencv/cv.hpp>

using namespace std;
using namespace cv;
using namespace sysctrl::visionctrl;

namespace ccss {

void ViconDataAcquisitor::changePath(string dataPathName) {
	this->dataPathName = dataPathName;
}

void ViconDataAcquisitor::init() {
	viconFile.open(dataPathName.c_str());
}

int ViconDataAcquisitor::getNextViconData(camera& cam1, camera& cam2,
		int& incT) {
	// Readin vicon values
	String line;
	int colCounter = 0;
	int init = 0;
	vector<string> splittedString;
	int counter = 0;
	if (viconFile.is_open()) {
		getline(viconFile, line);
		colCounter = line.size();

		for (int i = 0; i < colCounter; i++) {
			if (((int) line.at(i)) == 9) {
				splittedString.push_back(line.substr(init, i - init + 1));
				init = i + 1;
				counter++;
			}
		}
	} else
		return -1; // File isn't opened.

	// assigning values
	incT = atof(splittedString.at(0).c_str());

	// Update Cameras
	double a = atof(splittedString.at(10).c_str()), b = atof(
			splittedString.at(11).c_str()), c = atof(
			splittedString.at(12).c_str()); // alpha, beta, gamma.

	cam1.pos[0] = atof(splittedString.at(7).c_str());
	cam1.pos[1] = atof(splittedString.at(8).c_str());
	cam1.pos[2] = atof(splittedString.at(9).c_str());

	Mat R1 =
			(Mat_<double>(3, 3) << cos(b) * cos(c), -cos(b) * sin(c), sin(b), cos(
					a) * sin(c) + cos(c) * sin(a) * sin(b), cos(a) * cos(c)
					- sin(a) * sin(b) * sin(c), -cos(b) * sin(a), sin(a)
					* sin(c) - cos(a) * cos(c) * sin(b), cos(c) * sin(a)
					+ cos(a) * sin(b) * sin(c), cos(a) * cos(b));
	R1 = R1.inv();

	cam1.ori = R1;

	cam2.pos[0] = atof(splittedString.at(13).c_str());
	cam2.pos[1] = atof(splittedString.at(14).c_str());
	cam2.pos[2] = atof(splittedString.at(15).c_str());

	a = atof(splittedString.at(16).c_str());
	b = atof(splittedString.at(17).c_str());
	c = atof(splittedString.at(18).c_str()); // alpha, beta, gamma.

	Mat R2 =
			(Mat_<double>(3, 3) << cos(b) * cos(c), -cos(b) * sin(c), sin(b), cos(
					a) * sin(c) + cos(c) * sin(a) * sin(b), cos(a) * cos(c)
					- sin(a) * sin(b) * sin(c), -cos(b) * sin(a), sin(a)
					* sin(c) - cos(a) * cos(c) * sin(b), cos(c) * sin(a)
					+ cos(a) * sin(b) * sin(c), cos(a) * cos(b));
	R2 = R2.inv();

	cam2.ori = R2;

	return 0;
}

} /* namespace ccss */
