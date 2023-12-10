#include "Framebuffer.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
	m_framebufferId(0),
	m_renderbufferId(0),
	m_texture_attached(width, height)
{
	glGenFramebuffers(1, &m_framebufferId);

	bind();
	glViewport(0, 0, width, height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_attached.id(), 0);

	_createRenderBufferObject(width, height);

	unbind();
}
Framebuffer::~Framebuffer() {
	glDeleteRenderbuffers(1, &m_renderbufferId);
	glDeleteFramebuffers(1, &m_framebufferId);
}

bool Framebuffer::usable() const {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

unsigned int Framebuffer::id() const {
	return m_framebufferId;
}

unsigned int Framebuffer::textureId() const {
	return m_texture_attached.id();
}

void Framebuffer::resize(unsigned int width, unsigned int height) {
	m_texture_attached.resize(width, height);

	// need to recreate rbo
	glDeleteRenderbuffers(1, &m_renderbufferId);

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

void Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);
}

void Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::clear() {
	glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::_createRenderBufferObject(unsigned int width, unsigned int height) {
	glGenRenderbuffers(1, &m_renderbufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferId);
}
