//// MAIN FILE TO TEST

#include <fstream>
#include <string>
#include <iostream>
#include <cassert>

#include <GL/glx.h>
#include <X11/Xlib.h>

using namespace std;

void showFBConfigs(GLXFBConfig *_configs, int _nElem);
GLXFBConfig* queryEveryConfig(Display *_display);
GLXFBConfig* queryConfigAttb(Display *_display, const int * _attribs);

int main(void) {
	Display *display = XOpenDisplay(0);
	//int maxScreens = XScreenCount(display);

	std::cout << "Querying FBconfig to create a pbuffer" << std::endl;

	//queryEveryConfig(display);

	int attribsPbuffer[] = { GLX_DOUBLEBUFFER, 0, GLX_BUFFER_SIZE, 32,
	GLX_RED_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_RED_SIZE, 8,
	GLX_DRAWABLE_TYPE, GLX_PBUFFER, None };

	GLXFBConfig *configs = queryConfigAttb(display, attribsPbuffer);

	// Creating Pbuffer
	GLXPbuffer pbuffer = glXCreatePbuffer(display, configs[1], nullptr);

	GLXContext contextpbuffer = glXCreateNewContext(display, configs[1],
			GLX_RGBA_TYPE, NULL, true);

	if (glXMakeContextCurrent(display, pbuffer, pbuffer, contextpbuffer)) {
		std::cout << "Current context is a pbuffer" << std::endl;

	}

	// Creating Pixmap
	//XVisualInfo * visualInfo = glXChooseVisual(display, 0, attribsPbuffer);
	//Pixmap pixmap = XCreatePixmap(display, 640, 640, 480, 32);
	//GLXPixmap pixmap = glXCreatePixmap(display, configs[1], pixmap, nullptr);

	// Creating Window
	int attribsWindow[] = { GLX_DOUBLEBUFFER, 1, GLX_BUFFER_SIZE, 32,
	GLX_RED_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_RED_SIZE, 8,
	GLX_DRAWABLE_TYPE, GLX_WINDOW, None };


	XVisualInfo visual = glXChooseVisual(display, 0, attribsWindow);
	Window rootWnd = XRootWindow(display, 0);
	Window window = XCreateWindow(	display,		// X display
									rootWnd, 		// parent window
									0, 0, 640,480,	// X, Y, width, and height,
									0,				// Border width
									32,				//depth
									InputOutput,		// type
									visual.visual,
									0,
									attrib);


	GLXWindow = glXCreateWindow(display, configWnd, window, attribsWindow);

	// END
	return 0;
}

//---------------------------------------------------------------------------
void showFBConfigs(Display *_display, GLXFBConfig *_configs, int _nElem) {
	std::cout
			<< "ID\t bufSize\t dble\t auxBuff\t rSize\t bSize\t gSize\t aSize\t dSize\t drawType\t visualId "
			<< std::endl;
	for (int i = 0; i < _nElem; i++) {
		int value = 0;

		int succes = -1;
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_FBCONFIG_ID,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_BUFFER_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_DOUBLEBUFFER,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_AUX_BUFFERS,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_RED_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_BLUE_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_GREEN_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_ALPHA_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_DEPTH_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_DRAWABLE_TYPE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, _configs[i], GLX_VISUAL_ID,
				&value);
		std::cout << value << "\n";

		assert(succes == 0);
	}

}

//---------------------------------------------------------------------------
GLXFBConfig* queryEveryConfig(Display *_display) {
	int screen = 0;
	int nElem;
	GLXFBConfig *configs = glXGetFBConfigs(_display, screen, &nElem);

	showFBConfigs(_display, configs, nElem);
	return configs;
}

//---------------------------------------------------------------------------
GLXFBConfig* queryConfigAttb(Display *_display, const int * _attribs) {
	int screen = 0;
	int nElem;
	GLXFBConfig *configs = glXChooseFBConfig(_display, screen, _attribs, &nElem);

	showFBConfigs(_display, configs, nElem);

	return configs;
}
//---------------------------------------------------------------------------
