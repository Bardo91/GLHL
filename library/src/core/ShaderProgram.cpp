//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#include "ShaderProgram.h"

#include <iostream>

namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	ShaderProgram::ShaderProgram(){
		mProgramID = DriverGPU::get()->createProgram();
		assert(mProgramID);

	}

	//-----------------------------------------------------------------------------------------------------------------
	void ShaderProgram::attachShader(Shader _shader){
		DriverGPU::get()->attachShader(mProgramID, _shader);
	}

	//-----------------------------------------------------------------------------------------------------------------
	void ShaderProgram::bindAttribute(GLuint _index, const GLchar* _name){
		DriverGPU::get()->bindAttribLocation(mProgramID, _index, _name);

	}	
	//-----------------------------------------------------------------------------------------------------------------
	bool ShaderProgram::link(){
		GLint isLinked = -1;

		DriverGPU *driver = DriverGPU::get();

		driver->linkProgram(mProgramID);

		driver->getProgramiv(mProgramID, GL_LINK_STATUS, &isLinked);

		if (GL_FALSE == isLinked){
			GLint infoLen = 0;
			
			driver->getProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infoLen);
			
			if (infoLen > 1){
				char* infoLog = new char[infoLen];

				driver->getProgramInfoLog(mProgramID, infoLen, NULL, infoLog);
				std::cout << infoLog << std::endl;
				// infoLog got the error message and can be displayed. 666 TODO: generic display system.
				assert(FALSE);
				delete infoLog;
			}
			driver->deleteProgram(mProgramID);

			return false;
		}
		return true;

	}

	//-----------------------------------------------------------------------------------------------------------------
	void ShaderProgram::use(){
		DriverGPU::get()->useProgram(mProgramID);

	}

	//-----------------------------------------------------------------------------------------------------------------

}	//	namespace GLHL