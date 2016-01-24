 //// MAIN FILE TO TEST


#include <glhl/base/WindowGL.h>
#include <glhl/base/DriverGPU.h>
#include <glhl/glsl/ShaderProgram.h>
#include <glhl/glsl/Shader.h>
#include <glhl/base/Texture.h>
#include <glhl/base/FrameBuffer.h>


#include <fstream>
#include <string>
#include <iostream>

using namespace GLHL;
using namespace std;

void drawImage(const Texture &_texture, ShaderProgram _program);

const unsigned int w = 640;
const unsigned int h = 480;
unsigned char buf[w * h * 3];

int main(void){
	WindowGL window("Frame Buffer Test", 640, 480);
	
	DriverGPU * driver = DriverGPU::get();

	Texture tulipsTex("./Tulips.jpg");

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	Shader sobelShader(eShaderType::eFragmentShader, "../../src/shaders/sobel.fragment");

	ShaderProgram program;

	program.attachShader(vShader);
	
	program.attachShader(sobelShader);
	program.link();


	


	while(1){	
		#if defined(_WIN32)
		window.peekMessage();
		drawImage(tulipsTex, program);
		#endif

		window.swapBuffers();
	}

	//	delete window; 	Class has no destructor, undefined behaviour
	delete driver;

	return 0;
}

void drawImage(const Texture &_texture, ShaderProgram _program) {
	glViewport(0, 0, 640, 480);

	//glClear(GL_COLOR_BUFFER_BIT);
	
	DriverGPU *driver = DriverGPU::get();

	FrameBuffer frame;
	Texture resTex(640, 480, eTexType::eRGB8);			// 666 create empty texture. Constructor not implemented
	frame.attachTexture(resTex);



	GLuint texLoc;
	texLoc = driver->getUniformLocation(_program, "texture");
	driver->setUniform(texLoc, 0);
	
	frame.bind();
	_program.use();

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

	

	glDrawArrays(GL_QUADS, 0, 4);


	glFinish();
	
	//resTex.saveTexture("result.png");
}