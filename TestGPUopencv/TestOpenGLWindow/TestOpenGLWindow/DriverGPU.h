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

	public: // Public interface to shaders

	private:
	};

} // namespace GLHL



#endif //_GLHL_DRIVERGPU_H_