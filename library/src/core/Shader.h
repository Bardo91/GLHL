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

#include <gl\GL.h>

namespace GLHL{
	enum eShaders { eVertexShader = GL_VERTEX_SHADER, eFragmentShader = GL_FRAGMENT_SHADER };

	class Shader{
	public:
		Shader(std::string _shaderPath);
		~Shader();

	private:
		bool mIsOpened = false;

	};

}	//	namespace GLHL


#endif
