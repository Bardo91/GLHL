//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#include "DriverGPU.h"

#include <cassert>
#include <iostream>

namespace GLHL{
	//---------------------------------------------------------------------------
	//------------------------- Singleton Interface -----------------------------
	//---------------------------------------------------------------------------

	// Static initialization of DriverGPU's intance
	DriverGPU* DriverGPU::mInstance = nullptr;

	//---------------------------------------------------------------------------
	void DriverGPU::init(){
		if (mInstance == nullptr)
			mInstance = new DriverGPU();

	}

	//---------------------------------------------------------------------------
	DriverGPU* DriverGPU::get(){
		if (mInstance == nullptr)
			init();

		return mInstance;

	}

	//---------------------------------------------------------------------------
	void DriverGPU::end(){
		if (nullptr != mInstance)
			delete mInstance;
	}

	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------
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

		if (!initDriver())
			std::cerr << "Error could not load properly gl functions" << std::endl;

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
	GLuint DriverGPU::createProgram(){
		GLuint program = glCreateProgram();

		if(!program) // Check error
			return FALSE;

		return program;
		
	}
	
	//---------------------------------------------------------------------------
	GLuint DriverGPU::uploadShader(eShaders _shaderType, std::string _shaderSource, GLuint _program){
		
		GLuint shader = loadShader(_shaderType, _shaderSource.c_str());

		if(shader)
			glAttachShader(_program, shader);

		return shader;

	}

	//---------------------------------------------------------------------------
	void DriverGPU::bindAttribute(GLuint _program, GLuint _index, const GLchar* _name){
		glBindAttribLocation(_program, _index, _name);

	}
	//---------------------------------------------------------------------------
	bool DriverGPU::linkProgram(GLuint _program){
		GLint isLinked;

		// Link the mProgram
		glLinkProgram(_program);

		// Check link status
		glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);

		if(isLinked == GL_FALSE){
			GLint infoLen = 0;

			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen > 1){
				char* infoLog = new char[infoLen];

				glGetProgramInfoLog(_program, infoLen, NULL, infoLog);
				// infoLog got the error message and can be displayed. 666 TODO: generic display system.
				assert(FALSE);
				delete infoLog;
			}
			glDeleteProgram(_program);
			return FALSE;
		}
		return TRUE;
	}
	//---------------------------------------------------------------------------

	GLvoid DriverGPU::drawOnBuffer(GLint _width, GLint _height, GLuint _program){
		GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
								-0.5f, -0.5f, 0.0f,
								0.5f, -0.5f, 0.0f};
		glViewport(0, 0, _width, _height);

		glClear(GL_COLOR_BUFFER_BIT);

		GLHL::DriverGPU::glUseProgram(_program);

		// Load vertex Data
		GLHL::DriverGPU::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
		GLHL::DriverGPU::glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
} //namespace GLHL