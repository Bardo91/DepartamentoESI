/*
 * main.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: pablo
 */

#include "acquisition/ImageAcquisitor.h"
#include "colorclustersegmentation/ColorClusterSpace.h"
#include "colorclustersegmentation/ColorSpaceHSV8.h"
#include "colorclustersegmentation/SegmentateImage.h"
#include "colorclustersegmentation/SegmentedObject.h"
#include "colorclustersegmentation/FastStereoMatching.h"
#include "timefuns/TimeFunctions.hpp"
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
	static vector<vector<struct LineObjRLE> > aRLE1;

	// Vector of objects in the image.
	vector<SegmentedObject> objs1;

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

	// Time for EKF
	struct timespec timeEKFs[sizeof(uchar) * 8];

	for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
		clock_gettime(CLOCK_REALTIME, &timeEKFs[i]);
	}

	// Ref temp.
	timespec refTime0;
	timespec t1, t2;

	clock_gettime(CLOCK_REALTIME, &refTime0);

	Mat frame1, ori1;
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
			clock_gettime(CLOCK_REALTIME, &refTime0);
			for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
				clock_gettime(CLOCK_REALTIME, &timeEKFs[i]);
			}
		}
		//-------------------------------------

		clock_gettime(CLOCK_REALTIME, &t1);

		aRLE1.reserve(50000); // Need to be optimised
		objs1.reserve(5000);

		idManager.updateFrame();
		idManager.getFrame(frame1);

		frame1.copyTo(ori1);

		medianBlur(frame1, frame1, 5);
		medianBlur(frame1, frame1, 5);

		imageBGR2HSV(frame1);

		segmentateImage(frame1, CS, objs1, aRLE1);

		// Free memory
		aRLE1.clear();

		// Update camera positions
		double incT;

		idManager.getNextCamPos(cam1, incT);

		// EKFs
		for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
			// EKF triangulation.
			if (match[i].updated) {
				Mat Zk =
						(Mat_<double>(4, 1) << match[i].pixL.x, match[i].pixL.y);

				timespec auxTime;
				clock_gettime(CLOCK_REALTIME, &auxTime);
				double diff = diffTime(auxTime, timeEKFs[match[i].color]);

				if (incT == -1) {
					incT = diff;
				}

				timeEKFs[match[i].color] = auxTime;

				cout << "DIFERENCIA DE TIEMPO: " << diff << endl;
				cout << "Zk: {" << match[i].pixL.x << ", " << match[i].pixL.y
						<< ", " << match[i].pixR.x << ", " << match[i].pixR.y
						<< "} " << endl;

				EKFs[match[i].color].updateCameraPos(cam1.pos, cam1.ori);
				EKFs[match[i].color].updateIncT(diff);
				EKFs[match[i].color].stepEKF(Zk);

				timeEKFs[match[i].color] = auxTime;

				Mat Xak;
				EKFs[match[i].color].getStateVector(Xak);
				match[i].updated = FALSE;

				double refTime = diffTime(auxTime, refTime0);

				cout << "Time: " << refTime << endl << "State: " << Xak << endl;

				outFile[match[i].color] << refTime << " "
						<< Xak.ptr<double>(0)[0] << " " << Xak.ptr<double>(1)[0]
						<< " " << Xak.ptr<double>(2)[0] << endl;

			}
		}

		clock_gettime(CLOCK_REALTIME, &t2);
		double diff = diffTime(t2, t1);
		cout << "FINISHED IN " << diff << endl;

		// Since here everything is for & about displaying information not real algorithm, so it's not included
		// in the time counter.
		imageHSV2BGR(frame1);

		highlighObjs(objs1, ori1, sizeThreshold);

		hconcat(frame1, ori1, frame1);
		imshow("Frames", frame1);

		objs1.clear();

		idManager.updateCurrentFrame();
	}

	aRLE1.clear();
	objs1.clear();

}