#pragma once

#include <core/app.h>


class VertexBuffer {
private:
	unsigned int vbo;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
};