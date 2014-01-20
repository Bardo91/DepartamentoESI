//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-18											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL.h This header contain declaration, variables and structures
//	for creating the main OpenGl window

#include "windowGL.h"


namespace GLHL{
	//--------------------------------------------------------------------------------
	WindowGL::WindowGL(){
		active = TRUE;
		fullscreen = TRUE;
	}

	//--------------------------------------------------------------------------------
	GLboolean WindowGL::initGL(){
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
		
		return TRUE;											// Initialization Went OK. In this case, Shaders are used so, there is not necesary to use more GL Functions
	}

	//--------------------------------------------------------------------------------
} // namespace GLHL