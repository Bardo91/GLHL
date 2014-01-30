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

	driver->initShaders();

	FileManager* fileManager = FileManager::createFileManager();

	//std::string vShader;
	//const char* vShaderPath = "c:\a.txt";

	//vShader = fileManager->loadTextFile(vShaderPath);
	///

	std::ifstream file("c:\a.txt", std::ifstream::in);
	std::string source, line;

	//file.open(_filePath.c_str(), ifstream::in);

	if(!file.is_open())
		return NULL;
		
	while( getline(file, line) ){
		source += line += "\n";
	}

	file.close();


	///
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