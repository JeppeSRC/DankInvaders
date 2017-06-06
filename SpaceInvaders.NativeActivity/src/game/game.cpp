#include <core/app.h>
#include <core/log.h>
#include <core/def.h>
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
	} 
}

void game_main() {
	NativeApp* app = NativeApp::app;

	int ident;
	int events;
	CMD_CALLBACK process_cmd = nullptr;

	glDisable(GL_DEPTH_TEST);

	while (app->status) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		while ((ident = ALooper_pollAll(app->status == 2 ? -1 : 0, nullptr, &events, (void**)&process_cmd)) >= 0) {
			if (process_cmd) process_cmd();
		}



		eglSwapBuffers(app->display, app->surface);
	}

}