///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Test Performance - Sobel
//
//		Author: Pablo Ramon Soria
//		Date:	2014-12-11
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sobel GPU



#include "SobelGPU.h"

using namespace GLHL;

//---------------------------------------------------------------------------------------------------------------------
SobelGPU::SobelGPU(unsigned _width, unsigned _height): mWindow("Test Sobel", _width, _height){
	mWindow.hide();
	
	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/sobel.fragment");

	mProgram.attachShader(vShader);
	mProgram.attachShader(fShader);
	mProgram.link();

}

//---------------------------------------------------------------------------------------------------------------------
GpuTime SobelGPU::process(unsigned _width, unsigned _height, unsigned char *_image){
	DriverGPU *driver = DriverGPU::get();
	STime * sTime = STime::get();
	
	double t1 = sTime->getTime();
	Texture texture(_width, _height, eTexType::eRGB, _image);
	double t2 = sTime->getTime();
	
	glViewport(0, 0, 1024, 768);

	//glClear(GL_COLOR_BUFFER_BIT);

	GLuint texLoc;
	texLoc = driver->getUniformLocation(mProgram, "texture");
	driver->setUniform(texLoc, 0);

	mProgram.use();

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

	mWindow.swapBuffers();
	glFinish();
	double t3 = sTime->getTime();

	GpuTime gpuTime( t2 - t1, t3 - t1 );
	return gpuTime;

}

//---------------------------------------------------------------------------------------------------------------------