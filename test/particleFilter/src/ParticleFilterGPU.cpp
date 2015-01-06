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
void ParticleFilterGPU::step(vec4f _sense) {
	DriverGPU *driver = DriverGPU::get();

	mProgram.use();

	// Update simulation parameters.
	GLuint movLoc = driver->getUniformLocation(mProgram, "movement");
	driver->setUniform(movLoc, vec2f(0.1f, 5.0f));
	
	// Load previous state and attach it to an uniform.
	mStoreTexture.attachToUniform(mProgram, "lastSimulation");

	// Calculate next step.
	// Simulate
	GLuint stateLoc = driver->getUniformLocation(mProgram, "gState");
	driver->setUniform(stateLoc, 1);

	GLuint measurementLoc = driver->getUniformLocation(mProgram, "measurementReal");
	driver->setUniform(measurementLoc, _sense);

	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f)}});

	mStoreTexture.bind();
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, mStoreTexture.width(), mStoreTexture.height());

	// Resample
	// Read pixels, find max weigh, send to shader and resample
	GLfloat * pixels = new GLfloat[40 * 25 * 4];
	glReadPixels(0, 0, 40, 25, GL_RGBA, GL_FLOAT, pixels);

	GLfloat maxWeigh = 0.0f;
	for (int i = 3; i < 40 * 25 * 4; i = i + 4){
		if (pixels[i] > maxWeigh)
			maxWeigh = pixels[i];
	}
	
	mStoreTexture.attachToUniform(mProgram, "lastSimulation");

	GLuint nuParticles = driver->getUniformLocation(mProgram, "nuParticles");
	driver->setUniform(nuParticles, 40 * 25);
	GLuint maxWeighLoc = driver->getUniformLocation(mProgram, "maxWeigh");
	driver->setUniform(maxWeighLoc, maxWeigh);

	driver->setUniform(stateLoc, 2);
	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f)}});


	glFlush();

	

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

	GLuint initLoc = driver->getUniformLocation(mProgram, "gState");
	driver->setUniform(initLoc, 0);

	GLuint seed = driver->getUniformLocation(mProgram, "gSeed");
	vec3f seeds(float(rand()) / RAND_MAX, float(rand()) / RAND_MAX, float(rand()) / RAND_MAX);
	driver->setUniform(seed, seeds);
	


	driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
								std::array < vec2f, 4 > {{vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f)}});

	mStoreTexture.bind();
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, mStoreTexture.width(), mStoreTexture.height());

	glFlush();

}