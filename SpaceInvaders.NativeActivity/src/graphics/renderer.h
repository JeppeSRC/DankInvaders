#pragma once

#include <core/app.h>
#include <math/math.h>

struct Vertex {
	vec3 position;
	vec2 texCoord;
	vec4 color;
	float tid;
};

class Renderer {
private:
	unsigned int numVertices;
	Vertex* buffer;

public:
	Renderer()
};
