//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2013-01-15											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	LoaderOpenGLExtensions

#ifndef _GLHL_LOADEROPENGLEXTENSION_H_
#define _GLHL_LOADEROPENGLEXTENSION_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl/GL.h>
#include <gl/GLU.h>
#include "OpenGLExtensions/glext.h"

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

namespace GLHL {

	class OpenGLExtensions{ // 666 TODO: ¿Cambiar de clase  a algo tipo drivers o abstraccion de hardware o algo asi?
	public:
		OpenGLExtensions();

		static void loadOpenGLExtensions();

	public: // Extended functions - secured
		GLuint glCreteShader(GLenum _type);

	private: // Extended functions - unsecured
		//---------------------------------------------------------------------------
		// Shader Functions
		static PFNGLCREATESHADERPROC glCreateShaderUnsecure;
		static PFNGLSHADERSOURCEPROC glShaderSourceUnsecure;
		static PFNGLCOMPILESHADERPROC glCompileShaderUnsecure;
		static PFNGLGETSHADERIVPROC glGetShaderivUnsecure;
		static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLogUnsecure;
		static PFNGLDELETESHADERPROC glDeleteShaderUnsecure;

		//---------------------------------------------------------------------------
	};

} // namespace shadersGL.


#endif //_GLHL_LOADEROPENGLEXTENSION_H_.
