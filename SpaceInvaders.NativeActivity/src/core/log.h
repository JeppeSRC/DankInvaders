#pragma once

#include <android/log.h>

#define LOGDEF(fmt...) __android_log_print(ANDROID_LOG_DEFAULT,   "SpaceInvaders", fmt)
#define LOGD(fmt...)   __android_log_print(ANDROID_LOG_DEBUG,     "SpaceInvaders", fmt)
#define LOGE(fmt...)   __android_log_print(ANDROID_LOG_ERROR,     "SpaceInvaders", fmt)
#define LOGF(fmt...)   __android_log_print(ANDROID_LOG_FATAL,     "SpaceInvaders", fmt)
#define LOGI(fmt...)   __android_log_print(ANDROID_LOG_INFO,      "SpaceInvaders", fmt)
#define LOGS(fmt...)   __android_log_print(ANDROID_LOG_SILENT,    "SpaceInvaders", fmt)
#define LOGU(fmt...)   __android_log_print(ANDROID_LOG_UNKNOWN,   "SpaceInvaders", fmt)
#define LOGV(fmt...)   __android_log_print(ANDROID_LOG_VERBOSE,   "SpaceInvaders", fmt)
#define LOGW(fmt...)   __android_log_print(ANDROID_LOG_WARN,      "SpaceInvaders", fmt)
