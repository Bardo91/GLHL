//// MAIN FILE TO TEST

#include <fstream>
#include <string>
#include <iostream>
#include <cassert>


#include <GL/glx.h>
#include <X11/Xlib.h>

using namespace std;

void queryEveryConfig(Display *_display);
void queryConfigAttb(Display *_display, const int * _attribs);

int main(void) {
	Display *display = XOpenDisplay(0);
	//int maxScreens = XScreenCount(display);

	std::cout << "Querying FBconfig to create a pbuffer" << std::endl;

	//queryEveryConfig(display);

	const int attribsPbuffer[] = { GLX_DOUBLEBUFFER, 0, GLX_BUFFER_SIZE, 32,
	GLX_RED_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_RED_SIZE, 8,
	GLX_DRAWABLE_TYPE, GLX_PBUFFER, None };

	queryConfigAttb(display, attribsPbuffer);

return 0;
}

//---------------------------------------------------------------------------
void queryEveryConfig(Display *_display) {
	int screen = 0;
	int nElem;
	GLXFBConfig *configs = glXGetFBConfigs(_display, screen, &nElem);

	std::cout << "Configuration available on this screen: " << std::endl;

	std::cout
			<< "ID\t bufSize\t dble\t auxBuff\t rSize\t bSize\t gSize\t aSize\t dSize\t drawType\t visualId "
			<< std::endl;
	for (int i = 0; i < nElem; i++) {
		int value = 0;

		int succes = -1;
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_FBCONFIG_ID,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_BUFFER_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_DOUBLEBUFFER,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_AUX_BUFFERS,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_RED_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_BLUE_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_GREEN_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_ALPHA_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_DEPTH_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_DRAWABLE_TYPE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_VISUAL_ID, &value);
		std::cout << value << "\n";

		assert(succes == 0);
	}
}

//---------------------------------------------------------------------------
void queryConfigAttb(Display *_display, const int * _attribs) {
	int screen = 0;
	int nElem;
	GLXFBConfig *configs = glXChooseFBConfig(_display, screen, _attribs,  &nElem);

	std::cout << "Configuration available on this screen: " << std::endl;

	std::cout
			<< "ID\t bufSize\t dble\t auxBuff\t rSize\t bSize\t gSize\t aSize\t dSize\t drawType\t visualId "
			<< std::endl;
	for (int i = 0; i < nElem; i++) {
		int value = 0;

		int succes = -1;
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_FBCONFIG_ID,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_BUFFER_SIZE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_DOUBLEBUFFER,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_AUX_BUFFERS,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_RED_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_BLUE_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_GREEN_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_ALPHA_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_DEPTH_SIZE, &value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_DRAWABLE_TYPE,
				&value);
		std::cout << value << "\t";
		succes = glXGetFBConfigAttrib(_display, configs[i], GLX_VISUAL_ID, &value);
		std::cout << value << "\n";

		assert(succes == 0);
	}
}
//---------------------------------------------------------------------------
