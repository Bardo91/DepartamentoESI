/*
 * FastStereoMatching.h
 *
 *  Created on: Oct 28, 2013
 *      Author: pablo
 */

#ifndef FASTSTEREOMATCHING_H_
#define FASTSTEREOMATCHING_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <SegmentedObject.h>
#include <StereoVisionEKF.h>

namespace ccss {

typedef struct matchingLR {
	int iL, iR;
	cv::Point2d pixL, pixR;
	double energyFun;
	int color;
	bool updated;
} LR;

void objectMatching(const std::vector<SegmentedObject>& objsL,
		const std::vector<SegmentedObject>& objsR, LR * matching,
		const sysctrl::visionctrl::camera& cam1,
		const sysctrl::visionctrl::camera& cam2,
		const sysctrl::StereoVisionEKF EKFs[8], const unsigned int& threshold);

}
#endif /* FASTSTEREOMATCHING_H_ */
