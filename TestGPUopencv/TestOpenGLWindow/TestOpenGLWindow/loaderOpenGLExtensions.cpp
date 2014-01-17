//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-15											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	LoaderOpenGLExtensions

#include "loaderOpenGLExtensions.h"

#include <cassert>

using namespace GLHL;
//-----------------------------------------------------------------------------
// function pointers are initialized initially to nullptr in order to check 
// afterwards if they were loaded properlly.
/*PFNGLCREATESHADERPROC OpenGLExtensions::glCreateShaderUnsecure = nullptr;
PFNGLSHADERSOURCEPROC OpenGLExtensions::glShaderSourceUnsecure = nullptr;
PFNGLCOMPILESHADERPROC OpenGLExtensions::glCompileShaderUnsecure = nullptr;
PFNGLGETSHADERIVPROC OpenGLExtensions::glGetShaderivUnsecure = nullptr;
PFNGLGETSHADERINFOLOGPROC OpenGLExtensions::glGetShaderInfoLogUnsecure = nullptr;
PFNGLDELETESHADERPROC OpenGLExtensions::glDeleteShaderUnsecure = nullptr;

PFNGLCREATEPROGRAMPROC OpenGLExtensions::glCreateProgramUnsecure = nullptr;
PFNGLATTACHSHADERPROC OpenGLExtensions::glAttachShaderUnsecure = nullptr;
PFNGLBINDATTRIBLOCATIONPROC OpenGLExtensions::glBindAttribLocationUnsecure = nullptr;
PFNGLLINKPROGRAMPROC OpenGLExtensions::glLinkProgramUnsecure = nullptr;
PFNGLGETPROGRAMIVPROC OpenGLExtensions::glGetProgramivUnsecure = nullptr;
PFNGLGETPROGRAMINFOLOGPROC OpenGLExtensions::glGetProgramInfoLogUnsecure = nullptr;
PFNGLDELETEPROGRAMPROC OpenGLExtensions::glDeleteProgramUnsecure = nullptr;
PFNGLUSEPROGRAMPROC OpenGLExtensions::glUseProgramUnsecure = nullptr;

PFNGLVERTEXATTRIBPOINTERPROC OpenGLExtensions::glVertexAttribPointerUnsecure = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC OpenGLExtensions::glEnableVertexAttribArrayUnsecure = nullptr;*/

//-----------------------------------------------------------------------------
// Load OpenGL extended functions
void OpenGLExtensions::loadOpenGLExtensions(){

	//----------------------------------------------------------------------------
	// Shader Functions
	glCreateShaderUnsecure = (PFNGLCREATESHADERPROC) loadGlFunction("glCreateShader");
	glShaderSourceUnsecure = (PFNGLSHADERSOURCEPROC) loadGlFunction("glShaderSource");
	glCompileShaderUnsecure = (PFNGLCOMPILESHADERPROC) loadGlFunction("glCompileShader");
	glGetShaderivUnsecure = (PFNGLGETSHADERIVPROC) loadGlFunction("glGetShaderiv");
	glGetShaderInfoLogUnsecure = (PFNGLGETSHADERINFOLOGPROC) loadGlFunction("glGetShaderInfoLog");
	glDeleteShaderUnsecure = (PFNGLDELETESHADERPROC) loadGlFunction("glDeleteShader");

	glCreateProgramUnsecure = (PFNGLCREATEPROGRAMPROC) loadGlFunction("glCreateProgram");
	glAttachShaderUnsecure = (PFNGLATTACHSHADERPROC) loadGlFunction("glAttachShader");
	glBindAttribLocationUnsecure = (PFNGLBINDATTRIBLOCATIONPROC) loadGlFunction("glBindAttribLocation");
	glLinkProgramUnsecure = (PFNGLLINKPROGRAMPROC) loadGlFunction("glLinkProgram");
	glGetProgramivUnsecure = (PFNGLGETPROGRAMIVPROC) loadGlFunction("glGetProgramiv");
	glGetProgramInfoLogUnsecure = (PFNGLGETPROGRAMINFOLOGPROC) loadGlFunction("glGetProgramInfoLog");
	glDeleteProgramUnsecure = (PFNGLDELETEPROGRAMPROC) loadGlFunction("glDeleteFunction");
	glUseProgramUnsecure = (PFNGLUSEPROGRAMPROC) loadGlFunction("glUseProgram");

	glVertexAttribPointerUnsecure = (PFNGLVERTEXATTRIBPOINTERPROC) loadGlFunction("glAttribPointer");
	glEnableVertexAttribArrayUnsecure = (PFNGLENABLEVERTEXATTRIBARRAYPROC) loadGlFunction("glEnableVertexAttribArray");
}

//-----------------------------------------------------------------------------
GLuint OpenGLExtensions::glCreateShader(GLenum _type){
	assert(glCreateShaderUnsecure != nullptr);
	return glCreateShaderUnsecure(_type);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glShaderSource(GLuint _shader, GLsizei _count, const GLchar* const *_string, const GLint *_length){
	assert(glShaderSourceUnsecure != nullptr);
	glShaderSourceUnsecure(_shader, _count, _string, _length);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glCompileShader(GLuint _shader){
	assert(glCompileShaderUnsecure != nullptr);
	glCompileShaderUnsecure(_shader);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glGetShaderiv(GLuint _shader, GLenum _pname, GLint *_params){
	assert(glGetShaderivUnsecure != nullptr);
	glGetShaderivUnsecure(_shader, _pname, _params);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glGetShaderInfoLog(GLuint _shader, GLsizei _bufSize, GLsizei *_length, GLchar *_infoLog){
	assert(glGetShaderInfoLogUnsecure != nullptr);
	glGetShaderInfoLogUnsecure(_shader, _bufSize, _length, _infoLog);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glDeleteShader(GLuint _shader){
	assert(glDeleteShaderUnsecure != nullptr);
	glDeleteShaderUnsecure(_shader);
}

//-----------------------------------------------------------------------------
GLuint OpenGLExtensions::glCreateProgram(){
	assert(glCreateProgramUnsecure != nullptr);
	return glCreateProgramUnsecure();
}
//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glAttachShader(GLuint _program, GLuint _shader){
	assert(glAttachShaderUnsecure!= nullptr);
	glAttachShaderUnsecure(_program, _shader);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glBindAttribLocation(GLuint _program, GLuint _index, const GLchar *_name){
	assert(glBindAttribLocationUnsecure!= nullptr);
	glBindAttribLocationUnsecure(_program, _index, _name);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glLinkProgram(GLuint _program){
	assert(glLinkProgramUnsecure != nullptr);
	glLinkProgramUnsecure(_program);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glGetProgramiv (GLuint _program, GLenum _pname, GLint *_params){
	assert(glGetProgramivUnsecure != nullptr);
	glGetProgramivUnsecure(_program, _pname, _params);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glGetProgramInfoLog(GLuint _program, GLsizei _bufSize, GLsizei *_length, GLchar *_infoLog){
	assert(glGetProgramInfoLogUnsecure != nullptr);
	glGetProgramInfoLogUnsecure(_program, _bufSize, _length, _infoLog);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glDeleteProgram(GLuint _program){
	assert(glDeleteProgramUnsecure != nullptr);
	glDeleteProgramUnsecure(_program);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glUseProgram(GLuint _program){
	assert(glUseProgramUnsecure != nullptr);
	glUseProgramUnsecure(_program);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glVertexAttribPointer(GLuint _index, GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const GLvoid *_pointer){
	assert(glVertexAttribPointerUnsecure != nullptr);
	glVertexAttribPointerUnsecure(_index, _size, _type, _normalized, _stride, _pointer);
}

//-----------------------------------------------------------------------------
GLvoid OpenGLExtensions::glEnableVertexAttribArray(GLuint _index){
	assert(glEnableVertexAttribArrayUnsecure != nullptr);
	glEnableVertexAttribArrayUnsecure(_index);
}