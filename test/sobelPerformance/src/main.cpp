 //// MAIN FILE TO TEST


#include <src/core/base/WindowGL.h>
#include <src/core/base/DriverGPU.h>
#include <src/core/base/Texture.h>
#include <src/core/glsl/ShaderProgram.h>
#include <src/core/glsl/Shader.h>
#include <src/core/utils/time/time.h>

#include <fstream>
#include <string>
#include <iostream>

#include <SOIL.h>

using namespace GLHL;
using namespace std;

void sobelCPU();
void sobelGLHL();
void drawImage(const Texture &_texture, ShaderProgram _program);
void drawQuad();

int main(void){



	sobelCPU();

	sobelGLHL();

	#ifdef _WIN32
	system("PAUSE");
	#endif

	return 0;
}

void sobelCPU(){
	int width;
	int height;
	int channels;

	unsigned char *image = SOIL_load_image("./Tulips.jpg", &width, &height, &channels, SOIL_LOAD_AUTO);


}

void sobelGLHL(){
	WindowGL window("Sobel Performance", 1024, 768);

	DriverGPU * driver = DriverGPU::get();

	Texture texture("./Tulips.jpg");

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/sobel.fragment");

	ShaderProgram program;

	program.attachShader(vShader);
	program.attachShader(fShader);
	program.link();

	window.peekMessage();
	drawImage(texture, program);

	texture.saveTexture("result.bmp");
	window.swapBuffers();

	delete driver;

}


void drawImage(const Texture &_texture, ShaderProgram _program) {
	glViewport(0, 0, 1024, 768);

	//glClear(GL_COLOR_BUFFER_BIT);
	
	DriverGPU *driver = DriverGPU::get();

	GLuint texLoc;
	texLoc = driver->getUniformLocation(_program, "texture");
	driver->setUniform(texLoc, 0);
	
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

