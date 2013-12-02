////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ImageAcquisitor

#include "ImageAcquisitor.h"

using namespace std;
using namespace cv;

namespace vision {
//------------------------------------------------------------------------------
ImageAcquisitor::ImageAcquisitor() {
	width = height = inputMethod = -1;
	currentFrame = 0;
}

//------------------------------------------------------------------------------
ImageAcquisitor::ImageAcquisitor(string _pathName, std::string _imageNameFormat,
		int _width, int _height) {
	inputMethod = 1;
	pathName = _pathName;
	imageNameFormat = _imageNameFormat;
	width = _width;
	height = _height;
	currentFrame = 0;

}

//------------------------------------------------------------------------------
ImageAcquisitor::ImageAcquisitor(int _device, int _width, int _height) {
	inputMethod = 0;
	device = VideoCapture(_device);

	changeResolution(width, height);

	currentFrame = 0;

	assert(device.isOpened()); //Error, could not connect to the device
}

//------------------------------------------------------------------------------
ImageAcquisitor::~ImageAcquisitor() {
	device.release();
}

//------------------------------------------------------------------------------
void ImageAcquisitor::changeInputMethod(int _device) {
	inputMethod = 0;
	currentFrame = 0;
	if(device.isOpened()){
		device.release();
		waitKey(10); // Wait for the device to be stopped.
	}
	//device = VideoCapture(_device);
	assert(device.open(_device));
	assert(device.isOpened());  	//Error, could not connect to the device
}

//------------------------------------------------------------------------------
void ImageAcquisitor::changeInputMethod(string _pathName,
		string _imageNameFormat) {
	inputMethod = 1;
	currentFrame = 0;
	device.release();
	pathName = _pathName;
	imageNameFormat = _imageNameFormat;

}

//------------------------------------------------------------------------------
int ImageAcquisitor::changeResolution(int _width, int _height) {
	width = _width;
	height = _height;

	device.set(CV_CAP_PROP_FRAME_WIDTH, width);
	device.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	if (device.get(CV_CAP_PROP_FRAME_WIDTH) != width
			|| device.get(CV_CAP_PROP_FRAME_HEIGHT) != height)
		return -1; // Error changing properties

	return 0;
}

//------------------------------------------------------------------------------
void ImageAcquisitor::changePathName(std::string _pathName) {
	pathName = _pathName;
}

//------------------------------------------------------------------------------
void ImageAcquisitor::changeImageNameFormat(std::string _imageNameFormat) {
	imageNameFormat = _imageNameFormat;
}

//------------------------------------------------------------------------------
bool ImageAcquisitor::isOpened(){
	return device.isOpened();
}

//------------------------------------------------------------------------------
int ImageAcquisitor::closeDevice(){
	device.release();

	return 0;
}

//------------------------------------------------------------------------------
bool ImageAcquisitor::canCapture() {
	return device.isOpened();
}

//------------------------------------------------------------------------------
int ImageAcquisitor::updateFrame() {
	if (inputMethod) {
		const int sizeFormat = imageNameFormat.size() + 4;
		char *buffer;// +4 suposing that number of input images ar less than 99.999
		buffer = new char[sizeFormat];
		sprintf(buffer, imageNameFormat.c_str(), currentFrame);

		stringstream ss;
		ss << pathName << buffer;

		frame = cvLoadImage(ss.str().c_str(), 1);//imread(ss.str(), CV_LOAD_IMAGE_COLOR);

		assert(frame.cols != 0);

		if (frame.cols != height)
			resize(frame, frame, Size(width, height));

		currentFrame++;

		delete [] buffer;
	} else {
		assert(device.isOpened());
		device >> frame;
		assert(frame.cols != 0);
	}

	

	return frame.cols == 0 ? -1 : 0;
}

//------------------------------------------------------------------------------
int ImageAcquisitor::getFrame(Mat& _frame) {

	_frame = Mat(frame);
	return frame.cols == 0 ? -1 : 0;
}

int ImageAcquisitor::getInputMethod() const {
	return inputMethod;
}
//------------------------------------------------------------------------------
} // namespace vision
