#ifndef INTERNAL_yastack
#define INTERNAL_yastack

#include <stddef.h>

typedef struct yastack_entry yastack_entry_t;

size_t    _internal_get_yastack_entry_struct_size();

typedef void(*free_func)(void*);

void       _internal_init_yastack_entry(yastack_entry_t* entry);
int       _internal_free_yastack_entry(yastack_entry_t* entry, free_func func);

int       _internal_free_yastack_entries(yastack_entry_t* entry, free_func func);

void            _internal_set_next_yastack_entry(yastack_entry_t* entry, yastack_entry_t* next, free_func next_free_func);
yastack_entry_t* _internal_get_next_yastack_entry(yastack_entry_t* entry);

void      _internal_set_yastack_entry_data(yastack_entry_t* entry, void* data, free_func func);
void*     _internal_get_yastack_entry_data(yastack_entry_t* entry);

typedef struct yastack yastack_t;

size_t    _internal_get_yastack_struct_size();

int       _internal_init_yastack(yastack_t* stack);
void      _internal_free_yastack(yastack_t* stack);

int       _internal_yastack_push(yastack_t* stack, void* data, int opts);
void*     _internal_yastack_pop (yastack_t* stack, int opts);

size_t    _internal_get_yastack_size(yastack_t* stack);

#endif