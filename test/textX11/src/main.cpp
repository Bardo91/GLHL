//// MAIN FILE TO TEST

#include <fstream>
#include <string>
#include <iostream>
#include <cassert>

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

using namespace std;

void showFBConfigs(GLXFBConfig *_configs, int _nElem);
GLXFBConfig* queryEveryConfig(Display *_display);
GLXFBConfig* queryConfigAttb(Display *_display, const int * _attribs);

int main(void) {
	Display *display = XOpenDisplay(NULL);
	//int maxScreens = XScreenCount(display);
	std::cout << "connected to X server" << std::endl;
	static int visualAttribs[] = {None};
    int numberOfFrameBufferConfigurations;
    GLXFBConfig *fbConfigs = glXChooseFBConfig(display, DefaultScreen(display), visualAttribs, &numberOfFrameBufferConfigurations);
    std::cout << "got fbconfigs" << std::endl;
    int pBufferAttribs[] = { GLX_PBUFFER_WIDTH, 32, GLX_PBUFFER_HEIGHT, 32, None};

    GLXContext openGLContext = glXCreateNewContext(display, fbConfigs[0], GLX_RGBA_TYPE, NULL, false);
    std::cout << "created opengl context" << std::endl;
    GLXPbuffer pbuffer = glXCreatePbuffer(display, fbConfigs[0], pBufferAttribs);
	XFree(fbConfigs);
	XSync(display, False);
	if(!glXMakeContextCurrent(display, pbuffer, pbuffer, openGLContext)){
		std::cout << "error with content creation";
		return -1;
	}
	std::cout << "make context current" << std::endl;
	glXMakeCurrent(display, pbuffer, openGLContext);
	std::cout << "make context current?? twice??" << std::endl;

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
