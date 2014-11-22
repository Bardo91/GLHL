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
	const enum class eFrameBufferMode {	eRead = GL_READ_FRAMEBUFFER,
										eWrite = GL_DRAW_FRAMEBUFFER,
										eReadWrite = GL_FRAMEBUFFER	};

	class FrameBuffer{
	public:
		FrameBuffer();
		~FrameBuffer();

		operator GLuint() const{ return mBufferId; };

		void attachTexture(const Texture &_tex);
		void use();

	private:
		void bind();

		void checkErrors();

	private:
		std::vector<std::pair<unsigned, const Texture &>> mAttachments;

		GLuint mBufferId;
	};
}	//	namespace GLHL

#endif	//	_GLHL_CORE_BASE_FRAMEBUFFER_H_