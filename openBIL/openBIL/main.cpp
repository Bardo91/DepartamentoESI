///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include "ColorClustering.h"
#include "ColorSpaceHSV8.h"

int main(void){

	cv::Mat img;

	img = cv::imread("test.jpg", CV_LOAD_IMAGE_COLOR);

	cv::imshow("IMAGE", img);

	std::vector<BIL::algorithms::ImageObject> objects;

	vision::segmentation::ColorClusterSpace *cs = vision::segmentation::CreateHSVCS_8c(255U,255U,vision::segmentation::bin2dec("00010000"));

	BIL::algorithms::ColorClustering<uchar>(	img.data,		// Image pointer
												img.cols,		// Width
												img.rows,		// Height
												5,				// Size Threshold
												objects,		// Output Objects
												*cs);	// Segmentation function

	//BIL::algorithms::ColorClustering<unsigned char>(	img.data,		// Image pointer
	//													img.cols,		// Width
	//													img.rows,		// Height
	//													5,				// Size Threshold
	//													objects,		// Output Objects
	//													[](unsigned char *_a, unsigned char *_b, unsigned char *_c){	if(*_a < 80 && *_b < 80 && *_c > 200){
	//																														*_a = 0;
	//																														*_b = 0;
	//																														*_c = 255;
	//																														return 4;
	//																													} else{
	//																														*_a = 0;
	//																														*_b = 0;
	//																														*_c = 0;
	//																														return -1;
	//																													}
	//																													});	// Segmentation function

	cv::imshow("Segmentated", img);

	cv::waitKey();
	
	delete cs;


	return 0;

}