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
#include <vector>

namespace GLHL{
	class Texture{
	public:
		Texture();
		Texture(std::string _fileName);
		~Texture();

		operator GLuint() const { return mTexId; };

		void saveTexture(std::string _fileName);

	private:
		void use();

		GLuint mTexId;

		unsigned mWidth, mHeight, mChannels;


	};

}	//	namespace GLHL


#endif	// _GLHL_CORE_TEXTURE_H_