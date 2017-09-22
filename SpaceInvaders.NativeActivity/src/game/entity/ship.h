#pragma once

#include "entity.h"

class Ship : public Entity {
protected:

	float health;
	

	Ship(vec3 position, vec2 size);
public:
	virtual ~Ship() {}
};