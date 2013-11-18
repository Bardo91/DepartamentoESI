////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Endless thread that run the specified algorithm

#include "ThreadAlgorithm.h"


#include <iostream>
#include <opencv/cv.h>


using namespace std;
using namespace vision;

void threadAlgoritm(InfoPointers *infoPointers){

	while(cv::waitKey(5)){
		cout << "Heyy estoy corriendo y el imageManager está en "<< infoPointers->imageManager << endl;
	}

}