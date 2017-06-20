#include "renderer.h"
#include <string>

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

	shader = new Shader("shaders/vertex.hlsl", "shaders/fragment.hlsl", false);

	shader->Bind();

	int ids[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	
	shader->SetIntArray("samplers", 32, ids);
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

}

void Renderer::End() {

}

void Renderer::Present() {
	for (size_t i = 0; i < texIds.GetSize(); i++) {
		texIds[i]->Bind(i);
	}

	vbo->Bind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)12);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(Vertex), (const void*)20);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Vertex), (const void*)36);

	ibo->Bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, nullptr);
}