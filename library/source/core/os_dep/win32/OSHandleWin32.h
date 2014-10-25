//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifdef _WIN32

#ifndef _GLHL_CORE_OSDEP_WIN32_OSHANDLEWIN32_H_
#define _GLHL_CORE_OSDEP_WIN32_OSHANDLEWIN32_H_

#include <Windows.h>
#include <gl/GL.h>
#include <string>

namespace GLHL {
	namespace GLHL_WIN32{
		class OSHandleWin32{	// This class will deal with all Windows OS interface, and messages.
		public:
			static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

			static HINSTANCE registerWindowClass();

		private:
			static HINSTANCE mHInstance;		// Instancia del programa
			static GLboolean *keys;				// Array para las teclas del teclado.

		};	// class OSHandleWin32.
	}	// namespace GLHL_WIN32

}	// namespace GLHL


#endif	//_GLHL_CORE_OSDEP_WIN32_OSHANDLEWIN32_H_
#endif