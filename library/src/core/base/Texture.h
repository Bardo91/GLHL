//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-13											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_BASE_TEXTURE_H_
#define _GLHL_CORE_BASE_TEXTURE_H_

#include "DriverGPU.h"

#include <string>
#include <vector>

namespace GLHL{

	enum class eTexType { eRGB = GL_RGB, eRGB32F = GL_RGB32F, eRGBA = GL_RGBA, eRGBA32F = GL_RGBA32F };

	class Texture{
	public:
		Texture(unsigned _width, unsigned _height, eTexType _type);
		Texture(unsigned _width, unsigned _height, eTexType _type, unsigned char *data);
		Texture(std::string _fileName);
		~Texture();

		operator GLuint() const { return mTexId; };

		void saveTexture(std::string _fileName);
		void bind();
		void unbind();

	public:
		unsigned width()	const { return mWidth; };
		unsigned height()	const { return mHeight; };
		unsigned channels()	const { return mChannels; };

	private:
		void calcChannels();

		Texture(Texture &_tex);
	private:
		GLuint mTexId;

		GLint mWidth, mHeight, mChannels;
		GLint mTexType;
		
		GLint mBufferSize;


	};

}	//	namespace GLHL


#endif	// _GLHL_CORE_BASE_TEXTURE_H_