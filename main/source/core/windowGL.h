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

#include "os_dep\win32\WindowGLWin32.h"

namespace GLHL {
	class WindowGL{
	public:
		WindowGL * createWindow();

	public:
		virtual void swapBuffers() = 0;

	protected:
		WindowGL();

	protected:
		int width, height;

	};

	inline WindowGL* WindowGL::createWindow(){
		return new WindowGLWin32();
	}


}	// namespace GLHL.

#endif	// _GLHL_WINDOWGL_H_