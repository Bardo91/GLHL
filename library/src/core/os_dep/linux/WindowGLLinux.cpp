//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-28											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifdef __linux__

#include "WindowGLLinux.h"

#include <iostream>
#include <cassert>

namespace GLHL {
	namespace GLHL_LINUX{
		//---------------------------------------------------------------------------------
		WindowGLLinux::WindowGLLinux(int _width, int _height){
			mWidth = _width;
			mHeight = _height;

			initializeX();

			initializeWindow();
		}
		//---------------------------------------------------------------------------------
		void WindowGLLinux::swapBuffers(){
			glXSwapBuffers(mDpy, mWin);
		}

		//---------------------------------------------------------------------------------
		void WindowGLLinux::initializeX(){
			 mDpy = XOpenDisplay(NULL);	// Null means that the graphical output will be send to this same computer.
 	
 			if(mDpy == NULL) {
				std::cout << "cannot connect to X server" << std::endl;
				assert(false);	// Cant connect to X server.
			}

			mRoot = DefaultRootWindow(mDpy);	// Handle to the root window.

		}

		//---------------------------------------------------------------------------------
		void WindowGLLinux::initializeWindow(){
			mVi = glXChooseVisual(mDpy, 0, mAtt);	// Select visual adapted to our needs ("mAtt").

			if(mVi == NULL) {
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

			// Make the window apperas
			XMapWindow(mDpy, mWin);

			// Change window's name
			XStoreName(mDpy, mWin, mWndName.c_str());

			// Create the openGL context
			mGlc = glXCreateContext(mDpy, mVi, NULL, GL_TRUE);	// Last parameter set direct rendering direct
 			glXMakeCurrent(mDpy, mWin, mGlc);

 			glEnable(GL_DEPTH_TEST); 

		}

		//---------------------------------------------------------------------------------
		bool WindowGLLinux::selfDestroy(){
			
			return true;
		}
	}	// namespace GLHL_LINUX
}	// namespace GLHL.

#endif
