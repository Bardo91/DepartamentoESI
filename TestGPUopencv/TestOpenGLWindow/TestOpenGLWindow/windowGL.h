//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-18											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL.h This header contain declaration, variables and structures
//	for creating the main OpenGl window

#ifndef _GLHL_WINDOWGL_H_
#define _GLHL_WINDOWGL_H_

// Including basic libraries depending on the operative system
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef _linux
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

namespace GLHL{
	// Abstact classs of windows
	class windowGL{
	public:			// Public interface.
		windowGL();							//  Basic Constructor.
		
		// Función de set up de OpenGL
		int initGL(GLvoid);

		// Función para crear una ventana para OpenGL
		BOOL initWindow(char* _title, int _width, int _height, int _bits, bool _fullscreenFlag);

		// Función principal que cre la ventana y prepara el programa. 666 TODO: depende de windows
		int mainApp(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow);

		// Dibuja en la ventana
		void drawOnWindow(GLsizei _width, GLsizei _height, GLuint _program);

	protected:		// Private members
		// Declaración de WndProc. Funcion callback que se llama cuando se recibe un mensaje.
		LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM); // 666 TODO: depende de window

		// Función para redimensionar el tamaño de la ventana e inicializar al ventana. Esta será llamada cada vez que haya un cambio en el tamaño de la ventana, o se pase de fullscreen a screen, etc...
		GLvoid reSizeGLScene(GLsizei _width, GLsizei _height);

		// Función para destruir la ventana adecuadamente.
		GLvoid selfDestroy();

	protected:
		// Setting up in windows. En linux seria usando glx:
		HGLRC hRC;			// Permanent Rendering Context. (Conecta las llamadas de OpenGL con el Device Context)
		HDC hDC;				// Device Context. (Conecta la ventana de contexto con el GDI-Graphic device Interface)
		HWND hWnd;			// Handle window. (Manejador de la ventana en windows)
		HINSTANCE hInstance;		// Instancia de la ventana del programa.

		// Flags y variables varias:
		bool keys[256];				// Array para las teclas del teclado.
		bool active;			// Flag si no está o está minimizada la ventana.
		bool fullscreen;		// Flag para fullscreen o no.

	}; //class windowGL
} // namespace GLHL

#endif // _GLHL_WINDOWHL_H_