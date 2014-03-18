//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-14											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	main.cpp


#include "ActivityWin32.h"


using namespace GLHL;

int WINAPI WinMain(HINSTANCE _hInstance,			// Instance
				   HINSTANCE _hPrevInstance,		// Previous Instance
				   LPSTR _lpCmdLine,				// Command line parameters
				   int _nCmdShow){				// Windows show state
	
	ActivityWin32 activity(_hInstance, _hPrevInstance, _lpCmdLine, _nCmdShow);
	
	activity.mainProgram();

}