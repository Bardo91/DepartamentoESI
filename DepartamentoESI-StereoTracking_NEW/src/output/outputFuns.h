/*
 * outputFuns.h
 *
 *  Created on: Oct 29, 2013
 *      Author: pablo
 */

#ifndef OUTPUTFUNS_H_
#define OUTPUTFUNS_H_

#include <SegmentedObject.h>
#include <vector>
#include <opencv/cv.h>

namespace ccss {

void highlighObjs(std::vector<SegmentedObject>& objs, cv::Mat ori,
		unsigned int sizeThreshold);

}

#endif /* OUTPUTFUNS_H_ */
