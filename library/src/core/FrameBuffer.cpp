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
	void FrameBuffer::attachTexture(Texture _tex){
		assert(_tex != 0);
		
		unsigned attach = 0;
		if (mAttachments.size() == 0){
			attach = GL_COLOR_ATTACHMENT0;
		} else{
			attach = mAttachments.back().first + 1;
		}
		
		mAttachments.push_back(std::pair<unsigned, Texture>(attach, _tex));

		bind();

		DriverGPU::get()->framebufferTexture(GL_DRAW_FRAMEBUFFER, attach, _tex, 0);

	}

	//--------------------------------------------------------------------------------------------------------------------
	void FrameBuffer::use(){
		GLuint *attachments = new GLuint[mAttachments.size()];
		for (unsigned i = 0; i < mAttachments.size(); i++){
			attachments[i] = mAttachments[i].first;
		}

		bind();

		DriverGPU::get()->drawBuffers(mAttachments.size(), attachments);

		delete attachments;
	}


	//--------------------------------------------------------------------------------------------------------------------
	//	Private Interface
	//--------------------------------------------------------------------------------------------------------------------
	void FrameBuffer::bind(){
		DriverGPU::get()->bindFramebuffer(GL_DRAW_FRAMEBUFFER, mBufferId);

	}


}	// namespace GLHL