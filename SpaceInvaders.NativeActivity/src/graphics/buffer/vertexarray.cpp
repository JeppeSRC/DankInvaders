#include "vertexarray.h"


VertexArray::VertexArray(unsigned int stride) : stride(stride) {
	GL(glGenVertexArrays(1, &vao));
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::AddAttribute(unsigned int index, unsigned int comp, unsigned int type, bool normalize, unsigned int offset) const {
	glEnableVertexAttribArray(index);
	GL(glVertexAttribPointer(index, comp, type, normalize, stride, (const void*)offset));
}

void VertexArray::Bind() const {
	GL(glBindVertexArray(vao));
}
