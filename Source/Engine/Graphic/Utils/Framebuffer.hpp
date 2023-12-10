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

	bool usable() const;
	unsigned int id() const;
	unsigned int textureId() const;

	void resize(unsigned int width, unsigned int height);
	unsigned int width() const;
	unsigned int height() const;

	void bind();
	void unbind();
	virtual void clear(); // override if use different background color or utils buffers

protected:
	unsigned int m_framebufferId;
	unsigned int m_renderbufferId;
	Texture m_texture_attached;

private:
	void _createRenderBufferObject(unsigned int width, unsigned int height);
};