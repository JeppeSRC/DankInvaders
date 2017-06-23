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
#include <game/gamemanager.h>
#include <ctime>

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

float x = -1, y = -1;

int OnGameInput(AInputEvent* event) {
	NativeApp* app = NativeApp::app;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN) {
			LOGD("DOWN");
			
		}

		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP) {
			x = -1;
			y = -1;
			LOGD("UP");
		} else {
			x = AMotionEvent_getX(event, 0);
			y = AMotionEvent_getY(event, 0);
		}

		return 1;
	}

	return 0;
}


void game_main() {
	NativeApp* app = NativeApp::app;
	SetUPDisplay();

	GameManager manager;
	
	unsigned int lastTime = clock();

	while (app->status) {
		ProcessInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		unsigned int now = clock();

		float delta = ((float)(now - lastTime)) / 1000.0f;
		lastTime = now;

		manager.Update(delta, x, y);
		manager.Render();

		eglSwapBuffers(app->display, app->surface);
	}
}