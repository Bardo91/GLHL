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
#include <iostream>

using namespace GLHL;

struct data{
	float x = 0.0f, y = 0.0f, ori = 0.0f, w = 0.0f;
	data() = default;
	data(float _x, float _y, float _ori, float _w){ x = _x; y = _y; ori = _ori; w = _w; };
	void set(float _x, float _y, float _ori, float _w){ x = _x; y = _y; ori = _ori; w = _w; };
};

//---------------------------------------------------------------------------------------------------------------------
ParticleFilterGPU::ParticleFilterGPU(unsigned _nuParticles, std::string _particleShaderPath) :
						mComputeTexture(_nuParticles, 1, eTexType::eRGBA32F),
						mStoreTexture(_nuParticles, 1, eTexType::eRGBA32F),
						mVertexShaderDummy(eShaderType::eVertexShader,"../../src/shaders/particle.vertex"),
						mFragmentShader(eShaderType::eFragmentShader, _particleShaderPath) {

	mNuParticles = _nuParticles;

	glViewport(0, 0, _nuParticles, 1);
	initFBO();
	
	initProgram();

	initFilter();
	
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::step(vec4f _sense) {
	
	simulateAndWeigh(_sense);
	glFlush();
	resample();
	glFlush();
	glFinish();
	
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::simulateAndWeigh(vec4f _sense) {
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

}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::resample(){
	// Read pixels, find max weigh, send to shader and resample
	GLfloat * pixels = new GLfloat[mNuParticles * 4];
	glReadPixels(0, 0, mNuParticles, 1, GL_RGBA, GL_FLOAT, pixels);

	GLfloat maxWeigh = 0.0f;
	for (unsigned i = 3; i < mNuParticles * 4; i = i + 4){
		if (pixels[i] > maxWeigh)
			maxWeigh = pixels[i];
	}


	// Resample
	GLfloat * pixelsNew = new GLfloat[mNuParticles * 4];
	float beta = 0.0f;
	int index = int(float(rand()) / RAND_MAX * mNuParticles);
	
	beta += float(rand()) / RAND_MAX * 2.0f * maxWeigh;
	
	for (unsigned i = 0; i < mNuParticles; i++) {
		beta += float(rand()) / RAND_MAX * 2.0f * maxWeigh;
		while (beta > pixels[index*4 + 3]) {
			beta -= pixels[index * 4 + 3];
			index = (index + 1) % mNuParticles;
		}
	
		pixelsNew[i * 4 + 0] = pixels[index*4 + 0];
		pixelsNew[i * 4 + 1] = pixels[index*4 + 1];
		pixelsNew[i * 4 + 2] = pixels[index*4 + 2];
		pixelsNew[i * 4 + 3] = pixels[index*4 + 3];
	}

	//DriverGPU *driver = DriverGPU::get();
	//GLuint stateLoc = driver->getUniformLocation(mProgram, "gState");
	//mStoreTexture.attachToUniform(mProgram, "lastSimulation");
	//
	//GLuint nuParticles = driver->getUniformLocation(mProgram, "nuParticles");
	//driver->setUniform(nuParticles, int(mNuParticles));
	//GLuint maxWeighLoc = driver->getUniformLocation(mProgram, "maxWeigh");
	//driver->setUniform(maxWeighLoc, maxWeigh);
	//
	//driver->setUniform(stateLoc, 2);
	//driver->drawQuadTextured2f(	std::array < vec2f, 4 > {{vec2f(-1.0f, -1.0f), vec2f(1.0f, -1.0f), vec2f(1.0f, 1.0f), vec2f(-1.0f, 1.0f)}},
	//							std::array < vec2f, 4 > {{vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f)}});
	//
	//
	//GLfloat * pixelsNew = new GLfloat[mNuParticles * 4];
	//glReadPixels(0, 0, mNuParticles, 1, GL_RGBA, GL_FLOAT, pixelsNew);

	// Calc Particle
	float x = 0.0f, y = 0.0f, ori = 0.0f;
	for (unsigned i = 0; i < mNuParticles; i++){
		x +=	pixelsNew[4 * i + 0];
		y +=	pixelsNew[4 * i + 1];
		ori +=	pixelsNew[4 * i + 2];
	}

	x *= 100.0f / mNuParticles;
	y *= 100.0f / mNuParticles;
	ori *= 3.141596f * 2 / mNuParticles;

	std::cout << "Estimated particle: " << x << ", " << y << ", " << ori << std::endl;
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