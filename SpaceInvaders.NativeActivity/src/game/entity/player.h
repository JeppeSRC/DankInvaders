#pragma once

#include "entity.h"

class Player : public Entity {
public:
	Player(vec3 position) : Entity(position, vec2(10, 10)) {
		texture = new Texture2D("textures/dank.png");
	}
};
