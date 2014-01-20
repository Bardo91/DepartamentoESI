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
		glShadeModel(GL_SMOOTH);								// Enables Smooth Shading
	
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
		
		glClearDepth(1.0f);										// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);								// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);									// The Type Of Depth Test To Do

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// Really Nice Perspective Calculations

		return TRUE;											// Initialization Went OK
	}

	//--------------------------------------------------------------------------------
} // namespace GLHL