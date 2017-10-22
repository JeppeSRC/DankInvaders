#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <util/string.h>
#include <graphics/texture/texture2d.h>
#include <util/map.h>
#include <freetype-gl.h>
#include <math/vec2.h>

class Font {
public:
	static Font* currentFont;
private:
	ftgl::texture_atlas_t* atlas;
	ftgl::texture_font_t* font;

	Texture2D* texture;

	float size;

	void LoadFont(void* data, size_t size, float font_size);
public:
	Font(const String& filename, float font_size);
	Font(void* data, size_t size, float font_size);
	~Font();

	vec2 GetFontMetrics(const String& text) const;

	inline ftgl::texture_atlas_t* GetAtlas() const { return atlas; }
	inline ftgl::texture_font_t* GetFont() const { return font; }
	inline Texture2D* GetTexture() const { return texture; }
	inline float GetSize() const { return size; }
};