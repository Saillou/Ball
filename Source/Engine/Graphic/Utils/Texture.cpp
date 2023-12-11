#include "Texture.hpp"

Texture::Texture(unsigned int width, unsigned int height, GLuint texture_type) :
	m_textureId(0),
	m_width(width),
	m_height(height),
	m_texture_type(texture_type)
{
	glGenTextures(1, &m_textureId);

	bind();

	resize(m_width, m_height);
	glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
Texture::~Texture() {
	glDeleteTextures(1, &m_textureId);
}

unsigned int Texture::id() const {
	return m_textureId;
}

unsigned int Texture::width() const {
	return m_width;
}

unsigned int Texture::height() const {
	return m_height;
}

void Texture::bind() {
	glBindTexture(m_texture_type, m_textureId);
}

void Texture::unbind() {
	glBindTexture(m_texture_type, 0);
}

void Texture::resize(unsigned int width, unsigned int height) {
	m_width  = width;
	m_height = height;

	bind();
	switch (m_texture_type) {
	case GL_TEXTURE_2D_MULTISAMPLE:
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_RGB, m_width, m_height, GL_TRUE);
		break;

	case GL_TEXTURE_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		break;
	}
}
