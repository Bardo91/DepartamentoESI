//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-14											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL.cpp this source contain the definition of functions used to
//	configure the main window and main program (In Windows)

#include "DriverGPU.h"
#include "windowGL.h"

#include <cassert>

	int	mainApp(HINSTANCE _hInstance,				// Instance
				HINSTANCE _hPrevInstance,			// Previous Instance
				LPSTR _lpCmdLine,					// Command line parameters
				int _nCmdShow){						// Windows show state

		MSG msg;				// Windows menssage Structure.
		BOOL done = FALSE;		// Variable to exit loop.

		// Creamos la ventana de windows, si devuelve falso la función es que no se ha creado la ventana y acabamos la aplicación.
		if (!createGLWindow("OpenGl FrameWork",640,480,16,fullscreen)) {
			return 0;                           // Quit If Window Was Not Created
		}

		initGL();

		GLHL::DriverGPU driverGPU;
		// LOAD DriverGPU 666 sitio mejor?
		if(!driverGPU.initDriver()) // 666 TODO: aqui no funciona cargar drivers, no se ha iniciado algo???
			return 0;

		driverGPU.initShaders();

		while(!done){
			if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE)){ // Comprobamos si hay algun mensaje esperando en la cola
				if(msg.message == WM_QUIT) // Es un mensaje de cerrar?
					done = TRUE;
				else{
					TranslateMessage(&msg); // Traducimos el mensaje
					DispatchMessage(&msg); // Reenviamos el mensaje, lo despachamos
				}
			}
			driverGPU.drawOnWindow(640, 480, hDC);
			//glClear(GL_COLOR_BUFFER_BIT);
			SwapBuffers(hDC);
		}
