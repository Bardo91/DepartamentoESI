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

ImageAcquisitor::ImageAcquisitor() {
	width = height = inputMethod = -1;
	flagInputError = false;
}

ImageAcquisitor::ImageAcquisitor(string _pathName, std::string _imageNameFormat,
		int _width, int _height) {
	inputMethod = 1;
	pathName = _pathName;
	imageNameFormat = _imageNameFormat;
	width = _width;
	height = _height;

	flagInputError = false;
}

ImageAcquisitor::ImageAcquisitor(int _device, int _width, int _height) {
	inputMethod = 0;
	device = VideoCapture(_device);
	width = _width;
	height = _height;

	flagInputError = false;

	changeResolution(width, height);

	try {
		device.open(1);
	} catch (Exception e) { //Catching errors.
		cout << "Error, could not connect to the device" << endl;
		flagInputError = true;
	}
	if (!device.isOpened()) { // If camera can not be openned.
		cout << "Error, could not connect to the device" << endl;
		device.release();
		flagInputError = true;
	}
}

ImageAcquisitor::~ImageAcquisitor() {
	device.release();
}

void ImageAcquisitor::changeInputMethod(int _device) {
	inputMethod = 0;
	closeDevice();

	device = VideoCapture(device);
	device.open(1);

}

void ImageAcquisitor::changeInputMethod(string _pathName,
		string _imageNameFormat) {
	inputMethod = 1;
	device.release();
	pathName = _pathName;
	imageNameFormat = _imageNameFormat;

}

int ImageAcquisitor::changeResolution(int _width, int _height) {
	if (inputMethod) {
		width = _width;
		height = _height;
		return 0;
	}

	device.set(CV_CAP_PROP_FRAME_WIDTH, width);
	device.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	if (device.get(CV_CAP_PROP_FRAME_WIDTH) != width
			|| device.get(CV_CAP_PROP_FRAME_HEIGHT) != height)
		return -1; // Error changing properties

	return 0;
}

void ImageAcquisitor::changePathName(std::string _pathName) {
	pathName = _pathName;
}

void ImageAcquisitor::changeImageNameFormat(std::string _imageNameFormat) {
	imageNameFormat = _imageNameFormat;
}

void ImageAcquisitor::closeDevice(){
	if(!inputMethod)
		if (device.isOpened())
			device.release();
}

bool ImageAcquisitor::canCapture() {
	return !flagInputError;
}

int ImageAcquisitor::updateFrame(int currentImage) {
	if (inputMethod) {
		const int sizeFormat = imageNameFormat.size() + 4;
		char *buffer;// +4 suposing that number of input images ar less than 99.999
		buffer = (char*) new char(sizeof(char)*sizeFormat);
		sprintf(buffer, imageNameFormat.c_str(), currentImage);

		stringstream ss;
		ss << pathName << buffer;

		delete buffer;

		frame = imread(ss.str(), CV_LOAD_IMAGE_COLOR);

		if (frame.cols != height && frame.cols != 0)
			resize(frame, frame, Size(width, height));

	} else {
		device >> frame;
	}

	return frame.cols == 0 ? -1 : 0;
}

int ImageAcquisitor::getFrame(Mat& frame) {

	frame = Mat(this->frame);

	return frame.cols == 0 ? -1 : 0;
}

int ImageAcquisitor::getInputMethod() const {
	return inputMethod;
}
}
