#include "yastk.h"

#ifdef NDEBUG
#define HAD_NDEBUG 1
#else
#define HAD_NDEBUG 0
#endif

#ifndef NDEBUG
#define NDEBUG
#endif
#include "_internal_yastk.h"

#if HAD_NDEBUG

#else
#undef NDEBUG
#endif


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

yastk_t* new_yastk(int opts) {
    yastk_t* stack = malloc(_internal_get_yastk_struct_size());
    if (stack == NULL) {
        return NULL;
    }
    _internal_init_yastk(stack, opts);
    return stack;
}

void free_yastk(yastk_t* stack) {
    if (stack != NULL) {
        _internal_free_yastk(stack, 0);
    }
}

int push_yastk(yastk_t* stack, void* data, int opts) {
    if (stack == NULL) {
        return -1;
    }
    _internal_yastk_push(stack, data, opts);
    return 0;
}

void* pop_yastk(yastk_t* stack, int opts) {
    if (stack == NULL || get_size_yastk(stack) == 0) {
        return NULL;
    }
    void* result = NULL;
    _internal_yastk_pop(stack, &result, opts);
    return result;
}

size_t get_size_yastk(yastk_t* stack) {
    if (stack == NULL) {
        return 0;
    }
    return _internal_get_size_yastk(stack, 0);
}

void* peek_head_yastk(yastk_t* stack) {
    if (stack == NULL || _internal_get_head_yastk(stack, 0) == NULL) {
        return NULL;
    }
    return _internal_get_yastk_entry_data(_internal_get_head_yastk(stack, 0));
}

void* peek_tail_yastk(yastk_t* stack) {
    if (stack == NULL || _internal_get_tail_yastk(stack, 0) == NULL) {
        return NULL;
    }
    return _internal_get_yastk_entry_data(_internal_get_tail_yastk(stack, 0));
}

char* info_yastk() {
    char* buf = malloc(2048);
    if (!buf) return NULL;

    buf[0] = '\0';

    const char* build_type = 
#ifdef NDEBUG
        "Release"
#else
        "Debug"
#endif
    ;
    
    const char* compiler = 
#ifdef __clang__
        "Clang"
#elif defined(__GNUC__)
        "GCC"
#elif defined(_MSC_VER)
        "MSVC"
#else
        "Unknown"
#endif
    ;
    
    const char* platform = 
#ifdef __linux__
        "Linux"
#elif defined(_WIN32)
        "Windows"
#elif defined(__APPLE__)
        "macOS"
#else
        "Unknown OS"
#endif
    ;

    snprintf(buf, 2048,
        "yastk version %d.%d.%d\n"
        "Build: %s\n"
        "Compiler: %s\n"
        "Platform: %s\n"
        "Pointer size: %zu bytes\n",
        YASTK_VERSION_MAJOR,
        YASTK_VERSION_MINOR,
        YASTK_VERSION_PATCHLEVEL,
        build_type,
        compiler,
        platform,
        sizeof(void*)
    );

    return buf;
}
