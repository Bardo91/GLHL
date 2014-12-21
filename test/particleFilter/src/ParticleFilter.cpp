///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilter class

#include "ParticleFilter.h"

void ParticleFilterCPU::step() {
	simulate();
	calcWeigh();
	resample();
}


void ParticleFilterCPU::simulate() {
	for (auto particle : mParticles) {
		particle.simulate();
	}
}


void ParticleFilterCPU::calcWeigh() {
	for (auto particle : mParticles) {
		particle.calcWeigh();
	}
}


void ParticleFilterCPU::resample() {

}
