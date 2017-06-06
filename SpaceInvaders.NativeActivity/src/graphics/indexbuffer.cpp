#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const void* indices, unsigned int size, unsigned int format) {
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->format = format;
}

IndexBuffer::IndexBuffer(const unsigned short* indices, unsigned int num) : IndexBuffer(indices, num * sizeof(unsigned short), GL_UNSIGNED_SHORT) { count = num; }

IndexBuffer::IndexBuffer(const unsigned char* indices, unsigned int num) : IndexBuffer(indices, num * sizeof(unsigned char), GL_UNSIGNED_BYTE) { count = num; }

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &ibo);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}