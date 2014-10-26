//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#include "Shader.h"
#include "DriverGPU.h"

#include <fstream>

using namespace std;

namespace GLHL{
	//-------------------------------------------------------------
	Shader::Shader(eShaderType _type, string _shaderPath){
		ifstream shaderFile(_shaderPath);

		if (shaderFile.is_open()){
			string shaderSrc(istreambuf_iterator<char>(shaderFile), (istreambuf_iterator<char>()));

			compileShader(_type, shaderSrc.c_str());

		}
	}

	//-------------------------------------------------------------
	bool Shader::compileShader(eShaderType _type, const char* _shaderSrc){
		{
			// Externally, both shader and compiled shader are index to an internal reference.
			GLint isShaderCompiled;

			DriverGPU *driver = DriverGPU::get();

			// Create the shader object
			mShaderId = driver->glCreateShader(_type);
			if (!mShaderId){
				mShaderId = NULL;
				return false; // Check if the shader was created properlly.
			}

			// Load the shader from the source.
			driver->glShaderSource(mShaderId, 1, &_shaderSrc, NULL);

			// Compile the shader.
			driver->glCompileShader(mShaderId);

			// Check if compiled properlly.
			driver->glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &isShaderCompiled);

			if (!isShaderCompiled){
				GLint infoLen = 0;

				driver->glGetShaderiv(mShaderId, GL_INFO_LOG_LENGTH, &infoLen);

				if (infoLen > 1){
					char* infoLog = new char[infoLen];

					driver->glGetShaderInfoLog(mShaderId, infoLen, NULL, infoLog);
					// infoLog got the error message and can be displayed. 666 TODO: generic display system.
					assert(FALSE);

					delete infoLog;
				}
				driver->glDeleteShader(mShaderId);
				return false;
			}

			return isShaderCompiled == GL_TRUE ? true : false;
		}
	}

	//-------------------------------------------------------------

}	//	namespace GLHL