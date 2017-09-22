#pragma once

#include <core/app.h>
#include <math/math.h>
#include <game/entity/entity.h>
#include <graphics/vertexarray.h>
#include <graphics/vertexbuffer.h>
#include <graphics/indexbuffer.h>
#include <graphics/shader.h>
#include <util/map.h>

#define MAX_TEXTURES 0x10

struct Vertex {
	vec3 position;
	vec2 texCoord;
	unsigned int color;
	float tid;
};

class Renderer {
protected:
	unsigned int numSprites;
	unsigned short count;

	Vertex* buffer;

	VertexBuffer* vbo;
	IndexBuffer* ibo;

	List<Texture2D*> texIds;

	Shader* shader;

	float SubmitTexture(Texture2D* tex);

	Renderer(unsigned int num_sprites);
public:
	virtual ~Renderer();

	virtual void Begin() = 0;
	void		 Submit(Entity* e);
	virtual void End() = 0;
	virtual void Present() = 0;

public:
	static Renderer* CreateRenderer(unsigned int num_sprites);
};

class Renderer2 : public Renderer {
private:
	Vertex* rawBuffer;

public:
	Renderer2(unsigned int num_sprites);
	~Renderer2();

	void Begin() override;
	void End() override;
	void Present() override;
};

class Renderer3 : public Renderer {
private:
	VertexArray* vao;

public:
	Renderer3(unsigned int num_sprites);
	~Renderer3();

	void Begin() override;
	void End() override;
	void Present() override;
};