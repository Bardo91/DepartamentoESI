////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ImageManager


#ifndef _VISUAL_TRACKING_UI_IMAGE_MANAGER_H_
#define _VISUAL_TRACKING_UI_IMAGE_MANAGER_H_


#include "ImageAcquisitor.h"

namespace vision{
	class ImageManager{
	public:
		ImageManager();
		~ImageManager();

	public:
		int setUpImageAcquisitor(const int _number, const  int _device, const int _width, const int _heigth);
		int setUpImageAcquisitor(const int _number, const std::string& _pathName, const std::string& _nameFormat, const int _width, const int _heigth);

		void setTwoCameras(const bool set);

		void updateFrames();
		void getFrames(cv::Mat& _frame1, cv::Mat& _frame2);

	private:
		ImageAcquisitor *imageAcquisitor1;
		ImageAcquisitor *imageAcquisitor2; //Not always used, depend on the algorithm.

		bool twoCameras;

	};

} // namespace vision.

#endif // _VISUAL_TRACKING_UI_IMAGE_MANAGER_H_
