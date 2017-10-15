#pragma once

#include <core/app.h>
#include <math/math.h>
#include <graphics/texture2d.h>
#include <util/string.h>

class MenuItem {
protected:
	vec3 position;
	vec4 color;

	Texture2D* texture;

	String title;

	MenuItem(const vec3& position);
public:

	virtual bool OnPress();
	virtual bool OnRelease();
	
	inline vec3 GetPosition() const { return position; }
	inline vec4 GetColor() const { return color; }
	inline Texture2D* GetTexture() const { return texture; }
};
