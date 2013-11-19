////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ThreadManager

#ifndef _VISUAL_TRACKING_UI_THREAD_MANAGER_H_
#define _VISUAL_TRACKING_UI_THREAD_MANAGER_H_

#include <ComputerVisionLibraries/DataAcquisition/ImageManager.h>
#include "ThreadAlgorithm.h"

#include <thread>
#include <ui_mainwindow.h>


class MainWindow;

namespace vision{

	class ThreadManager{
	public:
		ThreadManager(MainWindow *mainWindow);
		~ThreadManager();

	private:
		bool running;		
		std::thread *pThread;
	public:
		bool isRunning();
		int startThread();
		int stopThread();

	public: // Functions that setUp the threads information.
		void ThreadManager::setUpThread();
		void setUpImageManager();
		// 666 TODO: void setUpPositionManager();
		// 666 TODO: void setUpAlgorithmManager();

	private: // Private scope with information about the thread type.
		MainWindow * mainWindow; // Pointer to current context.

		ImageManager * imageManager;

		InfoPointers infoPointers;

	};

} // namespace vision

#endif //_VISUAL_TRACKING_UI_THREAD_MANAGER_H_