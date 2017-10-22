#include "animatedtexture.h"


AnimatedTexture::AnimatedTexture(float fps) : fps(fps) {

}

AnimatedTexture::~AnimatedTexture() {

}

void AnimatedTexture::AddFrame(Texture2D* texture) {
	textures.Push_back(texture);
}

void AnimatedTexture::RemoveFrame(size_t location) {
	ASSERT(location >= textures.GetSize());
	textures.RemoveIndex(location);
}

void AnimatedTexture::RemoveFrame(const Texture2D* texture) {
	textures.Remove((Texture2D*)texture);
}

void AnimatedTexture::Update(float delta) {
	current += fps * delta;

	if ((size_t)current >= textures.GetSize()) current = 0;
}

Texture2D* AnimatedTexture::GetCurrent() const {
	return textures[(size_t)current];
}