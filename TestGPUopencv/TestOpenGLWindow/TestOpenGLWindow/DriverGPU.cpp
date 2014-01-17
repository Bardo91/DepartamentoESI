//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#include "DriverGPU.h"

namespace GLHL{
	//---------------------------------------------------------------------------
	PFNGLCREATESHADERPROC DriverGPU::glCreateShader = nullptr;
	PFNGLSHADERSOURCEPROC DriverGPU::glShaderSource = nullptr;
	PFNGLCOMPILESHADERPROC DriverGPU::glCompileShader = nullptr;
	PFNGLGETSHADERIVPROC DriverGPU::glGetShaderiv = nullptr;
	PFNGLGETSHADERINFOLOGPROC DriverGPU::glGetShaderInfoLog = nullptr;
	PFNGLDELETESHADERPROC DriverGPU::glDeleteShader = nullptr;

	PFNGLCREATEPROGRAMPROC DriverGPU::glCreateProgram = nullptr;
	PFNGLATTACHSHADERPROC DriverGPU::glAttachShader = nullptr;
	PFNGLBINDATTRIBLOCATIONPROC DriverGPU::glBindAttribLocation = nullptr;
	PFNGLLINKPROGRAMPROC DriverGPU::glLinkProgram = nullptr;
	PFNGLGETPROGRAMIVPROC DriverGPU::glGetProgramiv = nullptr;
	PFNGLGETPROGRAMINFOLOGPROC DriverGPU::glGetProgramInfoLog = nullptr;
	PFNGLDELETEPROGRAMPROC DriverGPU::glDeleteProgram = nullptr;
	PFNGLUSEPROGRAMPROC DriverGPU::glUseProgram = nullptr;

	PFNGLVERTEXATTRIBPOINTERPROC DriverGPU::glVertexAttribPointer = nullptr;
	PFNGLENABLEVERTEXATTRIBARRAYPROC DriverGPU::glEnableVertexAttribArray = nullptr;

	//---------------------------------------------------------------------------
	bool DriverGPU::initDriver(){
		//---------------------------------------------------------------------------
		glCreateShader = (PFNGLCREATESHADERPROC) loadGlFunction("glCreateShader");
		if(glCreateShader == nullptr)
			return false;

		glShaderSource = (PFNGLSHADERSOURCEPROC) loadGlFunction("glShaderSource");
		if(glShaderSource == nullptr)
			return false;

		glCompileShader = (PFNGLCOMPILESHADERPROC) loadGlFunction("glCompileShader");
		if(glCompileShader == nullptr)
			return false;

		glGetShaderiv = (PFNGLGETSHADERIVPROC) loadGlFunction("glGetShaderiv");
		if(glGetShaderiv == nullptr)
			return false;

		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) loadGlFunction("glGetShaderInfoLog");
		if(glGetShaderInfoLog == nullptr)
			return false;

		glDeleteShader = (PFNGLDELETESHADERPROC) loadGlFunction("glDeleteShader");
		if(glDeleteShader == nullptr)
			return false;

		//---------------------------------------------------------------------------
		glCreateProgram = (PFNGLCREATEPROGRAMPROC) loadGlFunction("glCreateProgram");
		if(glCreateProgram == nullptr)
			return false;

		glAttachShader = (PFNGLATTACHSHADERPROC) loadGlFunction("glAttachShader");
		if(glAttachShader == nullptr)
			return false;

		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) loadGlFunction("glBindAttribLocation");
		if(glBindAttribLocation == nullptr)
			return false;

		glLinkProgram = (PFNGLLINKPROGRAMPROC) loadGlFunction("glLinkProgram");
		if(glLinkProgram == nullptr)
			return false;

		glGetProgramiv = (PFNGLGETPROGRAMIVPROC) loadGlFunction("glGetProgramiv");
		if(glGetProgramiv == nullptr)
			return false;

		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) loadGlFunction("glGetProgramInfoLog");
		if(glGetProgramInfoLog == nullptr)
			return false;

		glDeleteProgram = (PFNGLDELETEPROGRAMPROC) loadGlFunction("glDeleteProgram");
		if(glDeleteProgram == nullptr)
			return false;

		glUseProgram = (PFNGLUSEPROGRAMPROC) loadGlFunction("glUseProgram");
		if(glUseProgram == nullptr)
			return false;
		
		//---------------------------------------------------------------------------
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) loadGlFunction("glVertexAttribPointer");
		if(glVertexAttribPointer == nullptr)
			return false;

		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) loadGlFunction("glEnableVertexAttribArray");
		if(glEnableVertexAttribArray == nullptr)
			return false;
			
		return true;
	}
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
} //namespace GLHL