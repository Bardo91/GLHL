///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilterGPU class

#include "ParticleFilterGPU.h"

//---------------------------------------------------------------------------------------------------------------------
ParticleFilterGPU::ParticleFilterGPU(unsigned _nuParticles): mFrontTexture(_nuParticles, 1, eTexType::eRGBA), mBackTexture(_nuParticles, 1, eTexType::eRGBA) {
	mFBO.attachTexture(mFrontTexture);
	mFBO.attachTexture(mBackTexture);

	mFBO.linkAttachments();

}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::init() {

}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::step() {

}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::swapFBO() {

}