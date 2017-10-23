#include "framebuffer2d.h"
#include <graphics/shader.h>
#include <math/math.h>
#include <graphics/buffer/vertexbuffer.h>
#include <graphics/buffer/indexbuffer.h>

Framebuffer2D::Framebuffer2D(unsigned int width, unsigned int height, unsigned int format, bool depthBuffer) : Texture2D(nullptr, width, height, format, GL_UNSIGNED_BYTE), fbo(0), dbo(0), clear(0) {
	GL(glGenFramebuffers(1, &fbo));
	GL(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
	
	GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0));

	clear |= GL_COLOR_BUFFER_BIT;

	if (depthBuffer) {
		GL(glGenRenderbuffers(1, &dbo));
		GL(glBindRenderbuffer(GL_RENDERBUFFER, dbo));
		GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height));
		GL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dbo));

		clear |= GL_DEPTH_BUFFER_BIT;
	}



	GLenum shit = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	if (shit != GL_FRAMEBUFFER_COMPLETE) {
		LOGF("Framebuffer not complete you nigga");
	}
}

Framebuffer2D::~Framebuffer2D() {
	GL(glDeleteRenderbuffers(1, &dbo));
	GL(glDeleteFramebuffers(1, &fbo));
}

void Framebuffer2D::BindAsRenderTarget() const {
	GL(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
	GL(glViewport(0, 0, width, height));
}

#define TEXT(x) #x

static const char* vertex =
"#version 100\n"

"attribute vec3 position;"
"attribute vec2 texCoords;"
"varying vec2 texCoord;"

"void main() {"
"texCoord = texCoords;"

"gl_Position = vec4(position, 1);"
"}"
"\n";


static const char* fragment =
"#version 100\n"
"precision mediump float;\n"
"\n"
"varying vec2 texCoord;\n"
"uniform sampler2D sampler;\n"
"void main() {\n"
"gl_FragColor = texture2D(sampler, texCoord);\n"
"}\n"
"\n";

void Framebuffer2D::DisplayFramebuffer() const {
	Shader shader(vertex, fragment, true);

	struct Vertex {
		vec3 position;
		vec2 texCoord;
	} vertices[4];

	vertices[0].position = vec3(-1, -1, 0);
	vertices[0].texCoord = vec2(0, 0);

	vertices[1].position = vec3(1, -1, 0);
	vertices[1].texCoord = vec2(1, 0);

	vertices[2].position = vec3(1, 1, 0);
	vertices[2].texCoord = vec2(1, 1);

	vertices[3].position = vec3(-1, 1, 0);
	vertices[3].texCoord = vec2(0, 1);

	VertexBuffer vbo(vertices, sizeof(vertices));

	unsigned short indices[]{ 0, 1, 2, 2, 3, 0 };

	IndexBuffer ibo(indices, 6);

	vbo.Bind();

	GL(glEnableVertexAttribArray(0));
	GL(glEnableVertexAttribArray(1));

	GL(glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0));
	GL(glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)12));

	ibo.Bind();
	shader.Bind();
	Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void Framebuffer2D::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, NativeApp::app->surface_width, NativeApp::app->surface_height);
}