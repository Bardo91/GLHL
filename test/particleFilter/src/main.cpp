///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main


#include <src/core/base/WindowGL.h>
#include <src/core/base/DriverGPU.h>
#include <src/core/glsl/Shader.h>
#include <src/core/glsl/ShaderProgram.h>

using namespace GLHL;

#include <fstream>
#include <string>


using namespace std;

GLvoid drawOnBuffer(GLint _width, GLint _height, ShaderProgram _program);

int main(void){
	WindowGL window("Triangle test", 640, 480);

	DriverGPU *driver = DriverGPU::get();

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/particleFilter.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/quad.fragment");

	ShaderProgram sProgram;
	sProgram.attachShader(vShader);
	sProgram.attachShader(fShader);
	sProgram.bindAttribute(0, "vPosition");
	//driver->bindFragDataLocation(sProgram, 0, "outColor");
	sProgram.link();

	bool condition = true;
	while(condition){
	#ifdef _WIN32
		window.peekMessage();
	#endif

		drawOnBuffer(640, 480, sProgram);

		window.swapBuffers();
	}

	//	delete window; 	Class has no destructor, undefined behaviour
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
