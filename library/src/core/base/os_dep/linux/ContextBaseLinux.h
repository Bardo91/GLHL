//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-22-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#if defined (__linux__)

#ifndef _GLHL_CORE_BASE_OSDEP_LINUX_CONTEXT_BASE_LINUX_H_
#define _GLHL_CORE_BASE_OSDEP_LINUX_CONTEXT_BASE_LINUX_H_

#include <GL/glew.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include <string>

namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	namespace GLHL_LINUX{
		class ContextBaseLinux{
		public:
			ContextBaseLinux();

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

		};	//	class ContextBaseLinux

	}	// namespace GLHL_LINUX

	typedef GLHL_LINUX::ContextBaseLinux ContextBase;

}	//	namespace GLHL

#endif	//	_GLHL_CORE_BASE_OSDEP_LINUX_CONTEXT_BASE_LINUX_H_
#endif	//	__linux__
