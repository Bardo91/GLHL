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
	class TextureLoader{
	public:
		static unsigned load2dTexture(std::string _texturePath){
			return SOIL_load_OGL_texture(	_texturePath.c_str(),
											SOIL_LOAD_AUTO,
											SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		}
		static void override2dTexture(std::string _texturePath, unsigned &_textureID){
			_textureID = SOIL_load_OGL_texture(	_texturePath.c_str(),
												SOIL_LOAD_AUTO,
												_textureID,
												SOIL_FLAG_DDS_LOAD_DIRECT);
		}

	};

}	//	namespace GLHL

#endif	//	_GLHL_CORE_TEXTURELOADER_H_