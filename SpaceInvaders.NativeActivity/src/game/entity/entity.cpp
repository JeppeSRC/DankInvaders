#include "entity.h"

Entity::Entity(vec3 position, vec2 size, ENTITY_TYPE type) : position(position), size(size), color(vec4(1, 1, 1, 1)), texture(nullptr), type(type) { }

void Entity::Update(float delta, vec2 input) { }