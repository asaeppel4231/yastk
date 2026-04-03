#include "yastack.h"

yastack_t* new_yastack (int opts);
void      free_yastack(yastack_t* stack);

int       yastack_push(yastack_t* stack, void* data, int opts);
void*     yastack_pop (yastack_t* stack, int opts);