#pragma once

#include <glad/glad.h>

class Framebuffer {
public:
	explicit Framebuffer();
	virtual ~Framebuffer();

	Framebuffer& operator=(const Framebuffer&)	= delete;
	Framebuffer(const Framebuffer&)				= delete;
	Framebuffer(Framebuffer&&)					= delete;

	bool isUsable() const;
	unsigned int getId() const;

	void bind();
	void unbind();

protected:
	unsigned int m_bufferId;
};