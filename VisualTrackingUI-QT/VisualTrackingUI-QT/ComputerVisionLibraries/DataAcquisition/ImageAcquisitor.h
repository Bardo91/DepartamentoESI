////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ImageAcquisitor

#ifndef _VISUAL_TRACKING_UI_IMAGEACQUISITOR_H_
#define _VISUAL_TRACKING_UI_IMAGEACQUISITOR_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace vision {

class ImageAcquisitor {
	cv::VideoCapture device;
	std::string pathName;
	std::string imageNameFormat; // Example:  "image%d_cam1.jpg"

	int width, height;

	int inputMethod; // 0 = from device ; 1 = from path

	int currentFrame;

	cv::Mat frame;
public:

	ImageAcquisitor();
	ImageAcquisitor(std::string, std::string, int, int); // Get image from path.
	ImageAcquisitor(int, int, int); // Get image from Device

	~ImageAcquisitor();

public:
	void changeInputMethod(int _device);
	void changeInputMethod(std::string, std::string);
	int changeResolution(int, int);
	void changePathName(std::string);
	void changeImageNameFormat(std::string);

	bool isOpened();
	int closeDevice();
public:
	bool canCapture();

	int updateFrame();
	int getFrame(cv::Mat&);
	int getInputMethod() const;

};

} // namespace vision

#endif // _VISUAL_TRACKING_UI_IMAGEACQUISITOR_H_
