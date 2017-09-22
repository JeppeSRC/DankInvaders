#pragma once

#include <core/app.h>
#include <util/list.h>
#include "texture2d.h"

class AnimatedTexture {
private:
	List<Texture2D*> textures;

	float fps;
	float current;

public:
	AnimatedTexture(float fps);
	~AnimatedTexture();

	void AddFrame(Texture2D* texture);
	void RemoveFrame(size_t location);
	void RemoveFrame(const Texture2D* texture);

	void Update(float delta);

	Texture2D* GetCurrent() const;
};
