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
		infoPointers.algorithmManager = new AlgorithmManager();

		mainWindow = _mainWindow;
	}

	//------------------------------------------------------------------------
	InfoCollector::~InfoCollector(){
			
	}

	void InfoCollector::deleteInfo(){
		if(infoPointers.imageManager != 0){
			delete infoPointers.imageManager;
			infoPointers.imageManager = 0;
		}
		if(infoPointers.segmentationManager != 0){
			delete infoPointers.segmentationManager;
			infoPointers.segmentationManager = 0;
		}
		if(infoPointers.positionManager != 0){
			delete infoPointers.positionManager;
			infoPointers.positionManager = 0;
		}
		if(infoPointers.algorithmManager != 0){
			delete infoPointers.algorithmManager;
			infoPointers.algorithmManager = 0;
		}
	}
	
	//------------------------------------------------------------------------
	int InfoCollector::CollectInfo(){
		int errors = 0;
		// Reserve space for Managers
		infoPointers.imageManager = new ImageManager();
		infoPointers.segmentationManager = new SegmentationManager();
		infoPointers.positionManager = new PositionManager();
		infoPointers.algorithmManager = new AlgorithmManager();
		// 666 TODO: whatalio!
		errors += setUpImageManager(); 
		errors += setUpSegmentationManager();
		errors += setUpPositionManager(mainWindow->getCameraInfoPath(), mainWindow->getCameraPositionPath(), mainWindow->getIsFixedCameras());
		errors += setUpAlgorithmManager();

		
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
		int nDev = mainWindow->getNumberDevices();
		if(method == 0){ // From device/s.
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
			int errors = 0;
			if(nDev == 1){
				int dev1 = mainWindow->getIdDevice1();
				errors += infoPointers.imageManager->setUpImageAcquisitor(1, mainWindow->getImagesPath(), mainWindow->getImageNameFormat1(), width, height);
				infoPointers.imageManager->setTwoCameras(false);
			}else if(nDev == 2){
				int dev1 = mainWindow->getIdDevice1();
				int dev2 = mainWindow->getIdDevice2();
				errors += infoPointers.imageManager->setUpImageAcquisitor(1, mainWindow->getImagesPath(), mainWindow->getImageNameFormat1(), width, height);
				errors += infoPointers.imageManager->setUpImageAcquisitor(2, mainWindow->getImagesPath(), mainWindow->getImageNameFormat2(), width, height);
				infoPointers.imageManager->setTwoCameras(true);
			}

			if(errors < 0){ 
				QMessageBox::information(mainWindow, "Error", "Cant find images");
				return -1;
			}

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
				infoPointers.segmentationManager->setAlgorithm(vision::eSegmentationAlgorithms::ColorClustering, mainWindow->getThreshold(), mainWindow->getColors());
				break;

			default:
				QMessageBox::information(mainWindow, "Error", "Cant load this Segmentation Algorithm");
				return -1;
				break;
		}

		return 0;
	}

	//------------------------------------------------------------------------
	int InfoCollector::setUpPositionManager(string& _cameraInfoPath, string& _positionPath, bool _isFixed){
		int posMethod = mainWindow->getPositionAcquisitionMethod();
		int errors = 0;
		
		switch (posMethod)
		{
		case 0:
			errors += infoPointers.positionManager->configureCams(_cameraInfoPath);
			errors += infoPointers.positionManager->preparePositioner(_positionPath, _isFixed); // Change filename

			break;
		case 1:
			// 666 TODO: vicon data method

			break;
		default:
			QMessageBox::information(mainWindow, "Error", "Cant open Camera Info-files");
			return -1;
		}
		
		return 0;
	}

	//------------------------------------------------------------------------
	int InfoCollector::setUpAlgorithmManager(){
		int algortihm = mainWindow->getTrackingAlgorithm();
		int errors = 0;
		
		vision::position::Camera cam1, cam2;
		TReal fakeT;

		switch (algortihm)
		{
		case 0: // Single Camera ground tracking
			// 666 TODO: Implement algorithm
			cam1 = infoPointers.positionManager->getCamera(1);
			errors += infoPointers.algorithmManager->setUpAlgorithm(vision::eAlgorithms::eSingleCameraGroundEKF,cam1, cam2);
			

			break;
		case 1: // Stereo Camera 3D tracking
			// 666 TODO: Implement algorithm
			cam1 = infoPointers.positionManager->getCamera(1);
			cam2 = infoPointers.positionManager->getCamera(2);
			infoPointers.positionManager->getCameraPosAndTime(cam1, cam2, fakeT);
			errors += infoPointers.algorithmManager->setUpAlgorithm(vision::eAlgorithms::eStereoVisionEKF,cam1, cam2);
			
			break;
		}

		return errors < 0 ? -1 : 0;
	}

	//------------------------------------------------------------------------

} // namespace vision.
