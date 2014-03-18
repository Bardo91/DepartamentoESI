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
#include <opencv/cv.h>

using namespace cv;
using namespace vision::tracking;
using namespace vision::position;

namespace vision{

	//--------------------------------------------------------------------
	AlgorithmManager::AlgorithmManager(){
		matching1 = 0;
		matching2 = 0;
		stereoEKF = 0;
		singleEKF = 0;
	}

	//--------------------------------------------------------------------
	AlgorithmManager::~AlgorithmManager(){
		
	}

	//--------------------------------------------------------------------
	int AlgorithmManager::setUpAlgorithm(eAlgorithms _algorithm,const Camera& _cam1, const Camera& _cam2){
		algorithm = _algorithm;

		switch (algorithm)
		{
		case vision::eStereoVisionEKF: // 666 TODO: allocate memory rightly
			// Prepare EKF stereo algorithms
			stereoEKF = new StereoVisionEKF[8];
			for(int i = 0; i < 8 ; i++){
				stereoEKF[i].init(matQ, matR, x0, _cam1, _cam2);
			}

			// Prepare matching algorithm.
			matching1 = new RobustStereoMatching();
			matching1->init(0.5);
			matching2 = new RobustStereoMatching();
			matching2->init(0.5);

			break;
		case vision::eSingleCameraGroundEKF: // 666 TODO: allocate memory rightly
			// Prepare EKF single algorithms.
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
	int AlgorithmManager::freeAlgorithms(){
		if(stereoEKF != 0){
			delete [] stereoEKF;
			delete matching1, matching2;
		}
		else if(singleEKF != 0)
			delete [] singleEKF;

		return 0;
	}

	//--------------------------------------------------------------------
	int AlgorithmManager::updateCameras(const position::Camera& _cam1, const position::Camera& _cam2){
		switch (algorithm)
		{
		case vision::eStereoVisionEKF:
			stereoEKF->updateCameraPos(_cam1.getPosition(), _cam2.getPosition(), _cam1.getOrientation(), _cam2.getOrientation());
			break;
		case vision::eSingleCameraGroundEKF:
			singleEKF->updateCameraPos(_cam1.getPosition(), _cam1.getOrientation());
			break;
		}

		return 0;
	}

	//--------------------------------------------------------------------
	int AlgorithmManager::applyAlgorithmStep(std::vector<SimpleObject>& _objects1, std::vector<SimpleObject>& _objects2, double _incT){
		switch (algorithm)
		{
		case vision::eStereoVisionEKF:{ // 666 TODO: allocate memory rightly
			matching1->updateObjects(_objects1);
			matching2->updateObjects(_objects2);

			SimpleObject *objectsZK1 = matching1->getObjects();
			SimpleObject *objectsZK2 = matching2->getObjects();

			for(int i = 0; i < 8; i ++){
				if(matching1->isUpdated(i) && matching2->isUpdated(i)){
					Mat zk = (Mat_<double>(4,1) << objectsZK1[i].centroid.x, objectsZK1[i].centroid.y,
													objectsZK2[i].centroid.x, objectsZK2[i].centroid.y);

					stereoEKF->updateIncT( _incT);
					stereoEKF->stepEKF(zk);
				}
			}
			break;
			}
		case vision::eSingleCameraGroundEKF:{ // 666 TODO: allocate memory rightly
			matching1->updateObjects(_objects1);

			SimpleObject *objectsZK1 = matching1->getObjects();

			for(int i = 0; i < 8; i ++){
				if(matching1->isUpdated(i)){
					Mat zk = (Mat_<double>(4,1) << objectsZK1[i].centroid.x, objectsZK1[i].centroid.y);

					singleEKF->updateIncT( _incT);
					singleEKF->stepEKF(zk);
				}
			}
			break;
			}
		default:
			assert(false);
			return -1;
		}

		return 0;
	}

	//--------------------------------------------------------------------
	void AlgorithmManager::getObjectPos(vector<Mat>& _objects){
		Mat auxPos;
		for(int i = 0; i < 8 ; i ++){ // Right assignment of object
			stereoEKF[i].getStateVector(auxPos);
			_objects.push_back(auxPos);
		}
	}

	//--------------------------------------------------------------------
	void AlgorithmManager::getObservationObjects(vector<SimpleObject>& _objects1, vector<SimpleObject>& _objects2){
		
		SimpleObject *objectsZK1 = matching1->getObjects();
		SimpleObject *objectsZK2 = matching2->getObjects();
		
		for(int i = 0; i < 8 ; i ++){ // Right assignment of object
			_objects1.push_back(objectsZK1[i]);
			_objects2.push_back(objectsZK2[i]);
		}
	}

	//--------------------------------------------------------------------
} // namespace vision