//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#include "Shader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace GLHL{
	//-------------------------------------------------------------
	Shader::Shader(eShaderType _type, string _shaderPath){
		ifstream shaderFile(_shaderPath);

		assert(shaderFile.is_open());

		string shaderSrc(istreambuf_iterator<char>(shaderFile), (istreambuf_iterator<char>()));
		compileShader(_type, shaderSrc.c_str());

		
		
	}

	//-------------------------------------------------------------
	bool Shader::compileShader(eShaderType _type, const char* _shaderSrc){
		{
			// Externally, both shader and compiled shader are index to an internal reference.
			GLint isShaderCompiled;

			DriverGPU *driver = DriverGPU::get();

			// Create the shader object
			mShaderId = driver->createShader(_type);
			if (!mShaderId){
				mShaderId = 0;
				return false; // Check if the shader was created properlly.
			}

			// Load the shader from the source.
			driver->shaderSource(mShaderId, 1, &_shaderSrc, NULL);

			// Compile the shader.
			driver->compileShader(mShaderId);

			// Check if compiled properlly.
			driver->getShaderiv(mShaderId, GL_COMPILE_STATUS, &isShaderCompiled);

			if (!isShaderCompiled){
				GLint infoLen = 0;

				driver->getShaderiv(mShaderId, GL_INFO_LOG_LENGTH, &infoLen);

				if (infoLen > 1){
					char* infoLog = new char[infoLen];

					driver->getShaderInfoLog(mShaderId, infoLen, NULL, infoLog);
					std::cout << infoLog << std::endl;
					// infoLog got the error message and can be displayed. 666 TODO: generic display system.
					assert(false);

					delete infoLog;
				}
				driver->deleteShader(mShaderId);
				return false;
			}

			return isShaderCompiled == GL_TRUE ? true : false;
		}
	}

	//-------------------------------------------------------------

}	//	namespace GLHL
