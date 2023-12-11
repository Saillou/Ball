#pragma once

#include <glad/glad.h>

class Texture {
public:
	Texture(unsigned int width, unsigned int height, GLuint texture_type = GL_TEXTURE_2D);
	virtual ~Texture();

	Texture& operator=(const Texture&)	= delete;
	Texture(const Texture&)				= delete;
	Texture(Texture&&)					= delete;

	unsigned int id() const;
	unsigned int width() const;
	unsigned int height() const;

	void bind();
	void unbind();

	void resize(unsigned int width, unsigned int height);

protected:
	unsigned int m_textureId;
	unsigned int m_width;
	unsigned int m_height;
	GLuint m_texture_type;
};