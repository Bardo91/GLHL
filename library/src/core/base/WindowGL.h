//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL


#ifndef _GLHL_CORE_BASE_WINDOWGL_H_
#define _GLHL_CORE_BASE_WINDOWGL_H_

#if defined(_WIN32)
	#include "os_dep\win32\WindowGLWin32.h"
#endif
#if defined(__linux__)
	#include "os_dep\linux\WindowGLLinux.h"
#endif

#include <string>

namespace GLHL {
	class WindowGL : public WindowGLBase{
	public:
		WindowGL(std::string _name, int _width, int _height) : WindowGLBase(_name, _width, _height) {};

	};
}	// namespace GLHL.

#endif	// _GLHL_CORE_BASE_WINDOWGL_H_