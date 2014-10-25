//// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>

using namespace GLHL;

#include <fstream>
#include <string>


using namespace std;

int main(void){
	MSG msg;				// Windows menssage Structure.
	BOOL done = FALSE;		// Variable to exit loop.

	WindowGL * window = WindowGL::createWindow(640, 480);
	//WindowGL * window2 = WindowGL::createWindow(320, 480);

	DriverGPU * driver = new DriverGPU;

	//driver->initShaders();
	ifstream vShaderPath, fShaderPath;
	vShaderPath.open("../../../../library/src/shaders/vTriangleShader.vertex");
	fShaderPath.open("../../../../library/src/shaders/fTriangleShader.fragment");

	string vShaderSrc(istreambuf_iterator<char>(vShaderPath), (istreambuf_iterator<char>()));
	string fShaderSrc(istreambuf_iterator<char>(fShaderPath), (istreambuf_iterator<char>()));
	
	//driver->compileShader(eShaders::eVertexShader, vShader);
	//driver->compileShader(eShaders::eFragmentShader, fShader);

	//driver->initShaders(vShaderSrc, fShaderSrc);
	GLuint program = driver->createProgram();
	GLuint vShader = driver->uploadShader(eShaders::eVertexShader, vShaderSrc, program);
	GLuint fShader = driver->uploadShader(eShaders::eFragmentShader, fShaderSrc, program);
	driver->bindAttribute(program, 0, "vPosition");
	bool linked = driver->linkProgram(program);


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
		//window2->swapBuffers();
	}

	delete window, driver;

	return 0;
}