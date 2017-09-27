#include "aiship.h"
#include <game/gamemanager.h>

AIShip::AIShip(vec3 position, vec2 size, AISHIP_TYPE type, GameManager* manager) : Ship(position, size, SHIP_TYPE_AISHIP, manager) { }

AIShip::~AIShip() {}