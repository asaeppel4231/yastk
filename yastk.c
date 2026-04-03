#include "yastk.h"

yastk_t* new_yastk (int opts);
void      free_yastk(yastk_t* stack);

int       yastk_push(yastk_t* stack, void* data, int opts);
void*     yastk_pop (yastk_t* stack, int opts);