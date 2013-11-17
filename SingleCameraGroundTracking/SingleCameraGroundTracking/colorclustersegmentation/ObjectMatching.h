////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/11/12
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object Matching

#ifndef OBJECTMATCHING_H_
#define OBJECTMATCHING_H_

#include "SegmentedObject.h"
#include <opencv/cv.h>
#include <vector>

namespace ccss {

	double energyDistance(cv::Point2d obj1, cv::Point2d obj2);
	
	struct trackedObject{
		cv::Point2d mPos;
		double mSize;
		bool flagUpdate;

		trackedObject();
		trackedObject(cv::Point2d _pos, double _size);
	};

	class ObjectMatching{
	public:
		void compareAndUpdate(const std::vector<SegmentedObject>& _objs);

		double objectDistance(const trackedObject& _obj1, const trackedObject& _obj2);

		void getCurrentObject(trackedObject& _obj, const int _color) const; 

		void setFlags(bool flag);

	public:
		ObjectMatching();
		~ObjectMatching();
	private:
		trackedObject *mCurrentObjs;

		double mVelocity;

	};

} // namespace ccss

#endif // OBJECTMATCHING_H_