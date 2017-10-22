#pragma once

#include <math/math.h>
#include <graphics/texture/texture2d.h>

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
	float rotation;

	unsigned int color;
	vec2 scaleTexture;
	Texture2D* texture;

	GameManager* manager;

	Entity(vec3 position, vec2 size, ENTITY_TYPE type, GameManager* manager);
public:
	virtual ~Entity() {}

	virtual void Update(float delta);

	vec2 GetTopLeft() const;
	vec2 GetTopRight() const;
	vec2 GetBottomRight() const;
	vec2 GetBottomLeft() const;
	
	virtual bool Intersects(Entity* other);

	inline vec3& GetPosition() { return position; }
	inline vec2& GetSize() { return size; }
	inline float& GetRotation() { return rotation; }
	inline unsigned int GetColor() { return color; }
	inline vec2 GetTextureScale() const { return scaleTexture; }
	inline Texture2D* GetTexture() const { return texture; }

	inline ENTITY_TYPE GetType() const { return type; }

	inline void SetTextureScale(const vec2& scale) { scaleTexture = scale; }
	inline void SetRotation(float angle) { this->rotation = angle; }
};