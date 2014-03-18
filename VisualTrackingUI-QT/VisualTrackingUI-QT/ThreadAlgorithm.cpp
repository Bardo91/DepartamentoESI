////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Endless thread that run the specified algorithm

#include "ThreadAlgorithm.h"
#include "ImageManager.h"
#include "SegmentationManager.h"
#include "ComputerVisionLibraries/Timing/time.h"
#include "ComputerVisionLibraries/Positioning/Camera.h"

#include <iostream>
#include <opencv/cv.h>


using namespace std;
using namespace vision;
using namespace cv;

namespace vision{
void threadAlgoritm(InfoPointers *infoPointers){
	//------------------------------------//
	const String wTitle = "example";
	cv::namedWindow(wTitle, CV_WINDOW_FREERATIO);
	ImageManager *imageManager = infoPointers->imageManager;
	SegmentationManager *segmentationManager = infoPointers->segmentationManager;
	PositionManager *positionManager = infoPointers->positionManager;
	AlgorithmManager *algorithmManager = infoPointers->algorithmManager;

	int threshold = infoPointers->threshold;

	Mat frame1, frame2, ori1, ori2;

	vector<SimpleObject> objects1;
	vector<SimpleObject> objects2;

	//------------------------------------//
	// OutputFiles
	// 666 TODO: implementar en fichero separado

	ofstream outFile[8];
	for (unsigned int i = 0; i < 8; i++) {
		String pathName;
		pathName = "C:/outputs/outputFile";
		pathName.push_back((char) (((int) '0') + i)); pathName.push_back('.'); pathName.push_back('t'); pathName.push_back('x');pathName.push_back('t');
		cout << pathName << endl;
		outFile[i].open(pathName.c_str());
	}

	//------------------------------------//
	position::Camera cam1 = positionManager->getCamera(1), cam2 = positionManager->getCamera(2);

	double currentTime = 0;

	//------------------------------------//
	// Prepare Timer.
	//STime::init(); <-- Is initialized at the PositionerManager

	STime *gTimer = STime::get();

	// Ref temp.
	double refTime0;
	double t1, t2;
	double lastTime, incT;

	// Get time for reference
	refTime0 = gTimer->frameTime();

	//------------------------------------//
	while(cv::waitKey(1) && infoPointers->looping){
		t1 = gTimer->frameTime(); //-------------

		imageManager->updateFrames();
		imageManager->getFrames(frame1, frame2);		

		frame1.copyTo(ori1);
		frame2.copyTo(ori2);


		// 666 TODO: Va más rápido sin el MedianBlur pero es más sensible al ruido, por lo que hay que mejorar el matching
		medianBlur(frame1, frame1, 5);
		medianBlur(frame1, frame1, 5);
		if(imageManager->areTwoCameras()){
			medianBlur(frame2, frame2, 5);
			medianBlur(frame2, frame2, 5);
		}

		segmentationManager->applyAlgorithm(frame1, frame2, objects1, objects2);

		positionManager->updatePosAndTime();

		lastTime = currentTime , incT;
		positionManager->getCameraPosAndTime(cam1,cam2, currentTime); 
		
		algorithmManager->updateCameras(cam1, cam2);

		incT = currentTime - lastTime;
		algorithmManager->applyAlgorithmStep(objects1, objects2, incT); // 666 TODO: Revisar con camaras y objeto verde controlado. Revisar

		vector<Mat> trackedObj;
		algorithmManager->getObjectPos(trackedObj);

		cout << trackedObj[4] << endl;

		t2 = gTimer->frameTime(); //-----------
		double diff = t2-t1; //-----------
		cout << "FINISHED IN " << diff << endl; //-----------


		// 666 TODO: BORRAR ESTO - IMPLEMENTAR BIEN EL RESALTADO DE OBJETOS DETECTADOS

		vector<SimpleObject> zk1;
		vector<SimpleObject> zk2;
		algorithmManager->getObservationObjects(zk1, zk2);

		for(int i = 0 ; i < 8; i++){
			rectangle(ori1, zk1[i].downRight, zk1[i].upperLeft, Scalar(0,0,0), 1);
		}
		if(frame2.rows != 0){
			for(int i = 0 ; i < 8; i++){
				rectangle(ori2, zk2[i].downRight, zk2[i].upperLeft, Scalar(0,0,0), 1);
			}
		}
		//-------------------------------------------------------------------------------

		//------------------------------//
		// OUTPUTFILES 
		// 666 TODO: implementar en fichero separado
		for(int i = 0 ; i < 8 ; i++){
			outFile[i] <<	currentTime							<< "\t" <<
				((double*) trackedObj[i].data)[0]	<< "\t" << 
				((double*) trackedObj[i].data)[1]	<< "\t" << 
				((double*) trackedObj[i].data)[2]	<< "\t" << 
				diff								<< "\t" <<
				zk1[4].centroid.x					<< "\t" <<
				zk1[4].centroid.y					<< "\t" <<
				zk2[4].centroid.x					<< "\t" <<
				zk2[4].centroid.y					<< "\t" << endl;
		}
		//------------------------------//

		if(imageManager->areTwoCameras()){
			hconcat(frame1, frame2, frame1);
			hconcat(ori1, ori2, ori1);
		}

		vconcat(ori1, frame1, frame1);

		imshow(wTitle, frame1);
		objects1.clear();
		objects2.clear();
	}
	//------------------------------------//
	positionManager->closeStream();
	algorithmManager->freeAlgorithms();
	//------------------------------------//
}

} // namespace vision