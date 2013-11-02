/*
 * ViconDataAcquisitor.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: pablo
 */

#include "ViconDataAcquisitor.h"

using namespace std;
using namespace cv;

namespace sysctrl {

#define PI 3.14159265359

void obtainRotationMatrix(const double& a, const double& b, const double& c,
		Mat& R) {

	Mat Rx = (Mat_<double>(3, 3) << 1, 0, 0, 0, cos(a), -sin(a), 0, sin(a), cos(
			a));

	Mat Ry = (Mat_<double>(3, 3) << cos(b), 0, sin(b), 0, 1, 0, -sin(b), 0, cos(
			b));

	Mat Rz =
			(Mat_<double>(3, 3) << cos(c), -sin(c), 0, sin(c), cos(c), 0, 0, 0, 1);

	R = Rx * Ry * Rz;

}

void ViconDataAcquisitor::changePath(string dataPathName) {
	this->dataPathName = dataPathName;
	init();

}

void ViconDataAcquisitor::init() {
	viconFile.open(dataPathName.c_str());
}

int ViconDataAcquisitor::getNextViconData(camera& cam1, camera& cam2,
		double& incT) {
// Reading vicon values
	string line;
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

	cam1.pos = (Mat_<double>(3, 1) << atof(splittedString.at(7).c_str()), atof(
			splittedString.at(8).c_str()), atof(splittedString.at(9).c_str()));

	Mat RE1, RE2, TR;
	obtainRotationMatrix(-PI / 2, 0, PI / 2, TR);

	obtainRotationMatrix(a, b, c, RE1);

	cam1.ori = TR * RE1;

	cam2.pos =
			(Mat_<double>(3, 1) << atof(splittedString.at(13).c_str()), atof(
					splittedString.at(14).c_str()), atof(
					splittedString.at(15).c_str()));

	a = atof(splittedString.at(16).c_str());
	b = atof(splittedString.at(17).c_str());
	c = atof(splittedString.at(18).c_str()); // alpha, beta, gamma.

	obtainRotationMatrix(a, b, c, RE2);

	cam2.ori = TR * RE2;

	return 0;
}
} /* namespace sysctrl */
