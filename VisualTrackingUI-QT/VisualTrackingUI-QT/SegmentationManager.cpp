////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/20
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#include "SegmentationManager.h"
#include "ComputerVisionLibraries/ImageSegmentation/ColocClusterImageSegmentation.h"

using namespace cv;
using namespace std;

namespace vision{

	//------------------------------------------------------------------------
	SegmentationManager::SegmentationManager(){

	}

	//------------------------------------------------------------------------
	SegmentationManager::~SegmentationManager(){

	}

	//------------------------------------------------------------------------
	void SegmentationManager::setAlgorithm(eSegmentationAlgorithms _algorithm){
		eAlgorithhm = _algorithm;
	}

	//------------------------------------------------------------------------
	int SegmentationManager::applyAlgorithm(eSegmentationAlgorithms _algorithm, Mat _frame, unsigned int threshold, vector<SimpleObject> _objects){
		if(_frame.rows == 0)
			return -1; // Error frame is empty

		switch (_algorithm)
		{
		case eSegmentationAlgorithms::ColorClustering:
			return segmentation::ColorClusterImageSegmentation(CS, _frame, threshold, _objects);
			break;
		}

		return 0;
	}

	//------------------------------------------------------------------------
	int SegmentationManager::applyAlgorithm(eSegmentationAlgorithms _algorithm, cv::Mat _frame1, cv::Mat _frame2, unsigned int threshold, std::vector<SimpleObject> _objects1, std::vector<SimpleObject> _objects2) {
		if(_frame1.rows == 0 ||_frame2.rows == 0)
			return -1; // Any or both of frames are empty.

		switch (_algorithm)
		{
		case eSegmentationAlgorithms::ColorClustering:
			return segmentation::ColorClusterImageSegmentation(CS, _frame1, _frame2,  threshold, _objects1, _objects2);	
			break;
		}

		return 0;
	}

} //namespace vision
