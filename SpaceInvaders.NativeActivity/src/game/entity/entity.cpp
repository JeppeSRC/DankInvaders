#include "entity.h"

#include <game/gamemanager.h>

Entity::Entity(vec3 position, vec2 size, ENTITY_TYPE type, GameManager* manager) : type(type), position(position), size(size), rotation(0), color(0xFFFFFFFF), scaleTexture(vec2(0, 0)), texture(nullptr), manager(manager) { }

void Entity::Update(float delta) { }

vec2 Entity::GetTopLeft() const {
	return vec2(position.x - size.x / 2.0f, position.y - size.y / 2.0f);
}

vec2 Entity::GetTopRight() const {
	return vec2(position.x + size.x / 2.0f, position.y - size.y / 2.0f);
}

vec2 Entity::GetBottomRight() const {
	return vec2(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

vec2 Entity::GetBottomLeft() const {
	return vec2(position.x - size.x / 2.0f, position.y + size.y / 2.0f);
}

bool Entity::Intersects(Entity* other) {
	const vec2& tl = GetTopLeft();
	const vec2& otl = other->GetTopLeft();
	const vec2& br = GetBottomRight();
	const vec2& obr = other->GetBottomRight();

	if (br.x > otl.x && br.y > otl.y) {
		if (obr.x > tl.x && obr.y > tl.y) {
			return true;
		}
	}

	return false;
}