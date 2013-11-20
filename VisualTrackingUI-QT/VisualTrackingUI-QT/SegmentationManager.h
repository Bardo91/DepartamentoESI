////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/19
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#ifndef _VISUAL_TRACKING_UI_SEGMENTATION_MANAGER_H_
#define _VISUAL_TRACKING_UI_SEGMENTATION_MANAGER_H_

#include <Types/SimpleObject.h>

#include <opencv/cv.h>
#include <vector>

namespace vision{

	static enum eSegmentationAlgorithms {ColorClustering};

	class SegmentationManager{
	public: // Constructors and deconstructors
		SegmentationManager();
		~SegmentationManager();

	public: // Config manager
		void setAlgorithm(eSegmentationAlgorithms _algorithm);
		eSegmentationAlgorithms getAlgorithm();

	public: // Manager external actions.
		int applyAlgorithm(cv::Mat _frame, unsigned int threshold, std::vector<SimpleObject> _objects);
		int applyAlgorithm(cv::Mat _frame1, cv::Mat _frame2, unsigned int threshold, std::vector<SimpleObject> _objects1, std::vector<SimpleObject> _objects2);

	private:
		eSegmentationAlgorithms eAlgorithm;
		unsigned int threshold;



	};
} //namespace vision


#endif //_VISUAL_TRACKING_UI_SEGMENTATION_MANAGER_H_