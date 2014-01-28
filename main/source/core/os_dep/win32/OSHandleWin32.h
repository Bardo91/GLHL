//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifndef _GLHL_OSDEP_WIN32_OSHANDLEWIN32_H_
#define _GLHL_OSDEP_WIN32_OSHANDLEWIN32_H_

#include <Windows.h>
#include <gl/GL.h>

namespace GLHL {
	class OSHandleWin32{	// This class will deal with all Windows OS interface, and messages.
	public:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		static HINSTANCE registerWindowClass();

	private:
		static HINSTANCE mHInstance;		// Instancia del programa
		static GLboolean *keys;				// Array para las teclas del teclado.

	};	// class OSHandleWin32.


}	// namespace GLHL


#endif	//_GLHL_OSDEP_WIN32_OSHANDLEWIN32_H_