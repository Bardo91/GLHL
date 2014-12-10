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

void sobelCPU(double &_loadTime, double &_computeTime);
void sobelGLHL(double &_loadTime, double &_transferTime, double &_computeTime);
void drawImage(const Texture &_texture, ShaderProgram _program);
void drawQuad();

int main(void){

	STime::init();

	std::cout << "Image characteristics: " << std::endl;
	std::cout << "\t Width = 1024" << std::endl;
	std::cout << "\t Height = 768" << std::endl;
	std::cout << "\t Channels = 1" << std::endl;

	const int REPETITIONS = 50;
	double loadTime = 0, computeTime = 0, transferTime = 0;

	for (int i = 0; i < REPETITIONS; i++){
		sobelCPU(loadTime, computeTime);
	}
	
	loadTime /= REPETITIONS;
	computeTime /= REPETITIONS;

	std::cout << "SOIL's image load spent: " << loadTime << std::endl;
	std::cout << "CPU spent: " << computeTime << std::endl;


	loadTime = 0; 
	computeTime = 0;
	WindowGL window("Sobel Performance", 1024, 768);
	window.hide();

	for (int i = 0; i < REPETITIONS; i++){
		sobelGLHL(loadTime, transferTime, computeTime);
	}

	loadTime /= REPETITIONS;
	computeTime /= REPETITIONS;
	transferTime /= REPETITIONS;

	std::cout << "SOIL's image load: " << loadTime << std::endl;
	std::cout << "Image transfer to GPU spent: " << transferTime << std::endl;
	std::cout << "GPU spent: " << computeTime << std::endl;

	#ifdef _WIN32
	system("PAUSE");
	#endif

	return 0;
}

void sobelCPU(double &_loadTime, double &_computeTime){		// Dont see >.<. Embarrassing code
	int width;
	int height;
	int channels;

	STime *time = STime::get();

	double t1 = time->getTime();
	unsigned char *image = SOIL_load_image("./Tulips.jpg", &width, &height, &channels, 1);
	double t2 = time->getTime();
	

	
	char sobelH[] = { 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 };
	char sobelV[] = { -1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0 };


	for (int i = 1; i < width - 1; i++){
		for (int j = 1; j < height - 1; j++){
			unsigned char c1 = image[(i - 1)*height + j - 1];
			unsigned char c2 = image[(i - 1)*height + j];
			unsigned char c3 = image[(i - 1)*height + j + 1];
			unsigned char c4 = image[(i)*height + j - 1];
			unsigned char c5 = image[(i)*height + j];
			unsigned char c6 = image[(i)*height + j + 1];
			unsigned char c7 = image[(i + 1)*height + j - 1];
			unsigned char c8 = image[(i + 1)*height + j];
			unsigned char c9 = image[(i + 1)*height + j + 1];

			int Gx =	sobelH[0] * c1 +
						sobelH[1] * c2 + 
						sobelH[2] * c3 + 
						sobelH[3] * c4 + 
						sobelH[4] * c5 + 
						sobelH[5] * c6 +
						sobelH[6] * c7 +
						sobelH[7] * c8 + 
						sobelH[8] * c9 ;

			int Gy =	sobelV[0] * c1 +
						sobelV[1] * c2 +
						sobelV[2] * c3 +
						sobelV[3] * c4 +
						sobelV[4] * c5 +
						sobelV[5] * c6 +
						sobelV[6] * c7 +
						sobelV[7] * c8 +
						sobelV[8] * c9;



			double val = sqrt(Gx*Gx + Gy*Gy);

			if (val > 0.3 * 255)
				image[i*height + j] = 1;
			else
				image[i*height + j] = 0;


		}
	}

	double t3 = time->getTime();
	_loadTime += t2 - t1;
	_computeTime += t3 - t2;
	
	//std::cout << "SOIL's image load spent: " << t2 - t1 << std::endl;
	//std::cout << "CPU spent: " << t3 - t2 << std::endl;
}

void sobelGLHL(double &_loadTime, double &_transferTime, double &_computeTime){
	DriverGPU * driver = DriverGPU::get();

	int width;
	int height;
	int channels;

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/sobel.fragment");

	ShaderProgram program;

	program.attachShader(vShader);
	program.attachShader(fShader);
	program.link();

	STime *time = STime::get();
	double t1 = time->getTime();
	unsigned char *image = SOIL_load_image("./Tulips.jpg", &width, &height, &channels, SOIL_LOAD_AUTO);

	double t2 = time->getTime();
	Texture texture(1024,768, eTexType::eRGB, image);

	double t3 = time->getTime();
	drawImage(texture, program);

	double t4 = time->getTime();

	_loadTime += t2 - t1;
	_transferTime += t3 - t2;
	_computeTime += t4 - t3;

	//std::cout << "SOIL's image load: " << t2 - t1 << std::endl;
	//std::cout << "Image transfer to GPU spent: " << t3 - t2 << std::endl;
	//std::cout << "GPU spent: " << t4 - t3 << std::endl;

	texture.saveTexture("result.bmp");

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

