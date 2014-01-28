//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//


#ifndef _GLHL_WINDOWWIN32_H_
#define _GLHL_WINDOWWIN32_H_

#include "../../WindowGL.h"

namespace GLHL{
	class WindowGLWin32 : public WindowGL{
	public:
		WindowGLWin32();

	public:
		void swapBuffers();

	private:
		HDC hDC;

	};


}	// namespace GLHL


#endif	// _GLHL_WINDOWWIN32_H_