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
	ActivityWin32::ActivityWin32(UINT8 _nWnd, HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow){
		// Prepare window and rendering context
		hInstance = _hInstance;
		hPrevInstance = _hPrevInstance;
		lpCmdLine = _lpCmdLine;
		nCmdShow = _nCmdShow;
		
		nWnd = _nWnd;
		windows = new WndWin32[nWnd];

		for(UINT8 i = 0; i < _nWnd ; i ++){
			windows[i].initWindow("window", 640, 480, 16, false);
		}

		// Prepare GPU interface
		driverGPU = new DriverGPU();
		assert(driverGPU->initDriver());
	}
	//---------------------------------------------------------------------------------
	ActivityWin32::~ActivityWin32(){
		delete driverGPU;
		delete[] windows;
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
			driverGPU->drawOnBuffer(640, 480, hDC);
			//glClear(GL_COLOR_BUFFER_BIT);
			SwapBuffers(hDC);
		}

		return TRUE;
	}

	//---------------------------------------------------------------------------------

}	// namespace GLHL