#include "renderer.h"
#include <string>
#include <util/utils.h>

Renderer::Renderer(unsigned int num_sprites) {
	numSprites = num_sprites;

	buffer = new Vertex[numSprites * 4];

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

	ibo = new IndexBuffer(indices, numSprites * 6);
	vbo = new VertexBuffer(nullptr, numSprites * 4 * sizeof(Vertex));

	shader = new Shader("shaders/renderer.vs", "shaders/renderer.fs", false);

	shader->Bind();

	int ids[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader->SetIntArray("samplers", 32, ids);

	shader->SetMat4("projection", mat4::Orthographic(0, 1280, 0, 720, -1, 1).GetData());

}

Renderer::~Renderer() {
	delete[] buffer;
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
		if (index >= 31) {
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

void Renderer::Begin() {
	texIds.Clear();
	count = 0;
}

void Renderer::Submit(Entity* e) {
	float tid = SubmitTexture(e->GetTexture());
	tid = -1.0f;
	vec4 color = e->GetColor();
	vec3 position = e->GetPosition();
	vec2 size = e->GetSize();

	Vertex* buffer = this->buffer;

	buffer->position = position;
	buffer->texCoord = vec2(0, 0);
	buffer->color = color;
	buffer->tid = tid;
	buffer++;

	buffer->position = position + vec3(size.x, 0, 0);
	buffer->texCoord = vec2(1, 0);
	buffer->color = color;
	buffer->tid = tid;
	buffer++;

	buffer->position = position + vec3(size.x, -size.y, 0);
	buffer->texCoord = vec2(1, 1);
	buffer->color = color;
	buffer->tid = tid;
	buffer++;

	buffer->position = position + vec3(0, -size.y, 0);
	buffer->texCoord = vec2(0, 1);
	buffer->color = color;
	buffer->tid = tid;
	buffer++;

	count += 6;
}

void Renderer::End() {
	vbo->SetData(buffer, (count / 6) * 4 * sizeof(Vertex));
}

void Renderer::Present() {
	shader->Bind();
	for (size_t i = 0; i < texIds.GetSize(); i++) {
		texIds[i]->Bind(i);
	}

	vbo->Bind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	unsigned int a = shader->GetAttributeLocation("positions");
	a = shader->GetAttributeLocation("texCoords");
	a = shader->GetAttributeLocation("colors");
	a = shader->GetAttributeLocation("tids");

	glVertexAttribPointer(shader->GetAttributeLocation("positions"), 3, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, position));
	glVertexAttribPointer(shader->GetAttributeLocation("texCoords"), 2, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texCoord));
	glVertexAttribPointer(shader->GetAttributeLocation("colors"), 4, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, color));
	glVertexAttribPointer(shader->GetAttributeLocation("tids"), 1, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, tid));

	ibo->Bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, nullptr);
}