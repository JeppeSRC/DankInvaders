#pragma once

#include "ship.h"

class Player : public Ship {
private:
	
public:
	Player(vec3 position, GameManager* manager);

	void Update(float delta) override;

};
