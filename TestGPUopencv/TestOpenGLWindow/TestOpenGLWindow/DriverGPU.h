//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
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

// La carga de funciones de expansi�n de OpenGl se hacen de forma diferente
// en windows y en linux, para que sea comodo el traslado del c�digo entre 
// una plataforma y otra se ha escrito la siguiente macro.
#ifdef _WIN32
#define loadGlFunction( func ) wglGetProcAddress ( func )
#endif
#ifdef _linux
#define loadGlFunction( func ) glXGetProcAddress ( (GLuint*)func )
#endif
//-------------------------------------------------------------------//

namespace GLHL{
	class DriverGPU{	// Only one GPU driver is created
	public:
		static bool initDriver();

	public: // Public interface to OpenGL Extended libraries
		// --> Shaders
		static PFNGLCREATESHADERPROC glCreateShader;
		static PFNGLSHADERSOURCEPROC glShaderSource;
		static PFNGLCOMPILESHADERPROC glCompileShader;
		static PFNGLGETSHADERIVPROC glGetShaderiv;
		static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
		static PFNGLDELETESHADERPROC glDeleteShader;
		
		static PFNGLCREATEPROGRAMPROC glCreateProgram;
		static PFNGLATTACHSHADERPROC glAttachShader;
		static PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		static PFNGLLINKPROGRAMPROC glLinkProgram;
		static PFNGLGETPROGRAMIVPROC glGetProgramiv;
		static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
		static PFNGLDELETEPROGRAMPROC glDeleteProgram;
		static PFNGLUSEPROGRAMPROC glUseProgram;
		
		static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	private:			
		DriverGPU();				// Class constructor.

	public:		// Public interface to shaders
		static bool initShaders();

	private:
		static GLuint loadShader(GLenum _type, const char* _shaderSrc);

	private:	// Shaders declaration.
		static GLuint vShader, gShader, fShader; // 666 TODO: maybe arent necessary
		static GLuint program;

	public: // Draw
		static void drawOnWindow(GLint _widt, GLint _height, HDC _hDC);
	};

} // namespace GLHL



#endif //_GLHL_DRIVERGPU_H_