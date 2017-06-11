#include "texture2d.h"
#include <android/asset_manager.h>

Texture2D::Texture2D(const char* const path) {

}

Texture2D::Texture2D(const void* const data, unsigned int width, unsigned int height, unsigned int format) {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	this->width = width;
	this->height = height;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, format, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}