#pragma once

#include <core/app.h>

class Texture2D {
protected:
	unsigned int textureID;
	unsigned int width;
	unsigned int height;

	void Load(const void* const data, unsigned int width, unsigned int height, unsigned int format, unsigned int type);

public:
	Texture2D(const char* const path);
	Texture2D(const void* const data, unsigned int width, unsigned int height, unsigned int format, unsigned int type);
	~Texture2D();

	void Bind(unsigned int slot = 0) const;

	inline unsigned int GetWidth() const { return width; }
	inline unsigned int GetHeight() const { return height; }
};
