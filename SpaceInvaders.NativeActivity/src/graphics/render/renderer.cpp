#include "renderer.h"
#include <string>
#include <util/utils.h>
#include <game/gamemanager.h>

Renderer::Renderer(unsigned int num_sprites) {
	numSprites = num_sprites;

	unsigned short offset = 0;
	unsigned short* indices = new unsigned short[numSprites * 6];

	for (unsigned int i = 0; i < numSprites; i++) {
		indices[i * 6 + 0] = offset + 0;
		indices[i * 6 + 1] = offset + 1;
		indices[i * 6 + 2] = offset + 2;
		indices[i * 6 + 3] = offset + 2;
		indices[i * 6 + 4] = offset + 3;
		indices[i * 6 + 5] = offset + 0;

		offset += 4;
	}

	vbo = new VertexBuffer(nullptr, numSprites * 4 * sizeof(Vertex));

	ibo = new IndexBuffer(indices, numSprites * 6);

	if (NativeApp::app->glesVersion == GLES_VERSION_2) {
		shader = new Shader("shaders/renderer_2.vs", "shaders/renderer_2.fs", false);
	}
	else {
		shader = new Shader("shaders/renderer_3.vs", "shaders/renderer_3.fs", false);
	}

	shader->Bind();
	
	int ids[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader->SetIntArray("samplers", MAX_TEXTURES, ids);

	shader->SetMat4("projection", mat4::Orthographic(0, GAME_AREA_WIDTH, 0, GAME_AREA_HEIGHT, -1, 1).GetData());
	//shader->SetMat4("projection", mat4::Identity().GetData());

}

Renderer::~Renderer() {
	delete vbo;
	delete ibo;
	delete shader;
}

float Renderer::SubmitTexture(Texture2D* tex) {
	if (!tex) return -1.0f;

	size_t index = texIds.Find(tex);

	if (index != (size_t)-1) {
		return (float)index + 0.5f;
	} else {
		index = texIds.GetSize();
		if (index >= MAX_TEXTURES-1) {
			End();
			Present();
			Begin();
			index = 0;
		}
		texIds.Push_back(tex);
		return (float)index + 0.5f;
	}

	return -0.0f;
}

void Renderer::Submit(Entity* e) {
	float tid = SubmitTexture(e->GetTexture());

	vec4 color = e->GetColor();
	vec3 position = e->GetPosition();
	vec2 size = e->GetSize();

	unsigned int r = (unsigned int)(color.x * 255) & 0xFF;
	unsigned int g = (unsigned int)(color.y * 255) & 0xFF;
	unsigned int b = (unsigned int)(color.z * 255) & 0xFF;
	unsigned int a = (unsigned int)(color.w * 255) & 0xFF;

	unsigned int col = a << 24 | b << 16 | g << 8 | r;

	buffer->position = position;
	buffer->texCoord = vec2(0, 0);
	buffer->color = col;
	buffer->tid = tid;
	buffer++;

	buffer->position = position + vec3(size.x, 0, 0);
	buffer->texCoord = vec2(1, 0);
	buffer->color = col;
	buffer->tid = tid;
	buffer++;

	buffer->position = position + vec3(size.x, size.y, 0);
	buffer->texCoord = vec2(1, 1);
	buffer->color = col;
	buffer->tid = tid;
	buffer++;

	buffer->position = position + vec3(0, size.y, 0);
	buffer->texCoord = vec2(0, 1);
	buffer->color = col;
	buffer->tid = tid;
	buffer++;
	
	count += 6;
}


Renderer* Renderer::CreateRenderer(unsigned int num_sprites) {
	if (NativeApp::app->glesVersion == GLES_VERSION_2) {
		return new Renderer2(num_sprites);
	}
	else {
		return new Renderer3(num_sprites);
	}

	return nullptr;
}