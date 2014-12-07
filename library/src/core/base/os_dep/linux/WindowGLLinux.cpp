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
		WindowGLLinux::WindowGLLinux(std::string _name, int _width, int _height){
			mWidth = _width;
			mHeight = _height;
			mName = _name;

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
			// GLX 1.3 Visual info obtainance.
			int nConfigs;
			GLXFBConfig *fbConfigs = glXChooseFBConfig(mDpy, DefaultScreen(mDpy), mAtt, &nConfigs);
			assert(nConfigs != 0);	// There aren't Frame Buffer configs adapted to your needs.
			
			mVi = glXGetVisualFromFBConfig( mDpy, fbConfigs[0] );	// Using the first fbconfig.
		
			//mVi = glXChooseVisual(mDpy, 0, mAtt);	// Select visual adapted to our needs ("mAtt").

			if(mVi == NULL) {
				std::cout << "No appropriate visual found" << std::endl;
				assert(false);	//	No appropriate visual found.
			} 
			std::cout << "visual " << ((void *)mVi->visualid) << " selected" << std::endl;

			mRoot = RootWindow(mDpy, mVi->screen);

			// Fill structure with window attributes.
			mSwa.border_pixel = 0;
			mSwa.event_mask = StructureNotifyMask;
			mSwa.colormap = XCreateColormap(mDpy, mRoot, mVi->visual, AllocNone);

			int swaMask = CWBorderPixel | CWColormap | CWEventMask;

			// Create a window with previous data.
			mWin = XCreateWindow(mDpy, mRoot, 0, 0, mWidth, mHeight, 0, mVi->depth, InputOutput, mVi->visual, swaMask, &mSwa);	

			// Create a GLX context for OpenGL rendering
			mGlc = glXCreateNewContext( mDpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, True );

			// Make the window apperas
			XMapWindow(mDpy, mWin);

			// Change window's name
			//XStoreName(mDpy, mWin, mName.c_str());

			// Create the openGL context
			//mGlc = glXCreateContext(mDpy, mVi, NULL, GL_TRUE);	// Last parameter set direct rendering direct
			//mGlc = glXCreateNewContext(mDpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, true );
			glXMakeContextCurrent( mDpy, mWin, mWin, mGlc );
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
