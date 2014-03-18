//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-19											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	ActivityWin32

#include "ActivityWin32.h"
#include "WndWin32.h"

namespace GLHL{
	//---------------------------------------------------------------------------------
	ActivityWin32::ActivityWin32(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow){
		// Prepare window and rendering context
		hInstance = _hInstance;
		hPrevInstance = _hPrevInstance;
		lpCmdLine = _lpCmdLine;
		nCmdShow = _nCmdShow;
		
		window = new WndWin32;

		window->initWindow("window", 640, 480, 16, false);

		// Prepare GPU interface
		driverGPU = new DriverGPU();
	}
	//---------------------------------------------------------------------------------
	ActivityWin32::~ActivityWin32(){
		delete driverGPU;
		delete[] window;
	}

	//---------------------------------------------------------------------------------
	bool ActivityWin32::mainProgram(){
		MSG msg;				// Windows menssage Structure.
		BOOL done = FALSE;		// Variable to exit loop.

		driverGPU->initShaders();

		while(!done){
			if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE)){ // Comprobamos si hay algun mensaje esperando en la cola
				if(msg.message == WM_QUIT) // Es un mensaje de cerrar?
					done = TRUE;
				else{
					TranslateMessage(&msg); // Traducimos el mensaje
					DispatchMessage(&msg); // Reenviamos el mensaje, lo despachamos
				}
			}

			driverGPU->drawOnBuffer(640, 480, static_cast<WndWin32*>(window)->getHDC());
			//glClear(GL_COLOR_BUFFER_BIT);
			SwapBuffers(static_cast<WndWin32*>(window)->getHDC());
		}

		return TRUE;
	}

	//---------------------------------------------------------------------------------

}	// namespace GLHL