//// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>
#include <src/core/TextureLoader.h>

#include <fstream>
#include <string>

using namespace GLHL;
using namespace std;

void drawImage(GLuint _texture);

int main(void){
	MSG msg;				// Windows menssage Structure.
	BOOL done = FALSE;		// Variable to exit loop.
	
	WindowGL * window = WindowGL::createWindow(640, 480);
	
	DriverGPU * driver = DriverGPU::get();

	GLuint texture = TextureLoader::load2dTexture("C:\\Tulips.jpg");

	while(1){
		if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE)){ // Comprobamos si hay algun mensaje esperando en la cola
			if(msg.message == WM_QUIT) // Es un mensaje de cerrar?
				done = TRUE;
			else{
				TranslateMessage(&msg); // Traducimos el mensaje
				DispatchMessage(&msg); // Reenviamos el mensaje, lo despachamos
			}
		}
		
		drawImage(texture);

		window->swapBuffers();
	}

	delete window, driver;

	return 0;
}

void drawImage(GLuint _texture) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 640, 0.0, 480, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 480, 0);
	glTexCoord2f(1, 1); glVertex3f(640, 480, 0);
	glTexCoord2f(1, 0); glVertex3f(640, 0, 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

}