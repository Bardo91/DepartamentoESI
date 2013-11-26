////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		
//		Author: Pablo Ramón Soria
//		Date: 2013/11/24
//
////////////////////////////////////////////////////////////////////////////////
// Algorithm Manager

#include "AlgorithmManager.h"
#include "ParamsEKF.h"

#include "ComputerVisionLibraries/Positioning/Camera.h"

#include <cassert>

using namespace cv;
using namespace vision::tracking;
using namespace vision::position;

namespace vision{
	namespace algorithms{

		//--------------------------------------------------------------------
		AlgorithmManager::AlgorithmManager(){
			stereoEKF = 0;
			singleEKF = 0;
		}

		//--------------------------------------------------------------------
		AlgorithmManager::~AlgorithmManager(){
			if(stereoEKF != 0)
				delete [] stereoEKF;
			else if(singleEKF != 0)
				delete [] singleEKF;
		}

		//--------------------------------------------------------------------
		int AlgorithmManager::setUpAlgorithm(eAlgorithms _algorithm, Camera _cam1, Camera _cam2){
			algorithm = _algorithm;

			switch (algorithm)
			{
			case vision::algorithms::eStereoVisionEKF: // 666 TODO: allocate memory rightly
				stereoEKF = new StereoVisionEKF[8];
				for(int i = 0; i < 8 ; i++){
					stereoEKF[i].init(matQ, matR, x0, _cam1, _cam2);
				}
				break;
			case vision::algorithms::eSingleCameraGroundEKF: // 666 TODO: allocate memory rightly
				singleEKF = new GroundTrackingEKF[8];
				for(int i = 0; i < 8 ; i++){
					singleEKF[i].init(matQ, matR, x0, _cam1);
				}
				break;
			default:
				assert(false);
				return -1;
			}

			return 0;
		}

		//--------------------------------------------------------------------
		int AlgorithmManager::applyAlgorithmStep(std::vector<SimpleObject> _objects1, std::vector<SimpleObject> _objects2, double _incT){
			switch (algorithm)
			{
			case vision::algorithms::eStereoVisionEKF: // 666 TODO: allocate memory rightly
				// 666 TODO: implement 2 robust matching
				break;
			case vision::algorithms::eSingleCameraGroundEKF: // 666 TODO: allocate memory rightly
				// 666 TODO: implement robust matching
				break;
			default:
				assert(false);
				return -1;
			}

			return 0;
		}

		//--------------------------------------------------------------------
		void AlgorithmManager::getObjectPos(vector<position::ObjectGeo> _objects){

		}
			

		//--------------------------------------------------------------------


	} // namespace algorithms
} // namespace vision