#pragma once

#include <game/entity/npc/aiship.h>


class AIShipDefault : public AIShip {
private:

public:
	AIShipDefault(vec3 position, vec2 size, GameManager* manager);

	void Update(float delta) override;
};