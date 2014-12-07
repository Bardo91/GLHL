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
		WindowGLLinux::WindowGLLinux(std::string _name, int _width, int _height) : mWidth(_width), mHeight(_height), mName(_name) {
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
		void WindowGLLinux::initializeWindow(){
			mDpy = XOpenDisplay(NULL);	// Null means that the graphical output will be send to this same computer.

			if(mDpy == NULL) {
				std::cout << "cannot connect to X server" << std::endl;
				assert(false);	// Cant connect to X server.
			}
			
			GLint fbAtt[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };	// Capabilities that the program needs
			GLXFBConfig *fbConfigs;
			int nConfigs;

			fbConfigs = glXChooseFBConfig(mDpy, DefaultScreen(mDpy), fbAtt, &nConfigs);
			assert(nConfigs != 0);	//	Error there aren't FBConfigs adapted to your needs.

			mVi = glXGetVisualFromFBConfig(mDpy, fbConfigs[0]);

			if(mVi == NULL) {
				std::cout << "No appropriate visual found" << std::endl;
				assert(false);	//	No appropriate visual found.
			} 

			mRoot = RootWindow(mDpy, mVi->screen);

			// Create a colormap for the window.
			mCmap = XCreateColormap(mDpy, mRoot, mVi->visual, AllocNone);

			// Fill structure with window attributes.
			mSwa.colormap = mCmap;
			mSwa.event_mask = ExposureMask | KeyPressMask;
			
			int swaMask = CWColormap | CWEventMask;

			// Create a window with previous data.
			mWin = XCreateWindow(mDpy, mRoot, 0, 0, mWidth, mHeight, 0, mVi->depth, InputOutput, mVi->visual, swaMask, &mSwa);
			
			// Make the window appears
			XMapWindow(mDpy, mWin);
			
			// Change window's name
			XStoreName(mDpy, mWin, mName.c_str());

			// Create the openGL context
			//mGlc = glXCreateNewContext(mDpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, GL_TRUE);
			mGlc = glXCreateContext(mDpy, mVi, NULL, GL_TRUE);
			//GLXWindow glxWin = glXCreateWindow( mDpy, fbConfigs[0], mWin, NULL );

			//glXMakeContextCurrent(mDpy, glxWin, glxWin, mGlc);
			//glXMakeContextCurrent(mDpy, mWin, mWin, mGlc);
			//glXMakeCurrent(mDpy, mWin, mGlc);
			makeCurrent();
			glEnable(GL_DEPTH_TEST); 

		}

		//---------------------------------------------------------------------------------
		bool WindowGLLinux::selfDestroy(){
			
			return true;
		}
	}	// namespace GLHL_LINUX
}	// namespace GLHL.

#endif
