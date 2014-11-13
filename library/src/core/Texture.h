//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-13											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_TEXTURE_H_
#define _GLHL_CORE_TEXTURE_H_

#include "DriverGPU.h"

#include <string>

namespace GLHL{
	class Texture{
	public:
		Texture();
		Texture(std::string _fileName);
		~Texture();

		operator GLuint() const { return mTexId; };

		void use();


	private:
		GLuint mTexId;
	};

}	//	namespace GLHL


#endif	// _GLHL_CORE_TEXTURE_H_