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

#include "SegmentedObject.h"
#include <StereoVisionEKF.h>

namespace ccss {

typedef struct matchingLR {
	int iL, iR;
	cv::Point2d pixL, pixR;
	double energyFun;
	int color;
	bool updated;

	// default constructor;
	matchingLR() {
		iL = -1, iR = -1, energyFun = 9999999, color = -1, updated = false;
	}

	matchingLR(const int& iL_, const int& iR_, const cv::Point2d& pixL_,
			const cv::Point2d& pixR_, const double& energy_, const int& color_,
			const bool& updated_) {
		iL = iL_, iR = iR_, pixL = pixL_, pixR = pixR_, energyFun = energy_, color =
				color_, updated = updated_;

	}
} LR;

void objectMatching(const std::vector<SegmentedObject>&,
		const std::vector<SegmentedObject>&, LR *, const sysctrl::camera&,
		const sysctrl::camera&, const sysctrl::StereoVisionEKF *,
		const unsigned int&);

}
#endif /* FASTSTEREOMATCHING_H_ */
