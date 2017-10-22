#include <core/app.h>
#include <core/log.h>
#include <core/def.h>
#include <core/event.h>
#include <graphics/shader.h>
#include <graphics/buffer/vertexbuffer.h>
#include <graphics/buffer/indexbuffer.h>
#include <graphics/texture2d.h>
#include <android/sensor.h>
#include <unistd.h>
#include <math/math.h>
#include <util/asset/fileutils.h>
#include <graphics/render/renderer.h>
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

GameManager* man;

int OnGameInput(AInputEvent* event) {
	NativeApp* app = NativeApp::app;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		vec2 v(-1.0f, -1.0f);
		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN) {
			v.x = AMotionEvent_getX(event, 0) * app->xUnitsPerPixel;
			v.y = AMotionEvent_getY(event, 0) * app->yUnitsPerPixel;;
			EventDispatcher::OnPress(v);
		} else if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_MOVE) {
			v.x = AMotionEvent_getX(event, 0) * app->xUnitsPerPixel;
			v.y = AMotionEvent_getY(event, 0) * app->yUnitsPerPixel;
			EventDispatcher::OnMove(v);
		} else if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP) {
			v.x = -1.0f;
			v.y = -1.0f;
			EventDispatcher::OnRelease();
		}

		man->inputCoord = v;

		return 1;
	}

	return 0;
}


void game_main() {
	NativeApp* app = NativeApp::app;

	SetUPDisplay();

	GameManager manager;
	
	man = &manager;

	unsigned long long fps = 0;
	unsigned long long lastTime = mikrotime();
	unsigned long long lastTime2 = mikrotime();
	eglSwapInterval(app->display, 1);
	while (app->status) {
		ProcessInput();
		glClear(GL_COLOR_BUFFER_BIT);

		unsigned long long now = mikrotime();

		float delta = ((float)(now - lastTime)) / (float)1000000;
		lastTime = now;
		 
		manager.Update(delta);
		manager.Render();

		eglSwapBuffers(app->display, app->surface);

	/*	fps++;

		if (mikrotime() - lastTime2 >= 1000000) {
			LOGI("FPS: %llu", fps);
			lastTime2 = mikrotime();
			fps = 0;
		}*/
	}
}