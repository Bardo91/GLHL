//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-14											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#include "Texture.h"

#include <assert.h>

#include <SOIL.h>

namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	// Public interface
	Texture::Texture(){
		DriverGPU::get()->genTextures(1, &mTexId);
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::Texture(std::string _fileName){
		mTexId = SOIL_load_OGL_texture(	_fileName.c_str(),
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::~Texture(){
		DriverGPU::get()->deleteTextures(1, &mTexId);
	}

	//-----------------------------------------------------------------------------------------------------------------
	void Texture::saveTexture(std::string _fileName){
		 
		//unsigned char *buffer = new unsigned char[mWidth * mHeight * mChannels];
		//
		//DriverGPU::get()->readPixels(0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer);
		//
		//SOIL_save_image("img.bmp", SOIL_SAVE_TYPE_BMP, mWidth, mHeight, mChannels, buffer);
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Private interface
	void Texture::use(){

	}

	//-----------------------------------------------------------------------------------------------------------------

}	//	namespace GLHL