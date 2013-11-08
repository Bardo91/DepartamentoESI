////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ram�n Soria (Based on Carmelo's J. Fern�ndez-Ag�era Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

#ifndef _CCSSTRACKING_TIMEFUNS_TIMESRC_H_
#define _CCSSTRACKING_TIMEFUNS_TIMESRC_H_

#include "time.h"

namespace sysctrl {

        class ITimeSrc
        {
        public:
                virtual        TReal        deltaTime        () const = 0;
        };

}        //namespace rev

#endif // _CCSSTRACKING_TIMEFUNS_TIMESRC_H_