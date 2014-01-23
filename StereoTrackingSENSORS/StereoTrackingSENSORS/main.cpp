////////////////////////////////////////////////////////////////////////////////
//	Stereo Tracking for Sensors Journal
//		Author: Pablo Ramón Soria
//		Date: 2014/01/21
////////////////////////////////////////////////////////////////////////////////
//	Main function to be executed

#include "LibsUS/ParamsEKF.h"
#include "LibsUS/PositionManager.h"
#include "LibsUS/ComputerVisionLibraries/DataAcquisition/ImageAcquisitor.h"
#include "LibsUS/ComputerVisionLibraries/ImageSegmentation/ColocClusterImageSegmentation.h"
#include "LibsUS/ComputerVisionLibraries/ImageSegmentation/ColorSpaceHSV8.h"
#include "LibsUS/ComputerVisionLibraries/ImageSegmentation/SegmentedObject.h"
#include "LibsUS/ComputerVisionLibraries/Timing/time.h"
#include "LibsUS/ComputerVisionLibraries/TrackingAlgorithm/RobustStereoMatching.h"
#include "LibsUS/ComputerVisionLibraries/TrackingAlgorithm/StereoVisionEKF.h"
#include "LibsUS/SimpleObject.h"

#include <cstdint>
#include <opencv/cv.h>
#include <string>

using namespace cv;
using namespace std;
using namespace vision;
using namespace vision::position;
using namespace vision::segmentation;
using namespace vision::tracking;

//---------------------------------------------------------------------------------------
struct MainArgs{
	uint16_t width;
	uint16_t height;
	uint16_t sizeThreshold;
	string imgPath;
	string imgName1;
	string imgName2;
	string viconFile;
	string camInfo;

}; 

//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	// 666 TODO: decode input arguments
	MainArgs mainArgs;
	mainArgs.width = 640;
	mainArgs.height = 480;
	mainArgs.imgPath = "C:/Programming/Imagenes Stereo Tracking/P1_640x480/Images/";
	mainArgs.imgName1 = "img%d_cam1.jpg";
	mainArgs.imgName2 = "img%d_cam2.jpg";
	mainArgs.viconFile = "C:/Programming/Imagenes Stereo Tracking/P1_640x480/ViconData2.txt";
	mainArgs.camInfo = "C:/Programming/Imagenes Stereo Tracking/P1_640x480/cameraInfo640480.txt";
	mainArgs.sizeThreshold = 50;


	#ifdef _DEBUG						// Displays are only used on debug mode, in order to accelerate the process on Release.
		// Window display configuration.
		string	wndNameOri = "No processed image",
				wndNameMod = "Segmentated image";

		namedWindow(wndNameOri, CV_WINDOW_NORMAL);
		namedWindow(wndNameMod, CV_WINDOW_NORMAL);
	#endif

	ImageAcquisitor imgAc1, imgAc2;		// This class manage the source of each frame of the secuence.
 
	imgAc1.changeInputMethod(mainArgs.imgPath, mainArgs.imgName1);
	imgAc2.changeInputMethod(mainArgs.imgPath, mainArgs.imgName2);

	imgAc1.changeResolution(mainArgs.width, mainArgs.height);
	imgAc2.changeResolution(mainArgs.width, mainArgs.height);


	Mat frame1, frame2;
	#ifdef _DEBUG
		Mat ori1, ori2;					// Matrixes to store the original image. Only for debugging purpose.
	#endif

	// Class that manage the colors
	segmentation::ColorClusterSpace* CS = segmentation::CreateHSVCS_8c(	segmentation::bin2dec("00010000"),		// Hue Mask
																		segmentation::bin2dec("11111111"),		// Saturation Mask
																		segmentation::bin2dec("11111111"));		// Value Mask

	// Allocate memory for vector of objects. 666 TODO: this is one of the uneficientest part..
	vector<SimpleObject> objs1, objs2;
	objs1.reserve(50000);	// 666 TODO:	se puede solucionar el fallo que da si no esta esto cambiando el código de la segmentacion
	objs2.reserve(50000);	//				usando iteradores en vez de punteros.

	// Matching class
	RobustStereoMatching matching1, matching2;
	matching1.init(1);		// Speed is setted unitary.
	matching2.init(1);

	// Create camera's abstraction
	PositionManager posManager;
	posManager.configureCams(mainArgs.camInfo);
	posManager.preparePositioner(mainArgs.viconFile, FALSE);

	// Instances of the cameras
	Camera cam1, cam2;

	// Extended Kalman Filter adapted to stereo vision.
	StereoVisionEKF ekf(matQ, matR, x0, cam1, cam2);

	STime::init();						// Initialize the global timer.
	STime *gTimer = STime::get();		// This function get a singleton of the static class STime. It will provide the global time to the process.

	double t1, t2;			// Variables used to compute time lapses.
	double ekfT, ekfLastT = 0;	// Variables used to calculate ekf increment of time.

	t2 = gTimer->frameTime();
	
	// Main loop. waitKey is necessary to allow the system to display images, if not necessary it can be replaced by another condition
	while(waitKey(1)){
		t1 = gTimer->frameTime();		// Get start time*/

		imgAc1.updateFrame();
		imgAc2.updateFrame();
		imgAc1.getFrame(frame1);
		imgAc2.getFrame(frame2);

		#ifdef _DEBUG
			frame1.copyTo(ori1);
			frame2.copyTo(ori2);
		#endif

		// Segmentate images
		ColorClusterImageSegmentation(frame1, frame2, *CS, mainArgs.sizeThreshold, objs1, objs2);

		// Find the current object from the whole detected objects.
		matching1.updateObjects(objs1);
		matching2.updateObjects(objs2);
		if(matching1.isUpdated(4) && matching2.isUpdated(4)){
			// Update Cameras.
			posManager.updatePosAndTime();
			posManager.getCameraPosAndTime(cam1, cam2, ekfT);

			// Update EKF		666 TODO: get cameras position and orientation, and get time from file
			ekf.updateCameraPos(cam1.getPosition(), cam2.getPosition(), cam1.getOrientation(), cam2.getOrientation());
			ekf.updateIncT(ekfT - ekfLastT);
			ekfLastT = ekfT;

			SimpleObject match1 = matching1.getObject(4);
			SimpleObject match2 = matching2.getObject(4);

			Mat zk = (Mat_<double>(4,1) << match1.centroid.x, match1.centroid.y, match2.centroid.x, match2.centroid.y);

			ekf.stepEKF(zk);

			#ifdef _DEBUG
				circle(ori1,match1.centroid, 30, Scalar(0, 255, 0), 2);
				circle(ori2,match2.centroid, 30, Scalar(0, 255, 0), 2);
			#endif
		}

		t2 = gTimer->frameTime();	// Get final time
		double diff = t2 - t1;
		#ifdef _DEBUG
			cout << "The process takes: " << diff << "ms" << endl;
			Mat x;
			ekf.getStateVector(x);
			cout << "Current state: " << x << endl;
		#endif

		#ifdef _DEBUG
			
			vconcat(frame1,frame2,frame1);
			vconcat(ori1,ori2,ori1);
			imshow(wndNameMod,frame1);
			imshow(wndNameOri,ori1);
		#endif

		objs1.clear();
		objs2.clear();
	}

	posManager.closeStream();		// Close txt file.
	
}

//---------------------------------------------------------------------------------------
