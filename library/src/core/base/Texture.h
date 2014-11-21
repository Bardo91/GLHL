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

	enum class eTexType {eRGB = GL_RGB, eRGBA = GL_RGBA};

	class Texture{
	public:
		Texture(unsigned _width, unsigned _height, eTexType _type);
		Texture(std::string _fileName);
		~Texture();

		operator GLuint() const { return mTexId; };

		void saveTexture(std::string _fileName);
		void bind();
	private:
		GLint channels();

		Texture(Texture &_tex);
		Texture(const Texture &_tex);
	private:
		GLuint mTexId;

		GLint mWidth, mHeight, mChannels;
		GLint mTexType;
		
		GLint mBufferSize;


	};

}	//	namespace GLHL


#endif	// _GLHL_CORE_TEXTURE_H_