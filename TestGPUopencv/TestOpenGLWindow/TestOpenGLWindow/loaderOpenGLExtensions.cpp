//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2013-01-15											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	LoaderOpenGLExtensions

#include "loaderOpenGLExtensions.h"

#include <cassert>

using namespace GLHL;
//-----------------------------------------------------------------------------
// function pointers are initialized initially to nullptr in order to check 
// afterwards if they were loaded properlly.
PFNGLCREATESHADERPROC OpenGLExtensions::glCreateShaderUnsecure = nullptr;
PFNGLSHADERSOURCEPROC OpenGLExtensions::glShaderSourceUnsecure = nullptr;
PFNGLCOMPILESHADERPROC OpenGLExtensions::glCompileShaderUnsecure = nullptr;
PFNGLGETSHADERIVPROC OpenGLExtensions::glGetShaderivUnsecure = nullptr;
PFNGLGETSHADERINFOLOGPROC OpenGLExtensions::glGetShaderInfoLogUnsecure = nullptr;
PFNGLDELETESHADERPROC OpenGLExtensions::glDeleteShaderUnsecure = nullptr;

//-----------------------------------------------------------------------------
GLuint OpenGLExtensions::glCreteShader(GLenum _type){
	assert(glCreateShaderUnsecure != nullptr); // Asegurarse que está cargada la función
	return glCreateShaderUnsecure(_type);
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Load OpenGL extended functions
void OpenGLExtensions::loadOpenGLExtensions(){

	//----------------------------------------------------------------------------
	// Shader Functions
	glCreateShaderUnsecure = (PFNGLCREATESHADERPROC) loadGlFunction("glCreateShader");
	glShaderSourceUnsecure = (PFNGLSHADERSOURCEPROC) loadGlFunction("glShaderSource");;
	glCompileShaderUnsecure = (PFNGLCOMPILESHADERPROC) loadGlFunction("glCompileShader");;
	glGetShaderivUnsecure = (PFNGLGETSHADERIVPROC) loadGlFunction("glGetShaderiv");;
	glGetShaderInfoLogUnsecure = (PFNGLGETSHADERINFOLOGPROC) loadGlFunction("glGetShaderInfoLog");;
	glDeleteShaderUnsecure = (PFNGLDELETESHADERPROC) loadGlFunction("glDeleteShader");;
	//---------------------------------------------------------------------------
}

//---------------------------------------------------------------------------