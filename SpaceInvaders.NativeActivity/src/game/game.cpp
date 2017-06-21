#include <core/app.h>
#include <core/log.h>
#include <core/def.h>
#include <graphics/shader.h>
#include <graphics/vertexbuffer.h>
#include <graphics/indexbuffer.h>
#include <graphics/texture2d.h>
#include <android/sensor.h>
#include <unistd.h>
#include <math/math.h>
#include <util/asset/fileutils.h>
#include <graphics/renderer.h>
#include <util/utils.h>

int OnGameInput(AInputEvent*);
void game_main();

static void SetUPDisplay() {
	int ident;
	int events;
	CMD_CALLBACK process_cmd = nullptr;

	while (!NativeApp::app->display) {
		while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&process_cmd)) >= 0) {
			if (process_cmd) process_cmd();
		}
	}
}

static void ProcessInput() {
	NativeApp* app = NativeApp::app;

	int ident;
	int events;
	CMD_CALLBACK process_cmd = nullptr;

	while ((ident = ALooper_pollAll(app->status == 2 ? -1 : 0, nullptr, &events, (void**)&process_cmd)) >= 0) {
		if (process_cmd) process_cmd();
	}
}

void* app_main(void*) {
	NativeApp* app = NativeApp::app;

	app->looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

	ALooper_addFd(app->looper, app->msgRead, LOOPER_ID_CMD, ALOOPER_EVENT_INPUT, nullptr, (void*)app->cmd);

	app->OnInput = OnGameInput;

	pthread_mutex_lock(&app->mutex);
	app->status = 1;
	pthread_cond_broadcast(&app->cond);
	pthread_mutex_unlock(&app->mutex);

	game_main();
	
	return nullptr;
}

int OnGameInput(AInputEvent* event) {
	NativeApp* app = NativeApp::app;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		float x = AMotionEvent_getX(event, 0);
		float y = AMotionEvent_getY(event, 0);


		return 1;
	} 

	return 0;
}


void game_main() {
	NativeApp* app = NativeApp::app;
	SetUPDisplay();

	Renderer renderer(128);

	Entity e(vec3(0, 0, 0.5f), vec2(0.5f, 0.5f));
	
	while (app->status) {
		ProcessInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer.Begin();
		renderer.Submit(&e);
		renderer.End();
		renderer.Present();


		eglSwapBuffers(app->display, app->surface);
	}

	/*Shader shader("shaders/vertex.hlsl", "shaders/fragment.hlsl", false);

	struct Vertex {
		vec3 position;
		vec2 texCoord;
	};

	Vertex vertices[]{
		{vec3(0, 1, 0), vec2(0.5, 0)},
		{vec3(1, -1, 0), vec2(1, 1)},
		{vec3(-1, -1, 0), vec2(0, 1)}
	};

	unsigned short indices[]{ 0, 1, 2 };

	VertexBuffer vbo(vertices, sizeof(vertices));
	IndexBuffer ibo(indices, 3);


	unsigned int pos = shader.GetAttributeLocation("position");
	unsigned int tex = shader.GetAttributeLocation("texCoords");

	shader.Bind();
	vbo.Bind();
	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(tex);

	glVertexAttribPointer(pos, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(tex, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)MOFFSET(Vertex, texCoord));

	Texture2D texture("textures/dank.png");

	shader.SetMat4("projection", mat4::Perspective(70.0f, 16.0f / 9.0f, 0.001f, 1000.0f).GetData());
	shader.SetMat4("model", mat4::Translate(vec3(0, 0, 3)).GetData());

	texture.Bind(0);

	glUniform1i(shader.GetUniformLocation("sampler"), 0);

	while (app->status) {
		ProcessInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	ibo.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), ibo.GetFormat(), nullptr);


		eglSwapBuffers(app->display, app->surface);
	}*/

}