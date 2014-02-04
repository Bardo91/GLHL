//// MAIN FILE TO TEST


#include "core/WindowGL.h"
#include "core/DriverGPU.h"
#include "core/FileManager.h"
using namespace GLHL;

#include <fstream>
#include <string>


int main(void){
	MSG msg;				// Windows menssage Structure.
	BOOL done = FALSE;		// Variable to exit loop.

	WindowGL * window = WindowGL::createWindow(640, 480);
	//WindowGL * window2 = WindowGL::createWindow(320, 480);

	DriverGPU * driver = new DriverGPU;

	//driver->initShaders();

	FileManager* fileManager = FileManager::createFileManager();

	std::string vShaderSrc, fShaderSrc;
	std::string vShaderPath = "../source/shaders/vTriangleShader.vertex";
	std::string fShaderPath = "../source/shaders/fTriangleShader.fragment";

	vShaderSrc = fileManager->loadTextFile(vShaderPath);
	fShaderSrc = fileManager->loadTextFile(fShaderPath);
	
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

		driver->drawOnBuffer(640, 480);

		window->swapBuffers();
		//window2->swapBuffers();
	}

	delete window;

	return 0;
}