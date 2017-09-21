#pragma once

#include <core/app.h>
#include <util/utils.h>

class VertexArray {
private:
	unsigned int vao;
	unsigned int stride;

public:
	VertexArray(unsigned int stride);
	~VertexArray();

	void AddAttribute(unsigned int index, unsigned int comp, unsigned int type, bool normalize, unsigned int offset) const;

	void Bind() const;
};