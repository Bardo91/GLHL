//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-25											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#include "TextureLoader.h"

namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	unsigned TextureLoader::load2dTexture(std::string _texturePath){
		return SOIL_load_OGL_texture(	_texturePath.c_str(), 
										SOIL_LOAD_AUTO, 
										SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	}

	//-----------------------------------------------------------------------------------------------------------------
	void TextureLoader::override2dTexture(std::string _texturePath, unsigned &_textureID){

	}

	//-----------------------------------------------------------------------------------------------------------------
}	//	namespace GLHL