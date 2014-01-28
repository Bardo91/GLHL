//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-01-27											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#include "WindowGLWin32.h"


namespace GLHL{
	//---------------------------------------------------------------------------------
	WindowGLWin32::WindowGLWin32(){
		int PixelFormat;				// Holds the results after searching for a Match.

		WNDCLASSA wc;					// en esta variable se almacena la informaci�n de nuestra ventana.
		DWORD dwExStyle;				// Estilo extendido de la ventana.
		DWORD dwStyle;					// Estilo normal de la ventana.

		RECT windowRect;
		windowRect.left = (long) 0;
		windowRect.right = (long) width;
		windowRect.top = (long) 0;
		windowRect.bottom = (long) height;


		// Configurar la clase de ventana.
		hInstance = GetModuleHandle(NULL);				// Tomamos una instancia para nuestra ventana.
		wc.style = CS_HREDRAW |CS_VREDRAW | CS_OWNDC;	// Los dos primeros fuerzan  a redibujar cuando la pantalla cambia de resoluci�n, y la tercera crea un DC privado para la ventana, asi no se compartira el DC entre aplicaciones.
		// 666 TODO: wc.lpfnWndProc = (WNDPROC) WndProc;				// Asignamos el WndProc que estara atento a los mensajes del programa.
		wc.cbClsExtra = 0;								// No extra windows data.
		wc.cbWndExtra =0;								// No extra windows data.
		wc.hInstance = hInstance;						// Guardamos la instancia de la ventana
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Ponermos el icono estandar.
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// Ponermos el icono de raton estandar.
		wc.hbrBackground = NULL;						// Background de la ventana, en este caso da igual ya que vendr� dado por OpenGL.
		wc.lpszMenuName = NULL;							// No vamos a poner menues.
		wc.lpszClassName = "OpenGL";					// Le ponemos un nombre cualquiera a la clase.

		// Vamos a registar la ventana, si algo sale mal, saldr� un menu popup y al clickear ok se cerrara el programa
		if(!RegisterClassA(&wc)){
			MessageBoxA(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);
		}

		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style

		// Ajusta la ventana.
		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

		if(!(hWnd = CreateWindowExA(dwExStyle,								// Estilo extendido para la ventana.
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
									hInstance,								// Instancia de la ventana
									NULL))){									// Ningun par�metro para WM_CREATE.
			selfDestroy(); //Reset the display
			MessageBoxA(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);
		}

		// el PIXELFORMATDESCRIPTOR le dice a windows como queremos mostrar los pixeles
		static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),		// tama�o del descriptor.
			1,									// version  del descriptor.
			PFD_DRAW_TO_WINDOW |				// el formato debe sorportar ventana.
			PFD_SUPPORT_OPENGL |				// el formato debe soportar opengl.
			PFD_DOUBLEBUFFER,					// debe soportar doble buffering.
			PFD_TYPE_RGBA,						// formato en RGBA.
			bits,								// selecciona el color del fondo.
			0, 0, 0, 0, 0, 0,					// Color bits ignored.
			0,									// Sin buffer para alpha.
			0,									// Shift Bit ignorado.
			0,									// Sin buffer de acumulaci�n.
			0, 0, 0, 0,							// Bit de acumulaci�n ignorado.
			16,									// 16 bits para el Z-buffer  (buffer de profundidad).
			0,									// No stencil buffer.
			0,									// No auxiliary buffer.
			PFD_MAIN_PLANE,						// capa principal de dibujo.
			0,									// Se pone como reservado.
			0, 0, 0 };							// se ignoran las mascaras de capas.

		if (!(hDC=GetDC(hWnd))){					// Did We Get A Device Context?
			selfDestroy();                         // Reset The Display
			MessageBoxA(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);							// Return FALSE
		} if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd))){	// Did Windows Find A Matching Pixel Format?
			selfDestroy();                         // Reset The Display
			MessageBoxA(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);                           // Return FALSE
		} if(!SetPixelFormat(hDC,PixelFormat,&pfd)){// Are We Able To Set The Pixel Format?
			selfDestroy();                         // Reset The Display
			MessageBoxA(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);							// Return FALSE
		} if (!(hRC=wglCreateContext(hDC))){		// Are We Able To Get A Rendering Context?
			selfDestroy();							// Reset The Display
			MessageBoxA(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);							// Return FALSE
		} if(!wglMakeCurrent(hDC,hRC)){				// Try To Activate The Rendering Context
			selfDestroy();                         // Reset The Display
			MessageBoxA(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			assert(false);                           // Return FALSE
		}

		// Una vez que todo ha funcionado hasta aqui y hemos creado la ventana es hora de visualizarla, ponerla como activa, darle prioridad poniendola de tipo foreground y redimensionandola a los tama�os dados

		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);

	}
	//---------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------
	void WindowGLWin32::selfDestroy(){
		if(hRC){ // Si tenemos un contexto de renderizado
			if(!wglMakeCurrent(NULL,NULL)){ // Comprobamos si podemos librerar el Device context y el render context.
				MessageBoxA(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			}
			if(!wglDeleteContext(hRC)){ // Podemos eliminar el render context?
				MessageBoxA(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
				}
			hRC=NULL;                           // Set RC To NULL
		}

		// Intentamos liberar ahora el device context
		if(hDC && !ReleaseDC(hWnd, hDC)){				// Podemos liberar el device context?
			MessageBoxA(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hDC=NULL;									// Set DC To NULL
		}

		// Ahora toca cerrar la ventana
		if (hWnd && !DestroyWindow(hWnd)){				// Are We Able To Destroy The Window?
			MessageBoxA(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hWnd=NULL;									// Set hWnd To NULL
		}

		// Por ultimo hay que "desregistar" la clase de ventana y asi podremos borrar adecuadamente la misma para poder reabrirla m�s tarde.
		if (!UnregisterClassA("OpenGL",hInstance)){		// Are We Able To Unregister Class
			MessageBoxA(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hInstance=NULL;								// Set hInstance To NULL
		}
	}
	//---------------------------------------------------------------------------------



}	// namespace GLHL