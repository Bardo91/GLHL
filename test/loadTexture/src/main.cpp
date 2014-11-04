//// MAIN FILE TO TEST


#include <src/core/WindowGL.h>
#include <src/core/DriverGPU.h>
#include <src/core/TextureLoader.h>
#include <src/core/ShaderProgram.h>
#include <src/core/Shader.h>

#include <fstream>
#include <string>

using namespace GLHL;
using namespace std;

void drawImage(GLuint _texture, ShaderProgram _program);

int main(void){
	MSG msg;				// Windows menssage Structure.
	BOOL done = FALSE;		// Variable to exit loop.

	WindowGL * window = WindowGL::createWindow(640, 480);
	
	DriverGPU * driver = DriverGPU::get();

	GLuint texture = TextureLoader::load2dTexture("C:\\Tulips.jpg");

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/flat.fragment");
	Shader blurShader(eShaderType::eFragmentShader, "../../src/shaders/blur.fragment");
	Shader segmentateShader(eShaderType::eFragmentShader, "../../src/shaders/segmentate.fragment");
	Shader sobelShader(eShaderType::eFragmentShader, "../../src/shaders/sobel.fragment");

	ShaderProgram program;

	program.attachShader(vShader);
	//program.attachShader(fShader);
	//program.attachShader(blurShader);
	//program.attachShader(segmentateShader);
	program.attachShader(sobelShader);
	program.link();


	const unsigned int w = 640;
	const unsigned int h = 480;
	unsigned char buf[w * h * 3];


	while(1){
		if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE)){ // Comprobamos si hay algun mensaje esperando en la cola
			if(msg.message == WM_QUIT) // Es un mensaje de cerrar?
				done = TRUE;
			else{
				TranslateMessage(&msg); // Traducimos el mensaje
				DispatchMessage(&msg); // Reenviamos el mensaje, lo despachamos
			}
		}
		
		drawImage(texture, program);

		glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, &buf[0]);

		int err = SOIL_save_image
			(
			"img.bmp",
			SOIL_SAVE_TYPE_BMP,
			w, h, 3,
			&buf[0]
			);

		window->swapBuffers();
	}

	delete window, driver;

	return 0;
}

void drawImage(GLuint _texture, ShaderProgram _program) {
	glViewport(0, 0, 640, 480);

	//glClear(GL_COLOR_BUFFER_BIT);
	
	DriverGPU *driver = DriverGPU::get();

	GLuint texLoc;
	texLoc = driver->glGetUniformLocation(_program, "texture");
	driver->glUniform1i(texLoc, 0);

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

	_program.use();

	glDrawArrays(GL_QUADS, 0, 4);


	glFinish();
}