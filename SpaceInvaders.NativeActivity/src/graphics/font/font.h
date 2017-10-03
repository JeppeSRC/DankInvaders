#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <util/string.h>
#include <graphics/texture2d.h>
#include <util/map.h>

class Font {
public:
	struct GLYPH {
		unsigned int unicode;

		float advance;

		float xOffset;
		float yOffset;

		float u0;
		float u1;
		float v0;
		float v1;

		unsigned int bitmapWidth;
		unsigned int bitmapHeight;

		unsigned char* bitmap;

		bool operator==(unsigned int unicode) const { return this->unicode == unicode; }
	};
	
private:
	FT_Library library;
	FT_Face face;

	Texture2D* atlas;

	List<GLYPH> glyphs;

	void LoadFont(void* data, size_t size, int font_size);
public:
	Font(const String& filename, int font_size);
	Font(void* data, size_t size, int font_size);
	~Font();

	const GLYPH& GetGlyph(unsigned int unicodeCharacter) const;
	Texture2D* GetAtlas() const { return atlas; }
};