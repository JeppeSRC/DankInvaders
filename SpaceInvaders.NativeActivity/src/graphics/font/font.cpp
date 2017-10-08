
#include "font.h"
#include <util/asset/fileutils.h>
#include <core/app.h>
#include <math.h>
#include <freetype-gl.h>

Font::Font(const String& filename, float font_size) {
	void* data = nullptr;
	unsigned int size;

	FileUtils::ReadFile(*filename, &data, &size);

	LoadFont(data, size, font_size);
}

Font::Font(void* data, size_t size, float font_size) {
	LoadFont(data, size, font_size);
}

Font::~Font() {
	texture_font_delete(font);
	texture_atlas_delete(atlas);

	delete texture;
}

void Font::LoadFont(void* data, size_t size, float font_size) {
	atlas = ftgl::texture_atlas_new(2048, 2048, 1);
	font = texture_font_new_from_memory(atlas, font_size, data, size);

	texture_font_get_glyph(font, '0');

	texture = new Texture2D(atlas);

	this->size = font_size;
}

