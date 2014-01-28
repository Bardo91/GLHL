//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-27											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#include "WindowGL.h"

#ifdef _WIN32
	#include "os_dep\win32\WindowGLWin32.h"
	#include <Windows.h>

#elif _defined(_linux)
	// 666 TODO: include linux related files
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

namespace GLHL {
	//---------------------------------------------------------------------------------
	WindowGL* WindowGL::window = nullptr;	// Static Definition of the singletone of the window.
	GLsizei WindowGL::width = 640;
	GLsizei WindowGL::height = 640;
	int WindowGL::bits = 16;
	bool WindowGL::fullscreenFlag = false;
	char* WindowGL::title = "GLHL";

	//---------------------------------------------------------------------------------
	WindowGL* WindowGL::getWindow(){
		if(!window){
			createWindow();
		}
		return window;
	}

	//---------------------------------------------------------------------------------
	void WindowGL::onDraw(){
		#ifdef _WIN32
			SwapBuffers(static_cast<WindowGLWin32 *>(window)->getHDC());
		#elif _defined(_linux)
			// 666 TODO: linux swapbuffers
		#endif
	}

	//---------------------------------------------------------------------------------
	void WindowGL::createWindow(){
		#ifdef _WIN32
			window = new WindowGLWin32;
		#elif _defined(_linux)
			// 666 TODO: window = new WindowGLLinux();
		#endif
	}


	//---------------------------------------------------------------------------------

}	// namespace GLHL