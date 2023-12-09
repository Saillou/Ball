#include "Framebuffer.hpp"

Framebuffer::Framebuffer() :
	m_bufferId(0)
{
	glGenFramebuffers(1, &m_bufferId);
}
Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, &m_bufferId);
}

bool Framebuffer::isUsable() const {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

unsigned int Framebuffer::getId() const {
	return m_bufferId;
}

void Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_bufferId);
}

void Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}