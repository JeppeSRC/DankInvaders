#include "ship.h"

Ship::Ship(vec3 position, vec2 size, SHIP_TYPE type) : Entity(position, size, ENTITY_TYPE_SHIP), type(type) { }