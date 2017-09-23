#pragma once

#include "ship.h"

class Player : public Ship {
private:
	
public:
	Player(vec3 position);

	void Update(float delta, vec2 input) override;

};
