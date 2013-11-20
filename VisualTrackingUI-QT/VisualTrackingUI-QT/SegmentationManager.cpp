////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/20
////////////////////////////////////////////////////////////////////////////////
// This class manage to collect all info setted at the UI and prepare it to be sent to the algorithm's thread


#include "SegmentationManager.h"
#include "ComputerVisionLibraries/ImageSegmentation/ColocClusterImageSegmentation.h"
#include "ComputerVisionLibraries/ImageSegmentation/ColorClusterSpace.h"


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
		eAlgorithm = _algorithm;
	}

	//------------------------------------------------------------------------
	eSegmentationAlgorithms SegmentationManager::getAlgorithm(){
		return eAlgorithm;
	}

	//------------------------------------------------------------------------
	int SegmentationManager::applyAlgorithm(Mat _frame, unsigned int threshold, vector<SimpleObject> _objects){
		if(_frame.rows == 0)
			return -1; // Error frame is empty

		switch (eAlgorithm)
		{
		case eSegmentationAlgorithms::ColorClustering:
			// Create cluster space
			segmentation::ColorClusterSpace CS = *segmentation::CreateHSVCS_8c(segmentation::bin2dec("11111111"),
			segmentation::bin2dec("11111111"), segmentation::bin2dec("11111111"));
			// Use Algorithm
			// 666 TODO: implement 1 camera algorithm
			// return segmentation::ColorClusterImageSegmentation(_frame, CS, _objects);
			break;
		}

		return 0;
	}

	//------------------------------------------------------------------------
	int SegmentationManager::applyAlgorithm(cv::Mat _frame1, cv::Mat _frame2, unsigned int threshold, std::vector<SimpleObject> _objects1, std::vector<SimpleObject> _objects2) {
		if(_frame1.rows == 0 ||_frame2.rows == 0)
			return -1; // Any or both of frames are empty.

		switch (eAlgorithm)
		{
		case eSegmentationAlgorithms::ColorClustering:			
			// Create cluster space
			segmentation::ColorClusterSpace CS = *segmentation::CreateHSVCS_8c(segmentation::bin2dec("11111111"),
			segmentation::bin2dec("11111111"), segmentation::bin2dec("11111111"));
			// Use Algorithm
			return segmentation::ColorClusterImageSegmentation(_frame1, _frame2, CS, _objects1, _objects2);	
			break;
		}

		return 0;
	}

} //namespace vision
