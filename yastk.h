#ifndef YASTK_H
#define YASTK_H

#include <stddef.h>

#define YASTK_VERSION_MAJOR 0
#define YASTK_VERSION_MINOR 1
#define YASTK_VERSION_PATCHLEVEL 0

typedef struct yastk yastk_t;

yastk_t* new_yastk (int opts);
void     free_yastk(yastk_t* stack);

int      push_yastk(yastk_t* stack, void* data, int opts);
void*    pop_yastk (yastk_t* stack, int opts);

size_t   get_size_yastk(yastk_t* stack);

char*    info_yastk();

#endif
