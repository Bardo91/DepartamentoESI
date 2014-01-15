//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2013-01-15											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	shaderFuns

#ifndef _GLHL_SHADERFUNS_H_
#define _GLHL_SHADERFUNS_H_

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace shadersGL{
	//---------------------------------------------------------------------------
	// This function is used to create the shader object. It's loaded from a 
	// source and then is compiled.
	GLuint LoadShader(const char* _shaderSrc, GLenum _type){
		// Externally, both shader and compiled shader are index to an internal reference.
		GLuint shader;
		GLint compiledShader;

		// Create the shader object
		shader = glCreateShader(_type);

		if(!shader)
			return 0; // Check if the shader was created properlly.

		// Load the shader from the source.
		glShaderSource(shader, 1, &_shaderSrc, NULL);

	}

	//---------------------------------------------------------------------------

} // namespace shadersGL



#endif // _GLHL_SHADERFUNS_H_