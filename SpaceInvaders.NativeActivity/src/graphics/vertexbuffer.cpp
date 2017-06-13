#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	ASSERT(size != 0);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, size, data, data ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->size = size;
	
	dynamic = data == nullptr;
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::SetData(const void* const data, unsigned int size) const {
	ASSERT(size <= this->size);
	ASSERT(dynamic == true);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}