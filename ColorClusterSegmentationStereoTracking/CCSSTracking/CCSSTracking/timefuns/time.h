////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria (Based on Carmelo's J. Fernández-Agüera Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

#ifndef _CCSSTRACKING_TIMEFUNS_TIME_H_
#define _CCSSTRACKING_TIMEFUNS_TIME_H_

namespace sysctrl
{
		typedef double TReal;

        class STime
        {
                /// \brief this system provides time meassures to game. time is considered constant along a whole frame.
        public:
                // --- Singleton life cycle ---
                static void init();
                static STime* get();        ///< Returns the singleton instance
                static void end();

        public:
                // --- System management ---
                void update();        ///< Update time system

                // --- Public interface ---
                TReal frameTime();

        private:
                STime();

        private:
                // Singleton instance
                static STime* sTime;

                // last frame duration.
                TReal mFrameTime;

                // Internal use.
		#if defined(_linux) || defined (ANDROID)
            unsigned double mLastTime;
		#endif
		#if defined (WIN32)
			unsigned double mLastTime;
		#endif
        };

        //------------------------------------------------------------------------------------------------------------------
        inline TReal STime::frameTime()
        {
            return mFrameTime;
        }

        //------------------------------------------------------------------------------------------------------------------
        inline STime * STime::get()
        {
            return sTime;
        }

}        // namespace sysctrl

#endif // _CCSSTRACKING_TIMEFUNS_TIME_H_