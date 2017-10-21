#pragma once

#include <core/app.h>
#include <math/math.h>
#include <graphics/texture2d.h>
#include <util/string.h>
#include <graphics/render/renderer.h>

class MenuItem {
protected:
	vec3 position;
	vec2 size;
	vec4 color;

	Texture2D* texture;

	String title;

	MenuItem(const vec3& position);
public:

	virtual void Render(Renderer* renderer) = 0;

	virtual bool OnPress(float x, float y);
	virtual bool OnMove(float x, float y);
	virtual bool OnRelease();

	bool IsPointInside(const vec2& point) const;
	
	inline vec3 GetPosition() const { return position; }
	inline vec2 GetSize() const { return size; }
	inline vec4 GetColor() const { return color; }
	inline Texture2D* GetTexture() const { return texture; }
};
