////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Endless thread that run the specified algorithm

#include "ThreadAlgorithm.h"
#include "ImageManager.h"
#include "SegmentationManager.h"s

#include <iostream>
#include <opencv/cv.h>


using namespace std;
using namespace vision;
using namespace cv;

namespace vision{
void threadAlgoritm(InfoPointers *infoPointers){
	const String wTitle = "example";
	cv::namedWindow(wTitle, CV_WINDOW_FREERATIO);
	ImageManager *imageManager = infoPointers->imageManager;
	SegmentationManager *segmentationManager = infoPointers->segmentationManager;

	Mat frame1, frame2;

	vector<SimpleObject> objects1;
	vector<SimpleObject> objects2;

	while(cv::waitKey(1) && infoPointers->looping){
		imageManager->updateFrames();
		imageManager->getFrames(frame1, frame2);
		if(imageManager->areTwoCameras())
			hconcat(frame1, frame2, frame1);
		
		// 666 TODO: implement threshold UI and etc...
		segmentationManager->applyAlgorithm(frame1, frame2, 500, objects1, objects2);

		imshow(wTitle, frame1);
	}
}

} // namespace vision