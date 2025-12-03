#ifndef _ANDROID_LOG_H
#define _ANDROID_LOG_H

// Compatibility layer for Android logging functions when building for standard JVM

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Android log priority values
typedef enum android_LogPriority {
    ANDROID_LOG_UNKNOWN = 0,
    ANDROID_LOG_DEFAULT,
    ANDROID_LOG_VERBOSE,
    ANDROID_LOG_DEBUG,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL,
    ANDROID_LOG_SILENT,
} android_LogPriority;

// Function declarations
int __android_log_write(int priority, const char* tag, const char* msg);
int __android_log_print(int priority, const char* tag, const char* fmt, ...);
void __android_log_assert(const char* cond, const char* tag, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // _ANDROID_LOG_H