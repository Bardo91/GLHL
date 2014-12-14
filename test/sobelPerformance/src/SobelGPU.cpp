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
	
	//Shader vShader(eShaderType::eVertexShader, "../../src/shaders/flat.vertex");
	//Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/sobel.fragment");

	Shader vShader(eShaderType::eVertexShader, "../../src/shaders/sobelUp.vertex");
	Shader fShader(eShaderType::eFragmentShader, "../../src/shaders/sobelUp.fragment");

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

	mProgram.use();

	GLuint texLoc, vOff, hOff;
	texLoc = driver->getUniformLocation(mProgram, "texture");
	driver->setUniform(texLoc, 0);
	vOff = driver->getUniformLocation(mProgram, "vOff");
	driver->setUniform(vOff, 1.0f / _height);
	hOff = driver->getUniformLocation(mProgram, "hOff");
	driver->setUniform(hOff, 1.0f / _width);

	glBegin(GL_TRIANGLES);
	// First triangle
	glVertex2f(-1.0f, -1.0f); glTexCoord2f(1.0, 1.0);
	glVertex2f(1.0f, -1.0f); glTexCoord2f(1.0, 0.0); 
	glVertex2f(1.0f, 1.0f); glTexCoord2f(0.0, 1.0);
	// Second triangle
	glVertex2f(-1.0f, -1.0f); glTexCoord2f(0.0, 0.0);
	glVertex2f(-1.0f, 1.0f); glTexCoord2f(1.0, 0.0);
	glVertex2f(1.0f, 1.0f); glTexCoord2f(0.0, 1.0);
	
	glEnd();

	//glDrawArrays(GL_QUADS, 0, 4);
	glFinish();
	double t3 = sTime->getTime();

	mWindow.swapBuffers();
	

	GpuTime gpuTime( t2 - t1, t3 - t1 );
	return gpuTime;

}

//---------------------------------------------------------------------------------------------------------------------