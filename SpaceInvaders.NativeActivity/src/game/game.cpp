#include <core/app.h>
#include <core/log.h>
#include <core/def.h>
#include <graphics/shader.h>
#include <graphics/vertexbuffer.h>
#include <graphics/indexbuffer.h>
#include <android/sensor.h>
#include <unistd.h>


int OnGameInput(AInputEvent*);
void game_main();

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
	
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		float x = AMotionEvent_getX(event, 0);
		float y = AMotionEvent_getY(event, 0);
		LOGD("X: %f Y: %f", x, y);
		return 1;
	} 

	return 0;
}

const char* vert =
"#version 100\n"
"attribute vec3 position;\n"
"void main() {\n"
"gl_Position = vec4(position, 1);"
"}\n"
"\n";

const char* frag =
"#version 100\n"
"void main() {\n"
"gl_FragColor = vec4(1, 1, 1, 1);\n"
"}\n"
"\n";

void game_main() {
	NativeApp* app = NativeApp::app;

	int ident;
	int events;
	CMD_CALLBACK process_cmd = nullptr;

	while (!app->display) {
		while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&process_cmd)) >= 0) {
			if (process_cmd) process_cmd();
		}
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Shader shader(vert, frag);
	shader.Bind();

	float vertices[]{
		0, 1, 0,
		1, -1, 0,
		-1, -1, 0
	};

	unsigned short indices[]{ 0, 1, 2 };

	VertexBuffer vbo(vertices, sizeof(vertices));
	IndexBuffer ibo(indices, 3);
	
	unsigned int position = shader.GetAttributeLocation("position");

	vbo.Bind();
	ibo.Bind();
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 3, GL_FLOAT, false, 0, 0);

	while (app->status) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		while ((ident = ALooper_pollAll(app->status == 2 ? -1 : 0, nullptr, &events, (void**)&process_cmd)) >= 0) {
			if (process_cmd) process_cmd();
		}
		
	
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

		eglSwapBuffers(app->display, app->surface);
	}

}