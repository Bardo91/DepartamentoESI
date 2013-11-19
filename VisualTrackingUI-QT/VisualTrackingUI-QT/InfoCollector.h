////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#ifndef _VISUAL_TRACKING_UI_INFO_COLLECTOR_H_
#define _VISUAL_TRACKING_UI_INFO_COLLECTOR_H_

#include <ComputerVisionLibraries/DataAcquisition/ImageManager.h>

class MainWindow;


namespace vision{
	struct InfoPointers{
	bool looping; // Variable used to stop the loop of the thread

	ImageManager *imageManager;
	//PositionManager *positionManager
	//AlgorithmManager *AlgorithmManager
	};

	class InfoCollector {
	public:
		InfoCollector(MainWindow *mainWindow);
		~InfoCollector();

	public: // Functions that setUp the threads information.
		void CollectInfo();
		InfoPointers * getPointers();

		void setUpImageManager();
		// 666 TODO: void setUpPositionManager();
		// 666 TODO: void setUpAlgorithmManager();



	private: // Private scope with information about the thread type.
		MainWindow * mainWindow; // Pointer to current context.

		ImageManager * imageManager;

		InfoPointers infoPointers;


	};

} // namespace vision


#endif // _VISUAL_TRACKING_UI_INFO_COLLECTOR_H_
