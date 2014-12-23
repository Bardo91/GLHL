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


// Particle filter class
class ParticleFilterGPU {
public:
	ParticleFilterGPU(unsigned _nuParticles);

	void init();
	void step(/*_realParticle*/);

};	// class ParticleFilterCPU

#include "ParticleFilterGPU.inl"

#endif	//	_GLHL_TEST_PARTICLE_FILTER_CPU_H_

