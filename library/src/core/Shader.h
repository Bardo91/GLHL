//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#ifndef _GLHL_CORE_SHADER_H_
#define _GLHL_CORE_SHADER_H_

#include <string>
#include <cassert>

#include "DriverGPU.h"

#include <gl\GL.h>

namespace GLHL{
	enum eShaderType { eVertexShader = GL_VERTEX_SHADER, eFragmentShader = GL_FRAGMENT_SHADER };

	class Shader{
	public:
		Shader(eShaderType _type, std::string _shaderPath);

	private:
		GLuint mShaderId = NULL;

	private:
		bool compileShader(eShaderType _type, const char* _shaderSrc);

	};

}	//	namespace GLHL


#endif
