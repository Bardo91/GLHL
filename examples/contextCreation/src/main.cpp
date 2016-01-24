//// MAIN FILE TO TEST


#include <glhl/base/WindowGL.h>
#include <glhl/base/DriverGPU.h>
#include <glhl/glsl/Shader.h>
#include <glhl/glsl/ShaderProgram.h>

#include <glhl/base/os_dep/win32/WindowGLWin32.h>

using namespace GLHL;

#include <fstream>
#include <string>
#include <iostream>
#include <thread>


using namespace std;

GLvoid drawOnBuffer(GLint _width, GLint _height, ShaderProgram _program, GLfloat _red);
void openGLThread(bool _draw, GLfloat _red);

volatile bool running = true;

int main(void){
	
	int command = 1;
	thread t1(openGLThread, true, 0.5);
	thread t2(openGLThread, true, 1);
	
	do{
		cin >> command;
	} while (command != 0);
	
	running = false;

	

	return 0;
}

//---------------------------------------------------------------------------

void openGLThread(bool _draw, GLfloat _red){
	//WindowGL * window = WindowGL::createWindow(640, 480);

	Context context;

	DriverGPU *driver = DriverGPU::get();

	Shader vShader(eShaderType::eVertexShader, "shaders/vTriangleShader.vertex");
	Shader fShader(eShaderType::eFragmentShader, "shaders/fTriangleShader.fragment");


	ShaderProgram sProgram;
	sProgram.attachShader(vShader);
	sProgram.attachShader(fShader);
	sProgram.bindAttribute(0, "vPosition");
	
	sProgram.link();

	while(running){
		//window->peekMessage();
		//window->swapBuffers();
		//if (_draw)
		//	drawOnBuffer(640, 480, sProgram, _red);
	}

	delete driver;
}

GLvoid drawOnBuffer(GLint _width, GLint _height, ShaderProgram _program, GLfloat _red){
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };
	
	glViewport(0, 0, _width, _height);

	//glClear(GL_COLOR_BUFFER_BIT);

	DriverGPU* driver = DriverGPU::get();

	GLint loc = driver->getUniformLocation(_program, "baseColor");
	driver->setUniform(loc, _red);
	_program.use();
	
	glFlush();
	
	// Load vertex Data
	driver->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	driver->enableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
	glFinish();
}
