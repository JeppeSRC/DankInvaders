#include "entity.h"

#include <game/gamemanager.h>

Entity::Entity(vec3 position, vec2 size, ENTITY_TYPE type) : type(type), position(position), size(size), color(vec4(1, 1, 1, 1)), texture(nullptr) { }

void Entity::Update(float delta, GameManager* manager) { }