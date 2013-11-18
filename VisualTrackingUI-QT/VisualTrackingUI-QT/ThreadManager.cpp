////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ThreadManager

#include "ThreadManager.h"
#include "ThreadAlgorithm.h"

#include <thread>
#include <qmessagebox.h>

using namespace vision;
using namespace Ui;
using namespace std;

ThreadManager::ThreadManager(MainWindow *_mainWindow){
	imageManager = new ImageManager();
	
	mainWindow = _mainWindow;
}

//------------------------------------------------------------------------------
ThreadManager::~ThreadManager(){
	delete imageManager;

}

//----------------------------------------------------------------------------
bool ThreadManager::isRunning(){
	return running;
}

//----------------------------------------------------------------------------
int ThreadManager::stopThread(){
	if(running){ //If Thread is currently been running first need to be stoped
		running = false;
		bool retry = true;
		while(retry){ // Make sure that the thread will be stopped.
			try{
				pThread->join();
				retry = false;
			}catch(_exception e){
				// try again.
			}
		}
	}
	return 0;
}

//----------------------------------------------------------------------------
int ThreadManager::startThread(){
	if(stopThread() != 0) //If Thread is currently been running first need to be stoped
		return -1; // Thread can not be stopped

	running = true; // Set the flag to control that the thread is going to be running.

	try{
		pThread = new thread(threadAlgoritm, infoPointers);
	}catch(_exception e){
		return -1; // Thread can not be started
	}

	return 0; // Thread started properly.

}

//----------------------------------------------------------------------------
//------------- SET UP THREAD FUNCTIONS--------------- -----------------------
void ThreadManager::setUpThread(){
	// Call functions.
	setUpImageManager();

	// Assign pointers to infoPointer structure to send it to the thread.
	infoPointers.imageManager = imageManager;
	*infoPointers.looping = true;
}

void ThreadManager::setUpImageManager(){
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

}