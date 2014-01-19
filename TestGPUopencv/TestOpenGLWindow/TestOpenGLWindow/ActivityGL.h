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
		ActivityGL();				// Basic constructor.
		~ActivityGL();				// Basic deconstructor.

		virtual bool mainProgram(){	// Main program that will be executed.
			assert(FALSE);
			return false;
		}

	protected:
		DriverGPU* driverGPU;
		WindowGL* windows; // Pointers to windows of the current windows.
		GLuint nWnd;
	}; // class ActivityGL.
} // namespace GLHL.

#endif // _GLHL_ACTIVITY_H_
