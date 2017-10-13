#include "renderer.h"

Renderer2::Renderer2(unsigned int num_sprites) : Renderer(num_sprites) {
	
	rawBuffer = new Vertex[num_sprites * 4];

}

Renderer2::~Renderer2() {
	delete[] rawBuffer;
}


void Renderer2::Begin() {
	texIds.Clear();
	count = 0;
	buffer = rawBuffer;
}


void Renderer2::End() {
	vbo->SetData(rawBuffer, (count / 6) * 4 * sizeof(Vertex));
	buffer = nullptr;
}

void Renderer2::Present() {
	shader->Bind();
	for (size_t i = 0; i < texIds.GetSize(); i++) {
		texIds[i]->Bind(i);
	}

	vbo->Bind();

	GL(glEnableVertexAttribArray(0));
	GL(glEnableVertexAttribArray(1));
	GL(glEnableVertexAttribArray(2));
	GL(glEnableVertexAttribArray(3));
	GL(glEnableVertexAttribArray(4));

	GL(glVertexAttribPointer(0, 3, GL_FLOAT,		 false, sizeof(Vertex), (const void*)MOFFSET(Vertex, position)));
	GL(glVertexAttribPointer(1, 2, GL_FLOAT,		 false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texCoord)));
	GL(glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, color)));
	GL(glVertexAttribPointer(3, 1, GL_FLOAT,		 false, sizeof(Vertex), (const void*)MOFFSET(Vertex, tid)));
	GL(glVertexAttribPointer(4, 1, GL_FLOAT,		 false, sizeof(Vertex), (const void*)MOFFSET(Vertex, text)));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ibo->Bind();
	glDrawElements(GL_TRIANGLES, count, ibo->GetFormat(), nullptr);

	glDisable(GL_BLEND);
}