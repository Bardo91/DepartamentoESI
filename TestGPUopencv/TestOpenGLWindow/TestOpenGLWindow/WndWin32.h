//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-18											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	WndWin32 window class that inherite from WindowGL

#ifndef _GLHL_WNDWIN32_H_
#define _GLHL_WNDWIN32_H_

#include "WindowGL.h"

namespace GLHL{
	// Declaración de WndProc. Funcion callback que se llama cuando se recibe un mensaje.
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

	class WndWin32: public WindowGL{
	public:				// Public interface.
		WndWin32();
		
		GLboolean initWindow(char* _title, int _width, int _height, int _bits, bool _fullscreenFlag);

	public:
		HDC getHDC() const;

	private:			// Private members
		GLvoid selfDestroy();

	private:
		// Setting up in windows. En linux seria usando glx:
		HGLRC hRC;					// Permanent Rendering Context. (Conecta las llamadas de OpenGL con el Device Context)
		HDC hDC;					// Device Context. (Conecta la ventana de contexto con el GDI-Graphic device Interface)
		HWND hWnd;					// Handle window. (Manejador de la ventana en windows)
		HINSTANCE hInstance;		// Instancia de la ventana del programa.

	};

	inline HDC WndWin32::getHDC() const{
		return hDC;
	}

} // namespace GLHL.
#endif // _GLHL_WNDWIN32_H_
