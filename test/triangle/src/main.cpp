//// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>
#include <src/core/Shader.h>
#include <src/core/ShaderProgram.h>

using namespace GLHL;

#include <fstream>
#include <string>


using namespace std;

GLvoid drawOnBuffer(GLint _width, GLint _height, GLuint _program);

int main(void){
	MSG msg;				// Windows menssage Structure.
	BOOL done = FALSE;		// Variable to exit loop.

	WindowGL * window = WindowGL::createWindow(640, 480);

	DriverGPU *driver = DriverGPU::get();

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/vTriangleShader.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/fTriangleShader.fragment");

	ShaderProgram sProgram;
	sProgram.attachShader(vShader);
	sProgram.attachShader(fShader);
	sProgram.bindAttribute(0, "vPosition");
	driver->glBindFragDataLocation(sProgram, 0, "outColor");
	sProgram.link();


	while(1){
		if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE)){ // Comprobamos si hay algun mensaje esperando en la cola
			if(msg.message == WM_QUIT) // Es un mensaje de cerrar?
				done = TRUE;
			else{
				TranslateMessage(&msg); // Traducimos el mensaje
				DispatchMessage(&msg); // Reenviamos el mensaje, lo despachamos
			}
		}

		drawOnBuffer(640, 480, sProgram);

		window->swapBuffers();
	}

	delete window, driver;

	return 0;
}

//---------------------------------------------------------------------------

GLvoid drawOnBuffer(GLint _width, GLint _height, GLuint _program){
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };
	glViewport(0, 0, _width, _height);

	glClear(GL_COLOR_BUFFER_BIT);

	DriverGPU* driver = DriverGPU::get();

	driver->glUseProgram(_program);

	// Load vertex Data
	driver->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	driver->glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}