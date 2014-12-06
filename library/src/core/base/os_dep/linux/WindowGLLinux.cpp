//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
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
		void WindowGLLinux::peekMessage(){
			XNextEvent(mDpy, &mXev);
        
	        if(mXev.type == Expose) {
				XGetWindowAttributes(mDpy, mWin, &mGwa);
				glViewport(0, 0, mGwa.width, mGwa.height);
	        }
	                
	        else if(mXev.type == KeyPress) {
				glXMakeCurrent(mDpy, None, NULL);
				glXDestroyContext(mDpy, mGlc);
				XDestroyWindow(mDpy, mWin);
				XCloseDisplay(mDpy);
				exit(0);
	        }
		}

		//---------------------------------------------------------------------------------
		void WindowGLLinux::swapBuffers(){
			glXSwapBuffers(mDpy, mWin);
		}


		//---------------------------------------------------------------------------------
		void WindowGLLinux::show(){

		}

		//---------------------------------------------------------------------------------
		void WindowGLLinux::hide(){

		}

		//---------------------------------------------------------------------------------
		void WindowGLLinux::makeCurrent(){
			glXMakeCurrent(mDpy, mWin, mGlc);
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
			GLint fbAtt[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };	// Capabilities that the program needs
			GLXFBConfig *fbConfigs;
			int nConfigs;

			fbConfigs = glXChooseFBConfig(mDpy, DefaultScreen(mDpy), fbAtt, &nConfigs);
			assert(nConfigs != 0);	//	Error there aren't FBConfigs adapted to your needs.

			XVisualInfo *visualInfo = glXGetVisualFromFBConfig(mDpy, fbConfigs[0]);

			if(visualInfo == NULL) {
				std::cout << "No appropriate visual found" << std::endl;
				assert(false);	//	No appropriate visual found.
			} 

			// Create a colormap for the window.
			mCmap = XCreateColormap(mDpy, mRoot, visualInfo->visual, AllocNone);

			// Fill structure with window attributes.
			mSwa.colormap = mCmap;
			mSwa.event_mask = ExposureMask | KeyPressMask;

			// Create a window with previous data.
			mWin = XCreateWindow(mDpy, mRoot, 0, 0, mWidth, mHeight, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &mSwa);

			// Change window's name
			XStoreName(mDpy, mWin, mWndName.c_str());

			// Create the openGL context
			mGlc = glXCreateNewContext(mDpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, GL_TRUE);

			GLXWindow glxWin = glXCreateWindow( mDpy, fbConfigs[0], mWin, NULL );

			// Make the window appears
			XMapWindow(mDpy, mWin);

			glXMakeContextCurrent(mDpy, glxWin, glxWin, mGlc);
			//glXMakeCurrent(mDpy, mWin, mGlc);
			//makeCurrent();

 			glEnable(GL_DEPTH_TEST); 

		}

		//---------------------------------------------------------------------------------
		bool WindowGLLinux::selfDestroy(){
			
			return true;
		}
	}	// namespace GLHL_LINUX
}	// namespace GLHL.

#endif
