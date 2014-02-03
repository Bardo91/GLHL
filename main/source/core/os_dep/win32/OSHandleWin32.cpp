//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//


#include "OSHandleWin32.h"


namespace GLHL {
	namespace GLHL_WIN32{
		// static definition.
		HINSTANCE OSHandleWin32::mHInstance = NULL;
		GLboolean *OSHandleWin32::keys = new GLboolean[256];

		//---------------------------------------------------------------------------------
		LRESULT CALLBACK OSHandleWin32::WndProc(	HWND _hWnd,			// Manejador para la ventana.
													UINT _uMsg,			// Mensaje para la ventana.
													WPARAM _wParam,		// Información adicional del mensaje.
													LPARAM _lParam){		// Información adicional del mensaje.
			switch (_uMsg) {			// Vamos aver que tipo de mensaje hemos recibido.
			case WM_ACTIVATE:			// Si es un mensaje de activación de la ventana.
				//if(!HIWORD(_wParam))	// Vemos el estado de minimización, si es activamos la ventana y si no, la desactivamos.
					//active = TRUE;
				//else
					//active = FALSE;
				return 0;
			case WM_SYSCOMMAND:			// Si interceptamos una señal del sistema.
				switch (_wParam) {
				case SC_SCREENSAVE:		// Empieza el salvapantallas.
				case SC_MONITORPOWER:	// El monitor se pone en powersave.
					return 0;			// evitamos que ocurra.
				}
				break;
			case WM_KEYDOWN:			// Si se presiona una tecla, ponemos su valor en el array a verdadero.
				keys[_wParam] = TRUE;	
				return 0;				// Acabamos.
			case WM_KEYUP:				// Si se levanta una tecla ponemos su valor en el array a falso.
				keys[_wParam] = FALSE;
				return 0;
			case WM_SIZE:				// Si se redimensiona la ventana
				//resizeViewport(LOWORD(_lParam), HIWORD(_lParam));	// Redimensionamos. Extraemos los parámetros LoWord = Width / HiWord = Height.
				return 0;
			}

			return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
		}
		//---------------------------------------------------------------------------------
		HINSTANCE OSHandleWin32::registerWindowClass(){
			if(!mHInstance){
				WNDCLASSA wc;					// en esta variable se almacena la información de nuestra ventana.

				// Configurar la clase de ventana.
				mHInstance = GetModuleHandle(NULL);				// Tomamos una instancia
				wc.style = CS_HREDRAW |CS_VREDRAW | CS_OWNDC;	// Los dos primeros fuerzan  a redibujar cuando la pantalla cambia de resolución, y la tercera crea un DC privado para la ventana, asi no se compartira el DC entre aplicaciones.
				wc.lpfnWndProc = DefWindowProc; //(WNDPROC) WndProc;				// Asignamos el WndProc que estara atento a los mensajes del programa.
				wc.cbClsExtra = 0;								// No extra windows data.
				wc.cbWndExtra = 0;								// No extra windows data.
				wc.hInstance = mHInstance;						// Guardamos la instancia de la ventana
				wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Ponermos el icono estandar.
				wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// Ponermos el icono de raton estandar.
				wc.hbrBackground = NULL;						// Background de la ventana, en este caso da igual ya que vendrá dado por OpenGL.
				wc.lpszMenuName = NULL;							// No vamos a poner menues.
				wc.lpszClassName = "OpenGL";					// Le ponemos un nombre cualquiera a la clase.

				// Vamos a registar la ventana, si algo sale mal, saldrá un menu popup y al clickear ok se cerrara el programa
				if(!RegisterClassA(&wc)){
					MessageBoxA(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
					return NULL;                           // Exit And Return FALSE
				}
			}

			return mHInstance;



		}
		//---------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------
	
		//---------------------------------------------------------------------------------

	}	// namespace GLHL_WIN32
	
}	// namespace GLHL.