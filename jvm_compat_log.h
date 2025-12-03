#ifndef JVM_COMPAT_LOG_H
#define JVM_COMPAT_LOG_H

// Compatibility layer for Android logging functions when building for standard JVM

#ifdef ANDROID_JVM_BUILD

#include <stdio.h>

// Define Android logging constants
#define ANDROID_LOG_VERBOSE 2
#define ANDROID_LOG_DEBUG 3
#define ANDROID_LOG_INFO 4
#define ANDROID_LOG_WARN 5
#define ANDROID_LOG_ERROR 6
#define ANDROID_LOG_FATAL 7

// Provide compatible implementations of Android logging functions
#define __android_log_print(prio, tag, fmt, ...) \
    fprintf(stderr, "[%d/%s] " fmt "\n", prio, tag, ##__VA_ARGS__)

#define __android_log_write(prio, tag, text) \
    fprintf(stderr, "[%d/%s] %s\n", prio, tag, text)

#define __android_log_assert(cond_str, tag, fmt, ...) \
    do { \
        fprintf(stderr, "Assertion failed: %s [%s] " fmt "\n", cond_str, tag, ##__VA_ARGS__); \
        abort(); \
    } while(0)

#endif // ANDROID_JVM_BUILD

#endif // JVM_COMPAT_LOG_H