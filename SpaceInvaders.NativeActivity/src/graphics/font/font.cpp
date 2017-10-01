
#include "font.h"
#include <util/asset/fileutils.h>
#include <core/app.h>
#include <math.h>

Font::Font(const String& filename, int font_size) {
	void* data = nullptr;
	unsigned int size;

	FileUtils::ReadFile(*filename, &data, &size);

	LoadFont(data, size, font_size);

	delete[] data;
}

Font::Font(void* data, size_t size, int font_size) {
	LoadFont(data, size, font_size);
}

Font::~Font() {
	delete atlas;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void Font::LoadFont(void* data, size_t size, int font_size) {

	FT_Init_FreeType(&library);

	FT_New_Memory_Face(library, (FT_Byte*)data, size, 0, &face);

	FT_Set_Char_Size(face, font_size * 64, 0, NativeApp::app->surface_width, NativeApp::app->surface_height);
	FT_Select_Charmap(face, FT_ENCODING_UNICODE);

	unsigned int segmentWidth = 0;
	unsigned int segmentHeight = 0;

	unsigned int symbols[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	unsigned int numSymbols = sizeof(symbols) / sizeof(unsigned int);

	for (unsigned int i = 0; i < numSymbols; i++) {
		unsigned int index = symbols[i];

		if (index == 0) continue;

		FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);

		FT_GlyphSlot glyphSlot = face->glyph;

		FT_Render_Glyph(glyphSlot, FT_RENDER_MODE_NORMAL);

		FT_Bitmap bitmap = glyphSlot->bitmap;
		FT_Glyph_Metrics metrics = glyphSlot->metrics;

		GLYPH glyph;

		glyph.unicode = i;
		glyph.advance = (float)glyphSlot->advance.x / 64.0f;
		glyph.xOffset = (float)metrics.horiBearingX / 64.0f;
		glyph.yOffset = (float)(metrics.height - metrics.horiBearingY) / 64.0f;
		glyph.bitmapWidth = bitmap.width;
		glyph.bitmapHeight = bitmap.rows;

		unsigned int bitmapSize = bitmap.width * bitmap.rows;

		glyph.bitmap = new unsigned char[bitmapSize];

		memcpy(glyph.bitmap, bitmap.buffer, bitmapSize);

		if (glyph.bitmapWidth > segmentWidth) segmentWidth = glyph.bitmapWidth;
		if (glyph.bitmapHeight > segmentHeight) segmentHeight = glyph.bitmapHeight;

		glyphs.Push_back(glyph);
	}

	unsigned int bitmapSquareSize = (unsigned int)ceilf(sqrtf((float)numSymbols));
	unsigned int bitmapWidth = bitmapSquareSize * segmentWidth;
	unsigned int bitmapHeight = bitmapSquareSize * segmentHeight;

	unsigned int bitmapSize = bitmapWidth * bitmapHeight;
	unsigned char* bitmap = new unsigned char[bitmapSize];

	float xStep = (float)segmentWidth / bitmapWidth;
	float yStep = (float)segmentHeight / bitmapHeight;

	memset(bitmap, 0, bitmapSize);

	for (unsigned int i = 0; i < numSymbols; i++) {
		GLYPH& glyph = glyphs[i];

		unsigned int xStart = i % bitmapSquareSize;
		unsigned int yStart = i / bitmapSquareSize;

		glyph.u0 = (float)xStart * xStep;
		glyph.u1 = (float)yStart * yStep;
		glyph.v0 = glyph.u0 + xStep;
		glyph.v1 = glyph.u1 + yStep;

		unsigned int yOffset = segmentHeight - glyph.bitmapHeight;

		for (unsigned int y = 0; y < glyph.bitmapHeight; y++) {
			unsigned int ya = (yStart * segmentHeight) + y + yOffset;
			for (unsigned int x = 0; x < glyph.bitmapWidth; x++) {
				unsigned int xa = (xStart * segmentWidth) + x;
				bitmap[xa + ya * bitmapWidth] = glyph.bitmap[x + y * glyph.bitmapWidth];
			}
		}

		delete[] glyph.bitmap;

		glyph.bitmap = nullptr;
	}

	atlas = new Texture2D(bitmap, bitmapWidth, bitmapHeight, GL_R8, GL_UNSIGNED_BYTE);
}

const Font::GLYPH& Font::GetGlyph(unsigned int unicodeCharacter) const {
	size_t index = glyphs.Find<unsigned int>([](const GLYPH& item, unsigned int other) -> bool { return item == other; }, unicodeCharacter);

	ASSERT(index == (size_t)-1);

	return glyphs[index];
}