/*
 * ImageAcquisitor.h
 *
 *  Created on: Oct 31, 2013
 *      Author: pablo
 */

#ifndef IMAGEACQUISITOR_H_
#define IMAGEACQUISITOR_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace ccss {

class ImageAcquisitor {
	cv::VideoCapture device;
	std::string pathName;
	std::string imageNameFormat; // Example:  "image%d_cam1.jpg"

	int width, height;

	int inputMethod; // 0 = from device ; 1 = from path

	bool flagInputError;

	cv::Mat frame;
public:

	ImageAcquisitor(std::string, std::string, int, int); // Get image from path.
	ImageAcquisitor(int, int, int); // Get image from Device

	~ImageAcquisitor();

	void changeInputMethod(int currentFrame = 0);
	void changeInputMethod(std::string, std::string);
	int changeResolution(int, int);
	void changePathName(std::string);
	void changeImageNameFormat(std::string);

	bool canCapture();

	int updateFrame(int currentImage=0);
	int getFrame(cv::Mat&);
	int getInputMethod() const;

};

} /* namespace std */

#endif /* IMAGEACQUISITOR_H_ */
