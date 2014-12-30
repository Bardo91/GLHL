 //// MAIN FILE TO TEST


#include <src/core/base/WindowGL.h>
#include <src/core/base/DriverGPU.h>
#include <src/core/base/Texture.h>
#include <src/core/glsl/ShaderProgram.h>
#include <src/core/glsl/Shader.h>

#include <fstream>
#include <string>
#include <iostream>

using namespace GLHL;
using namespace std;

void drawImage(ShaderProgram _program);
void drawQuad();

int main(void){
	WindowGL window("Texture loader", 640, 480);
	
	DriverGPU * driver = DriverGPU::get();

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/flat.fragment");

	ShaderProgram program;

	program.attachShader(vShader);
	program.attachShader(fShader);
	program.link();

	bool condition = true;
	do{	
		#if defined(_WIN32)
		window.peekMessage();
		drawImage(program);
		#endif
		window.swapBuffers();
		
	} while (condition);


	window.hide();

	#ifdef _WIN32
	system("PAUSE");
	#endif
	//	delete window; 	Class has no destructor, undefined behaviour
	delete driver;

	return 0;
}

void drawImage(ShaderProgram _program) {
	glViewport(0, 0, 640, 480);

	//glClear(GL_COLOR_BUFFER_BIT);
	Texture texture1("./Tulips.jpg");
	Texture texture2("./Koala.jpg");
	DriverGPU *driver = DriverGPU::get();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//texture1.attachToUniform(_program, "texture1");
	//texture2.attachToUniform(_program, "texture2");

	GLuint texLoc1;
	texLoc1 = driver->getUniformLocation(_program, "texture1");
	driver->setUniform(texLoc1, 0);
	
	GLuint texLoc2;
	texLoc2 = driver->getUniformLocation(_program, "texture2");
	driver->setUniform(texLoc2, 1);



	_program.use();

	drawQuad();

	glDrawArrays(GL_QUADS, 0, 4);

	glFinish();
}

void drawQuad(){
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glEnd();
}