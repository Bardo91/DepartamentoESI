//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	ActivityGL

#ifndef _GLHL_ACTIVITYGL_H_
#define _GLHL_ACTIVITYGL_H_

#include "DriverGPU.h"
#include "WindowGL.h"

namespace GLHL{
	class ActivityGL{
	public:
		
	private:
		DriverGPU driverGPU;
		WindowGL** windows; // Pointers to windows of the current activity
	}; // class ActivityGL
} // namespace GLHL

#endif // _GLHL_ACTIVITY_H_
