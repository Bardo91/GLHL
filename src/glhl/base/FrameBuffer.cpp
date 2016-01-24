//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-11											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#include "FrameBuffer.h"

#include <cassert>

namespace GLHL{
	//--------------------------------------------------------------------------------------------------------------------
	// Public interface
	//--------------------------------------------------------------------------------------------------------------------
	FrameBuffer::FrameBuffer(){
		mBufferId = DriverGPU::get()->genFramebuffer();
	}

	//--------------------------------------------------------------------------------------------------------------------
	FrameBuffer::~FrameBuffer(){
		DriverGPU::get()->deleteFramebuffers(1, &mBufferId);
	}

	//--------------------------------------------------------------------------------------------------------------------
	void FrameBuffer::attachTexture(const Texture &_tex){
		assert(_tex != 0);
		
		unsigned attach = 0;
		if (mAttachments.size() == 0){
			attach = GL_COLOR_ATTACHMENT0;
		} else{
			attach = mAttachments.back().first + 1;
		}
		
		mAttachments.push_back(std::pair<unsigned, const Texture &>(attach, _tex));
		
		bind();
		DriverGPU::get()->framebufferTexture(GL_FRAMEBUFFER, attach, _tex, 0);
		DriverGPU::get()->checkErrors();
		checkErrors();

	}

	//--------------------------------------------------------------------------------------------------------------------
	//	666 TODO: generate errors
	//void FrameBuffer::detachTexture(const Texture &_tex){
	//	assert(_tex != 0);
	//
	//	unsigned attach = 0;
	//	for (unsigned i = 0; i < mAttachments.size(); ++i){
	//		if (mAttachments[i].second == _tex){
	//			attach = GL_COLOR_ATTACHMENT0 + i;
	//			break;
	//		}
	//	}
	//	if (attach == 0)
	//		return;
	//
	//	bind();
	//	DriverGPU::get()->framebufferTexture(GL_DRAW_FRAMEBUFFER, attach, 0, 0);
	//	DriverGPU::get()->checkErrors();
	//	checkErrors();
	//
	//}

	//--------------------------------------------------------------------------------------------------------------------
	void FrameBuffer::linkAttachments(){
		GLuint *attachments = new GLuint[mAttachments.size()];
		for (unsigned i = 0; i < mAttachments.size(); i++){
			attachments[i] = mAttachments[i].first;
		}

		bind();
		DriverGPU::get()->drawBuffers(mAttachments.size(), attachments);
		DriverGPU::get()->checkErrors();		

		delete attachments;
	}

	void FrameBuffer::bind(){
		DriverGPU::get()->bindFramebuffer(GL_FRAMEBUFFER, mBufferId);

	}

	void FrameBuffer::unbind(){
		DriverGPU::get()->bindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	//--------------------------------------------------------------------------------------------------------------------
	//	Private Interface
	//--------------------------------------------------------------------------------------------------------------------
	

	void FrameBuffer::checkErrors(){
		bind();

		GLenum error = DriverGPU::get()->checkFramebufferStatus(GL_FRAMEBUFFER);
		switch (error) {
		case GL_FRAMEBUFFER_UNDEFINED:
			printf("FBO Undefined\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("FBO Incomplete Attachment\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("FBO Missing Attachment\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			printf("FBO Incomplete Draw Buffer\n");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("FBO Unsupported\n");
			break;
		case GL_FRAMEBUFFER_COMPLETE:
			printf("FBO OK\n");
			break;
		default:
			printf("FBO Problem?\n");
		}

		if (error != GL_FRAMEBUFFER_COMPLETE)
			assert(false);	// Trouble with FBO
		
	}


}	// namespace GLHL