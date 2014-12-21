///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Robot class


#ifndef _GLHL_TEST_PARTICLE_FILTER_H_
#define _GLHL_TEST_PARTICLE_FILTER_H_

#include <vector>

template <typename ParticleType_>
class ParticleFilterCPU {
public:
	void step();
	std::vector<ParticleType_> particles() { return mParticles; } const;

private:
	void simulate();
	void weigh();
	void resample();

private:
	unsigned mNoParticles;
	std::vector<ParticleType_> mParticles;

};	// class ParticleFilterCPU

#endif	//	_GLHL_TEST_PARTICLE_FILTER_H_