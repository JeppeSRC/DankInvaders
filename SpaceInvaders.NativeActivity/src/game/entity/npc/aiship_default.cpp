#include "aiship_default.h"

#include <game/gamemanager.h>

AIShipDefault::AIShipDefault(vec3 position, vec2 size, GameManager* manager) : AIShip(position, size, AISHIP_TYPE_DEFAULT, manager) {
	health = 100;
}

void AIShipDefault::Update(float delta) {

}
