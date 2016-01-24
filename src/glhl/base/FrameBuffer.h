//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-11											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_BASE_FRAMEBUFFER_H_
#define _GLHL_CORE_BASE_FRAMEBUFFER_H_

#include "DriverGPU.h"
#include "Texture.h"

#include <vector>

namespace GLHL{
	enum eFrameBufferMode {	eRead = GL_READ_FRAMEBUFFER,
							eWrite = GL_DRAW_FRAMEBUFFER,
							eReadWrite = GL_FRAMEBUFFER	};

	/** Abstraction of OpenGL frame buffers. 666 not finished.
	*/
	class FrameBuffer{
	public:
		/** \brief Frame buffer's constructor
		*/
		FrameBuffer();

		/** \brief Frame buffer destructor
		*/
		~FrameBuffer();

		/** \brief getter of the FBO id
		*/
		operator GLuint() const{ return mBufferId; };

		/** \brief attach a texture to the buffer.
		*/
		void attachTexture(const Texture &_tex);

		/** \brief link all attached textures to make GPU to draw on them.
		*/
		void linkAttachments();
		
		//void detachTexture(const Texture &_tex); 666 TODO: generate errors

		/** \brief bind the buffer as the FBO to be draw on.
		*/
		void bind();

		/** \brief un bind the buffer from the draw pipeline.
		*/
		void unbind();

	private:
		void checkErrors();

	private:
		std::vector<std::pair<unsigned, const Texture &>> mAttachments;

		GLuint mBufferId;
	};
}	//	namespace GLHL

#endif	//	_GLHL_CORE_BASE_FRAMEBUFFER_H_