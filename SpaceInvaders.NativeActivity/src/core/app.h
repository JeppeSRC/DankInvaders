#pragma once

#include <android/native_activity.h>
#include <android/native_window.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <pthread.h>

#define CMD_WINDOW_CREATE	0x01
#define CMD_WINDOW_DESTROY	0x02
#define CMD_INPUT_CHANGED	0x03
#define CMD_ON_START		0x04
#define CMD_ON_STOP			0x05
#define CMD_ON_PAUSE		0x06
#define CMD_ON_RESUME		0x07
#define CMD_ON_DESTROY		0x08

#define APP_STATUS_TERMINATE	0x0
#define APP_STATUS_RUNNING		0x1
#define APP_STATUS_PAUSE		0x2

typedef void(*CMD_CALLBACK)();
typedef int(*INPUT_CALLBACK)(AInputEvent*);

class NativeApp {
public:
	static NativeApp* app;

	static bool Intialize(ANativeActivity* activity);
	static void Destroy();
public:
	ANativeActivity* activity;
	ANativeWindow* window;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	int surface_width;
	int surface_height;

	int msgRead;
	int msgWrite;

	int status;

	pthread_mutex_t mutex;
	pthread_cond_t cond;

	pthread_t thread;

	CMD_CALLBACK cmd;
	CMD_CALLBACK input;

	INPUT_CALLBACK OnInput;

	ALooper* looper;

private:
	NativeApp(ANativeActivity* activity);
	~NativeApp();

public:
	void Lock();
	void Unlock();

	void Start(void*(*startRoutine)(void*));
};

int read_cmd();
void write_cmd(int cmd);
