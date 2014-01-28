//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-27											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_WINDOWGL_H_
#define _GLHL_WINDOWGL_H_

#include <cassert>

namespace GLHL{
	// Abstact classs of windows
	class WindowGL{
	public:
		static WindowGL* getWindow();		// Get Singletone.

	public:
		void onDraw();						// Draw gl buffer on current screen.

	protected:	// Public interface.
		WindowGL();							// Basic contructor

		static WindowGL *window;			// Singleton

	protected:
		static int width, height;
		static int bits;
		static char* title;
		static bool fullscreenFlag;

	private:
		static void createWindow();
		
	}; //class windowGL


} // namespace GLHL




#endif // _GLHL_WINDOWHL_H_