#include "app.h"

#include "log.h"
#include "def.h"
#include <unistd.h>

void process_command();
void process_input();

NativeApp* NativeApp::app = nullptr;

bool NativeApp::Intialize(ANativeActivity* activity) {
	LOGD("Creating NativeApp");
	NativeApp::app = new NativeApp(activity);
	return true;
}

void NativeApp::Destroy() {
	LOGD("Destroying NativeApp");
	delete NativeApp::app;
}

NativeApp::NativeApp(ANativeActivity* activity) {
	this->activity = activity;

	window = nullptr;

	surface_width = 0;
	surface_height = 0;

	display = nullptr;
	surface = nullptr;
	context = nullptr;

	activity->instance = this;

	pthread_mutex_init(&mutex, nullptr);
	pthread_cond_init(&cond, nullptr);

	if (pipe(&msgRead) != 0) {
		LOGF("Failed to get pipes!");
		_exit(1);
	}

	cmd = process_command;
	input = process_input;
	OnInput = nullptr;
}

NativeApp::~NativeApp() {
	activity->instance = nullptr;

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}

void NativeApp::Lock() {
	pthread_mutex_lock(&mutex);
}

void NativeApp::Unlock() {
	pthread_mutex_unlock(&mutex);
}

void NativeApp::Start(void*(*startRoutine)(void*)) {

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	status = APP_STATUS_TERMINATE;
	pthread_create(&thread, &attr, startRoutine, nullptr);

	pthread_mutex_lock(&mutex);
	while(status != APP_STATUS_RUNNING) 
		pthread_cond_wait(&cond, &mutex);
	pthread_mutex_unlock(&mutex);
}

void InitializeDisplay() {
	NativeApp* app = NativeApp::app;

	int attrib[]{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_NONE
	};

	app->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	
	if (eglInitialize(app->display, 0, 0) == 0) {
		LOGE("Failed to initialize egl display");
	}

	int num_configs;
	EGLConfig config;

	eglChooseConfig(app->display, attrib, &config, 1, &num_configs);

	int format;

	eglGetConfigAttrib(app->display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

	app->surface = eglCreateWindowSurface(app->display, config, app->window, nullptr);
	app->context = eglCreateContext(app->display, config, nullptr, nullptr);

	if (eglMakeCurrent(app->display, app->surface, app->surface, app->context) == 0) {
		LOGE("Failed to make context current!");
		_exit(2);
	}
	
	eglQuerySurface(app->display, app->surface, EGL_WIDTH, &app->surface_width);
	eglQuerySurface(app->display, app->surface, EGL_HEIGHT, &app->surface_height);

	const char* version = eglQueryString(app->display, EGL_VERSION);
	const char* vendor = eglQueryString(app->display, EGL_VENDOR);
	const char* extensions = eglQueryString(app->display, EGL_EXTENSIONS);
	const char* apis = eglQueryString(app->display, EGL_CLIENT_APIS);

	LOGD("EGL Version: %s", version);
	LOGD("EGL Vendor:  %s", vendor);
	LOGD("EGL Extensions: %s", extensions);
	LOGD("EGL Client APIs: %s", apis);
	
	LOGD("Surface: width=%d height=%d", app->surface_width, app->surface_height);
}

void DestroyDisplay() {
	NativeApp* app = NativeApp::app;
	if (app->window) {
		eglMakeCurrent(app->display, 0, 0, 0);
		if (app->context) {
			eglDestroyContext(app->display, app->context);
			app->context = nullptr;
		}

		if (app->surface) {
			eglDestroySurface(app->display, app->surface);
		}

		eglTerminate(app->display);
	}

	app->display = nullptr;
	app->context = nullptr;
	app->surface = nullptr;
}

void process_command() {
	int cmd = read_cmd();
	NativeApp* app = NativeApp::app;

	switch (cmd) {
	case CMD_WINDOW_CREATE:
		InitializeDisplay();
		break;
	case CMD_WINDOW_DESTROY:
		DestroyDisplay();
		break;
	case CMD_ON_START:
	case CMD_ON_RESUME:
		app->status = APP_STATUS_RUNNING;
		break;
	case CMD_ON_PAUSE:
	case CMD_ON_STOP:
		app->status = APP_STATUS_PAUSE;
		break;
	case CMD_INPUT_CREATED:
		AInputQueue_attachLooper(app->inputQueue, app->looper, LOOPER_ID_INPUT, 0, (void*)app->input);
		break;
	case CMD_INPUT_DESTROYED:
		AInputQueue_detachLooper(app->inputQueue);
		app->inputQueue = nullptr;
		break;
	}
}

void process_input() {
	NativeApp* app = NativeApp::app;
	AInputEvent* event = nullptr;
	while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
		if (AInputQueue_preDispatchEvent(app->inputQueue, event)) continue;

		int h = 0;
		if (app->OnInput) h = app->OnInput(event);
		AInputQueue_finishEvent(app->inputQueue, event, h);
	}
}

int read_cmd() {
	int cmd = 0;
	if (read(NativeApp::app->msgRead, &cmd, sizeof(int)) == sizeof(int)) {
		return cmd;
	} 

	LOGE("No data in command pipe");
	return -1;
}

void write_cmd(int cmd) {
	if (write(NativeApp::app->msgWrite, &cmd, sizeof(int)) != sizeof(int)) {
		LOGE("Failed to write cmd!");
	}
}