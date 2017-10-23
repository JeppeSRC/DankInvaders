#pragma once

#include "texture2d.h"

class Framebuffer2D : public Texture2D {
private:
	unsigned int fbo;
	unsigned int dbo;

	unsigned int clear;

public:
	Framebuffer2D(unsigned int width, unsigned int height, unsigned int format, bool depthBuffer);
	~Framebuffer2D();

	void BindAsRenderTarget() const;
	void DisplayFramebuffer() const;

	static void Unbind();
};
