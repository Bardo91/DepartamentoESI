/*
 * main.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: pablo
 */

#include <ImageAcquisitor.h>
#include <ColorClusterSpace.h>

using namespace ccss;

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

}

