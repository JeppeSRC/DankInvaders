#pragma once

#include <math/math.h>
#include <graphics/texture2d.h>

class Entity {
protected:
	vec3 position;
	vec2 size;

	vec4 color;
	Texture2D* texture;

	Entity(vec3 position, vec2 size);
public:

	virtual void Update(float delta, vec2 input);
	
	inline vec3& GetPosition() { return position; }
	inline vec2& GetSize() { return size; }
	inline vec4& GetColor() { return color; }
	inline Texture2D* GetTexture() const { return texture; }
};