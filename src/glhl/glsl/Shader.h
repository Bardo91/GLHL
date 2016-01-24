//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#ifndef _GLHL_CORE_GLSL_SHADER_H_
#define _GLHL_CORE_GLSL_SHADER_H_

#include <string>
#include <cassert>

#include "../base/DriverGPU.h"


namespace GLHL{
	// 666 TODO: safer way with enum class?
	enum eShaderType { eVertexShader = GL_VERTEX_SHADER, eFragmentShader = GL_FRAGMENT_SHADER };


	/** Abstraction of shader code.
	*/
	class Shader{
	public:
		/** \brief Shader constructor: Create a shader of the given type using a text file.
		*	@param _type shader type. Using enum eShaderType (Vertex shader or fragment shader).
		*	@param _shaderPath path to the shader file
		*/
		Shader(eShaderType _type, std::string _shaderPath);

		/** \brief getter of the shader's id
		*/
		operator GLuint() const{ return mShaderId; };

	private:
		GLuint mShaderId = 0;

		bool compileShader(eShaderType _type, const char* _shaderSrc);

	};

}	//	namespace GLHL


#endif	//_GLHL_CORE_GLSL_SHADER_H_
