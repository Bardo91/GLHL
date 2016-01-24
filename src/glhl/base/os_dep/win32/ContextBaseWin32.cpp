//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-25											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#include "ContextBaseWin32.h"
#include "OSHandleWin32.h"

#if defined (_WIN32)

#include <cassert>

namespace GLHL{
	namespace GLHL_WIN32{
		ContextBaseWin32::ContextBaseWin32(){
			mHDC = NULL;
			mHInstance = NULL;
			mHRC = NULL;
			mHWnd = NULL;

			initContext();
		}

		//---------------------------------------------------------------------------------
		void ContextBaseWin32::makeCurrent(){
			if (!wglMakeCurrent(mHDC, mHRC)){				// Try To Activate The Rendering Context
				selfDestroy();                         // Reset The Display
				MessageBoxA(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				assert(false);                           
			}
		}

		//---------------------------------------------------------------------------------
		bool ContextBaseWin32::initContext(){
			int PixelFormat;				// Holds the results after searching for a Match.

			DWORD dwExStyle;				// Estilo extendido de la ventana.
			DWORD dwStyle;					// Estilo normal de la ventana.

			RECT windowRect;
			windowRect.left = (long)0;
			windowRect.right = (long)640;	// Choose window size 666 TODO template?
			windowRect.top = (long)0;
			windowRect.bottom = (long)480;


			// 666 TODO: SOLO HAY QUE REGISTAR LA CLASE UNA SOLA VEZ, CREAR UNA FUNCIÖN ESTATICA QUE SE ENCARGUE DE ESTO YLO LO HAGA UNA VEZ.
			mHInstance = OSHandleWin32::registerWindowClass();

			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
			dwStyle = WS_OVERLAPPEDWINDOW;					// Windows Style

			// Ajusta la ventana.
			AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

			if (!(mHWnd = CreateWindowExA(dwExStyle,								// Estilo extendido para la ventana.
				"OpenGL",								// Nombre de la clase de la ventana.
				"OpenGl Window",						// Titulo de la ventana.
				WS_CLIPSIBLINGS |						// Propiedad necesaria para que OpenGL funcione adecuadamente
				WS_CLIPCHILDREN |						// Propiedad necesaria para que OpenGL funcione adecuadamente
				dwStyle,								// Estilo de la ventana
				0, 0,									// Posicion de la ventana
				windowRect.right - windowRect.left,		// Calcula el ancho de la ventana ajustada
				windowRect.bottom - windowRect.top,		// Calcula el alto de la ventana ajustada
				NULL,									// No tiene ventana padre
				NULL,									// No tiene menu
				mHInstance,								// Instancia de la ventana
				NULL))){									// Ningun parámetro para WM_CREATE.
				selfDestroy(); //Reset the display
				MessageBoxA(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;                           // Return FALSE
			}

			// el PIXELFORMATDESCRIPTOR le dice a windows como queremos mostrar los pixeles
			static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),		// tamaño del descriptor.
				1,									// version  del descriptor.
				PFD_DRAW_TO_WINDOW |				// el formato debe sorportar ventana.
				PFD_SUPPORT_OPENGL |				// el formato debe soportar opengl.
				PFD_DOUBLEBUFFER,					// debe soportar doble buffering.
				PFD_TYPE_RGBA,						// formato en RGBA.
				32, //_bits,								// selecciona el color del fondo.
				0, 0, 0, 0, 0, 0,					// Color bits ignored.
				0,									// Sin buffer para alpha.
				0,									// Shift Bit ignorado.
				0,									// Sin buffer de acumulación.
				0, 0, 0, 0,							// Bit de acumulación ignorado.
				24,									// 16 bits para el Z-buffer  (buffer de profundidad).
				0,									// No stencil buffer.
				0,									// No auxiliary buffer.
				PFD_MAIN_PLANE,						// capa principal de dibujo.
				0,									// Se pone como reservado.
				0, 0, 0 };							// se ignoran las mascaras de capas.

			if (!(mHDC = GetDC(mHWnd))){					// Did We Get A Device Context?
				selfDestroy();                         // Reset The Display
				MessageBoxA(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;							// Return FALSE
			} if (!(PixelFormat = ChoosePixelFormat(mHDC, &pfd))){	// Did Windows Find A Matching Pixel Format?
				selfDestroy();                         // Reset The Display
				MessageBoxA(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;                           // Return FALSE
			} if (!SetPixelFormat(mHDC, PixelFormat, &pfd)){// Are We Able To Set The Pixel Format?
				selfDestroy();                         // Reset The Display
				MessageBoxA(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;							// Return FALSE
			} if (!(mHRC = wglCreateContext(mHDC))){		// Are We Able To Get A Rendering Context?
				selfDestroy();							// Reset The Display
				MessageBoxA(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;							// Return FALSE
			}

			makeCurrent();

			//ShowWindow(mHWnd, SW_SHOW);
			//SetForegroundWindow(mHWnd);
			//SetFocus(mHWnd);

			return true;
		}

		//---------------------------------------------------------------------------------
		bool ContextBaseWin32::selfDestroy(){
			if (mHRC){								// Si tenemos un contexto de renderizado
				if (!wglMakeCurrent(NULL, NULL)){		// Comprobamos si podemos librerar el Device context y el render context.
					MessageBoxA(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				if (!wglDeleteContext(mHRC)){		// Podemos eliminar el render context?
					MessageBoxA(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				mHRC = NULL;                           // Set RC To NULL
			}

			// Intentamos liberar ahora el device context
			if (mHDC && !ReleaseDC(mHWnd, mHDC)){				// Podemos liberar el device context?
				MessageBoxA(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				mHDC = NULL;									// Set DC To NULL
			}

			// Ahora toca cerrar la ventana
			if (mHWnd && !DestroyWindow(mHWnd)){				// Are We Able To Destroy The Window?
				MessageBoxA(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				mHWnd = NULL;									// Set hWnd To NULL
			}

			// Por ultimo hay que "desregistar" la clase de ventana y asi podremos borrar adecuadamente la misma para poder reabrirla más tarde.
			if (!UnregisterClassA("OpenGL", mHInstance)){		// Are We Able To Unregister Class
				MessageBoxA(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				mHInstance = NULL;								// Set hInstance To NULL
			}


			return true;
		}

	}	//	namespace GLHL_WIN32
}	//	namespace GLHL


#endif