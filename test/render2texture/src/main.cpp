 //// MAIN FILE TO TEST


#include <src/core/base/WindowGL.h>
#include <src/core/base/DriverGPU.h>
#include <src/core/base/Texture.h>
#include <src/core/base/FrameBuffer.h>

#include <src/core/glsl/ShaderProgram.h>
#include <src/core/glsl/Shader.h>
#include <src/core/types/Types.h>

#include <array>
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

void drawQuads();

int main(void){
	WindowGL window("render2texture", 640, 480);
	
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

void drawImage(Texture &_texture, ShaderProgram _program) {
	glViewport(0, 0, 640, 480);

	DriverGPU *driver = DriverGPU::get();
	
	// create a RGBA color texture
	Texture colorTex(640, 480, eTexType::eRGB8);

	// create the framebuffer object
	FrameBuffer fbo;
	fbo.attachTexture(colorTex);
	fbo.linkAttachments();
	
	_program.use();

	_texture.attachToUniform(_program, "texture");

	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f), vec2f(0.0f, 0.0f)}});

	glFlush();
	
	//fbo.detachTexture(colorTex);
	//colorTex.saveTexture("result.bmp");
 
	glFinish();

	std::cout << "finished" << std::endl;
}
