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

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace ccss;
using namespace std;
using namespace sysctrl;

bool exitFlag = true;

static void onMouse(int event, int x, int y, int, void*) {
	if (event == EVENT_LBUTTONDOWN)
		exitFlag = false;

}

int main(int argc, char** argv) {
	//namedWindow("Viewer", CV_WINDOW_AUTOSIZE);
	//namedWindow("Ori", CV_WINDOW_AUTOSIZE);

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

	ImageAcquisitor imagAc1(dev1, width, height);
	ImageAcquisitor imagAc2(dev2, width, height);

	namedWindow("Frames", CV_WINDOW_FREERATIO);

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

	// Vicon Data
	ViconDataAcquisitor vicon;
	if (imagAc1.getInputMethod()) {
		vicon.changePath(
				"/home/pablo/Desktop/Estimation/P4_640x480/Images/ViconData2.txt");
	}

	ColorClusterSpace CS = *CreateHSVCS_8c(bin2dec("11111111"),
			bin2dec("11111111"), bin2dec(argv[6]));

	// Vector to organize RLEs
	static vector<vector<struct LineObjRLE> > aRLE1;
	static vector<vector<struct LineObjRLE> > aRLE2;

	// Vector of objects in the image.
	vector<SegmentedObject> objs1;
	vector<SegmentedObject> objs2;

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
	struct timespec timeEKFs[sizeof(uchar) * 8];

	for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
		clock_gettime(CLOCK_REALTIME, &timeEKFs[i]);
	}

	// Ref temp.
	timespec refTime0;
	timespec t1, t2;

	clock_gettime(CLOCK_REALTIME, &refTime0);

	Mat frame1, frame2, ori1, ori2;
	// loop
	while (waitKey(1) && exitFlag) {
		waitKey(5);
		clock_gettime(CLOCK_REALTIME, &t1);

		aRLE1.reserve(50000); // Need to be optimised
		aRLE2.reserve(50000); // Need to be optimised
		objs1.reserve(5000);
		objs2.reserve(5000);

		imagAc1.updateFrame();
		imagAc2.updateFrame(12);

		imagAc1.getFrame(frame1);

		imagAc2.getFrame(frame2);

		frame1.copyTo(ori1);
		frame2.copyTo(ori2);

		medianBlur(frame1, frame1, 5);
		medianBlur(frame1, frame1, 5);
		medianBlur(frame2, frame2, 5);
		medianBlur(frame2, frame2, 5);

		imageBGR2HSV(frame1);
		imageBGR2HSV(frame2);

		segmentateImage(frame1, frame2, CS, objs1, aRLE1, objs2, aRLE2);

		// Free memory
		aRLE1.clear();
		aRLE2.clear();

		// Update camera positions
		cam1.pos = (Mat_<double>(3, 1) << 0, 0, 0);
		cam2.pos = (Mat_<double>(3, 1) << 0, -0.16, 0);

		cam1.ori = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
		cam2.ori = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);

		// Matching
		LR match[8];

		objectMatching(objs1, objs2, match, cam1, cam2, EKFs, sizeThreshold);

		// EKFs
		for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
			// EKF triangulation.
			if (match[i].updated) {
				Mat Zk =
						(Mat_<double>(4, 1) << match[i].pixL.x, match[i].pixL.y, match[i].pixR.x, match[i].pixR.y);

				timespec auxTime;
				clock_gettime(CLOCK_REALTIME, &auxTime);
				double diff = diffTime(auxTime, timeEKFs[match[i].color]);

				timeEKFs[match[i].color] = auxTime;

				cout << "DIFERENCIA DE TIEMPO: " << diff << endl;
				cout << "Zk: {" << match[i].pixL.x << ", " << match[i].pixL.y
						<< ", " << match[i].pixR.x << ", " << match[i].pixR.y
						<< "} " << endl;

				EKFs[match[i].color].updateCameraPos(cam1.pos, cam2.pos,
						cam1.ori, cam2.ori);
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
		imageHSV2BGR(frame2);

		highlighObjs(objs1, ori1, sizeThreshold);
		highlighObjs(objs2, ori2, sizeThreshold);

		hconcat(frame1, frame2, frame1);
		hconcat(ori1, ori2, ori1);
		vconcat(ori1, frame1, ori1);

		imshow("Frames", ori1);

		objs1.clear();
		objs2.clear();
	}

	aRLE1.clear();
	aRLE2.clear();
	objs1.clear();
	objs2.clear();

}
