//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL

#ifndef _GLHL_CORE_BASE_PIXELBUFFER_H_
#define _GLHL_CORE_BASE_PIXELBUFFER_H_
#if defined(_WIN32)
#endif
#if defined(__linux__)
#endif

class PixelBufferGL : public PixelBufferGLBase{
public:
	PixelBufferGL(unsigned _width, unsigned _height) : PixelBufferBaseGL(_width, _height){};

};

#endif	//	_GLHL_CORE_BASE_PIXELBUFFER_H_