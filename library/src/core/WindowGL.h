//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL


#ifndef _GLHL_CORE_WINDOWGL_H_
#define _GLHL_CORE_WINDOWGL_H_

namespace GLHL {
	class WindowGL{
	public:
		static WindowGL * createWindow(int _width, int _height);

	public:
		virtual void peekMessage() = 0;
		virtual void swapBuffers() = 0;

	protected:
		WindowGL(){};

	protected:
		int mWidth, mHeight;

	};
}	// namespace GLHL.

#endif	// _GLHL_CORE_WINDOWGL_H_