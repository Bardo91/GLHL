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
	Texture::Texture(unsigned _width, unsigned _height, eTexType _type): mWidth(_width), mHeight(_height), mTexType( (unsigned)_type) {
		DriverGPU::get()->genTextures(1, &mTexId);
		use();
		DriverGPU::get()->texImage2D(GL_TEXTURE_2D, 0, (unsigned) _type, _width, _height, 0, (unsigned) _type, GL_UNSIGNED_BYTE, NULL);
		mChannels = channels();
		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::Texture(std::string _fileName){
		mTexId = SOIL_load_OGL_texture(	_fileName.c_str(),
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		use();
		DriverGPU::get()->getTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &mWidth);
		DriverGPU::get()->getTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &mHeight);
		DriverGPU::get()->getTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &mTexType);
		mChannels = channels();
		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::~Texture(){
		DriverGPU::get()->deleteTextures(1, &mTexId);
	}

	//-----------------------------------------------------------------------------------------------------------------
	void Texture::saveTexture(std::string _fileName){
		 
		unsigned char *buffer = new unsigned char[mBufferSize];
		
		use();
		DriverGPU::get()->readPixels(0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer);

		SOIL_save_image("img.bmp", SOIL_SAVE_TYPE_BMP, mWidth, mHeight, mChannels, buffer);
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Private interface
	void Texture::use(){
		DriverGPU::get()->bindTexture(GL_TEXTURE_2D, mTexId);
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	GLint Texture::channels(){
		unsigned channels = 0;
		switch (mTexType) {
		case GL_RGB:
		case GL_COMPRESSED_RGB_S3TC_DXT1_ANGLE:
			channels = 3;
			break;
		case GL_RGBA:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE:
			channels = 4;
			break;
		default:
			assert(false);
			break;
		}

		return channels;
	}

	//-----------------------------------------------------------------------------------------------------------------
}	//	namespace GLHL