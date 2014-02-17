///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include "ColorClustering.h"

int main(void){

	cv::Mat img;

	img = cv::imread("test.jpg", CV_LOAD_IMAGE_COLOR);

	cv::imshow("IMAGE", img);

	std::vector<BIL::algorithms::ImageObject> objects;

	std::function<int (uchar, uchar, uchar)> segFuntion = [](uchar _a, uchar _b, uchar _c){ return int(_a + _b + _c)/3;};

	BIL::algorithms::ColorClustering<uchar>(	img.data,		// Image pointer
												img.cols,		// Width
												img.rows,		// Height
												5,				// Size Threshold
												objects,		// Output Objects
												segFuntion);	// Segmentation function

	cv::imshow("Segmentated", img);

	cv::waitKey();
	
	return 0;

}