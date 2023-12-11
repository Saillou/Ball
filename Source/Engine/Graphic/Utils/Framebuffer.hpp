#pragma once

#include <glad/glad.h>

#include "Texture.hpp"

class Framebuffer {
public:
	enum Type {
		Unique,
		Multisample
	};

	Framebuffer(Type type, unsigned int width, unsigned int height);
	virtual ~Framebuffer();

	Framebuffer& operator=(const Framebuffer&)	= delete;
	Framebuffer(const Framebuffer&)				= delete;
	Framebuffer(Framebuffer&&)					= delete;

	static bool CurrIsUsable();

	unsigned int id() const;
	Texture& texture();

	void resize(unsigned int width, unsigned int height);
	unsigned int width() const;
	unsigned int height() const;

	void bind() const;
	void unbind() const;
	virtual void clear(); // override if use different background color or utils buffers

protected:
	const Type m_type;

	unsigned int m_framebufferId;
	unsigned int m_renderbufferId;
	Texture m_texture_attached;

private:
	void _createRenderBufferObject(unsigned int width, unsigned int height);
};