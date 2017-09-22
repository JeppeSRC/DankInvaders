#pragma once

#include <game/entity/ship.h>

class AIShip : public Ship {
protected:
	
	AIShip(vec3 position, vec2 size);
public:
	virtual ~AIShip();

};
