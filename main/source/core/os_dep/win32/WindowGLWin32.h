//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-27											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_WINDOWGLWIN32_H_
#define _GLHL_WINDOWGLWIN32_H_

#include <Windows.h>

#include "../../WindowGL.h"

namespace GLHL {
	class WindowGLWin32: public WindowGL{
	public:
		WindowGLWin32();			// Basic Constructor
	
	public:
		HDC getHDC() const;

	private:
		void selfDestroy();

	private:
		HGLRC hRC;					// Permanent Rendering Context. (Conecta las llamadas de OpenGL con el Device Context)
		HDC hDC;					// Device Context. (Conecta la ventana de contexto con el GDI-Graphic device Interface)
		HWND hWnd;					// Handle window. (Manejador de la ventana en windows)
		HINSTANCE hInstance;		// Instancia de la ventana del programa.
	};
	
}	// namespace GLHL


#endif	// _GLHL_WINDOWGLWIN32_H_
