#include "android/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int __android_log_write(int priority, const char* tag, const char* msg) {
    fprintf(stderr, "[android_log:%d] [%s] %s\n", priority, tag, msg);
    return 0;
}

int __android_log_print(int priority, const char* tag, const char* fmt, ...) {
    fprintf(stderr, "[android_log:%d] [%s] ", priority, tag);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    return 0;
}

void __android_log_assert(const char* cond, const char* tag, const char* fmt, ...) {
    fprintf(stderr, "[android_assert] [%s] ", tag);
    if (cond) {
        fprintf(stderr, "%s: ", cond);
    }
    if (fmt) {
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }
    fprintf(stderr, "\n");
    abort();
}