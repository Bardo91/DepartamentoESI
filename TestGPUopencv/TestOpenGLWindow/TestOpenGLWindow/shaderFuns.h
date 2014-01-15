//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-15											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	shaderFuns

#ifndef _GLHL_SHADERFUNS_H_
#define _GLHL_SHADERFUNS_H_

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
namespace GLHL{
	namespace shadersGL{
		// This function is used to create the shader object. It's loaded from a source and then is compiled.
		GLuint loadShader(GLenum _type, const char* _shaderSrc);
	
		// This function initialize the vertex and fragment shaders 666 TODO: this is a prototype, do it better
		bool initShaders();

	} // namespace shadersGL
} // namespace GLHL


#endif // _GLHL_SHADERFUNS_H_