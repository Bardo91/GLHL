//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#ifndef _GLHL_CORE_GLSL_SHADER_PROGRAM_H_
#define _GLHL_CORE_GLSL_SHADER_PROGRAM_H_

#include "../base/DriverGPU.h"
#include "Shader.h"

namespace GLHL{

	/** Abstraction of shader program. Gather shaders and allows it's use easily.
	*/
	class ShaderProgram{
	public:
		/** \brief Shader Program's constructor.
		*/
		ShaderProgram();
		
		/** \brief id getter of the shader program.
		*/
		operator GLuint() const { return mProgramID; };;
	public:
		/** \brief attach given shader to the program.
		*	@param	_shader shader to be attached.
		*/
		void attachShader(Shader _shader);

		/** \brief bind a vertex attribute with given name to the program
		*	@param _index index of the attribute in OpenGL
		*	@param _name name of the attribute in the shader.
		*/
		void bindAttribute(GLuint _index, const GLchar *_name);

		/** \brief link all the shaders attached to the program.
		*/
		bool link();

		/** \brief execute program. It causes the execution of the pipeline and consequently draw to current buffers.
		*/
		void use();

	private:
		GLuint mProgramID = 0;

	};

}	//	namespace GLHL


#endif	//	_GLHL_CORE_GLSL_SHADER_PROGRAM_H_
