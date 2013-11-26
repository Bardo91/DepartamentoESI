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
#include "ComputerVisionLibraries/Positioning/ObjectGeo.h"
#include "Types\SimpleObject.h"

#include <vector>

namespace vision{
	namespace algorithms{
		enum eAlgorithms {eStereoVisionEKF, eSingleCameraGroundEKF};

		class AlgorithmManager{
		public:
			AlgorithmManager();
			~AlgorithmManager();

			int setUpAlgorithm(eAlgorithms _algorithm, position::Camera _cam1, position::Camera _cam2);
		public: 
			int applyAlgorithmStep(std::vector<SimpleObject> _objects1, std::vector<SimpleObject> _objects2, double _incT);
			void getObjectPos(std::vector<position::ObjectGeo> _objects);

		private:
			eAlgorithms algorithm; // Define algorithm type
			
			tracking::StereoVisionEKF *stereoEKF; // 666 TODO: Implement generic algorithm class.
			tracking::GroundTrackingEKF * singleEKF;

		}; // class AlgorithmManager.


	} // namespace algorithms
} // namespace vision


#endif //_VISUAL_TRACKING_UI_ALGORITHM_MANAGER_H_

