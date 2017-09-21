#pragma once

#include <core/app.h>
#include <math/math.h>
#include <game/entity/entity.h>
#include <graphics/vertexarray.h>
#include <graphics/vertexbuffer.h>
#include <graphics/indexbuffer.h>
#include <graphics/shader.h>
#include <util/map.h>

struct Vertex {
	vec3 position;
	vec2 texCoord;
	unsigned int color;
	float tid;
};

class Renderer {
private:
	unsigned int numSprites;
	unsigned short count;

	Vertex* buffer;

	VertexArray* vao;
	VertexBuffer* vbo;
	IndexBuffer* ibo;

	List<Texture2D*> texIds;

	Shader* shader;

	float SubmitTexture(Texture2D* tex);

public:
	Renderer(unsigned int num_sprites);
	~Renderer();

	void Begin();
	void Submit(Entity* e);
	void End();
	void Present();
};
