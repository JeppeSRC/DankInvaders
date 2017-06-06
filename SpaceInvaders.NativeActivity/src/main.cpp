
#include <core/log.h>
#include <android/native_activity.h>
#include <android/configuration.h>
#include <core/app.h>
#include <game/game.h>


static void OnConfigurationChagned(ANativeActivity* activity) {
	LOGD("OnConfigurationChagned");
}

static void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
	LOGD("OnInputQueueCreated");
	NativeApp::app->inputQueue = queue;
	write_cmd(CMD_INPUT_CREATED);
}

static void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
	LOGD("OnInputQueueDestroyed");
	write_cmd(CMD_INPUT_DESTROYED);
}

static void OnLowMemory(ANativeActivity* activity) {
	LOGW("OnLowMemory!");
}

static void OnWindowFocusChagned(ANativeActivity* activity, int focus) {
	LOGD("OnWindowFocusChagned");
	write_cmd(focus ? CMD_ON_FOCUS : CMD_ON_FOCUS_LOST);
}

static void OnDestroy(ANativeActivity* activity) {
	LOGD("OnDestroy");
	write_cmd(CMD_ON_DESTROY);
}

static void OnPause(ANativeActivity* activity) {
	LOGD("OnPause");
	write_cmd(CMD_ON_PAUSE);
}

static void OnResume(ANativeActivity* activity) {
	LOGD("OnResume");
	write_cmd(CMD_ON_RESUME);
}

static void OnStart(ANativeActivity* activity) {
	LOGD("OnStart");
	write_cmd(CMD_ON_START);
}

static void OnStop(ANativeActivity* activity) {
	LOGD("OnStop");
	write_cmd(CMD_ON_STOP);
}

static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
	LOGD("OnNativeWindowCreated");
	((NativeApp*)activity->instance)->window = window;
	write_cmd(CMD_WINDOW_CREATE);
}

static void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
	LOGD("OnNativeWindowDestroyed");
	((NativeApp*)activity->instance)->window = nullptr;
	write_cmd(CMD_WINDOW_DESTROY);
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
	LOGD("OnCreate");

	activity->callbacks->onConfigurationChanged = OnConfigurationChagned;
	activity->callbacks->onDestroy = OnDestroy;
	activity->callbacks->onInputQueueCreated = OnInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed;
	activity->callbacks->onLowMemory = OnLowMemory;
	activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated;
	activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed;
	activity->callbacks->onPause = OnPause;
	activity->callbacks->onResume = OnResume;
	activity->callbacks->onStart = OnStart;
	activity->callbacks->onStop = OnStop;
	activity->callbacks->onWindowFocusChanged = OnWindowFocusChagned;

	NativeApp::Intialize(activity);

	NativeApp::app->Start(app_main);
}