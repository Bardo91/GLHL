//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-25											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_TEXTURELOADER_H_
#define _GLHL_CORE_TEXTURELOADER_H_

#include <string>
#include <SOIL.h>

namespace GLHL{
	static class TextureLoader{
		static unsigned load2dTexture(std::string _texturePath);
		static void override2dTexture(std::string _texturePath, unsigned &_textureID);

	};

}	//	namespace GLHL

#endif	//	_GLHL_CORE_TEXTURELOADER_H_