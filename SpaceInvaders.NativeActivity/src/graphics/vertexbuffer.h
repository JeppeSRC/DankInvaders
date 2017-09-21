#pragma once

#include <core/app.h>


class VertexBuffer {
private:
	unsigned int vbo;
	unsigned int size;
	
	bool dynamic;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void SetData(const void* const data, unsigned int size) const;
	void* Map(unsigned int mode) const;
	void Unmap() const;
};