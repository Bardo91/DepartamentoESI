////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/11/29
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Robust matching between simpleObjects adquires at previous steps

#include "RobustStereoMatching.h"
#include <opencv/cv.h>

using namespace cv;

namespace vision{
	namespace tracking{
		//--------------------------------------------------------------------
		RobustStereoMatching::RobustStereoMatching(){

		}

		//--------------------------------------------------------------------
		RobustStereoMatching::~RobustStereoMatching(){

		}

		//--------------------------------------------------------------------
		void RobustStereoMatching::init(double _speed){
			for(int i = 0; i < 8 ; i ++){
				objects[i] = SimpleObject();
				updated[8] = false;
			}
			//Speed determine the speed of the matching algorithm. the more hight it's setted, the more sensible is the algorithm to both tracking objects and noise.
			speed = _speed; 

		}

		//--------------------------------------------------------------------
		void RobustStereoMatching::updateObjects(std::vector<vision::SimpleObject>& _objects){
			double *error = new double[8];
			SimpleObject *tempObjects  = new SimpleObject[8];
			for(int i = 0; i < 8 ; i ++){
				tempObjects[i].centroid = Point(640, 320); // set it to the oposite corner in order not to confuse the algorithm at the firsts interations.
				error[i] = objects[i].distanceTo(tempObjects[i].centroid); // 666 TODO: this calculus is always the same, sustitute it for the value;
				updated[i] = false;
			}


			for(int i = _objects.size()-1 ; i >= 0  ; i--){
				double auxError = _objects[i].distanceTo(objects[_objects[i].color].centroid);
				if(error[_objects[i].color] > auxError){
					error[_objects[i].color]  = auxError;
					tempObjects[_objects[i].color] = _objects[i];

					updated[_objects[i].color] = true; // Set flag to 1 in order to know if the EKF must do a step.
				}

			}

			for(int i = 0; i < 8 ; i++){
				objects[i] = tempObjects[i];

			}

			delete[] error, tempObjects;
		}
		//--------------------------------------------------------------------
		SimpleObject *RobustStereoMatching::getObjects(){
			return objects;
		}

		//--------------------------------------------------------------------
		bool RobustStereoMatching::isUpdated(unsigned int i){
			return updated[i];
		}

		//--------------------------------------------------------------------

	} //  namespace tracking
} // namespace vision