//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-14											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	main.cpp


#include "windowGL.h"

using namespace windowGL;

int WINAPI WinMain(HINSTANCE _hInstance,			// Instance
				   HINSTANCE _hPrevInstance,		// Previous Instance
				   LPSTR _lpCmdLine,				// Command line parameters
				   int _nCmdShow){				// Windows show state
	
	mainApp(_hInstance, _hPrevInstance, _lpCmdLine, _nCmdShow);
	
}