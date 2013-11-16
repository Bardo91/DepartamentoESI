////////////////////////////////////////////////////////////////////////////////
//	Single Camera Ground Tracking - Extended Kalman Filter
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// main

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "acquisition/ImageAcquisitor.h"
#include "colorclustersegmentation/ColorClusterSpace.h"
#include "colorclustersegmentation/ColorSpaceHSV8.h"
#include "colorclustersegmentation/SegmentateImage.h"
#include "colorclustersegmentation/SegmentedObject.h"
#include "colorclustersegmentation/ObjectMatching.h"
#include "timefuns/time.h"
#include "output/outputFuns.h"
#include "kalmanfilter/GroundTrackingEKF.h"
#include "kalmanfilter/CameraDataEKF.h"
#include "kalmanfilter/ViconDataAcquisitor.h"

#include "kalmanfilter/InputDataManager.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace ccss;
using namespace std;
using namespace sysctrl;

bool exitFlag = true;
int switchButtonValue = 0;
bool changeMethodDone = true;

static void onMouse(int event, int x, int y, int, void*) {
	if (event == EVENT_LBUTTONDOWN)
		exitFlag = false;

}
void switch_callback(int position) {
	changeMethodDone = false;
}
int main(int argc, char** argv) {
	if (argc < 6) {
		printf("Invalid input arguments\n");
		return -1;
	}
	unsigned int dev1 = 0, width = 0, height = 0, sizeThreshold = 0; // Width and height of the capture and minimun obj size
	sscanf(argv[1], "%d", &dev1);
	sscanf(argv[2], "%d", &width);
	sscanf(argv[3], "%d", &height);
	sscanf(argv[4], "%d", &sizeThreshold);

	InputDataManager idManager(dev1, width, height);

	namedWindow("Frames", CV_WINDOW_FREERATIO);

	///  CREATE SWITCH
	cvCreateTrackbar("Switch", "Frames", &switchButtonValue, 1,
			switch_callback);
	///

	setMouseCallback("Frames", onMouse, 0); // Callback for properly closing the app.

	// OutputFile
	ofstream outFile[8];
	for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
		String pathName;
		pathName = "outputs/outputFile";
		char ext[5] = { (char) (((int) '0') + i), '.', 't', 'x', 't' };
		pathName.append(ext);
		cout << pathName << endl;
		outFile[i].open(pathName.c_str());
	}
	ColorClusterSpace CS = *CreateHSVCS_8c(bin2dec("11111111"),
			bin2dec("11111111"), bin2dec(argv[5]));

	// Vector to organize RLEs
	static vector<vector<struct LineObjRLE> > aRLE;

	// Vector of objects in the image.
	vector<SegmentedObject> objs;

	// Preparando los filtros de Kalman
	Mat x0 = (Mat_<double>(6, 1) << 2, 2, 2, 0, 0, 0);

	// Extended Kalman filter applicated to Stereo Vision variables
	GroundTrackingEKF EKFs[8] = { GroundTrackingEKF(matQ, matR, x0),
			GroundTrackingEKF(matQ, matR, x0), GroundTrackingEKF(matQ, matR, x0),
			GroundTrackingEKF(matQ, matR, x0), GroundTrackingEKF(matQ, matR, x0),
			GroundTrackingEKF(matQ, matR, x0), GroundTrackingEKF(matQ, matR, x0),
			GroundTrackingEKF(matQ, matR, x0) };

	camera cam(alphaX, alphaY, gammaSkew, u0, v0, distortionMat,
			projectionMat);
	
	// ObjectMatching ---> Searcher of current tracked objects (8 colors)

	ObjectMatching objectMatching;

	// Time for EKF
	
	STime::init();

	STime *gTimer = STime::get();

	TReal *timers = new TReal[8];
	// Ref temp.
	TReal refTime0;
	TReal t1, t2;

	// Update timer.
	gTimer->update();

	// Get time for reference
	refTime0 = gTimer->frameTime();

	// Time reference for EKF filter
	for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
		gTimer->update();
		timers[i] = gTimer->frameTime();
	}

	Mat frame, ori;
	// loop
	while (waitKey(1) && exitFlag) {
		// MIRAR SI HEMOS CAMBIADO EL SWITCH
		if (!changeMethodDone) {
			if (switchButtonValue) {
				idManager.changeMethod(
						"/home/pablo/Desktop/Estimation/P1_640x480/Images/",
						"img%d_cam1.jpg", width, height,
						"/home/pablo/Desktop/Estimation/P1_640x480/ViconData2.txt");
				changeMethodDone = true;
				CS = *CreateHSVCS_8c(bin2dec("11111111"), bin2dec("11111111"),
						bin2dec("00010000"));
				sizeThreshold = 20;
			} else {
				idManager.changeMethod(dev1, width, height);
				changeMethodDone = true;
				CS = *CreateHSVCS_8c(bin2dec("11111111"), bin2dec("11111111"),
						bin2dec("10000000"));
				sizeThreshold = 500;
			}
			// Get time for reference
			refTime0 = gTimer->frameTime();

			// Time reference for EKF filter
			for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
				gTimer->update();
				timers[i] = gTimer->frameTime();
			}
		}
		//-------------------------------------

		gTimer->update();
		t1 = gTimer->frameTime();

		aRLE.reserve(50000); // Need to be optimised
		objs.reserve(5000);

		idManager.updateFrame();
		idManager.getFrame(frame);

		frame.copyTo(ori);

		medianBlur(frame, frame, 5);
		medianBlur(frame, frame, 5);

		imageBGR2HSV(frame);

		segmentateImage(frame, CS, objs, aRLE);

		// Free memory
		aRLE.clear();

		// Update camera positions
		double incT;

		idManager.getNextCamPos(cam, incT);

		// EKFs
		for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
			// EKF triangulation.
			trackedObject match;
			objectMatching.getCurrentObject(match,i);

			if (match.flagUpdate) {
				Mat Zk =
					(Mat_<double>(4, 1) <<match.mPos.x, match.mPos.y);  // Zk = [x', y'] <-- variables de estado observado es el centroide del objeto en la imagen

				TReal auxTime;
				gTimer->update();
				auxTime = gTimer->frameTime();
				double diff = timers[i]-refTime0;

				if (incT == -1) {
					incT = diff;
				}

				timers[i] = auxTime;

				cout << "DIFERENCIA DE TIEMPO: " << diff << endl;
				cout << "Zk: {" << match.mPos.x << ", " << match.mPos.y
						<< "} " << endl;

				EKFs[i].updateCameraPos(cam.pos, cam.ori);
				EKFs[i].updateIncT(diff);
				EKFs[i].stepEKF(Zk);

				timers[i] = auxTime;

				Mat Xak;
				EKFs[i].getStateVector(Xak);
				double refTime = auxTime - refTime0;


				cout << "Time: " << refTime << endl << "State: " << Xak << endl;

				outFile[i] << refTime << " "
						<< Xak.ptr<double>(0)[0] << " " << Xak.ptr<double>(1)[0]
						<< " " << Xak.ptr<double>(2)[0] << endl;

			}
		}

		objectMatching.setFlags(false);

		gTimer->update();
		t2 = gTimer->frameTime();
		double diff = t2-t1;
		cout << "FINISHED IN " << diff << endl;

		// Since here everything is for & about displaying information not real algorithm, so it's not included
		// in the time counter.
		imageHSV2BGR(frame);

		highlighObjs(objs, ori, sizeThreshold);

		hconcat(frame, ori, frame);
		imshow("Frames", frame);

		objs.clear();

		idManager.updateCurrentFrame();
	}

	aRLE.clear();
	objs.clear();

}
