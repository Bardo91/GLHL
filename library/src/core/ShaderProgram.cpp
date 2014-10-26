//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#include "ShaderProgram.h"

namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	ShaderProgram::ShaderProgram(){
		mProgramID = DriverGPU::get()->glCreateProgram();
		assert(mProgramID);

	}

	//-----------------------------------------------------------------------------------------------------------------
	void ShaderProgram::attachShader(Shader _shader){
		DriverGPU::get()->glAttachShader(mProgramID, _shader);
	}

	//-----------------------------------------------------------------------------------------------------------------
	void ShaderProgram::bindAttribute(GLuint _index, const GLchar* _name){
		DriverGPU::get()->glBindAttribLocation(mProgramID, _index, _name);

	}	
	//-----------------------------------------------------------------------------------------------------------------
	bool ShaderProgram::link(){
		GLint isLinked = -1;

		DriverGPU *driver = DriverGPU::get();

		driver->glLinkProgram(mProgramID);

		driver->glGetProgramiv(mProgramID, GL_LINK_STATUS, &isLinked);

		if (GL_FALSE == isLinked){
			GLint infoLen = 0;
			
			driver->glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infoLen);
			
			if (infoLen > 1){
				char* infoLog = new char[infoLen];

				driver->glGetShaderInfoLog(mProgramID, infoLen, NULL, infoLog);
				// infoLog got the error message and can be displayed. 666 TODO: generic display system.
				assert(FALSE);
				delete infoLog;
			}
			driver->glDeleteProgram(mProgramID);

			return false;
		}
		return true;

	}
	//-----------------------------------------------------------------------------------------------------------------


}	//	namespace GLHL