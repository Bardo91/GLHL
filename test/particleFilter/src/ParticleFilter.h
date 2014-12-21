///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilter class


#ifndef _GLHL_TEST_PARTICLE_FILTER_H_
#define _GLHL_TEST_PARTICLE_FILTER_H_

#include <vector>

// Particle interface
class Particle {
public:
	virtual void simulate() = 0;
	virtual void calcWeigh() = 0;

	double weigh() const { return mWeigh; };
	
private:
	double mWeigh;
};	//	 class Particle


// Particle filter class
class ParticleFilterCPU {
public:
	void step();
	std::vector<Particle> particles() const{ return mParticles; };

private:
	void simulate();
	void calcWeigh();
	void resample();

private:
	unsigned mNoParticles;
	std::vector<Particle> mParticles;

};	// class ParticleFilterCPU

#endif	//	_GLHL_TEST_PARTICLE_FILTER_H_

