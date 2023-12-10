#pragma once

#include <glad/glad.h>

#include "Texture.hpp"

class Framebuffer {
public:
	Framebuffer(unsigned int width, unsigned int height);
	virtual ~Framebuffer();

	Framebuffer& operator=(const Framebuffer&)	= delete;
	Framebuffer(const Framebuffer&)				= delete;
	Framebuffer(Framebuffer&&)					= delete;

	bool isUsable() const;
	unsigned int getId() const;

	void resize(unsigned int width, unsigned int height);
	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void bind();
	void unbind();

protected:
	unsigned int m_framebufferId;
	unsigned int m_renderbufferId;
	Texture m_texture_attached;

private:
	void _createRenderBufferObject(unsigned int width, unsigned int height);
};