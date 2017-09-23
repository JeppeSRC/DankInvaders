#pragma once

#include <math/math.h>
#include <graphics/texture2d.h>

enum ENTITY_TYPE {
	ENTITY_TYPE_UNKNOWN,
	ENTITY_TYPE_PICKUP,
	ENTITY_TYPE_SHIP,
	ENTITY_TYPE_WEAPON,
	ENTITY_TYPE_PROJECTILE
};

class GameManager;

class Entity {
private:
	ENTITY_TYPE type;
protected:
	vec3 position;
	vec2 size;

	vec4 color;
	Texture2D* texture;

	Entity(vec3 position, vec2 size, ENTITY_TYPE type);
public:
	virtual ~Entity() {}

	virtual void Update(float delta, GameManager* manager);
	
	inline vec3& GetPosition() { return position; }
	inline vec2& GetSize() { return size; }
	inline vec4& GetColor() { return color; }
	inline Texture2D* GetTexture() const { return texture; }

	inline ENTITY_TYPE GetType() const { return type; }
};