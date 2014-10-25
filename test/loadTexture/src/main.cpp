//// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>
#include <src/core/TextureLoader.h>

#include <fstream>
#include <string>

using namespace GLHL;
using namespace std;

int main(void){
	MSG msg;				// Windows menssage Structure.
	BOOL done = FALSE;		// Variable to exit loop.
	
	WindowGL * window = WindowGL::createWindow(640, 480);
	
	DriverGPU * driver = new DriverGPU;

	ifstream vShaderPath, fShaderPath;
	vShaderPath.open("../../../../library/src/shaders/vTriangleShader.vertex");
	fShaderPath.open("../../../../library/src/shaders/fTriangleShader.fragment");

	string vShaderSrc(istreambuf_iterator<char>(vShaderPath), (istreambuf_iterator<char>()));
	string fShaderSrc(istreambuf_iterator<char>(fShaderPath), (istreambuf_iterator<char>()));
	
	GLuint program = driver->createProgram();
	GLuint vShader = driver->uploadShader(eShaders::eVertexShader, vShaderSrc, program);
	GLuint fShader = driver->uploadShader(eShaders::eFragmentShader, fShaderSrc, program);
	driver->bindAttribute(program, 0, "vPosition");
	bool linked = driver->linkProgram(program);

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

		driver->drawOnBuffer(640, 480, program);

		window->swapBuffers();
	}

	delete window, driver;

	return 0;
}