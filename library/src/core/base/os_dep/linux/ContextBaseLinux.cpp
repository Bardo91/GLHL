//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-22-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifdef __linux__

#include "ContextBaseLinux.h"

#include <iostream>

namespace GLHL {
	namespace GLHL_LINUX{
		//---------------------------------------------------------------------------------
		ContextBaseLinux::ContextBaseLinux(){
			initializeX();

			initializeWindow();
		}

		//---------------------------------------------------------------------------------
		void ContextBaseLinux::makeCurrent(){
			glXMakeCurrent(mDpy, mWin, mGlc);
		}

		//---------------------------------------------------------------------------------
		void ContextBaseLinux::initializeX(){
			mDpy = XOpenDisplay(NULL);	// Null means that the graphical output will be send to this same computer.

			if (mDpy == NULL) {
				std::cout << "cannot connect to X server" << std::endl;
				assert(false);	// Cant connect to X server.
			}

			mRoot = DefaultRootWindow(mDpy);	// Handle to the root window.

		}

		//---------------------------------------------------------------------------------
		void ContextBaseLinux::initializeWindow(){
			mVi = glXChooseVisual(mDpy, 0, mAtt);	// Select visual adapted to our needs ("mAtt").

			if (mVi == NULL) {
				std::cout << "No appropriate visual found" << std::endl;
				assert(false);	//	No appropriate visual found.
			}
			std::cout << "visual " << ((void *)mVi->visualid) << " selected" << std::endl;

			// Create a colormap for the window.
			mCmap = XCreateColormap(mDpy, mRoot, mVi->visual, AllocNone);

			// Fill structure with window attributes.
			mSwa.colormap = mCmap;
			mSwa.event_mask = ExposureMask | KeyPressMask;

			// Create a window with previous data.
			mWin = XCreateWindow(mDpy, mRoot, 0, 0, mWidth, mHeight, 0, mVi->depth, InputOutput, mVi->visual, CWColormap | CWEventMask, &mSwa);

			// Change window's name
			XStoreName(mDpy, mWin, mWndName.c_str());

			// Create the openGL context
			mGlc = glXCreateContext(mDpy, mVi, NULL, GL_TRUE);	// Last parameter set direct rendering direct
			
			makeCurrent();

			glEnable(GL_DEPTH_TEST);

		}

		//---------------------------------------------------------------------------------
		bool ContextBaseLinux::selfDestroy(){

			return true;
		}
	}	// namespace GLHL_LINUX
}	// namespace GLHL.



#endif	//	__linux__
