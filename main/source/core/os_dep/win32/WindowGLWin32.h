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

#include <Windows.h>

namespace GLHL{
	class WindowGLWin32 : public WindowGL{
	public:
		WindowGLWin32(int _width, int _height);

	public:
		void swapBuffers();

	private:
		bool initializeWindow();

		bool selfDestroy();

	private:
		HGLRC hRC;					// Permanent Rendering Context.			(Conecta las llamadas de OpenGL con el Device Context)
		HDC hDC;					// Window's device context.				(Conecta la ventana de contexto con el GDI-Graphic device Interface)
		HINSTANCE hInstance;		// Window's instance of the program.	
		HWND hWnd;					// Window's handle.						(Manejador de la ventana en windows)

	};


}	// namespace GLHL


#endif	// _GLHL_WINDOWWIN32_H_