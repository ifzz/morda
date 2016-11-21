#include "OpenGL2FrameBuffer.hpp"
#include "OpenGL2Texture2D.hpp"

#include "OpenGL2_util.hpp"

#include <GL/glew.h>

OpenGL2FrameBuffer::OpenGL2FrameBuffer(std::shared_ptr<morda::Texture2D_n> color) :
		morda::FrameBuffer_n(std::move(color))
{
	glGenFramebuffers(1, &this->fbo);
	AssertOpenGLNoError();
	
	GLint oldFb;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFb);
	
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
	AssertOpenGLNoError();
	
	ASSERT(dynamic_cast<OpenGL2Texture2D*>(this->color.operator->()))
	auto& tex = static_cast<OpenGL2Texture2D&>(*this->color);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.tex, 0);
	AssertOpenGLNoError();
	
	//Check for completeness
	{
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		AssertOpenGLNoError();
		ASSERT(status == GL_FRAMEBUFFER_COMPLETE)
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, oldFb);
	AssertOpenGLNoError();
}


OpenGL2FrameBuffer::~OpenGL2FrameBuffer()noexcept{
	glDeleteFramebuffers(1, &this->fbo);
	AssertOpenGLNoError();
}