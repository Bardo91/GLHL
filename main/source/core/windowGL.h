//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL


#ifndef _GLHL_WINDOWGL_H_
#define _GLHL_WINDOWGL_H_

namespace GLHL {
	class WindowGL{
	public:
		static WindowGL * createWindow(int _width, int _height);

	public:
		virtual void swapBuffers() = 0;

	protected:
		WindowGL();

	protected:
		int width, height;

	};
}	// namespace GLHL.

#endif	// _GLHL_WINDOWGL_H_