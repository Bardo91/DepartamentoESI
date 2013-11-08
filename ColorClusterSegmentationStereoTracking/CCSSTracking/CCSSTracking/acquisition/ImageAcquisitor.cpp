/*
 * ImageAcquisitor.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: pablo
 */

#include "ImageAcquisitor.h"

using namespace std;
using namespace cv;

namespace ccss {

ImageAcquisitor::ImageAcquisitor() {
	width = height = inputMethod = -1;
	flagInputError = false;
}

ImageAcquisitor::ImageAcquisitor(string pathName, std::string imageNameFormat,
		int width, int height) {
	inputMethod = 1;
	this->pathName = pathName;
	this->imageNameFormat = imageNameFormat;
	this->width = width;
	this->height = height;

	flagInputError = false;
}

ImageAcquisitor::ImageAcquisitor(int device, int width, int height) {
	inputMethod = 0;
	this->device = VideoCapture(device);
	this->width = width;
	this->height = height;

	flagInputError = false;

	changeResolution(width, height);

	try {
		this->device.open(1);
	} catch (Exception e) { //Catching errors.
		cout << "Error, could not connect to the device" << endl;
		flagInputError = true;
	}
	if (!this->device.isOpened()) { // If camera can not be openned.
		cout << "Error, could not connect to the device" << endl;
		this->device.release();
		flagInputError = true;
	}
}

ImageAcquisitor::~ImageAcquisitor() {
	device.release();
}

void ImageAcquisitor::changeInputMethod(int device) {
	inputMethod = 0;
	if (this->device.isOpened())
		this->device.release();

	this->device = VideoCapture(device);
	this->device.open(1);

}

void ImageAcquisitor::changeInputMethod(string pathName,
		string imageNameFormat) {
	inputMethod = 1;
	device.release();
	this->pathName = pathName;
	this->imageNameFormat = imageNameFormat;

}

int ImageAcquisitor::changeResolution(int width, int height) {
	if (inputMethod) {
		this->width = width;
		this->height = height;
		return 0;
	}

	device.set(CV_CAP_PROP_FRAME_WIDTH, width);
	device.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	if (device.get(CV_CAP_PROP_FRAME_WIDTH) != width
			|| device.get(CV_CAP_PROP_FRAME_HEIGHT) != height)
		return -1; // Error changing properties

	return 0;
}

void ImageAcquisitor::changePathName(std::string pathName) {
	this->pathName = pathName;
}

void ImageAcquisitor::changeImageNameFormat(std::string imageNameFormat) {
	this->imageNameFormat = imageNameFormat;
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
