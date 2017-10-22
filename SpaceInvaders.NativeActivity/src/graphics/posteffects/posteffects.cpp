#include "posteffect.h"

PostEffect::PostEffect(Shader* shader) : shader(shader) {
	Vertex vertices[4];

	vertices[0].position = vec2(-1, -1);
	vertices[0].texCoord = vec2(0, 0);

	vertices[1].position = vec2(1, -1);
	vertices[1].texCoord = vec2(1, 0);

	vertices[2].position = vec2(1, 1);
	vertices[2].texCoord = vec2(1, 1);

	vertices[3].position = vec2(-1, 1);
	vertices[3].texCoord = vec2(0, 1);

	vbo = new VertexBuffer(vertices, sizeof(vertices));

	unsigned char indices[]{ 0, 1, 2, 2, 3, 0 };

	ibo = new IndexBuffer(indices, 6);
}

PostEffect::~PostEffect() {
	delete shader;
	delete vbo;
	delete ibo;
}

