#pragma once

#include "entity.h"

class Player : public Entity {
private:
public:
	Player(vec3 position);

	void Update(float delta, vec2 input) override;

};
