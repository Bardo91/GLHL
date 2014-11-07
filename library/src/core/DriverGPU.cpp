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
	// OpenGL interface
	//---------------------------------------------------------------------------
	// --> Shaders
	GLuint createShader(GLenum _shaderType){
		return glCreateShader(_shaderType);
	}
	void shaderSource(GLuint _shader, GLsizei _count, const char **_string, const GLint *_length);
	void compileShader(GLuint _shader);
	void getShaderiv(GLuint _shader, GLenum _pname, GLint *_params);
	void getShaderInfoLog(GLuint _shader, GLsizei _maxLength, GLsizei *_length, char *_infoLog);
	void deleteShader(GLuint _shader);

} //namespace GLHL