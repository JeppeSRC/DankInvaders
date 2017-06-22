#pragma once

#include <math/math.h>
#include <graphics/texture2d.h>

class Entity {
protected:
	vec3 position;
	vec2 size;

	vec4 color;
public:
	Texture2D* texture;

public:
	Entity(vec3 position, vec2 size);
	
	inline vec3& GetPosition() { return position; }
	inline vec2& GetSize() { return size; }
	inline vec4& GetColor() { return color; }
	inline Texture2D* GetTexture() const { return texture; }
};