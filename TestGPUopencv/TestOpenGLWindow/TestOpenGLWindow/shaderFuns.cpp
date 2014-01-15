//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-01-15											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	shaderFuns


#include "loaderOpenGLExtensions.h"
#include "shaderFuns.h"

#include <cassert>

using namespace GLHL;
using namespace shadersGL;
//---------------------------------------------------------------------------
// This function is used to create the shader object. It's loaded from a 
// source and then is compiled.
GLuint LoadShader(GLenum _type, const char* _shaderSrc){
	// Externally, both shader and compiled shader are index to an internal reference.
	GLuint shader;
	GLint isShaderCompiled;

	// Create the shader object
	shader = OpenGLExtensions::glCreateShader(_type);
	if(!shader)
		return 0; // Check if the shader was created properlly.

	// Load the shader from the source.
	OpenGLExtensions::glShaderSource(shader, 1, &_shaderSrc, NULL);

	// Compile the shader.
	OpenGLExtensions::glCompileShader(shader);

	// Check if compiled properlly.
	OpenGLExtensions::glGetShaderiv(shader, GL_COMPILE_STATUS, &isShaderCompiled);

	if(!isShaderCompiled){
		GLint infoLen = 0;

		OpenGLExtensions::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1){
			char* infoLog = new char[infoLen];

			OpenGLExtensions::glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			// infoLog got the error message and can be displayed. 666 TODO: generic display system.
			assert(FALSE);

			delete infoLog;
		}
		OpenGLExtensions::glDeleteShader(shader);
		return 0;
	}

	return shader;
}

//---------------------------------------------------------------------------
bool initShaders(/*666 TODO: parametro de entrada con info de entrada y salida*/){
	GLchar vShaderStr[] = {
		"attribute vec4 vPosition;		\n"
		"void main()					\n"
		"{								\n"
		"	gl_position = vPosition;	\n"
		"}								\n"
	};

	GLchar fShaderStr[] = {
		"precision medium float;					\n"
		"void main()								\n"
		"{											\n"
		"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0)	\n"
		"}											\n"
	};

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint isLinked;

	// Load vertex and fragment shader
	vertexShader = loadShader(GL_VERTEX_SHADER, vShaderStr);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fShaderStr);

	// Create a program object to attach the shaders
	programObject = OpenGLExtensions::glCreateProgram();

	if(!programObject) // Check error
		return FALSE;

	// Attachs the shaders
	OpenGLExtensions::glAttachShader(programObject, vertexShader);
	OpenGLExtensions::glAttachShader(programObject, fragmentShader);

	// Bind vPosition to attribute 0 --> 666 TODO: only because this tutorial, do it generic...
	OpenGLExtensions::glBindAttribLocation(programObject, 0, "vPosition");

	// Link the program
	OpenGLExtensions::glLinkProgram(programObject);

	// Check link status
	OpenGLExtensions::glGetPRogramiv(programObject, GL_LINK_STATUS, &isLinked);

	if(!isLinked){
		GLint infoLen = 0;

		OpenGLExtensions::glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1){
			char* infoLog = new char[infoLen];

			OpenGLExtensions::glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			// infoLog got the error message and can be displayed. 666 TODO: generic display system.
			assert(FALSE);

			delete infoLog;
		}

		OpenGLExtensions::glDeleteProgram(programObject);
		return FALSE;
	}

	// 666 TODO: Habria que guardar ahora el programa en alguna variable de entrada, a�adir variable de entrada etc...

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	return TRUE;

}


//---------------------------------------------------------------------------