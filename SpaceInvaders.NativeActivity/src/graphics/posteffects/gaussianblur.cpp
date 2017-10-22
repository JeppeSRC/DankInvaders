#include "posteffect.h"

static const char* vertex = "#version 100\n"
"attribute vec2 position;\n"
"attribute vec2 texCoords;\n"
""
"varying vec2 texCoord;\n"
""
"void main() {"
""
"	texCoord = texCoords;"
""
"	gl_Position = vec4(position, 0, 1);"
""
"}"
"\n"
"";


static const char* fragment = "#version 100\n"
"precision mediump float;"
""
""
"varying vec2 texCoord;\n"
""
"uniform sampler2D sampler;\n"
"uniform vec2 res;\n"
"uniform vec2 direction;\n"
""
"void main() {\n"
""
"	vec4 color = vec4(0);\n"
"	"
"   color += texture2D(sampler, texCoord + (vec2(-2, -2) * direction) / res) * 0.06136;\n"
"   color += texture2D(sampler, texCoord + (vec2(-1, -1) * direction) / res) * 0.24477;\n"
"   color += texture2D(sampler, texCoord + (vec2( 0,  0) * direction) / res) * 0.38774;\n"
"   color += texture2D(sampler, texCoord + (vec2( 1,  1) * direction) / res) * 0.24477;\n"
"   color += texture2D(sampler, texCoord + (vec2( 2,  2) * direction) / res) * 0.06136;\n"

" gl_FragColor = vec4(1, 0, 1, 1);\n"
"}"
"\n"
"";


PostEffectBlur::PostEffectBlur() : PostEffect(new Shader(vertex, fragment, true)) {

}

void PostEffectBlur::Render(Framebuffer2D* target, Texture2D* texture) {
	target->Bind();
	glClear(GL_COLOR_BUFFER_BIT);
	texture->Bind();

	vbo->Bind();

	GL(glEnableVertexAttribArray(0));
	GL(glEnableVertexAttribArray(1));

	GL(glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0));
	GL(glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)12));

	ibo->Bind();

	shader->Bind();

	shader->SetVec2("res", (float)texture->GetWidth(), (float)texture->GetHeight());
	shader->SetVec2("direction", 1, 0);
	

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	Framebuffer2D::Unbind();

}