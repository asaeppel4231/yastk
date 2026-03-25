#include "mstack.h"

mstack_t* new_mstack (int opts);
void      free_mstack(mstack_t* stack);

int       mstack_push(mstack_t* stack, void* data, int opts);
void*     mstack_pop (mstack_t* stack, int opts);