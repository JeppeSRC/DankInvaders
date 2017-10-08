#include "texture2d.h"
#include <android/asset_manager.h>
#include <android/configuration.h>
#include <util/asset/fileutils.h>
#include <core/log.h>
#include <util/stb_image.h>
#include <freetype-gl.h>

struct BMP_HEADER {
	unsigned short	identity;
	unsigned int	size;
	unsigned int	reserved0;
	unsigned int	dataOffset;

	unsigned int	hdrSize;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bitDepth;
	unsigned int	compMeth;
	unsigned int	imageSize;
	int				xLength;
	int				yLength;
	unsigned int	paletts;
	unsigned int	colors;
};

void Texture2D::Load(const void* const data, unsigned int width, unsigned int height, unsigned int format, unsigned int type)  {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	this->width = width;
	this->height = height;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(ftgl::texture_atlas_t* atlas) : shouldDelete(false), textureID(atlas->id), width(atlas->width), height(atlas->height) {

}

Texture2D::Texture2D(const char* const path) : shouldDelete(true) {
	unsigned int size = 0;
	void* data = nullptr;

	FileUtils::ReadFile(path, &data, &size);

	int width = 0;
	int height = 0;
	int comp = 0;

	unsigned char* image = stbi_load_from_memory((const unsigned char*)data, size, &width, &height, &comp, 4);

	if (!image) {
		LOGD("You suck!!! Failed to load texture");
		return;
	}

	
	Load(image, width, height, GL_RGBA, GL_UNSIGNED_BYTE);

	stbi_image_free(image);

	delete[] data;
}

Texture2D::Texture2D(const void* const data, unsigned int width, unsigned int height, unsigned int format, unsigned int type) : shouldDelete(true) {
	Load(data, width, height, format, type);
}

Texture2D::~Texture2D() {
	if (shouldDelete) glDeleteTextures(1, &textureID);
}

void Texture2D::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture2D::UpdateAtlas(ftgl::texture_atlas_t* atlas) {
	textureID = atlas->id;
	width = atlas->width;
	height = atlas->height;
}