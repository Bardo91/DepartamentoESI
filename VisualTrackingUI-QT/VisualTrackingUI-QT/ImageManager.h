////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ImageManager


#ifndef _VISUAL_TRACKING_UI_IMAGE_MANAGER_H_
#define _VISUAL_TRACKING_UI_IMAGE_MANAGER_H_


#include "ComputerVisionLibraries/DataAcquisition/ImageAcquisitor.h"


namespace vision{
	class ImageManager{
	public:
		ImageManager();
		~ImageManager();

	public:
		int setUpImageAcquisitor(const int _number, const  int _device, const int _width, const int _heigth);
		int setUpImageAcquisitor(const int _number, const std::string& _pathName, const std::string& _nameFormat, const int _width, const int _heigth);

		void setTwoCameras(const bool set);
		bool areTwoCameras();

		void updateFrames();
		void getFrames(cv::Mat& _frame1, cv::Mat& _frame2);
		int showCurrentFrames();

	private:
		ImageAcquisitor *imageAcquisitor1;
		ImageAcquisitor *imageAcquisitor2; //Not always used, depend on the algorithm.

		bool twoCameras;

	};

} // namespace vision.

#endif // _VISUAL_TRACKING_UI_IMAGE_MANAGER_H_
