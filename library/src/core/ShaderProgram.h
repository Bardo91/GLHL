//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#ifndef _GLHL_CORE_SHADER_PROGRAM_H_
#define _GLHL_CORE_SHADER_PROGRAM_H_

#include "DriverGPU.h"
#include "Shader.h"

#include <gl\GL.h>

namespace GLHL{
	class ShaderProgram{
	public:
		ShaderProgram();
		
	public:
		void attachShader(Shader _shader);
		void bindAttribute(GLuint _index, const GLchar *_name);

		bool link();

	private:
		GLuint mProgramID = NULL;

	};

}	//	namespace GLHL


#endif
