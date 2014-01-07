#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>


using namespace std;
using namespace cv;


int main(void){
	/*//-----------------------------------------------------------------------
	// Load image for Non Gpu process
	Mat imageNonGpu = imread("C:/Hydrangeas.jpg"), dstNonGpu;

	// Test non-gpu processing.
	Canny(imageNonGpu, dstNonGpu, 0.4,0.6);

	imshow("Non GPU", dstNonGpu);
	waitKey();
	
	//-----------------------------------------------------------------------
	// Load image for Gpu process
	waitKey();

	gpu::GpuMat imageGPU(imageNonGpu), dstGpu;

	// Test gpu processing.
	gpu::Canny(imageGPU, dstGpu, 0.4,0.6);
	
	Mat dst(dstGpu);
	imshow("GPU", dst);
	waitKey();*/
	
}