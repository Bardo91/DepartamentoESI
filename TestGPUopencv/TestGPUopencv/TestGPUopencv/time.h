////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria (Based on Carmelo's J. Fernández-Agüera Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

#ifndef _VISUAL_TRACKING_UI_TIME_H_
#define _VISUAL_TRACKING_UI_TIME_H_

namespace vision
{
	#if defined(_linux) || defined(ANDROID) || defined (WIN32)
		typedef float TReal;
	#endif // _linux || ANDROID || WIN32


    class STime
    {
            /// \brief this system provides time meassures to game. time is considered constant along a whole frame.
    public:
            // --- Singleton life cycle ---
            static void init();
            static STime* get();        ///< Returns the singleton instance
            static void end();
			static bool isInitialized();

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
        int mLastTime;
	#endif
	#if defined (WIN32)
		unsigned mLastTime;
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

}        // namespace vision

#endif // _VISUAL_TRACKING_UI_TIME_H_