////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Robust matching between simpleObjects adquires at previous steps

#ifndef _VISUAL_TRACKING_UI_ROBUSTSTEREOMATCHING_H_
#define _VISUAL_TRACKING_UI_ROBUSTSTEREOMATCHING_H_

#include <Types/SimpleObject.h>

#include <vector>

namespace vision {
	namespace tracking {
		//--------------------------------------------------------------------
		class RobustStereoMatching{
		public:
			RobustStereoMatching();
			~RobustStereoMatching();

			void init(double _speed);

		//--------------------------------------------------------------------
		public:
			void updateObjects(std::vector<vision::SimpleObject>& _objects);
			SimpleObject *getObjects();
			bool isUpdated(unsigned int i);
		//--------------------------------------------------------------------
		private:
			vision::SimpleObject objects[8];
			bool updated[8];
			double speed;

		//--------------------------------------------------------------------
		};
	//--------------------------------------------------------------------
	} // namespace tracking
} // namespace vision






#endif // _VISUAL_TRACKING_UI_ROBUSTSTEREOMATCHING_H_