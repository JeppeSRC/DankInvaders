#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	ASSERT(size == 0);
	GL(glGenBuffers(1, &vbo));
	GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	
	GL(glBufferData(GL_ARRAY_BUFFER, size, data, data ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	
	this->size = size;
	
	dynamic = data == nullptr;
}

VertexBuffer::~VertexBuffer() {
	GL(glDeleteBuffers(1, &vbo));
}

void VertexBuffer::Bind() const {
	GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
}

void VertexBuffer::SetData(const void* const data, unsigned int size) const {
	ASSERT(size >= this->size);
	ASSERT(dynamic != true);
	GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void* VertexBuffer::Map(unsigned int mode) const {
	Bind();
	return glMapBufferRange(GL_ARRAY_BUFFER, 0, size, mode);
}

void VertexBuffer::Unmap() const {
	GL(glUnmapBuffer(GL_ARRAY_BUFFER));
}