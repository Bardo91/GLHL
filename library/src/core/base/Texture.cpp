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
		bind();
		DriverGPU::get()->texImage2D(GL_TEXTURE_2D, 0, (unsigned) _type, _width, _height, 0, (unsigned) _type, GL_UNSIGNED_BYTE, nullptr);
		
		calcChannels();
		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::Texture(unsigned _width, unsigned _height, eTexType _type, unsigned char *data) : mWidth(_width), mHeight(_height), mTexType((unsigned)_type) {
		DriverGPU::get()->genTextures(1, &mTexId);
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		DriverGPU::get()->texImage2D(GL_TEXTURE_2D, 0, (unsigned)_type, _width, _height, 0, (unsigned)_type, GL_UNSIGNED_BYTE, data);

		calcChannels();
		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::Texture(std::string _fileName){
		mTexId = SOIL_load_OGL_texture(	_fileName.c_str(),
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		bind();
		DriverGPU::get()->getTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &mWidth);
		DriverGPU::get()->getTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &mHeight);
		DriverGPU::get()->getTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &mTexType);
		
		calcChannels();
		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::~Texture(){
		bind();
		DriverGPU::get()->deleteTextures(1, &mTexId);
		mTexId = 0;
		
	}

	//-----------------------------------------------------------------------------------------------------------------
	void Texture::saveTexture(std::string _fileName){
		 
		unsigned char *buffer = new unsigned char[mBufferSize];
		
		unbind();
		DriverGPU::get()->readPixels(0, 0, mWidth, mHeight, mTexType, GL_UNSIGNED_BYTE, buffer);
		SOIL_save_image(_fileName.c_str(), SOIL_SAVE_TYPE_BMP, mWidth, mHeight, mChannels, buffer);
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Private interface
	void Texture::bind(){
		DriverGPU::get()->bindTexture(GL_TEXTURE_2D, mTexId);
	}

	void Texture::unbind(){
		DriverGPU::get()->bindTexture(GL_TEXTURE_2D, 0);
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void Texture::calcChannels(){
		switch (mTexType) {
		case GL_RGB:
		case GL_RGB32F:
		case GL_COMPRESSED_RGB_S3TC_DXT1_ANGLE:
			mTexType = GL_RGB;
			mChannels = 3;
			break;
		case GL_RGBA:
		case GL_RGBA32F:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE:
			mTexType = GL_RGBA;
			mChannels = 4;
			break;
		default:
			assert(false);
			break;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
}	//	namespace GLHL