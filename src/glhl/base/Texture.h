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

	/** Class to store and deal with textures.
	*/
	class Texture{
	// Static interface
	private:
		static std::vector<GLuint> sTexUnitUsed;

	// Class interface
	public:
		/** \brief Texture constructor. Create an empty texture:
		*	@param	_width width of texture.
		*	@param	_height	height of texture.
		*	@param	_type texture type defined by eTexType (RGB8, RGB32F, RGBA8, RGBA32F).
		*/
		Texture(unsigned _width, unsigned _height, eTexType _type);

		/** \brief Texture constructor. Create a texture and fill it with the given buffer.
		*	@param	_width width of texture.
		*	@param	_height height of texture.
		*	@param	_type texture type defined by eTexType (RGB8, RGB32F, RGBA8, RGBA32F).
		*	@param	_data pointer to texture data.
		*/
		Texture(unsigned _width, unsigned _height, eTexType _type, unsigned char *_data);

		/** \brief Texture constructor. Load image from a path and store it into a new texture.
		*	@param _fileName path to image file.
		*/
		Texture(std::string _fileName);

		/** \brief Texture destructor. Deinitialize and destroy properly texture:
		*/
		~Texture();

		/** \brief getter of texture id
		*/
		operator GLuint() const { return mTexId; };

		/** \brief bind texture. Set texture as the active one in the fixed pipeline.
		*/
		void bind();
		
		/** \brief unbind texture.
		*/
		void unbind();

		/** \brief Attach texture to a uniform inside the given program
		*	@param	_program shader program where is the uniform to link the texture
		*	@param	_name name of the uniform inside the shader program
		*/
		void attachToUniform(GLuint _program, std::string _name);

		/** \brief Save the texture
		*	@param _fileName path of the file to be stored.
		*/
		void saveTexture(std::string _fileName);

	public:
		/** \brief Return width of texture.
		*/
		unsigned width()	const { return mWidth; };

		/** \brief Return height of texture.
		*/
		unsigned height()	const { return mHeight; };

		/** \brief Return number of channels of texture.
		*/
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