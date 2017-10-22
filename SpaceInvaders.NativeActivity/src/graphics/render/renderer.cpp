#include "renderer.h"
#include <string>
#include <util/utils.h>
#include <game/gamemanager.h>
#include <freetype-gl.h>

Shader* Renderer::displayShader = nullptr;
VertexBuffer* Renderer::displayVbo = nullptr;
IndexBuffer* Renderer::displayIbo = nullptr;
Renderer::V Renderer::vertices[4];

Renderer::Renderer(unsigned int num_sprites) {
	numSprites = num_sprites;

	unsigned short offset = 0;
	unsigned short* indices = new unsigned short[numSprites * 6];

	for (unsigned int i = 0; i < numSprites; i++) {
		indices[i * 6 + 0] = offset + 0;
		indices[i * 6 + 1] = offset + 1;
		indices[i * 6 + 2] = offset + 2;
		indices[i * 6 + 3] = offset + 2;
		indices[i * 6 + 4] = offset + 3;
		indices[i * 6 + 5] = offset + 0;

		offset += 4;
	}

	vbo = new VertexBuffer(nullptr, numSprites * 4 * sizeof(Vertex));

	ibo = new IndexBuffer(indices, numSprites * 6);

	if (NativeApp::app->glesVersion == GLES_VERSION_2) {
		shader = new Shader("shaders/renderer_2.vs", "shaders/renderer_2.fs", false);
	}
	else {
		shader = new Shader("shaders/renderer_3.vs", "shaders/renderer_3.fs", false);
	}

	shader->Bind();
	
	int ids[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader->SetIntArray("samplers", MAX_TEXTURES, ids);

	shader->SetMat4("projection", mat4::Orthographic(0, GAME_AREA_WIDTH, 0, GAME_AREA_HEIGHT, -1, 1).GetData());
	//shader->SetMat4("projection", mat4::Identity().GetData());

	if (!displayShader) {
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

		displayShader = new Shader(vertex, fragment, true);

		vertices[0].position = vec3(-1, -1, 0);
		vertices[0].texCoord = vec2(0, 0);

		vertices[1].position = vec3(1, -1, 0);
		vertices[1].texCoord = vec2(1, 0);

		vertices[2].position = vec3(1, 1, 0);
		vertices[2].texCoord = vec2(1, 1);

		vertices[3].position = vec3(-1, 1, 0);
		vertices[3].texCoord = vec2(0, 1);

		displayVbo = new VertexBuffer(vertices, sizeof(vertices));

		unsigned char indices[]{ 0, 1, 2, 2, 3, 0 };

		displayIbo = new IndexBuffer(indices, 6, GL_UNSIGNED_BYTE);
	}
}

Renderer::~Renderer() {
	delete vbo;
	delete ibo;
	delete shader;
}

float Renderer::SubmitTexture(Texture2D* tex) {
	if (!tex) return -1.0f;

	size_t index = texIds.Find(tex);

	if (index != (size_t)-1) {
		return (float)index + 0.5f;
	} else {
		index = texIds.GetSize();
		if (index >= MAX_TEXTURES-1) {
			End();
			Present();
			Begin();
			index = 0;
		}
		texIds.Push_back(tex);
		return (float)index + 0.5f;
	}

	return -0.0f;
}

void Renderer::Submit(const vec3& position, const vec2& size, unsigned int color, Texture2D* texture) {
	float tid = SubmitTexture(texture);

	buffer->position = position + vec2(size.x * -0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(0, 0);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	buffer->position = position + vec2(size.x * 0.5f, size.y * -0.5f);
	buffer->texCoord = vec2(1, 0);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	buffer->position = position + vec2(size.x * 0.5f, size.y * 0.5f);
	buffer->texCoord = vec2(1, 1);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	buffer->position = position + vec2(size.x * -0.5f, size.y * 0.5f);
	buffer->texCoord = vec2(0, 1);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	count += 6;
}

void Renderer::Submit(Entity* e) {
	float tid = SubmitTexture(e->GetTexture());

	unsigned int color = e->GetColor();
	const vec3& position = e->GetPosition();
	const vec2& size = e->GetSize();
	const vec2& scale = e->GetTextureScale();
	const float& rotation = e->GetRotation();

	/*unsigned int r = (unsigned int)(color.x * 255) & 0xFF;
	unsigned int g = (unsigned int)(color.y * 255) & 0xFF;
	unsigned int b = (unsigned int)(color.z * 255) & 0xFF;
	unsigned int a = (unsigned int)(color.w * 255) & 0xFF;*/

	//unsigned int col = a << 24 | b << 16 | g << 8 | r;

	buffer->position = position + vec2(size.x * -0.5f, size.y * -0.5f).RotateZ(rotation);
	buffer->texCoord = scale;
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	buffer->position = position + vec2(size.x * 0.5f, size.y * -0.5f).RotateZ(rotation);
	buffer->texCoord = vec2(1.0f - scale.x, scale.y);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	buffer->position = position + vec2(size.x * 0.5f, size.y * 0.5f).RotateZ(rotation);
	buffer->texCoord = vec2(1.0f - scale.x, 1.0f - scale.y);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;

	buffer->position = position + vec2(size.x * -0.5f, size.y * 0.5f).RotateZ(rotation);
	buffer->texCoord = vec2(scale.x, 1.0f - scale.y);
	buffer->color = color;
	buffer->tid = tid;
	buffer->text = 0.0f;
	buffer++;
	
	count += 6;
}

void Renderer::Submit(const String& text, Font* font, const vec2& position, unsigned int color) {
	float tid = SubmitTexture(font->GetTexture());

	float xPos = position.x;
	float yPos = position.y;

	ftgl::texture_font_t* f = font->GetFont();

	color |= 0xFF000000;

	for (size_t i = 0; i < text.length; i++) {
		char c = text[i];

		if (c == ' ') {
			xPos += font->GetSize() * NativeApp::app->xUnitsPerPixel * 0.25f;
			continue;
		}

		ftgl::texture_glyph_t* glyph = texture_font_get_glyph(f, c);

		float x = xPos + glyph->offset_x * NativeApp::app->xUnitsPerPixel;
		float y = yPos - glyph->offset_y * NativeApp::app->yUnitsPerPixel;

		if (i != 0) {
			float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			x += kerning * NativeApp::app->xUnitsPerPixel;
		}

		float bitmapWidth = (float)glyph->width * NativeApp::app->xUnitsPerPixel;
		float bitmapHeight = (float)glyph->height * NativeApp::app->yUnitsPerPixel;

		float u0 = glyph->s0;
		float v0 = glyph->t0;
		float u1 = glyph->s1;
		float v1 = glyph->t1;

		buffer->position.x = x;
		buffer->position.y = y;
		buffer->texCoord.x = u0;
		buffer->texCoord.y = v0;
		buffer->color = color;
		buffer->tid = tid;
		buffer->text = 1.0f;
		buffer++;

		buffer->position.x = x + bitmapWidth;
		buffer->position.y = y;
		buffer->texCoord.x = u1;
		buffer->texCoord.y = v0;
		buffer->color = color;
		buffer->tid = tid;
		buffer->text = 1.0f;
		buffer++;

		buffer->position.x = x + bitmapWidth;
		buffer->position.y = y + bitmapHeight;
		buffer->texCoord.x = u1;
		buffer->texCoord.y = v1;
		buffer->color = color;
		buffer->tid = tid;
		buffer->text = 1.0f;
		buffer++;

		buffer->position.x = x;
		buffer->position.y = y + bitmapHeight;
		buffer->texCoord.x = u0;
		buffer->texCoord.y = v1;
		buffer->color = color;
		buffer->tid = tid;
		buffer->text = 1.0f;
		buffer++;

		count += 6;

		xPos += glyph->advance_x * NativeApp::app->xUnitsPerPixel;
	}

}

Renderer* Renderer::CreateRenderer(unsigned int num_sprites) {
	if (NativeApp::app->glesVersion == GLES_VERSION_2) {
		return new Renderer2(num_sprites);
	}
	else {
		return new Renderer3(num_sprites);
	}

	return nullptr;
}

void Renderer::DisplayTexture(Texture2D* texture) {
	displayShader->Bind();

	displayVbo->Bind();

	GL(glEnableVertexAttribArray(0));
	GL(glEnableVertexAttribArray(1));

	GL(glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(V), 0));
	GL(glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(V), (const void*)12));

	displayIbo->Bind();

	texture->Bind();

	GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0));
}