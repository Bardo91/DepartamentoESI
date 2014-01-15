//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
//			Date:	2013-01-14											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL.h This header contain declaration, variables and structures
//	for creating the main OpenGl window (In Windows)

#ifndef _GLHL_WINDOWGL_H_
#define _GLHL_WINDOWGL_H_

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <string>

namespace windowGL{
	// Setting up in windows. En linux seria usando glx:
	static HGLRC hRC = NULL;			// Permanent Rendering Context. (Conecta las llamadas de OpenGL con el Device Context)
	static HDC hDC = NULL;				// Device Context. (Conecta la ventana de contexto con el GDI-Graphic device Interface)
	static HWND hWnd = NULL;			// Handle window. (Manejador de la ventana en windows)
	static HINSTANCE hInstance;		// Instancia de la ventana del programa.

	// Flags y variables varias:
	static bool keys[256];				// Array para las teclas del teclado.
	static bool active = TRUE;			// Flag si no est� o est� minimizada la ventana.
	static bool fullscreen = TRUE;		// Flag para fullscreen o no.

	// Declaraci�n de WndProc. Funcion callback que se llama cuando se recibe un mensaje.
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

	// Funci�n para redimensionar el tama�o de la ventana e inicializar al ventana. Esta ser� llamada cada vez que haya un cambio en el tama�o de la ventana, o se pase de fullscreen a screen, etc...
	GLvoid ReSizeGLScene(GLsizei _width, GLsizei _height);

	// Funci�n de set up de OpenGL
	int InitGL(GLvoid);

	// Funci�n para destruir la ventana adecuadamente.
	GLvoid KillGLWindow();

	// Funci�n para crear una ventana para OpenGL
	BOOL CreateGLWindow(char* _title, int _width, int _height, int _bits, bool _fullscreenFlag);

	// Funci�n principal que cre la ventana y prepara el programa.
	int mainApp(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow);

}	//namespace windowGL.

#endif //_GLHL_WINDOWGL_H_