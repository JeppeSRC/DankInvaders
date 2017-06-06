#include "vertexbuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}