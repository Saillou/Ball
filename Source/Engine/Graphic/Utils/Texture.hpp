#pragma once

#include <glad/glad.h>

class Texture {
public:
	explicit Texture();
	virtual ~Texture();

	Texture& operator=(const Texture&)	= delete;
	Texture(const Texture&)				= delete;
	Texture(Texture&&)					= delete;

	unsigned int getId() const;

protected:
	unsigned int m_bufferId;
};