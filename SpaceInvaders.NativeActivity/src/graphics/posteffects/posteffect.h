#pragma once

#include <graphics/texture/framebuffer2d.h>
#include <graphics/shader.h>
#include <graphics/buffer/vertexbuffer.h>
#include <graphics/buffer/indexbuffer.h>
#include <math/vec2.h>

class PostEffect {
protected:
	struct Vertex {
		vec2 position;
		vec2 texCoord;
	};
protected:
	Shader* shader;

	VertexBuffer* vbo;
	IndexBuffer* ibo;

	PostEffect(Shader* effectShader);
	virtual ~PostEffect();
public:

	virtual void Render(Framebuffer2D* target, Texture2D* texture) = 0;
};

class PostEffectBlur : public PostEffect {
private:
	Framebuffer2D* tmp;

	float amount;
public:
	PostEffectBlur(float amount = 0.0f);
	~PostEffectBlur();

	void Render(Framebuffer2D* target, Texture2D* texture) override;
};