#include "Texture.hpp"

Texture::Texture() :
	m_bufferId(0)
{
	glGenBuffers(1, &m_bufferId);
}
Texture::~Texture() {
	glDeleteBuffers(1, &m_bufferId);
}

unsigned int Texture::getId() const {
	return m_bufferId;
}