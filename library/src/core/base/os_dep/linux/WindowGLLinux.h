//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifdef __linux__

#ifndef _GLHL_CORE_BASE_OSDEP_LINUX_WINDOWLINUX_H_
#define _GLHL_CORE_BASE_OSDEP_LINUX_WINDOWLINUX_H_

#include "../../WindowGL.h"

#include <GL/glew.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include <string>

namespace GLHL{
	namespace GLHL_LINUX{
		class WindowGLLinux : public WindowGL{
		public:
			WindowGLLinux(int _width, int _height);

		public:
			void peekMessage();
			void swapBuffers();
			
			void show();
			void hide();

			void makeCurrent();
		private:
			void initializeX();
			void initializeWindow();

			bool selfDestroy();

		private:

			std::string mWndName = "Test";

			Display                 *mDpy;
			Window                  mRoot;
			GLint                   mAtt[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };	// Capabilities that the program needs
			XVisualInfo             *mVi;
			Colormap                mCmap;
			XSetWindowAttributes    mSwa;
			Window                  mWin;
			GLXContext              mGlc;
			XWindowAttributes       mGwa;
			XEvent                  mXev;

		};
	}	//namespace GLHL_LINUX
}	// namespace GLHL


#endif	// _GLHL_CORE_OSDEP_LINUX_WINDOWLINUX_H_

#endif
