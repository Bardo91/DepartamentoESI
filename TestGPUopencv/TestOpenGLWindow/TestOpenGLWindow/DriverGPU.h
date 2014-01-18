//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#ifndef _GLHL_DRIVERGPU_H_
#define _GLHL_DRIVERGPU_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

#include "OpenGLExtensions/glext.h"
#include "OpenGLExtensions/wglext.h"

// La carga de funciones de expansión de OpenGl se hacen de forma diferente
// en windows y en linux, para que sea comodo el traslado del código entre 
// una plataforma y otra se ha escrito la siguiente macro.
#ifdef _WIN32
#define loadGlFunction( args ) wglGetProcAddress ( args )
#endif
#ifdef _linux
#define loadGlFunction( args ) glXGetProcAddress ( (GLuint*)args )
#endif
//-------------------------------------------------------------------//

namespace GLHL{
	class DriverGPU{	// Only one GPU driver is created
	public:			
		DriverGPU();				// Class constructor.
	public:
		bool initDriver();

	public: // Public interface to OpenGL Extended libraries
		// --> Shaders
		PFNGLCREATESHADERPROC glCreateShader;
		PFNGLSHADERSOURCEPROC glShaderSource;
		PFNGLCOMPILESHADERPROC glCompileShader;
		PFNGLGETSHADERIVPROC glGetShaderiv;
		PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
		PFNGLDELETESHADERPROC glDeleteShader;
		
		PFNGLCREATEPROGRAMPROC glCreateProgram;
		PFNGLATTACHSHADERPROC glAttachShader;
		PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		PFNGLLINKPROGRAMPROC glLinkProgram;
		PFNGLGETPROGRAMIVPROC glGetProgramiv;
		PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
		PFNGLDELETEPROGRAMPROC glDeleteProgram;
		PFNGLUSEPROGRAMPROC glUseProgram;
		
		PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	

	public:		// Public interface to shaders
		bool initShaders();

	private:
		GLuint loadShader(GLenum _type, const char* _shaderSrc);

	private:	// Shaders declaration.
		GLuint vShader, gShader, fShader; // 666 TODO: maybe arent necessary
		GLuint program;

	public: // Draw
		void drawOnBuffer(GLint _widt, GLint _height, HDC _hDC);
	};

} // namespace GLHL



#endif //_GLHL_DRIVERGPU_H_