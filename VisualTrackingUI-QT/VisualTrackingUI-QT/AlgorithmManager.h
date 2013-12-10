////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//
//		Author: Pablo Ramón Soria
//		Date: 2013/11/24
//
////////////////////////////////////////////////////////////////////////////////
// Algorithm Manager


#ifndef _VISUAL_TRACKING_UI_ALGORITHM_MANAGER_H_
#define _VISUAL_TRACKING_UI_ALGORITHM_MANAGER_H_

#include "ComputerVisionLibraries/TrackingAlgorithm/GroundTrackingEKF.h"
#include "ComputerVisionLibraries/TrackingAlgorithm/StereoVisionEKF.h"
#include "ComputerVisionLibraries/TrackingAlgorithm/RobustStereoMatching.h"
#include "ComputerVisionLibraries/Positioning/ObjectGeo.h"
#include "Types\SimpleObject.h"

#include <vector>

namespace vision{ // 666 TODO: add algorithms and algorithm manager to  InfoCollect class and set it up to be used in Threadalgorithm
	enum eAlgorithms {eStereoVisionEKF, eSingleCameraGroundEKF};

	class AlgorithmManager{
	public:
		AlgorithmManager();
		~AlgorithmManager();

		int setUpAlgorithm(eAlgorithms _algorithm,const position::Camera& _cam1,const position::Camera& _cam2);

		int freeAlgorithms(); // This functions need to be called when the thread is closing in order to free memory, and let the application to setup new algorithms
	public: 
		int updateCameras(const position::Camera& _cam1,const position::Camera& _cam2);
		int applyAlgorithmStep(std::vector<SimpleObject>& _objects1, std::vector<SimpleObject>& _objects2, double _incT);
		void getObjectPos(std::vector<cv::Mat>& _objects);

		void getObservationObjects(std::vector<SimpleObject>& _objects1, std::vector<SimpleObject>& _objects2);

	private:
		eAlgorithms algorithm; // Define algorithm type
			
		tracking::RobustStereoMatching *matching1, *matching2; // Only one matching, because the vector of objects received from image segmentation has a mixture of objects.
		tracking::StereoVisionEKF *stereoEKF; // Array of EKFs,one for each color.
		tracking::GroundTrackingEKF * singleEKF; // Array of EKFs,one for each color.

	}; // class AlgorithmManager.
} // namespace vision


#endif //_VISUAL_TRACKING_UI_ALGORITHM_MANAGER_H_

