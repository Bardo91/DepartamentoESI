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
		~ActivityGL();				// Basic deconstructor.

		virtual bool mainProgram() = 0;		// Main program that will be executed.
		
	protected:
		ActivityGL();				// Basic constructor.

	protected:
		DriverGPU* driverGPU;
		WindowGL* window; // Pointers to windows of the current windows.
		GLuint nWnd;
	}; // class ActivityGL.
} // namespace GLHL.

#endif // _GLHL_ACTIVITY_H_
