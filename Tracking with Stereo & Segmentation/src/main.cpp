/*
 * main.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: pablo
 */

#include <vector>

#include <ImageAcquisitor.h>
#include <ColorClusterSpace.h>
#include <SegmentedObject.h>
#include <StereoVisionEKF.h>

#include <FastStereoMatching.cpp>
#include <CameraDataEKF.cpp>

using namespace cv;
using namespace std;
using namespace sysctrl;

using namespace ccss;

bool exitFlag = true;

static void onMouse(int event, int x, int y, int, void*) {
	if (event == EVENT_LBUTTONDOWN)
		exitFlag = false;

}

double diffTime(struct timespec t2, struct timespec t1) {
	if (t2.tv_nsec < t1.tv_nsec) {
		return ((double) (t2.tv_nsec - t1.tv_nsec + 1000000000)) / 1000000000
				+ t2.tv_sec - t1.tv_sec - 1;
	} else {
		return ((double) (t2.tv_nsec - t1.tv_nsec)) / 1000000000 + t2.tv_sec
				- t1.tv_sec;
	}
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

	ImageAcquisitor imgAc1(dev1, width, height);
	ImageAcquisitor imgAc2(dev2, width, height);

	int MaskH, MaskS, MaskV;
	MaskH = MaskS = MaskV = bin2dec("11111111");
	MaskH = bin2dec(argv[6]);

	ColorClusterSpace CS;
	CreateHSVCS_8c(MaskH, MaskS, MaskV, CS);

	namedWindow("Frames", CV_WINDOW_FREERATIO);

	setMouseCallback("Frames", onMouse, 0); // Callback for properly closing the app.

	// Vector to organize RLEs
	static vector<vector<struct LineObjRLE> > aRLE1;
	static vector<vector<struct LineObjRLE> > aRLE2;

	// Vector of objects in the image.
	vector<SegmentedObject> objs1;
	vector<SegmentedObject> objs2;

	// OutputFile
	ofstream outFile[sizeof(uchar) * 8];
	for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
		String pathName;
		pathName = "outputs/outputFile";
		char ext[5] = { (char) (((int) '0') + i), '.', 't', 'x', 't' };
		pathName.append(ext);
		cout << pathName << endl;
		outFile[i].open(pathName.c_str());
	}

	ViconDataAcquisitor vicon;
	if (imgAc1.getInputMethod()) {
		vicon.changePath(
				"/home/pablo/Desktop/Estimation/P4_640x480/Images/ViconData2.txt");
	}

	// Preparing EKF
	Mat R1 = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
	R1 = R1.inv();
	Mat R2 = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
	R2 = R2.inv();

	visionctrl::camera cam1 = { { 0, 0, 0 }, R1, false, alphaX };
	visionctrl::camera cam2 = { { 0, 0.16, 0 }, R2, true, alphaX };

	Vec3f x0(0, 0, 0);

	StereoVisionEKF EKFs[sizeof(uchar) * 8] = { StereoVisionEKF(cam1, cam2,
			matQ, matR, x0), StereoVisionEKF(cam1, cam2, matQ, matR, x0),
			StereoVisionEKF(cam1, cam2, matQ, matR, x0), StereoVisionEKF(cam1,
					cam2, matQ, matR, x0), StereoVisionEKF(cam1, cam2, matQ,
					matR, x0), StereoVisionEKF(cam1, cam2, matQ, matR, x0),
			StereoVisionEKF(cam1, cam2, matQ, matR, x0), StereoVisionEKF(cam1,
					cam2, matQ, matR, x0) };

	waitKey();

	// Time for EKF
	struct timespec timeEKFs[sizeof(uchar) * 8];

	for (unsigned int i = 0; i < sizeof(uchar) * 8; i++) {
		clock_gettime(CLOCK_REALTIME, &timeEKFs[i]);
	}

	// Ref temp.
	struct timespec t1, t2;
	struct timespec refTime0;

	clock_gettime(CLOCK_REALTIME, &refTime0);

	Mat frame1, frame2, ori1, ori2;

	while (waitKey(1) && exitFlag) {
		aRLE1.reserve(50000); // Need to be optimised
		aRLE2.reserve(50000); // Need to be optimised
		objs1.reserve(5000);
		objs2.reserve(5000);

		clock_gettime(CLOCK_REALTIME, &t1); // Time counter1

		imgAc1.updateFrame();
		imgAc1.getFrame(frame1);
		imgAc2.updateFrame();
		imgAc2.getFrame(frame2);

		frame1.copyTo(ori1);
		frame2.copyTo(ori2);

		printf("%d %d \n", frame1.cols, frame1.rows);

		// Decreasing noise by median filter;
		medianBlur(frame1, frame1, 5);
		medianBlur(frame1, frame1, 5);
		medianBlur(frame2, frame2, 5);
		medianBlur(frame2, frame2, 5);

		cv::cvtColor(frame1, frame2, cv::COLOR_BGR2HSV);
		cv::cvtColor(frame1, frame2, cv::COLOR_BGR2HSV);

		segmentateImage(frame1, frame2, CS, objs1, aRLE1, objs2, aRLE2);

		// Free memory
		aRLE1.clear();
		aRLE2.clear();

		LR matching[sizeof(uchar) * 8];

		objectMatching(objs1, objs2, matching, cam1, cam2, EKFs, sizeThreshold);

		cout << "Nº objsL : " << objs1.size() << endl;
		cout << "Nº objsR : " << objs2.size() << endl;

	}
}

