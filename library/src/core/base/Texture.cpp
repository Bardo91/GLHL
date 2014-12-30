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
	// Static Data initialization
	std::vector<GLuint> Texture::sTexUnitUsed;

	//-----------------------------------------------------------------------------------------------------------------
	// Public interface
	Texture::Texture(unsigned _width, unsigned _height, eTexType _type): mWidth(_width), mHeight(_height), mTexType( (unsigned)_type), mTexUnit(0) {	
		DriverGPU::get()->genTextures(1, &mTexId);
		bind();
		calcChannels();
		
		DriverGPU::get()->texImage2D(GL_TEXTURE_2D, 0, mTexType, _width, _height, 0, mChannelsGL, mChannelTypeGL, nullptr);
		
		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::Texture(unsigned _width, unsigned _height, eTexType _type, unsigned char *data) : mWidth(_width), mHeight(_height), mTexType((unsigned)_type), mTexUnit(0) {
		DriverGPU::get()->genTextures(1, &mTexId);
		bind();

		calcChannels();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		DriverGPU::get()->texImage2D(GL_TEXTURE_2D, 0, mTexType, _width, _height, 0, mChannelsGL, mChannelTypeGL, data);

		mBufferSize = mWidth * mHeight * mChannels;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Texture::Texture(std::string _fileName): mTexUnit(0){
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
		unbind();

	}

	//-----------------------------------------------------------------------------------------------------------------
	void Texture::bind(){
		DriverGPU *driver = DriverGPU::get();

		int maxUnits;	// 666 TODO: performance analysis of calling this every time.
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);
		
		// Get an empty unit slot
		for (GLuint unit = GL_TEXTURE0; unit <= maxUnits + 1; unit++){
			if (std::find(sTexUnitUsed.begin(), sTexUnitUsed.end(), unit) != sTexUnitUsed.end()){
				sTexUnitUsed.push_back(unit);
				mTexUnit = unit;
				break;
			}
		}

		assert(mTexUnit = maxUnits + 1);

		// Bind texture to it
		driver->activeTexture(mTexUnit);
		driver->bindTexture(GL_TEXTURE_2D, mTexId);
	}

	void Texture::unbind(){
		DriverGPU *driver = DriverGPU::get();

		driver->activeTexture(mTexUnit);
		driver->bindTexture(GL_TEXTURE_2D, 0);
		sTexUnitUsed.erase(std::find(sTexUnitUsed.begin(), sTexUnitUsed.end(), mTexUnit));
		mTexUnit = 0;
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void Texture::attachToUniform(GLuint _program, std::string _name){
		DriverGPU *driver = DriverGPU::get();
		GLuint loc = driver->getUniformLocation(_program, _name.c_str());
		driver->setUniform(loc, mTexUnit);
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
	void Texture::calcChannels(){
		switch (mTexType) {
		// RGB
		case GL_RGB8:
		case GL_COMPRESSED_RGB_S3TC_DXT1_ANGLE:
			mTexType = GL_RGB8;
			mChannelsGL = GL_RGB;
			mChannels = 3;
			mChannelTypeGL = GL_UNSIGNED_BYTE;
			break;
		case GL_RGB32F:
			mTexType = GL_RGB32F;
			mChannelsGL = GL_RGB;
			mChannels = 3;
			mChannelTypeGL = GL_FLOAT;
			break;

		// RGBA
		case GL_RGBA8:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE:
			mTexType = GL_RGBA8;
			mChannelsGL = GL_RGBA;
			mChannels = 4;
			mChannelTypeGL = GL_UNSIGNED_BYTE;
			break;
		case GL_RGBA32F:
			mTexType = GL_RGBA32F;
			mChannelsGL = GL_RGBA;
			mChannels = 4;
			mChannelTypeGL = GL_FLOAT;
			break;
		default:
			assert(false);
			break;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
}	//	namespace GLHL