#pragma once

#include <core/app.h>

namespace ftgl {

struct texture_atlas_t;
struct texture_font_t;

};

class Texture2D {
private:
	bool shouldDelete;
protected:
	unsigned int textureID;
	unsigned int width;
	unsigned int height;

	void Load(const void* const data, unsigned int width, unsigned int height, unsigned int format, unsigned int type);

public:
	Texture2D(ftgl::texture_atlas_t* atlas);
	Texture2D(const char* const path);
	Texture2D(const void* const data, unsigned int width, unsigned int height, unsigned int format, unsigned int type);
	~Texture2D();

	void Bind(unsigned int slot = 0) const;

	void UpdateAtlas(ftgl::texture_atlas_t* atlas);
	
	inline unsigned int GetWidth() const { return width; }
	inline unsigned int GetHeight() const { return height; }
};
