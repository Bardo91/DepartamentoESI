////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Endless thread that run the specified algorithm

#include "ThreadAlgorithm.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <opencv/cv.h>


using namespace std;

namespace vision{
void threadAlgoritm(InfoPointers *infoPointers){
	cv::namedWindow("example", CV_WINDOW_AUTOSIZE);
	while(cv::waitKey(100) && infoPointers->looping){
		cv::Mat aux = cv::Mat::eye(100,100, CV_64F);
		cv::imshow("example", aux);
	}
}

} // namespace vision