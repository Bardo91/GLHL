//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL

#include "windowGL.h"

#ifdef _WIN32
	#include "os_dep/win32/WindowGLWin32.h"
//#elif defined(__linux__)
//	#include "os_dep/linux/WindowGLLinux.h"
#endif


namespace GLHL {
	//---------------------------------------------------------------------------------
	WindowGL* WindowGL::createWindow(int _width, int _height){
		#ifdef _WIN32
			return new GLHL_WIN32::WindowGLWin32(_width, _height);
		//#elif defined(__linux__)
		//	return new WindowGLLinux(_width, _height);
		#endif
	}
	//---------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------


}	// namespace GLHL.