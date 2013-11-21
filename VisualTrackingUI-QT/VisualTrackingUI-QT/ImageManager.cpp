////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ImageManager

#include "ImageManager.h"

#include <qmessagebox.h>
#include <cassert>
using namespace cv;

namespace vision{
//------------------------------------------------------------------------------
ImageManager::ImageManager(){
	imageAcquisitor1 = new ImageAcquisitor();
	imageAcquisitor2 = new ImageAcquisitor();
}

//------------------------------------------------------------------------------
ImageManager::~ImageManager(){
	// Deallocate ImageAcquisitors.
	if(imageAcquisitor1 != 0)
		delete imageAcquisitor1;
	if(imageAcquisitor2 !=0)
		delete imageAcquisitor2;
}

//------------------------------------------------------------------------------
int ImageManager::setUpImageAcquisitor(const int _number, const int _device, const  int _width, const  int _heigth){
	if(_number == 1){
		imageAcquisitor1->changeInputMethod(_device);
		imageAcquisitor1->changeResolution(_width, _heigth);
	}else if(_number  == 2){
		imageAcquisitor2->changeInputMethod(_device);
		imageAcquisitor2->changeResolution(_width, _heigth);
	}else{
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------
int ImageManager::setUpImageAcquisitor(const int _number, const std::string& _pathName, const std::string& _nameFormat, const int _width, const int _heigth){
	if(_number == 1){
		imageAcquisitor1->changeInputMethod(_pathName, _nameFormat);
		imageAcquisitor1->changeResolution(_width, _heigth);
		assert(imageAcquisitor1->isOpened());
	}else if(_number  == 2){
		imageAcquisitor2->changeInputMethod(_pathName, _nameFormat);
		imageAcquisitor2->changeResolution(_width, _heigth);
		assert(imageAcquisitor2->isOpened());
	}else{
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------
void ImageManager::setTwoCameras(const bool set){
	twoCameras = set;
}

//------------------------------------------------------------------------------
bool ImageManager::areTwoCameras(){
	return twoCameras;
}


//------------------------------------------------------------------------------
void ImageManager::updateFrames(){
	imageAcquisitor1->updateFrame();
	if(twoCameras)
		imageAcquisitor2->updateFrame();
}

//------------------------------------------------------------------------------
void ImageManager::getFrames(Mat& _frame1, Mat& _frame2){
	imageAcquisitor1->getFrame(_frame1);
	assert(_frame1.rows != 0); // Make sure that the frame is properly acquired, if not the error might be while updating the frame.

	if(twoCameras){
		imageAcquisitor2->getFrame(_frame2);
		assert(_frame2.rows != 0); // Make sure that the frame is properly acquired, if not the error might be while updating the frame.
	}
	
}

//------------------------------------------------------------------------------
int ImageManager::showCurrentFrames(){
	if(!imageAcquisitor1->canCapture())
		return -1; // Error: device 1 is not found.
	if(imageAcquisitor2 != 0 && !imageAcquisitor2->canCapture())
		return -2; // Error: device 2 is not found.

	Mat frame1, frame2;
	if(imageAcquisitor1->updateFrame() == -1)
		return -1;
	imageAcquisitor1->getFrame(frame1);
	if(twoCameras){
		if(imageAcquisitor2->updateFrame() == -1)
			return -2;
		imageAcquisitor2->getFrame(frame2);
		hconcat(frame1, frame2, frame1);
	}	
	
	imshow("Test Devices", frame1);

	return 0;
}

}
