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
	vec3i testvec(1, 2, 4);

	//driver->drawTriangleTextured3f(	std::array < vec3f, 3 > {{	vec3f(1.0f, 1.0f, 0.0f),
	//															vec3f(-1.0f, 1.0f, 0.0f),
	//															vec3f(-1.0f, -1.0f, 0.0f) }},
	//								std::array < vec3f, 3 > {{ vec3f(-1.0f, -1.0f, 0.0f),
	//															vec3f(1.0f, 1.0f, 0.0f),
	//															vec3f(-1.0f, -1.0f, 0.0f) }});

	//glTexCoord2f(1, 1);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glTexCoord2f(0, 1);
	//glVertex3f(-1.0f, 1.0f, 0.0f);
	//glTexCoord2f(0, 0);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//// Second triangle
	//glTexCoord2f(1, 0);
	//glVertex3f(-1.0f, -1.0f, 0.0f);	//glTexCoord2f(1, 1);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glTexCoord2f(0, 0);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glEnd();

	//glDrawArrays(GL_QUADS, 0, 4);
	glFinish();
	double t3 = sTime->getTime();

	mWindow.swapBuffers();
	

	GpuTime gpuTime( t2 - t1, t3 - t1 );
	return gpuTime;

}

//---------------------------------------------------------------------------------------------------------------------