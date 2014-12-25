///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-23
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilterGPU class


#ifndef _GLHL_TEST_PARTICLE_FILTER_GPU_H_
#define _GLHL_TEST_PARTICLE_FILTER_GPU_H_

#include <vector>
#include <src/core/base/FrameBuffer.h>
#include <src/core/base/Texture.h>

#include <src/core/glsl/Shader.h>
#include <src/core/glsl/ShaderProgram.h>

// Particle filter class
class ParticleFilterGPU {
public:
	ParticleFilterGPU(unsigned _nuParticles, std::string _particleShaderPath);

	void step(/*_realParticle*/);

private:
	void swapFBO();

private:
	GLHL::FrameBuffer mFBO;
	GLHL::Texture mFrontTexture, mBackTexture;

	bool currentTexture;

	GLuint mSeed;

	GLHL::Shader mVertexShaderDummy, mFragmentShader;
	GLHL::ShaderProgram mProgram;

};	// class ParticleFilterCPU

#endif	//	_GLHL_TEST_PARTICLE_FILTER_CPU_H_

