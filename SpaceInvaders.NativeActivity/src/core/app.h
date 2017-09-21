#pragma once

#include <android/native_activity.h>
#include <android/native_window.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <pthread.h>

#include <core/log.h>

#define CMD_WINDOW_CREATE	0x01
#define CMD_WINDOW_DESTROY	0x02
#define CMD_INPUT_CREATED	0x03
#define CMD_INPUT_DESTROYED	0x04
#define CMD_ON_START		0x05
#define CMD_ON_STOP			0x06
#define CMD_ON_PAUSE		0x07
#define CMD_ON_RESUME		0x08
#define CMD_ON_DESTROY		0x09
#define CMD_ON_FOCUS		0x0A
#define CMD_ON_FOCUS_LOST	0x0B

#define APP_STATUS_TERMINATE	0x0
#define APP_STATUS_RUNNING		0x1
#define APP_STATUS_PAUSE		0x2

inline void GLCallLog(const char* const func, const char* const file, int line) {
	unsigned int error = glGetError();

	if (error) {
		LOGF("Error %u calling %s in %s:%u", error, func, file, line);
	}
}

#ifdef _DEBUG
#define DBG(code) code
#define ASSERT(x) if (!(x)) { LOGF("Assertion Failed: \"%s\" in \"%s:%u\"", #x, __FILE__, __LINE__); }
#define GL(func) func; GLCallLog(#func, __FILE__, __LINE__)
#else
#define ASSERT(x)
#define DBG(code)
#define GL(func) func
#endif

typedef void(*CMD_CALLBACK)();
typedef int(*INPUT_CALLBACK)(AInputEvent*);

class NativeApp {
public:
	static NativeApp* app;

	static bool Intialize(ANativeActivity* activity);
	static void Destroy();

	static float GetAspectRatio() { return (float)app->surface_width / app->surface_height; }
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
	AInputQueue* inputQueue;

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
