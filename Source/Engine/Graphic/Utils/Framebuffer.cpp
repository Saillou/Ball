#include "Framebuffer.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
	m_framebufferId(0),
	m_renderbufferId(0),
	m_texture_attached(width, height)
{
	glGenFramebuffers(1, &m_framebufferId);

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_attached.id(), 0);
	_createRenderBufferObject(width, height);
	unbind();
}
Framebuffer::~Framebuffer() {
	glDeleteRenderbuffers(1, &m_renderbufferId);
	glDeleteFramebuffers(1, &m_framebufferId);
}

bool Framebuffer::CurrIsUsable() {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

unsigned int Framebuffer::id() const {
	return m_framebufferId;
}

Texture& Framebuffer::texture() {
	return m_texture_attached;
}

void Framebuffer::resize(unsigned int width, unsigned int height) {
	m_texture_attached.resize(width, height);
	
	bind();
	_createRenderBufferObject(width, height);
	unbind();
}

unsigned int Framebuffer::width() const {
	return m_texture_attached.width();
}

unsigned int Framebuffer::height() const {
	return m_texture_attached.height();
}

void Framebuffer::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);
}

void Framebuffer::unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::clear() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::_createRenderBufferObject(unsigned int width, unsigned int height) {
	glDeleteRenderbuffers(1, &m_renderbufferId);

	glGenRenderbuffers(1, &m_renderbufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferId);
}
