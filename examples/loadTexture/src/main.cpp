 //// MAIN FILE TO TEST

#include <glhl/base/WindowGL.h>
#include <glhl/base/DriverGPU.h>
#include <glhl/base/Texture.h>
#include <glhl/glsl/ShaderProgram.h>
#include <glhl/glsl/Shader.h>

#include <glhl/utils/time/time.h>

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

	Shader vShader(eShaderType::eVertexShader, "shaders/flat.vertex");
	Shader fShader(eShaderType::eFragmentShader, "shaders/flat.fragment");

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
	STime *sTime = STime::get();

	glViewport(0, 0, 640, 480);

	//glClear(GL_COLOR_BUFFER_BIT);
	double t0 = sTime->getTime();
	Texture texture1("./Tulips.jpg");
	Texture texture2("./Koala.jpg");
	Texture texture3("./Penguins.jpg");
	double t1 = sTime->getTime();

	DriverGPU *driver = DriverGPU::get();

	texture1.attachToUniform(_program, "texture1");
	texture2.attachToUniform(_program, "texture2");
	texture3.attachToUniform(_program, "texture3");



	_program.use();

	double t2 = sTime->getTime();
	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f)}});

	double t3 = sTime->getTime();

	glFinish();

	std::cout << "Load textures time: " << t1 - t0 << "; program use time: " << t3 - t1 << std::endl;
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