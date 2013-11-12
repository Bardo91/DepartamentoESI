////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/11/12
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object Matching


#include "ObjectMatching.h"

using namespace ccss;
using namespace cv;

ObjectMatching::ObjectMatching(){
	mCurrentObjs = new trackedObject[8]; // Reserve memory for every object according to color
	for (unsigned i = 0; i < 8 ; i++){
		mCurrentObjs[i].mSize = 1;
		mCurrentObjs[i].mPos = Point(1,1);
	}

	mVelocity = 0.5; // 0.0 to 1.0 param that define the velocity of the matching algorithm

}

ObjectMatching::~ObjectMatching(){
	delete mCurrentObjs;
}	

double ObjectMatching::objectDistance(const trackedObject& obj1, const trackedObject& obj2){
	// This function calculate "energy distance" between two objects.
	return energyDistance(obj1.mPos, obj2.mPos) + sqrt(obj1.mSize < obj2.mSize ? obj2.mSize -obj2.mSize : obj1.mSize - obj2.mSize);
}


void ObjectMatching::compareAndUpdate(const std::vector<SegmentedObject>& _objs){
	
	double energy[] = {9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999};
	int ci[] = {-1, -1, -1, -1, -1, -1, -1, -1};
	
	for(unsigned i = 0 ; i < _objs.size() ; i++){
		int color = _objs[i].getColor();

		trackedObject lObj(_objs[i].getCentroid(), _objs[i].getSize());

		double lEnergy = objectDistance(mCurrentObjs[color], lObj);

		if(lEnergy < energy[color]){
			energy[color] = lEnergy;
			ci[color] = i;
		}
	}

	for(unsigned i = 0 ; i < 8 ; i++){
		if(ci[i] != -1){
			Point2d newPoint = _objs[ci[i]].getCentroid();
			Point2d lastPoint = mCurrentObjs[i].mPos;

			mCurrentObjs[i].mPos.x = (mVelocity*lastPoint.x + (1-mVelocity)*newPoint.x)/2;
			mCurrentObjs[i].mPos.y = (mVelocity*lastPoint.y + (1-mVelocity)*newPoint.y)/2;

			mCurrentObjs[i].flagUpdate = true;

		}else{
			mCurrentObjs[i].flagUpdate = false;
		}
	}
}

void ObjectMatching::setFlags(bool _flag){
	for(unsigned i = 0 ; i < 8 ; i++){
		mCurrentObjs[i].flagUpdate = _flag;
	}
}

void ObjectMatching::getCurrentObject(trackedObject& _obj, const int _color) const{
	_obj = mCurrentObjs[_color];
}

void StereoObjectMatching::compareAndUpdate(const std::vector<SegmentedObject>& _objs1, const std::vector<SegmentedObject>& _objs2){
	mObjMatching1.compareAndUpdate(_objs1);
	mObjMatching2.compareAndUpdate(_objs2);
}


void StereoObjectMatching::getCurrentObjects(trackedObject& _obj1, trackedObject& _obj2, const int _color) const{
	mObjMatching1.getCurrentObject(_obj1, _color);
	mObjMatching2.getCurrentObject(_obj2, _color);
}

void StereoObjectMatching::setFlags(bool _flag){
	mObjMatching1.setFlags(_flag);
	mObjMatching2.setFlags(_flag);

}
