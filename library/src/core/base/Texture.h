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
#include <map>

namespace GLHL{

	enum class eTexType { eRGB8 = GL_RGB8, eRGB32F = GL_RGB32F, eRGBA8 = GL_RGBA8, eRGBA32F = GL_RGBA32F };

	class Texture{
	// Static interface
	private:
		static std::vector<GLuint> sTexUnitUsed;

	// Class interface
	public:
		Texture(unsigned _width, unsigned _height, eTexType _type);
		Texture(unsigned _width, unsigned _height, eTexType _type, unsigned char *data);
		Texture(std::string _fileName);
		~Texture();

		operator GLuint() const { return mTexId; };

		void bind();
		void unbind();

		void attachToUniform(GLuint _program, std::string _name);

		void saveTexture(std::string _fileName);

	public:
		unsigned width()	const { return mWidth; };
		unsigned height()	const { return mHeight; };
		unsigned channels()	const { return mChannels; };

	private:
		void calcChannels();

		Texture(Texture &_tex);
	private:
		GLuint mTexId;
		GLint mTexUnit;

		GLint mWidth, mHeight, mChannels;

		GLint mChannelTypeGL;
		GLint mChannelsGL;
		GLint mTexType;
		
		GLint mBufferSize;


	};

}	//	namespace GLHL


#endif	// _GLHL_CORE_BASE_TEXTURE_H_