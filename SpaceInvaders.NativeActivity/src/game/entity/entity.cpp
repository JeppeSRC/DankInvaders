#include "entity.h"

Entity::Entity(vec3 position, vec2 size) {
	this->position = position;
	this->size = size;
	this->color = vec4(1, 1, 1, 1);
}