//// MAIN FILE TO TEST


#include <src/core/base/WindowGL.h>
#include <src/core/base/DriverGPU.h>
#include <src/core/glsl/Shader.h>
#include <src/core/glsl/ShaderProgram.h>

#include <src/core/base/os_dep/win32/WindowGLWin32.h>

using namespace GLHL;

#include <fstream>
#include <string>


using namespace std;

GLvoid drawOnBuffer(GLint _width, GLint _height, ShaderProgram _program);

int main(void){
	WindowGL * window = WindowGL::createWindow(640, 480);

	DriverGPU *driver = DriverGPU::get();

	WindowGL * window2 = WindowGL::createWindow(480, 480);

	DriverGPU *driver2 = DriverGPU::get();

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/vTriangleShader.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/fTriangleShader.fragment");

	ShaderProgram sProgram;
	sProgram.attachShader(vShader);
	sProgram.attachShader(fShader);
	sProgram.bindAttribute(0, "vPosition");
	driver->bindFragDataLocation(sProgram, 0, "outColor");
	sProgram.link();

	unsigned i = 0;


	for(;;){
		window->peekMessage();
		window2->peekMessage();
		window->swapBuffers();
		window2->swapBuffers();

		//if (i == 4)
		//	wglMakeCurrent();
		//else if (i == 8)
		//	wglMakeCurrent();



		drawOnBuffer(640, 480, sProgram);

		i++;
		if (i == 8)
			i = 0;
	}
	

	delete window;
	delete driver;

	return 0;
}

//---------------------------------------------------------------------------

GLvoid drawOnBuffer(GLint _width, GLint _height, ShaderProgram _program){
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };
	glViewport(0, 0, _width, _height);

	//glClear(GL_COLOR_BUFFER_BIT);

	DriverGPU* driver = DriverGPU::get();

	_program.use();

	// Load vertex Data
	driver->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	driver->enableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}