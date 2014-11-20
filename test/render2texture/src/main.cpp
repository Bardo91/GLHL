 //// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>
#include <src/core/ShaderProgram.h>
#include <src/core/Shader.h>
#include <src/core/Texture.h>
#include <src/core/FrameBuffer.h>

#include <SOIL.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace GLHL;
using namespace std;

void drawImage(Texture &_texture, ShaderProgram _program);

const unsigned int w = 640;
const unsigned int h = 480;
const unsigned int c = 4;
std::vector<unsigned char> buf(w * h * c);

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
	

	GLuint colorTex, depthTex, fbo;
	// create a RGBA color texture
	glGenTextures(1, &colorTex);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	// create the framebuffer object
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// attach color
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTex, 0);
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (e != GL_FRAMEBUFFER_COMPLETE)
		printf("There is a problem with the FBO\n");

	// bind the framebuffer as the output framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// define the index array for the outputs
	GLuint attachments[1] = { GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, attachments);

	//--------------------------------------------
	//Texture colorTex(640, 480, eTexType::eRGBA);
	//
	//FrameBuffer fbo;
	//fbo.attachTexture(colorTex);
	//fbo.use();
	//
	//_texture.bind();
	//GLuint texLoc;
	//texLoc = driver->getUniformLocation(_program, "texture");
	//driver->setUniform(texLoc, 0);
	
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

	//glDrawArrays(GL_QUADS, 0, 4);
	glFlush();
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buf.data());
	SOIL_save_image("result.bmp", SOIL_SAVE_TYPE_BMP, w, h, 4, buf.data());

	//colorTex.saveTexture("result.png");
	glFinish();
	glDeleteTextures(1, &colorTex);
	glDeleteFramebuffers(1, &fbo);

	std::cout << "finished" << std::endl;
}