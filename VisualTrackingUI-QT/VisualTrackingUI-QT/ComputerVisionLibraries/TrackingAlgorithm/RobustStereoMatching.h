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

		class RobustStereoMatching{
		public:
			RobustStereoMatching();
			~RobustStereoMatching();

		public:
			void updateObjects(std::vector<vision::SimpleObject> _objects);

		private:
			vision::SimpleObject *objects;
			double velocity;

		};

	} // namespace tracking
} // namespace vision






#endif // _VISUAL_TRACKING_UI_ROBUSTSTEREOMATCHING_H_