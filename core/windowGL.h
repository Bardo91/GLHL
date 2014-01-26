	//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-01-18											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	windowGL.h This header contain declaration, variables and structures
//	for creating the main OpenGl window

#ifndef _GLHL_WINDOWGL_H_
#define _GLHL_WINDOWGL_H_

// Including basic libraries depending on the operative system
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef _linux
#endif

#include <cassert>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace GLHL{
	// Abstact classs of windows
	class WindowGL{
	public:			// Public interface.
		WindowGL();							//  Basic Constructor.

		// Funci�n para crear una ventana para OpenGL. This functions depend on the OS
		virtual GLboolean initWindow(char* _title, int _width, int _height, int _bits, bool _fullscreenFlag){ 
			assert(FALSE);
			return false;
		}

		// Dibuja en la ventana. Esta funci�n cambia el buffer de la imagen de la ventana que ya ha sido rellenado por el driver de la GPU
		virtual GLboolean onDraw(){ 
			assert(FALSE);
			return FALSE;
		}

	protected:		// Private members
		// Funci�n para redimensionar el tama�o de la ventana e inicializar al ventana. Esta ser� llamada cada vez que haya un cambio en el tama�o de la ventana, o se pase de fullscreen a screen, etc... (Por esta raz�n, sera inline)
		GLvoid resizeViewport(GLsizei _width, GLsizei _height);

		GLboolean initGL();

		// Funci�n para destruir la ventana adecuadamente. This functions depend on the OS
		virtual GLvoid selfDestroy(){ 
			assert(FALSE);
		}

	protected:
		// Flags y variables varias:
		GLuint width, height;

		GLboolean keys[256];				// Array para las teclas del teclado.
		GLboolean active;			// Flag si no est� o est� minimizada la ventana.
		GLboolean fullscreen;		// Flag para fullscreen o no.

	}; //class windowGL

	inline GLvoid WindowGL::resizeViewport(GLsizei _width, GLsizei _height){
		glViewport(0, 0, _width, _height); // Resetea el viewport actual.
	}

} // namespace GLHL

#endif // _GLHL_WINDOWHL_H_