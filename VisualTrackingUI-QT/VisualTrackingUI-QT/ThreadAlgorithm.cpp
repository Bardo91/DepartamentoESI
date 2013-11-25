////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Endless thread that run the specified algorithm

#include "ThreadAlgorithm.h"
#include "ImageManager.h"
#include "SegmentationManager.h"
#include "ComputerVisionLibraries/Timing/time.h"
#include "ComputerVisionLibraries/Positioning/Camera.h"

#include <iostream>
#include <opencv/cv.h>


using namespace std;
using namespace vision;
using namespace cv;

namespace vision{
void threadAlgoritm(InfoPointers *infoPointers){
	//------------------------------------//
	const String wTitle = "example";
	cv::namedWindow(wTitle, CV_WINDOW_FREERATIO);
	ImageManager *imageManager = infoPointers->imageManager;
	SegmentationManager *segmentationManager = infoPointers->segmentationManager;
	PositionManager *positionManager = infoPointers->positionManager;

	int threshold = infoPointers->threshold;

	Mat frame1, frame2, ori1, ori2;

	vector<SimpleObject> objects1;
	vector<SimpleObject> objects2;
	//------------------------------------//
	position::Camera cam1, cam2;
	TReal currentTime;

	//------------------------------------//
	// Prepare Timer.
	//STime::init(); <-- Is initialized at the PositionerManager

	STime *gTimer = STime::get();

	// Ref temp.
	TReal refTime0;
	TReal t1, t2;

	// Update timer.
	gTimer->update();

	// Get time for reference
	refTime0 = gTimer->frameTime();
	//------------------------------------//
	while(cv::waitKey(1) && infoPointers->looping){
		/*gTimer->update();
		t1 = gTimer->frameTime();*/
		imageManager->updateFrames();
		imageManager->getFrames(frame1, frame2);		

		frame1.copyTo(ori1);
		frame2.copyTo(ori2);

		medianBlur(frame1, frame1, 5);
		medianBlur(frame1, frame1, 5);
		if(imageManager->areTwoCameras()){
			medianBlur(frame2, frame2, 5);
			medianBlur(frame2, frame2, 5);
		}

		segmentationManager->applyAlgorithm(frame1, frame2, threshold, objects1, objects2);

		positionManager->updatePosAndTime();
		
		positionManager->getCameraAndTime(cam1,cam2, currentTime);

		cout << "Camera1: " << cam1.getPosition() << endl;
		cout << "Camera2: " << cam2.getPosition() << endl;
		cout << "CurrentTime" << currentTime << endl;


		if(imageManager->areTwoCameras()){
			hconcat(frame1, frame2, frame1);
			hconcat(ori1, ori2, ori1);
		}

		vconcat(ori1, frame1, frame1);

		imshow(wTitle, frame1);
		/*gTimer->update();
		t2 = gTimer->frameTime();
		double diff = t2-t1;
		cout << "FINISHED IN " << diff << endl;*/

	}
	//------------------------------------//
	//------------------------------------//
}

} // namespace vision