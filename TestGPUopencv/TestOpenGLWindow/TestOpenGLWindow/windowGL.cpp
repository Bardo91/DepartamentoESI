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

namespace windowGL{
	// Función para redimensionar el tamaño de la ventana e inicializar al ventana. Esta será llamada cada vez que haya un cambio en el tamaño de la ventana, o se pase de fullscreen a screen, etc...
	GLvoid reSizeGLScene(GLsizei _width, GLsizei _height){
		if(_height == 0) // Para evitar divisiones por cero.
			_height = 1;

		glViewport(0, 0, _width, _height); // Resetea el viewport actual.

		//glMatrixMode(GL_PROJECTION); // Seleciona la matriz de proyección para ser modificada.
		//glLoadIdentity(); // Cargamos la matriz identidad sobre la matriz de proyección para setearla a cero

		//gluPerspective(45.f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f); // Calculamos la matriz de proyección con los parámetros que le pasamos en la función (apertura en grados, relación de aspecto, distancia mínima, distancia máxima).

		//glMatrixMode(GL_MODELVIEW); // Cambiamos ahora la matriz que vamos a modificar a la matrix de modelo de vista.
		//glLoadIdentity(); // Cargamos la matriz identidad (No se deforma la vista).

		// Aquí pueden variar los parámetros en función de la perspectiva y el modelo de vista que queramos usar.

	}

	// Función de set up de OpenGL
	int initGL(GLvoid){
		//glShadeModel(GL_SMOOTH); // habilita smooth shading (Sombredo suave o transiciones suaves entre sombras y luces).

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Estabece el color de "limpiado" de la pantalla, en este caso el negro. Los parámetros son (R,G,B,A).

		//glClearDepth(1.0f);	// Prepara el depth buffer.
		//glEnable(GL_DEPTH_TEST); // Habilita el testeo de la profundidad.
		//glDepthFunc(GL_LEQUAL); // Define el tipo de test de profundidad.

		return true;
	}

	// Función para destruir la ventana adecuadamente.
	GLvoid killGLWindow(){
		if(hRC){ // Si tenemos un contexto de renderizado
			if(!wglMakeCurrent(NULL,NULL)){ // Comprobamos si podemos librerar el Device context y el render context.
				MessageBoxA(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			}
			if(!wglDeleteContext(hRC)){ // Podemos eliminar el render context?
				MessageBoxA(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
				}
			hRC=NULL;                           // Set RC To NULL
		}

		// Intentamos liberar ahora el device context
		if(hDC && !ReleaseDC(hWnd, hDC)){				// Podemos liberar el device context?
			MessageBoxA(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hDC=NULL;									// Set DC To NULL
		}

		// Ahora toca cerrar la ventana
		if (hWnd && !DestroyWindow(hWnd)){				// Are We Able To Destroy The Window?
			MessageBoxA(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hWnd=NULL;									// Set hWnd To NULL
		}

		// Por ultimo hay que "desregistar" la clase de ventana y asi podremos borrar adecuadamente la misma para poder reabrirla más tarde.
		if (!UnregisterClassA("OpenGL",hInstance)){		// Are We Able To Unregister Class
			MessageBoxA(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hInstance=NULL;								// Set hInstance To NULL
		}
	}


	// Función para crear una ventana para OpenGL
	BOOL createGLWindow(char* _title, int _width, int _height, int _bits, bool _fullscreenFlag){
		GLuint PixelFormat;				// Holds the results after searching for a Match.

		WNDCLASSA wc;					// en esta variable se almacena la información de nuestra ventana.
		DWORD dwExStyle;				// Estilo extendido de la ventana.
		DWORD dwStyle;					// Estilo normal de la ventana.

		RECT windowRect;
		windowRect.left = (long) 0;
		windowRect.right = (long) _width;
		windowRect.top = (long) 0;
		windowRect.bottom = (long) _height;

		fullscreen = _fullscreenFlag;

		// Configurar la clase de ventana.
		hInstance = GetModuleHandle(NULL);				// Tomamos una instancia para nuestra ventana.
		wc.style = CS_HREDRAW |CS_VREDRAW | CS_OWNDC;	// Los dos primeros fuerzan  a redibujar cuando la pantalla cambia de resolución, y la tercera crea un DC privado para la ventana, asi no se compartira el DC entre aplicaciones.
		wc.lpfnWndProc = (WNDPROC) WndProc;				// Asignamos el WndProc que estara atento a los mensajes del programa.
		wc.cbClsExtra = 0;								// No extra windows data.
		wc.cbWndExtra =0;								// No extra windows data.
		wc.hInstance = hInstance;						// Guardamos la instancia de la ventana
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Ponermos el icono estandar.
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// Ponermos el icono de raton estandar.
		wc.hbrBackground = NULL;						// Background de la ventana, en este caso da igual ya que vendrá dado por OpenGL.
		wc.lpszMenuName = NULL;							// No vamos a poner menues.
		wc.lpszClassName = "OpenGL";					// Le ponemos un nombre cualquiera a la clase.

		// Vamos a registar la ventana, si algo sale mal, saldrá un menu popup y al clickear ok se cerrara el programa
		if(!RegisterClassA(&wc)){
			MessageBoxA(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;                           // Exit And Return FALSE
		}

		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style

		// Ajusta la ventana.
		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

		if(!(hWnd = CreateWindowExA(dwExStyle,								// Estilo extendido para la ventana.
									"OpenGL",								// Nombre de la clase de la ventana.
									"OpenGl Window",						// Titulo de la ventana.
									WS_CLIPSIBLINGS |						// Propiedad necesaria para que OpenGL funcione adecuadamente
									WS_CLIPCHILDREN |						// Propiedad necesaria para que OpenGL funcione adecuadamente
									dwStyle,								// Estilo de la ventana
									0, 0,									// Posicion de la ventana
									windowRect.right - windowRect.left,		// Calcula el ancho de la ventana ajustada
									windowRect.bottom - windowRect.top,		// Calcula el alto de la ventana ajustada
									NULL,									// No tiene ventana padre
									NULL,									// No tiene menu
									hInstance,								// Instancia de la ventana
									NULL))){									// Ningun parámetro para WM_CREATE.
			killGLWindow(); //Reset the display
			MessageBoxA(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;                           // Return FALSE
		}

		// el PIXELFORMATDESCRIPTOR le dice a windows como queremos mostrar los pixeles
		static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),		// tamaño del descriptor.
			1,									// version  del descriptor.
			PFD_DRAW_TO_WINDOW |				// el formato debe sorportar ventana.
			PFD_SUPPORT_OPENGL |				// el formato debe soportar opengl.
			PFD_DOUBLEBUFFER,					// debe soportar doble buffering.
			PFD_TYPE_RGBA,						// formato en RGBA.
			_bits,								// selecciona el color del fondo.
			0, 0, 0, 0, 0, 0,					// Color bits ignored.
			0,									// Sin buffer para alpha.
			0,									// Shift Bit ignorado.
			0,									// Sin buffer de acumulación.
			0, 0, 0, 0,							// Bit de acumulación ignorado.
			16,									// 16 bits para el Z-buffer  (buffer de profundidad).
			0,									// No stencil buffer.
			0,									// No auxiliary buffer.
			PFD_MAIN_PLANE,						// capa principal de dibujo.
			0,									// Se pone como reservado.
			0, 0, 0 };							// se ignoran las mascaras de capas.

		if (!(hDC=GetDC(hWnd))){					// Did We Get A Device Context?
			killGLWindow();                         // Reset The Display
			MessageBoxA(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;							// Return FALSE
		} if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd))){	// Did Windows Find A Matching Pixel Format?
			killGLWindow();                         // Reset The Display
			MessageBoxA(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;                           // Return FALSE
		} if(!SetPixelFormat(hDC,PixelFormat,&pfd)){// Are We Able To Set The Pixel Format?
			killGLWindow();                         // Reset The Display
			MessageBoxA(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;							// Return FALSE
		} if (!(hRC=wglCreateContext(hDC))){		// Are We Able To Get A Rendering Context?
			killGLWindow();							// Reset The Display
			MessageBoxA(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;							// Return FALSE
		} if(!wglMakeCurrent(hDC,hRC)){				// Try To Activate The Rendering Context
			killGLWindow();                         // Reset The Display
			MessageBoxA(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;                           // Return FALSE
		}

		// Una vez que todo ha funcionado hasta aqui y hemos creado la ventana es hora de visualizarla, ponerla como activa, darle prioridad poniendola de tipo foreground y redimensionandola a los tamaños dados

		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		reSizeGLScene(_width, _height);

		// Por último llamamos a la funcion initGL

		if(!initGL()){
			killGLWindow();
			MessageBoxA(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return false;
		}

		return true;

	}

	LRESULT CALLBACK WndProc (HWND _hWnd,			// Manejador para la ventana.
							  UINT _uMsg,			// Mensaje para la ventana.
							  WPARAM _wParam,		// Información adicional del mensaje.
							  LPARAM _lParam){		// Información adicional del mensaje.
		switch (_uMsg) {			// Vamos aver que tipo de mensaje hemos recibido.
		case WM_ACTIVATE:			// Si es un mensaje de activación de la ventana.
			if(!HIWORD(_wParam))	// Vemos el estado de minimización, si es activamos la ventana y si no, la desactivamos.
				active = TRUE;
			else
				active = FALSE;
			return 0;
		case WM_SYSCOMMAND:			// Si interceptamos una señal del sistema.
			switch (_wParam) {
			case SC_SCREENSAVE:		// Empieza el salvapantallas.
			case SC_MONITORPOWER:	// El monitor se pone en powersave.
				return 0;			// evitamos que ocurra.
			}
			break;
		case WM_KEYDOWN:			// Si se presiona una tecla, ponemos su valor en el array a verdadero.
			keys[_wParam] = TRUE;	
			return 0;				// Acabamos.
		case WM_KEYUP:				// Si se levanta una tecla ponemos su valor en el array a falso.
			keys[_wParam] = FALSE;
			return 0;
		case WM_SIZE:				// Si se redimensiona la ventana
			reSizeGLScene(LOWORD(_lParam), HIWORD(_lParam));	// Redimensionamos. Extraemos los parámetros LoWord = Width / HiWord = Height.
			return 0;
		}

		return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
	}


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

		return 1;
	}
}	// namespace windowGL
