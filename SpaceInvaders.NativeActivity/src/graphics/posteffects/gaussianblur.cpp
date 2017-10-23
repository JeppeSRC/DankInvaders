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
"	vec4 color = vec4(0, 0, 0, 1);\n"
"	"
"   color.xyz += texture2D(sampler, texCoord + (vec2(-4, -4) * direction) / res).xyz * 0.000229;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2(-3, -3) * direction) / res).xyz * 0.005977;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2(-2, -2) * direction) / res).xyz * 0.060598;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2(-1, -1) * direction) / res).xyz * 0.241732;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2( 0,  0) * direction) / res).xyz * 0.382928;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2( 1,  1) * direction) / res).xyz * 0.241732;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2( 2,  2) * direction) / res).xyz * 0.060598;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2( 3,  3) * direction) / res).xyz * 0.005977;\n"
"   color.xyz += texture2D(sampler, texCoord + (vec2( 4,  4) * direction) / res).xyz * 0.000229;\n"
" "
" gl_FragColor = color;\n"
"}"
"\n"
"";


PostEffectBlur::PostEffectBlur(float amount) : PostEffect(new Shader(vertex, fragment, true)), amount(1.0f - amount) {
	tmp = new Framebuffer2D(NativeApp::app->surface_width, NativeApp::app->surface_height, GL_RGB, false);
}

PostEffectBlur::~PostEffectBlur() {
	delete tmp;
}

void PostEffectBlur::Render(Framebuffer2D* target, Texture2D* texture) {
	tmp->BindAsRenderTarget();
	glClear(GL_COLOR_BUFFER_BIT);
	texture->Bind();

	vbo->Bind();

	GL(glEnableVertexAttribArray(0));
	GL(glEnableVertexAttribArray(1));

	GL(glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0));
	GL(glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)8));

	ibo->Bind();

	shader->Bind();

	shader->SetVec2("res", (float)texture->GetWidth() * amount, (float)texture->GetHeight() * amount);
	shader->SetVec2("direction", 1, 0);
	

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	target->BindAsRenderTarget();
	glClear(GL_COLOR_BUFFER_BIT);

	tmp->Bind();

	shader->SetVec2("direction", 0, 1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	Framebuffer2D::Unbind();

}