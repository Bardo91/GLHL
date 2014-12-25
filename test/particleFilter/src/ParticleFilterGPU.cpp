///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilterGPU class

#include "ParticleFilterGPU.h"

#include <ctime>

using namespace GLHL;

//---------------------------------------------------------------------------------------------------------------------
ParticleFilterGPU::ParticleFilterGPU(unsigned _nuParticles, std::string _particleShaderPath) :
						mFrontTexture(_nuParticles, 1, eTexType::eRGBA),
						mBackTexture(_nuParticles, 1, eTexType::eRGBA),
						mVertexShaderDummy(eShaderType::eVertexShader,"../../src/shaders/particle.vertex"),
						mFragmentShader(eShaderType::eFragmentShader, _particleShaderPath)
						{

	DriverGPU *driver = DriverGPU::get();
	
	mFBO.attachTexture(mFrontTexture);
	mFBO.attachTexture(mBackTexture);

	mFBO.linkAttachments();
	
	/*Init program*/
	mProgram.attachShader(mVertexShaderDummy);
	mProgram.attachShader(mFragmentShader);

	mProgram.link();

	GLuint initLoc = driver->getUniformLocation(mProgram, "init");
	driver->setUniform(initLoc, true);
	mSeed = driver->getUniformLocation(mProgram, "seed");
	driver->setUniform(mSeed, unsigned(time(NULL)));

	mProgram.use();
	/* 666 TODO draw line to exe shader*/

	
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::step() {
	DriverGPU *driver = DriverGPU::get();

	mProgram.use();

	driver->drawLine2f	(	std::array<vec2f, 2> { {	vec2f(-1.0f, 0.0f),
														vec2f(1.0f, 0.0f)}} );	
	glFinish();
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::swapFBO() {

}