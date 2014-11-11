//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_FRAMEBUFFER_H_
#define _GLHL_CORE_FRAMEBUFFER_H_

#include "DriverGPU.h"

namespace GLHL{
	class FrameBuffer{
	public:
		FrameBuffer();
		~FrameBuffer();

		operator GLuint() const{ return mFrameBufferId; };
	private:

		GLuint mFrameBufferId;
	};
}	//	namespace GLHL

#endif	//	_GLHL_CORE_FRAMEBUFFER_H_