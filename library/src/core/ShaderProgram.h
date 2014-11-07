//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#ifndef _GLHL_CORE_SHADER_PROGRAM_H_
#define _GLHL_CORE_SHADER_PROGRAM_H_

#include "DriverGPU.h"
#include "Shader.h"

namespace GLHL{

	class ShaderProgram{
	public:
		ShaderProgram();
		
		operator GLuint() const { return mProgramID; };;
	public:
		void attachShader(Shader _shader);
		void bindAttribute(GLuint _index, const GLchar *_name);

		bool link();

		void use();

	private:
		GLuint mProgramID = 0;

	};

}	//	namespace GLHL


#endif
