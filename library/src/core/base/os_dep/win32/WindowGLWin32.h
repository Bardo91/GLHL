//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#if defined(_WIN32)

#ifndef _GLHL_CORE_OSDEP_WIN32_WINDOWWIN32_H_
#define _GLHL_CORE_OSDEP_WIN32_WINDOWWIN32_H_

#include <Windows.h>

namespace GLHL{
	namespace GLHL_WIN32{
		class WindowGLWin32 {
		public:
			WindowGLWin32(std::string _name, int _width, int _height);

		public:
			void peekMessage();
			void swapBuffers();

			void show();
			void hide();

			void makeCurrent();
		private:
			bool initializeWindow();

			bool selfDestroy();

		private:
			int mWidth, mHeight;

			HGLRC mHRC;					// Permanent Rendering Context.			(Conecta las llamadas de OpenGL con el Device Context)
			HDC mHDC;					// Window's device context.				(Conecta la ventana de contexto con el GDI-Graphic device Interface)
			HINSTANCE mHInstance;		// Window's instance of the program.	
			HWND mHWnd;					// Window's handle.						(Manejador de la ventana en windows)

		};
	}	//namespace GLHL_WIN32

	typedef GLHL_WIN32::WindowGLWin32 WindowGLBase;
}	// namespace GLHL


#endif	// _GLHL_CORE_OSDEP_WIN32_WINDOWWIN32_H_

#endif