////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#include "InfoCollector.h"
#include "mainwindow.h"

#include <qmessagebox.h>


namespace vision{
	InfoCollector::InfoCollector(MainWindow *_mainWindow){
		imageManager = new ImageManager();
	
		mainWindow = _mainWindow;
	}

	InfoCollector::~InfoCollector(){
			delete imageManager;
	}

	void InfoCollector::CollectInfo(){
		setUpImageManager(); // Prepare image manager
		//setUpPositionManager();
		//setUpAlgorithmManager();

		//infoPointers.positionManager = positionManager
		//infoPointers.algorithManager = algorithmManager

		infoPointers.looping = true;

	}

	InfoPointers * InfoCollector::getPointers(){
		return &infoPointers;
	}

	void InfoCollector::setUpImageManager(){
		int method = mainWindow->getImgAcqMethod(); // 777 TODO: implement width and heigth.
		if(method == 0){ // From device/s.
			imageManager->setUpImageAcquisitor(1, mainWindow->getIdDevice1(), 320, 240);
			if(mainWindow->getNumberDevices() == 2){
				imageManager->setUpImageAcquisitor(2, mainWindow->getIdDevice2(), 320, 240);
				imageManager->setTwoCameras(true);
			}else{
				imageManager->setTwoCameras(false);
			}

		}else if(method == 1){ // From images.
			// 777 TODO: implement two edit text to different camera name Format
			imageManager->setUpImageAcquisitor(1, mainWindow->getImagesPath(), mainWindow->getImageNameFormat(), 320, 240);
			if(mainWindow->getNumberDevices() == 2){
				imageManager->setUpImageAcquisitor(2, mainWindow->getImagesPath(), mainWindow->getImageNameFormat(), 320,240);
				imageManager->setTwoCameras(true);
			}else{
				imageManager->setTwoCameras(false);
			}

		} else if(method == 2){ // From video
			QMessageBox::information(mainWindow, "Error", "Video acquisition method is not implemented");
			// 666 TODO: Implement video acquisition method.
		}

		infoPointers.imageManager = imageManager;
	}

}