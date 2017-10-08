#pragma once

#include <core/app.h>
#include <math/math.h>
#include <game/entity/entity.h>
#include <graphics/buffer/vertexarray.h>
#include <graphics/buffer/vertexbuffer.h>
#include <graphics/buffer/indexbuffer.h>
#include <graphics/shader.h>
#include <graphics/font/font.h>
#include <util/map.h>
#include <util/string.h>
#include <math/vec3.h>
#include <math/vec2.h>


#define MAX_TEXTURES 0x10

struct Vertex {
	vec3 position;
	vec2 texCoord;
	unsigned int color;
	float tid;
};

class Renderer {
private:
	float xUnitsPerPixel;
	float yUnitsPerPixel;
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
	void		 Submit(const String& text, Font* font, const vec2& position);
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