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
ParticleFilterGPU::ParticleFilterGPU(unsigned _nuParticles): mFrontTexture(_nuParticles, 1, eTexType::eRGBA), mBackTexture(_nuParticles, 1, eTexType::eRGBA) {
	DriverGPU *driver = DriverGPU::get();
	
	mFBO.attachTexture(mFrontTexture);
	mFBO.attachTexture(mBackTexture);

	mFBO.linkAttachments();

	/*Program & shaders initialization*/

	mSeed = driver->getUniformLocation(mStepProgram, "seed");
	
	/*Init program*/
	Shader initShaderVertex(eShaderType::eVertexShader, "shader/initParticles.fragment");
	ShaderProgram initProgram;

	initProgram.attachShader(initShaderVertex);
	//initProgram.attachShader(initShaderFragment);

	initProgram.link();

	GLuint seed = driver->getUniformLocation(initProgram, "seed");
	driver->setUniform(mSeed, unsigned(time(NULL)));
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::step() {
	glBegin(GL_LINE);		// 666 TODO: create a method in DriverGPU to draw lines, triangles... with and without textures
	glVertex2f(0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(1.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glEnd();

	mStepProgram.use();
}

//---------------------------------------------------------------------------------------------------------------------
void ParticleFilterGPU::swapFBO() {

}