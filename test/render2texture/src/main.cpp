 //// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>
#include <src/core/ShaderProgram.h>
#include <src/core/Shader.h>
#include <src/core/Texture.h>
#include <src/core/FrameBuffer.h>


#include <fstream>
#include <string>
#include <iostream>

using namespace GLHL;
using namespace std;

void drawImage(Texture &_texture, ShaderProgram _program);

const unsigned int w = 640;
const unsigned int h = 480;
unsigned char buf[w * h * 3];

int main(void){
	WindowGL * window = WindowGL::createWindow(640, 480);
	
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
		window->peekMessage();
		drawImage(tulipsTex, program);
		#endif

		window->swapBuffers();
	}

	//	delete window; 	Class has no destructor, undefined behaviour
	delete driver;

	return 0;
}

void drawImage(Texture &_texture, ShaderProgram _program) {
	glViewport(0, 0, 640, 480);

	//glClear(GL_COLOR_BUFFER_BIT);
	
	DriverGPU *driver = DriverGPU::get();
	

	//--------------------------------------------
	Texture colorTex(640, 480, eTexType::eRGBA);
	
	
	FrameBuffer fbo;
	fbo.attachTexture(colorTex);
	fbo.use();

	_texture.bind();
	GLuint texLoc;
	texLoc = driver->getUniformLocation(_program, "texture");
	driver->setUniform(texLoc, 0);
	
	
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
	//glDeleteTextures(1, &colorTex);
	//glDeleteFramebuffers(1, &fbo);
	
	colorTex.saveTexture("C:/result.png");
}