///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilter class

#include "ParticleFilter.h"
template<Particle ParticleType_>
void ParticleFilterCPU<ParticleType_>::step() {
	simulate();
	calcWeigh();
	resample();
}

template<Particle ParticleType_>
void ParticleFilterCPU<ParticleType_>::simulate() {
	for (unsigned i = 0; i < mNuParticles; i ++) {
		mParticles[i].simulate();
	}
}

template<Particle ParticleType_>
void ParticleFilterCPU<ParticleType_>::calcWeigh() {
	for (unsigned i = 0; i < mNuParticles; i++) {
		mParticles[i].calcWeigh();
	}
}

template<Particle ParticleType_>
void ParticleFilterCPU<ParticleType_>::resample() {
	std::vector<ParticleType_> newParticles;
	double beta = 0.0;
	unsigned index = unsigned(rand() * mNuParticles);
	double maxWeigh = 0.0;

	for (unsigned i = 0; i < mNuParticles; i++) {
		if (mParticles[i].weigh() > maxWeigh)
			maxWeigh = mParticles[i].weigh();
	}

	for (unsigned i = 0; i < mNuParticles; i++) {
		beta += rand() * 2.0 * maxWeigh;
		while (beta > mParticles[index].weigh()) {
			beta -= mParticles[index].weigh();
			index = (index + 1) % mNuParticles;
		}
		newParticles.push_back(mParticles[index]);
	}
}
