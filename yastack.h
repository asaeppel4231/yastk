#ifndef yastack_H
#define yastack_H

#include <stddef.h>

typedef struct yastack yastack_t;

yastack_t* new_yastack (int opts);
void      free_yastack(yastack_t* stack);

int       yastack_push(yastack_t* stack, void* data, int opts);
void*     yastack_pop (yastack_t* stack, int opts);

size_t    get_yastack_size(yastack_t* stack);

#endif
