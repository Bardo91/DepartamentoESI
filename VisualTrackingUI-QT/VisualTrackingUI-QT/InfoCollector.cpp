////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#include "InfoCollector.h"
#include "mainwindow.h"


#include <qmessagebox.h>

using namespace std;

namespace vision{
	//------------------------------------------------------------------------
	InfoCollector::InfoCollector(MainWindow *_mainWindow){
		infoPointers.imageManager = new ImageManager();
		infoPointers.segmentationManager = new SegmentationManager();
		infoPointers.positionManager = new PositionManager();

		mainWindow = _mainWindow;
	}

	//------------------------------------------------------------------------
	InfoCollector::~InfoCollector(){
			delete infoPointers.imageManager;
			delete infoPointers.segmentationManager;
			delete infoPointers.positionManager;
	}

	//------------------------------------------------------------------------
	int InfoCollector::CollectInfo(){
		int errors = 0;
		errors += setUpImageManager(); 
		errors += setUpSegmentationManager();
		errors += setUpPositionManager(mainWindow->getCameraInfoPath(), mainWindow->getCameraPositionPath(), mainWindow->getIsFixedCameras());
		//error += setUpAlgorithmManager();

		
		//infoPointers.algorithManager = algorithmManager


		infoPointers.looping = true;
		infoPointers.threshold = mainWindow->getThreshold();

		if(errors < 0)
			return -1; // ERROR collecting information.
		return 0;
	}

	//------------------------------------------------------------------------
	InfoPointers * InfoCollector::getPointers(){
		return &infoPointers;
	}

	//------------------------------------------------------------------------
	int InfoCollector::setUpImageManager(){
		infoPointers.imageManager->closeDevices(); //Release every device to avoid errors if device IDs are crossed.
		int method = mainWindow->getImgAcqMethod(); // 777 TODO: implement width and heigth.
		int width = mainWindow->getWidth();
		int height = mainWindow->getHeight();

		if(method == 0){ // From device/s.
			int nDev = mainWindow->getNumberDevices();
			if(nDev == 1){
				int dev1 = mainWindow->getIdDevice1();
				infoPointers.imageManager->setUpImageAcquisitor(1, dev1, width, height);
				infoPointers.imageManager->setTwoCameras(false);
			}else if(nDev == 2){
				int dev1 = mainWindow->getIdDevice1();
				int dev2 = mainWindow->getIdDevice2();
				if(dev1 == dev2){  // Devices cant have the same ID
					QMessageBox::information(mainWindow, "Error", "Devices cant have the same ID");
					return -1;
				}
				infoPointers.imageManager->setUpImageAcquisitor(1, dev1, width, height);
				infoPointers.imageManager->setUpImageAcquisitor(2, dev2, width, height);
				infoPointers.imageManager->setTwoCameras(true);
			}
		}else if(method == 1){ // From images.
			// 777 TODO: implement 
			

		} else if(method == 2){ // From video
			QMessageBox::information(mainWindow, "Error", "Video acquisition method is not implemented");
			// 666 TODO: Implement video acquisition method.
		}

		return 0;
	}

	//------------------------------------------------------------------------
	int InfoCollector::setUpSegmentationManager(){
		switch (mainWindow->getSegmentationAlgorithm())
		{
			case 0:
				infoPointers.segmentationManager->setAlgorithm(vision::eSegmentationAlgorithms::ColorClustering);
				break;

			default:
				QMessageBox::information(mainWindow, "Error", "Cant load this Segmentation Algorithm");
				assert(false);
				break;
		}

		return 0;
	}

	//------------------------------------------------------------------------
	int InfoCollector::setUpPositionManager(string& _cameraInfoPath, string& _positionPath, bool _isFixed){
		int posMethod = mainWindow->getPositionAcquisitionMethod();
		int errors = 0;
		if(posMethod == 0){
			errors += infoPointers.positionManager->configureCams(_cameraInfoPath);
			errors += infoPointers.positionManager->preparePositioner(_positionPath, _isFixed); // Change filename
		}else if (posMethod == 1){
			// 666 TODO: vicon data method
		}

		if(errors < 0)
			QMessageBox::information(mainWindow, "Error", "Cant open camera files");

		return 0;
	}
}