//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#include "DriverGPU.h"

#include <cassert>

namespace GLHL{
	//---------------------------------------------------------------------------
	DriverGPU::DriverGPU(){
		glCreateShader = nullptr;
		glShaderSource = nullptr;
		glCompileShader = nullptr;
		glGetShaderiv = nullptr;
		glGetShaderInfoLog = nullptr;
		glDeleteShader = nullptr;

		glCreateProgram = nullptr;
		glAttachShader = nullptr;
		glBindAttribLocation = nullptr;
		glLinkProgram = nullptr;
		glGetProgramiv = nullptr;
		glGetProgramInfoLog = nullptr;
		glDeleteProgram = nullptr;
		glUseProgram = nullptr;

		glVertexAttribPointer = nullptr;
		glEnableVertexAttribArray = nullptr;

		initDriver();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
	//---------------------------------------------------------------------------
	GLboolean DriverGPU::initDriver(){
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
	//---------------------- SHADERS -------------------------------------------
	//---------------------------------------------------------------------------
	GLuint DriverGPU::loadShader(GLenum _type, const char* _shaderSrc){
			// Externally, both shader and compiled shader are index to an internal reference.
			GLuint shader;
			GLint isShaderCompiled;

			// Create the shader object
			shader = DriverGPU::glCreateShader(_type);
			if(!shader)
				return 0; // Check if the shader was created properlly.

			// Load the shader from the source.
			DriverGPU::glShaderSource(shader, 1, &_shaderSrc, NULL);

			// Compile the shader.
			DriverGPU::glCompileShader(shader);

			// Check if compiled properlly.
			DriverGPU::glGetShaderiv(shader, GL_COMPILE_STATUS, &isShaderCompiled);

			if(!isShaderCompiled){
				GLint infoLen = 0;

				DriverGPU::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

				if(infoLen > 1){
					char* infoLog = new char[infoLen];

					DriverGPU::glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
					// infoLog got the error message and can be displayed. 666 TODO: generic display system.
					assert(FALSE);

					delete infoLog;
				}
				DriverGPU::glDeleteShader(shader);
				return 0;
			}

			return shader;
		}
	//---------------------------------------------------------------------------
	GLboolean DriverGPU::initShaders(){
		GLchar vShaderStr[] = 
			 "attribute vec4 vPosition; \n"
			 "void main() \n"
			 "{ \n"
			 " gl_Position = vPosition; \n"
			 "} \n";

		GLchar fShaderStr[] = 
			 "void main() \n"
			 "{ \n"
			 " gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
			 "} \n";

		GLuint vertexShader;
		GLuint fragmentShader;
		GLint isLinked;

		// Load vertex and fragment shader
		vertexShader = DriverGPU::loadShader(GL_VERTEX_SHADER, vShaderStr);
		fragmentShader = DriverGPU::loadShader(GL_FRAGMENT_SHADER, fShaderStr);

		// Create a program object to attach the shaders
		program = DriverGPU::glCreateProgram();

		if(!program) // Check error
			return FALSE;

		// Attachs the shaders
		DriverGPU::glAttachShader(program, vertexShader);
		DriverGPU::glAttachShader(program, fragmentShader);

		// Bind vPosition to attribute 0 --> 666 TODO: only because this tutorial, do it generic...
		DriverGPU::glBindAttribLocation(program, 0, "vPosition");

		// Link the program
		DriverGPU::glLinkProgram(program);

		// Check link status
		DriverGPU::glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

		if(!isLinked){
			GLint infoLen = 0;

			DriverGPU::glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen > 1){
				char* infoLog = new char[infoLen];

				DriverGPU::glGetProgramInfoLog(program, infoLen, NULL, infoLog);
				// infoLog got the error message and can be displayed. 666 TODO: generic display system.
				assert(FALSE);

				delete infoLog;
			}

			DriverGPU::glDeleteProgram(program);
			return FALSE;

		}

		// 666 TODO: Habria que guardar ahora el programa en alguna variable de entrada, añadir variable de entrada etc...

		return TRUE;

	}
	//---------------------------------------------------------------------------

	GLvoid DriverGPU::drawOnBuffer(GLint _width, GLint _height, HDC _hDC){
		GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
								-0.5f, -0.5f, 0.0f,
								0.5f, -0.5f, 0.0f};
		glViewport(0, 0, _width, _height);

		glClear(GL_COLOR_BUFFER_BIT);

		GLHL::DriverGPU::glUseProgram(program);

		// Load vertex Data
		GLHL::DriverGPU::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
		GLHL::DriverGPU::glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	//---------------------------------------------------------------------------
} //namespace GLHL