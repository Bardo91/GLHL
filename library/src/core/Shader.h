//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#ifndef _GLHL_CORE_SHADER_H_
#define _GLHL_CORE_SHADER_H_

#include <string>
#include <cassert>

#include "DriverGPU.h"


namespace GLHL{
	enum eShaderType { eVertexShader = GL_VERTEX_SHADER, eFragmentShader = GL_FRAGMENT_SHADER };

	class Shader{
	public:
		Shader(eShaderType _type, std::string _shaderPath);

		operator GLuint() const{ return mShaderId; };

	private:
		GLuint mShaderId = 0;

		bool compileShader(eShaderType _type, const char* _shaderSrc);

	};

}	//	namespace GLHL


#endif
