#ifndef INTERNAL_MSTACK
#define INTERNAL_MSTACK

#include <stddef.h>

typedef struct mstack_entry mstack_entry_t;

size_t    _internal_get_mstack_entry_struct_size();

typedef void(*free_func)(void*);

void       _internal_init_mstack_entry(mstack_entry_t* entry);
int       _internal_free_mstack_entry(mstack_entry_t* entry, free_func func);

int       _internal_free_mstack_entries(mstack_entry_t* entry, free_func func);

void            _internal_set_next_mstack_entry(mstack_entry_t* entry, mstack_entry_t* next, free_func next_free_func);
mstack_entry_t* _internal_get_next_mstack_entry(mstack_entry_t* entry);

void      _internal_set_mstack_entry_data(mstack_entry_t* entry, void* data, free_func func);
void*     _internal_get_mstack_entry_data(mstack_entry_t* entry);

typedef struct mstack mstack_t;

size_t    _internal_get_mstack_struct_size();

int       _internal_init_mstack(mstack_t* stack);
void      _internal_free_mstack(mstack_t* stack);

int       _internal_mstack_push(mstack_t* stack, void* data, int opts);
void*     _internal_mstack_pop (mstack_t* stack, int opts);

size_t    _internal_get_mstack_size(mstack_t* stack);

#endif