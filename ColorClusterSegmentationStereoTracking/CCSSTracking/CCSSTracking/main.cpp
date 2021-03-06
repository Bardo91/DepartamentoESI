////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ram�n Soria
//		Date: 2013/10/31
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // 666 TODO: clear definition and solve warnings
#endif

#include "acquisition/ImageAcquisitor.h"
#include "colorclustersegmentation/ColorClusterSpace.h"
#include "colorclustersegmentation/ColorSpaceHSV8.h"
#include "colorclustersegmentation/SegmentateImage.h"
#include "colorclustersegmentation/SegmentedObject.h"
#include "colorclustersegmentation/ObjectMatching.h"
#include "timefuns/time.h"
#include "output/outputFuns.h"
#include "kalmanfilter/StereoVisionEKF.h"
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
bool changeMethodDone = false;

static void onMouse(int event, int x, int y, int, void*) {
	if (event == EVENT_LBUTTONDOWN)
		exitFlag = false;

}
void switch_callback(int position) {
	changeMethodDone = false;
}
int main(int argc, char** argv) {
	if (argc < 7) {
		printf("Invalid input arguments\n");
		return -1;
	}
	unsigned int dev1 = 0, dev2 = 1, width = 0, height = 0, sizeThreshold = 0; // Width and height of the capture and minimun obj size
	sscanf(argv[1], "%d", &dev1);
	sscanf(argv[2], "%d", &dev2);
	sscanf(argv[3], "%d", &width);
	sscanf(argv[4], "%d", &height);
	sscanf(argv[5], "%d", &sizeThreshold);

	///
	namedWindow("Frames", CV_WINDOW_FREERATIO);
	setMouseCallback("Frames", onMouse, 0); // Callback for properly closing the app.

	///  CREATE SWITCH
	cvCreateTrackbar("Switch", "Frames", &switchButtonValue, 1,
			switch_callback);

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
			bin2dec("11111111"), bin2dec(argv[6]));

	// Vector to organize RLEs
	static vector<vector<struct LineObjRLE> > aRLE1;
	static vector<vector<struct LineObjRLE> > aRLE2;

	// Vector of objects in the image.
	vector<SegmentedObject> objs1;
	vector<SegmentedObject> objs2;

	// Preparing ObjectMatching.
	StereoObjectMatching stereoMatching;


	// Preparando los filtros de Kalman
	Mat x0 = (Mat_<double>(6, 1) << 2, 2, 2, 0, 0, 0);

	// Extended Kalman filter applicated to Stereo Vision variables
	StereoVisionEKF EKFs[8] = { StereoVisionEKF(matQ, matR, x0),
			StereoVisionEKF(matQ, matR, x0), StereoVisionEKF(matQ, matR, x0),
			StereoVisionEKF(matQ, matR, x0), StereoVisionEKF(matQ, matR, x0),
			StereoVisionEKF(matQ, matR, x0), StereoVisionEKF(matQ, matR, x0),
			StereoVisionEKF(matQ, matR, x0) };

	camera cam1(alphaX, alphaY, gammaSkew, u0, v0, distortionMat,
			projectionMat);
	camera cam2(alphaX, alphaY, gammaSkew, u0, v0, distortionMat,
			projectionMat);

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

	Mat frame1, frame2, ori1, ori2;
	InputDataManager idManager;
	waitKey();
	// loop
	while (waitKey(1) && exitFlag) {
		// MIRAR SI HEMOS CAMBIADO EL SWITCH
		if (!changeMethodDone) {
			if (switchButtonValue) {
				idManager.changeMethod(
						"/home/pablo/Desktop/Estimation/P1_640x480/Images/",
						"img%d_cam1.jpg", "img%d_cam2.jpg", width, height,
						"/home/pablo/Desktop/Estimation/P1_640x480/ViconData2.txt");
				changeMethodDone = true;
				CS = *CreateHSVCS_8c(bin2dec("11111111"), bin2dec("11111111"),
						bin2dec("00010000"));
				sizeThreshold = 20;
			} else {
				idManager.changeMethod(dev1, dev2, width, height);
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

		aRLE1.reserve(50000); // Need to be optimised
		aRLE2.reserve(50000); // Need to be optimised
		objs1.reserve(5000);
		objs2.reserve(5000);

		idManager.updateFrame();
		idManager.getFrames(frame1, frame2);

		frame1.copyTo(ori1);
		frame2.copyTo(ori2);

		medianBlur(frame1, frame1, 5);
		medianBlur(frame1, frame1, 5);
		medianBlur(frame2, frame2, 5);
		medianBlur(frame2, frame2, 5);

		imageBGR2HSV(frame1);
		imageBGR2HSV(frame2);

		segmentateImage(frame1, frame2, CS, objs1, aRLE1, objs2, aRLE2);

		//imshow("blurred", frame1);


		// Free memory
		aRLE1.clear();
		aRLE2.clear();

		// Update camera positions
		double incT;

		idManager.getNextCamPos(cam1, cam2, incT);

		// Update Matching object
		stereoMatching.compareAndUpdate(objs1,objs2);

		// EKFs
		for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
			// EKF triangulation.
			trackedObject match1, match2;
			stereoMatching.getCurrentObjects(match1, match2, i);

			if (match1.flagUpdate && match2.flagUpdate) {
				Mat Zk =
					(Mat_<double>(4, 1) <<match1.mPos.x, match1.mPos.y, match2.mPos.x, match2.mPos.y);

				TReal auxTime;
				gTimer->update();
				auxTime = gTimer->frameTime();
				double diff = timers[i]-refTime0;

				if (incT == -1) {
					incT = diff;
				}

				timers[i] = auxTime;

				cout << "DIFERENCIA DE TIEMPO: " << diff << endl;
				cout << "Zk: {" << match1.mPos.x << ", " << match1.mPos.y
						<< ", " << match2.mPos.x << ", " << match2.mPos.x
						<< "} " << endl;

				EKFs[i].updateCameraPos(cam1.pos, cam2.pos,
						cam1.ori, cam2.ori);
				EKFs[i].updateIncT(diff);
				EKFs[i].stepEKF(Zk);

				Mat Xak;
				EKFs[i].getStateVector(Xak);

				double refTime = auxTime - refTime0;

				cout << "Time: " << refTime << endl << "State: " << Xak << endl;

				outFile[i] << refTime << " "
						<< Xak.ptr<double>(0)[0] << " " << Xak.ptr<double>(1)[0]
						<< " " << Xak.ptr<double>(2)[0] << endl;

			}
		}
		stereoMatching.setFlags(false);

		gTimer->update();
		t2 = gTimer->frameTime();
		double diff = t2-t1;
		cout << "FINISHED IN " << diff << endl;

		// Since here everything is for & about displaying information not real algorithm, so it's not included
		// in the time counter.
		imageHSV2BGR(frame1);
		imageHSV2BGR(frame2);

		highlighObjs(objs1, ori1, sizeThreshold);
		highlighObjs(objs2, ori2, sizeThreshold);

		hconcat(frame1, frame2, frame1);
		hconcat(ori1, ori2, ori1);
		vconcat(ori1, frame1, ori1);

		imshow("Frames", ori1);

		objs1.clear();
		objs2.clear();

		idManager.updateCurrentFrame();
	}

	aRLE1.clear();
	aRLE2.clear();
	objs1.clear();
	objs2.clear();

	STime::end();

}
