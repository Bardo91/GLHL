///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilterGPU class currently Robot class

#include "ParticleFilterGPU.h"

#include <ctime>

using namespace GLHL;

//---------------------------------------------------------------------------------------------------------------------
ParticleFilterGPU::ParticleFilterGPU(unsigned _nuParticles, std::string _particleShaderPath) :
						mComputeTexture(40, 25, eTexType::eRGBA32F),
						mStoreTexture(40, 25, eTexType::eRGBA32F),
						mVertexShaderDummy(eShaderType::eVertexShader,"../../src/shaders/particle.vertex"),
						mFragmentShader(eShaderType::eFragmentShader, _particleShaderPath) {

	_nuParticles;

	glViewport(0, 0, 40, 25);
	initFBO();
	
	initProgram();

	initFilter();
	
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::step() {
	DriverGPU *driver = DriverGPU::get();

	mProgram.use();

	// Update simulation parameters
	//GLuint movLoc = driver->getUniformLocation(mProgram, "movement");
	//driver->setUniform(movLoc, vec2f(0.1f, 0.05f));
	//
	//driver->setUniform(mSeed, float(rand()) / RAND_MAX);
	//GLuint storedDataLoc = driver->getUniformLocation(mProgram, "lastSimulation");
	//driver->setUniform(storedDataLoc, mStoreTexture);

	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f), vec2f(0.0f, 0.0f)}});

	glFlush();

	mStoreTexture.bind();
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, mStoreTexture.width(), mStoreTexture.height());

	glFinish();
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::swapFBO() {

}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::initFBO(){
	mFBO.attachTexture(mComputeTexture);

	mFBO.linkAttachments();
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::initProgram(){
	mProgram.attachShader(mVertexShaderDummy);
	mProgram.attachShader(mFragmentShader);

	mProgram.link();

	mProgram.use();

}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::initFilter(){
	DriverGPU *driver = DriverGPU::get();

	GLuint initLoc = driver->getUniformLocation(mProgram, "init");
	driver->setUniform(initLoc, true);
	mSeed = driver->getUniformLocation(mProgram, "seed");
	driver->setUniform(mSeed, float(rand()) / RAND_MAX);

	mProgram.use();

	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f)}});

	driver->setUniform(initLoc, false);

	mStoreTexture.bind();
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, mStoreTexture.width(), mStoreTexture.height());

	glFlush();

}