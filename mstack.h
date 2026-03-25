#ifndef MSTACK_H
#define MSTACK_H

#include <stddef.h>

typedef struct mstack mstack_t;

mstack_t* new_mstack (int opts);
void      free_mstack(mstack_t* stack);

int       mstack_push(mstack_t* stack, void* data, int opts);
void*     mstack_pop (mstack_t* stack, int opts);

size_t    get_mstack_size(mstack_t* stack);

#endif
