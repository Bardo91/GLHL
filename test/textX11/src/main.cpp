
//// MAIN FILE TO TEST

#include <fstream>
#include <string>
#include <iostream>
#include <cassert>

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

using namespace std;

void showFBConfigs(Display *_display, GLXFBConfig *_configs, int _nElem);
GLXFBConfig* queryEveryConfig(Display *_display);
GLXFBConfig* queryConfigAttb(Display *_display, const int * _attribs);
void createPbuffer();
void createWindow();
void createWindow2();

int main(void) {
	//createPbuffer();
	createWindow2();
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
void createPbuffer(){
	Display *display = XOpenDisplay(0);
	//int maxScreens = XScreenCount(display);
	if(display == 0)
		assert(false);

	std::cout << "connected to X server" << std::endl;
	static int visualAttribs[] = {None};
	int nElems;
    	GLXFBConfig *fbConfigs = glXChooseFBConfig(display, DefaultScreen(display), visualAttribs, &nElems);
    	std::cout << "got fbconfigs" << std::endl;
    	int pBufferAttribs[] = { GLX_PBUFFER_WIDTH, 32, GLX_PBUFFER_HEIGHT, 32, None};

    	showFBConfigs(display, fbConfigs, nElems);
    	std::cout << "Choose display:" << std::endl;
    	int index = -1;
    	std::cin >> index;

    	GLXContext openGLContext = glXCreateNewContext(display, fbConfigs[index], GLX_RGBA_TYPE, NULL, false);
    	std::cout << "created opengl context" << std::endl;
    	GLXPbuffer pbuffer = glXCreatePbuffer(display, fbConfigs[index], pBufferAttribs);
	XFree(fbConfigs);
	XSync(display, False);
	if(!glXMakeContextCurrent(display, pbuffer, pbuffer, openGLContext)){
		std::cout << "error with content creation";
		assert(false);
	}
	std::cout << "make context current" << std::endl;


}
//---------------------------------------------------------------------------
void createWindow(){
	Display *display = XOpenDisplay(":0.0");
	assert(display != 0);

	std::cout << "Connected to X Server" << std::endl;

	int screen = 0;
	int depth = XDefaultDepth(display, screen);
	Visual *visual = XDefaultVisual(display, screen);

	unsigned long attMask = 0;
	XSetWindowAttributes *att = new XSetWindowAttributes();

	Window wnd = XCreateWindow(	display, 			// Connection to X server
					DefaultRootWindow(display),	// Parent window
					0, 0, 640, 480,			// x, y, width and height
					0,				// Border width
					depth,				// Wnd depth
					InputOutput,			// Window class (inputonly or inputoutput)
					visual,				// Visual type
					attMask,			// Which att are defined
					att);				// Strucure of attributes

	std::cout << "Window created" << std::endl;
	
	XMapWindow(display, wnd);
	
	std::cout << "Mapped window" << std::endl;

	XDestroyWindow(display, wnd);
	delete att;
}

//---------------------------------------------------------------------------
void createWindow2(){
    Display              *dpy;
    Window                xWin;
    XVisualInfo          *vInfo;
    XSetWindowAttributes  swa;
    GLXFBConfig          *fbConfigs;
    GLXContext            context;
    GLXWindow             glxWin;
    int                   swaMask;
    int                   numReturned;

    const int doubleBufferAttributes[] = {None};

    /* Open a connection to the X server */
    dpy = XOpenDisplay( NULL );
    if ( dpy == NULL ) {
        printf( "Unable to open a connection to the X server\n" );
        exit( EXIT_FAILURE );
    }

    /* Request a suitable framebuffer configuration - try for a double 
    ** buffered configuration first */
    fbConfigs = glXChooseFBConfig( dpy, DefaultScreen(dpy),
                                   doubleBufferAttributes, &numReturned );

    /* Create an X colormap and window with a visual matching the first
    ** returned framebuffer config */
    vInfo = glXGetVisualFromFBConfig( dpy, fbConfigs[0] );

    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;
    swa.colormap = XCreateColormap( dpy, RootWindow(dpy, vInfo->screen),
                                    vInfo->visual, AllocNone );

    swaMask = CWBorderPixel | CWColormap | CWEventMask;

    xWin = XCreateWindow( dpy, RootWindow(dpy, vInfo->screen), 0, 0, 256, 256,
                          0, vInfo->depth, InputOutput, vInfo->visual,
                          swaMask, &swa );

    /* Create a GLX context for OpenGL rendering */
    context = glXCreateNewContext( dpy, fbConfigs[0], GLX_RGBA_TYPE,
				 NULL, True );

    /* Create a GLX window to associate the frame buffer configuration
    ** with the created X window */
    glxWin = glXCreateWindow( dpy, fbConfigs[0], xWin, NULL );
    
    /* Map the window to the screen, and wait for it to appear */
    XMapWindow( dpy, xWin );

    /* Bind the GLX context to the Window */
    glXMakeContextCurrent( dpy, glxWin, glxWin, context );

 
}

