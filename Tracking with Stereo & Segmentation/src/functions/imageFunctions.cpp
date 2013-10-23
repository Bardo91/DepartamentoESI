/*
 * imageFunctions.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: Pablo Ramón Soria
 *
 *		This algorithm is an implementation of James Bruce's, Tucker Balch's &
 *      Manuela Veloso's "Fast an inexpensive" algorithm for color image segmentation.
 *
 *      Report: http://www.cs.cmu.edu/~mmv/papers/00iros-cmvision.pdf
 *
 */

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <iostream>
#include <fstream>

#include <vector>

#include "ColorClusterSpace.h"
#include "SegmentedObject.h"

using namespace ccss;
using std::vector;

int imageClusterSegmentation(cv::Mat frame1, cv::Mat frame2,
		const ColorClusterSpace& cs, vector<SegmentedObject> *objs1,
		vector<vector<> > *aRLE1,
		vector<SegmentedObject> *objs2,
		vector<vector<> > *aRLE2) {


	return 0;
}

