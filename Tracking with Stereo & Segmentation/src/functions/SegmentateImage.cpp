/*
 * SegmentateImage.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

/*
 * ImageClusterSegmentation.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#include <opencv/cv.h>
#include <vector>

#include <ColorClusterSpace.h>
#include <SegmentedObject.h>

using namespace std;
using namespace ccss;
using namespace cv;

void segmentateImage(Mat frame1, Mat frame2, ColorClusterSpace CS,
		vector<SegmentedObject> *objs1, vector<vector<LineObjRLE> > *aRLE1,
		vector<SegmentedObject> *objs2, vector<vector<LineObjRLE> > *aRLE2) {

}
