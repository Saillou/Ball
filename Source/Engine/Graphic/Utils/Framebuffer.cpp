#include "Framebuffer.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
	m_framebufferId(0),
	m_renderbufferId(0),
	m_texture_attached(width, height)
{
	glGenFramebuffers(1, &m_framebufferId);

	bind();
	glViewport(0, 0, width, height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_attached.getId(), 0);

	_createRenderBufferObject(width, height);

	unbind();
}
Framebuffer::~Framebuffer() {
	glDeleteRenderbuffers(1, &m_renderbufferId);
	glDeleteFramebuffers(1, &m_framebufferId);
}

bool Framebuffer::isUsable() const {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

unsigned int Framebuffer::getId() const {
	return m_framebufferId;
}

void Framebuffer::resize(unsigned int width, unsigned int height) {
	m_texture_attached.resize(width, height);

	// need to recreate rbo
	glDeleteRenderbuffers(1, &m_renderbufferId);

	bind();
	_createRenderBufferObject(width, height);
	unbind();
}

unsigned int Framebuffer::getWidth() const {
	return m_texture_attached.getWidth();
}

unsigned int Framebuffer::getHeight() const {
	return m_texture_attached.getHeight();
}

void Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);
}

void Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::_createRenderBufferObject(unsigned int width, unsigned int height) {
	glGenRenderbuffers(1, &m_renderbufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferId);
}
