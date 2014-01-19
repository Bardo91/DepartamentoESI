//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-19											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	ActivityWin32


#ifndef _GLHL_ACTIVITYWIN32_H_
#define _GLHL_ACTIVITYWIN32_H_

#include "ActivityGL.h"

namespace GLHL{
	class ActivityWin32: public ActivityGL{
	public:
		ActivityWin32(UINT8 _nWnd, HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow);
		~ActivityWin32();

		bool mainProgram();

	private:
		HGLRC			hRC;					// Permanent Rendering Context
		HDC				hDC;					// Private GDI Device Context
		HWND			hWnd;					// Holds Our Window Handle
		HINSTANCE		hInstance;				// Holds The Instance Of The Application
		HINSTANCE		hPrevInstance;			// 
		LPSTR			lpCmdLine;				// 
		int				nCmdShow;				// 
	};

}	// namespace GLHL.


#endif // _GLHL_ACTIVITYWIN32_H_
