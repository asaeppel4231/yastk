#ifndef YASTK_H
#define YASTK_H

#include <stddef.h>

typedef struct yastk yastk_t;

yastk_t* new_yastk (int opts);
void      free_yastk(yastk_t* stack);

int       yastk_push(yastk_t* stack, void* data, int opts);
void*     yastk_pop (yastk_t* stack, int opts);

size_t    get_yastk_size(yastk_t* stack);

#endif
