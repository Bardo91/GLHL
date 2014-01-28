//// MAIN FILE TO TEST


#include "core/WindowGL.h"
#include "core/DriverGPU.h"

using namespace GLHL;

int main(void){

	WindowGL * window = WindowGL::createWindow(640, 480);
	WindowGL * window2 = WindowGL::createWindow(320, 480);

	while(1){

	}

	delete window;

	return 0;
}