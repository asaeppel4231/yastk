#include "yastk.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

yastk_t* new_yastk (int opts);
void      free_yastk(yastk_t* stack);

int       push_yastk(yastk_t* stack, void* data, int opts);
void*     pop_yastk(yastk_t* stack, int opts);

char* info_yastk() {
    char* buf = malloc(2048);
    if (!buf) return NULL;

    buf[0] = '\0';

    snprintf(buf, 2048,
        "yastk version %d.%d.%d\n"
        "Build: %s\n"
        "Compiler: %s\n"
        "Platform: %s\n"
        "Pointer size: %zu bytes\n",
        YASTK_VERSION_MAJOR,
        YASTK_VERSION_MINOR,
        YASTK_VERSION_PATCHLEVEL,
#ifdef NDEBUG
        "Release",
#else
        "Debug",
#endif
#ifdef __clang__
    "Compiler: Clang %d.%d.%d\n",
    __clang_major__, __clang_minor__, __clang_patchlevel__,
#elif defined(__GNUC__)
    "Compiler: GCC %d.%d.%d\n",
    __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__,
#elif defined(_MSC_VER)
    "Compiler: MSVC %d\n",
    _MSC_VER
#else
    "Compiler: Unknown\n"
#endif
#ifdef __linux__
        "Linux",
#elif _WIN32
        "Windows",
#elif __APPLE__
        "macOS",
#else
        "Unknown OS",
#endif
        sizeof(void*)
    );

    return buf;
}
