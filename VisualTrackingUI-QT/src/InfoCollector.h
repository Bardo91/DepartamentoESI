////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/19
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#ifndef _VISUAL_TRACKING_UI_INFO_COLLECTOR_H_
#define _VISUAL_TRACKING_UI_INFO_COLLECTOR_H_

#include "ImageManager.h"
#include  "SegmentationManager.h"

class MainWindow;


namespace vision{
	//------------------------------------------------------------------------
	struct InfoPointers{
	bool looping; // Variable used to stop the loop of the thread
	
	int threshold;

	ImageManager *imageManager;
	SegmentationManager *segmentationManager;
	//PositionManager *positionManager;
	//AlgorithmManager *AlgorithmManager;
	};
	//------------------------------------------------------------------------
	class InfoCollector {
	public:
		InfoCollector(MainWindow *mainWindow);
		~InfoCollector();

	public: // Functions that setUp the threads information.
		int CollectInfo();
		InfoPointers * getPointers();

	private:
		int setUpImageManager();
		int setUpSegmentationManager();
		// 666 TODO: void setUpPositionManager();
		// 666 TODO: void setUpAlgorithmManager();



	private: // Private scope with information about the thread type.
		MainWindow * mainWindow; // Pointer to current context.

		InfoPointers infoPointers;


	};

} // namespace vision


#endif // _VISUAL_TRACKING_UI_INFO_COLLECTOR_H_
