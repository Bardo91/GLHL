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
		// --> Shaders
		glCreateShader				= nullptr;
		glShaderSource				= nullptr;
		glCompileShader				= nullptr;
		glGetShaderiv				= nullptr;
		glGetShaderInfoLog			= nullptr;
		glDeleteShader				= nullptr;

		// --> Vertex shader
		glGetUniformLocation		= nullptr;
		glUniform1f					= nullptr;
		glUniform2f					= nullptr;
		glUniform3f					= nullptr;
		glUniform4f					= nullptr;
		glUniform1i					= nullptr;
		glUniform2i					= nullptr;
		glUniform3i					= nullptr;
		glUniform4i					= nullptr;
		glUniformMatrix2fv			= nullptr;
		glUniformMatrix3fv			= nullptr;
		glUniformMatrix4fv			= nullptr;

		// --> Fragment Shader
		glBindFragDataLocation		= nullptr;

		// --> Textures
		glActiveTexture				= nullptr;
		glBindTexture				= nullptr;
		glBindSampler				= nullptr;

		// --> Program
		glCreateProgram				= nullptr;
		glAttachShader				= nullptr;
		glBindAttribLocation		= nullptr;
		glLinkProgram				= nullptr;
		glGetProgramiv				= nullptr;
		glGetProgramInfoLog			= nullptr;
		glDeleteProgram				= nullptr;
		glUseProgram				= nullptr;

		// --> Vertex
		glVertexAttribPointer		= nullptr;
		glEnableVertexAttribArray	= nullptr;

		// --> Memory
		glGenBuffers				= nullptr;
		glBindBuffer				= nullptr;
		glBufferData				= nullptr;

		if (!initDriver())
			std::cerr << "Error could not load properly gl functions" << std::endl;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
	//---------------------------------------------------------------------------
	GLboolean DriverGPU::initDriver(){
		//---------------------------------------------------------------------------
		// --> Shaders
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

		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)loadGlFunction("glGetUniformLocation");
		if (glGetUniformLocation == nullptr)
			return false;

		glUniform1f = (PFNGLUNIFORM1FPROC)loadGlFunction("glUniform1f");
		if (glUniform1f == nullptr)
			return false;

		glUniform2f = (PFNGLUNIFORM2FPROC)loadGlFunction("glUniform2f");
		if (glUniform2f == nullptr)
			return false;

		glUniform3f = (PFNGLUNIFORM3FPROC)loadGlFunction("glUniform3f");
		if (glUniform3f == nullptr)
			return false;

		glUniform4f = (PFNGLUNIFORM4FPROC)loadGlFunction("glUniform4f");
		if (glUniform4f == nullptr)
			return false;

		glUniform1i = (PFNGLUNIFORM1IPROC)loadGlFunction("glUniform1i");
		if (glUniform1i == nullptr)
			return false;

		glUniform2i = (PFNGLUNIFORM2IPROC)loadGlFunction("glUniform2i");
		if (glUniform2i == nullptr)
			return false;

		glUniform3i = (PFNGLUNIFORM3IPROC)loadGlFunction("glUniform3i");
		if (glUniform3i == nullptr)
			return false;

		glUniform4i = (PFNGLUNIFORM4IPROC)loadGlFunction("glUniform4i");
		if (glUniform4i == nullptr)
			return false;

		glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)loadGlFunction("glUniformMatrix2fv");
		if (glUniformMatrix2fv == nullptr)
			return false;

		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)loadGlFunction("glUniformMatrix3fv");
		if (glUniformMatrix3fv == nullptr)
			return false;

		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)loadGlFunction("glUniformMatrix4fv");
		if (glUniformMatrix4fv == nullptr)
			return false;


		//---------------------------------------------------------------------------
		// --> Fragment Shader
		glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)loadGlFunction("glBindFragDataLocation");
		if (glBindFragDataLocation == nullptr)
			return false;


		//---------------------------------------------------------------------------
		// --> Textures
		glActiveTexture = (PFNGLACTIVETEXTUREPROC)loadGlFunction("glActiveTexture");
		if (glActiveTexture == nullptr)
			return false;

		glBindTexture = (PFNGLBINDTEXTUREEXTPROC)loadGlFunction("glBindTexture");
		if (glBindTexture == nullptr)
			return false;

		glBindSampler = (PFNGLBINDSAMPLERPROC)loadGlFunction("glBindSampler");
		if (glBindSampler == nullptr)
			return false;

		//---------------------------------------------------------------------------
		// --> Programs
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
		
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)loadGlFunction("glGetAttribLocation");
		if (glGetAttribLocation == nullptr)
			return false;

		//---------------------------------------------------------------------------
		// --> Vertex
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) loadGlFunction("glVertexAttribPointer");
		if(glVertexAttribPointer == nullptr)
			return false;

		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) loadGlFunction("glEnableVertexAttribArray");
		if(glEnableVertexAttribArray == nullptr)
			return false;
			
		//---------------------------------------------------------------------------
		// --> Memory
		glGenBuffers = (PFNGLGENBUFFERSPROC)loadGlFunction("glGenBuffers");
		if (glGenBuffers == nullptr)
			return false;

		glBindBuffer = (PFNGLBINDBUFFERPROC)loadGlFunction("glBindBuffer");
		if (glBindBuffer == nullptr)
			return false;

		glBufferData = (PFNGLBUFFERDATAPROC)loadGlFunction("glBufferData");
		if (glBufferData == nullptr)
			return false;

		//---------------------------------------------------------------------------
		return true;
	}

	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
} //namespace GLHL