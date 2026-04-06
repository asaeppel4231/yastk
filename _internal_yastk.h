#ifndef INTERNAL_YASTK
#define INTERNAL_YASTK

#include <stddef.h>

#define YASTK_NO_OPTS 0
#define YASTK_STUB 1
#define YASTK_PROVOCATE_ERROR 2

#define YASTK_STUB_RETVAL 0

typedef struct yastk_entry yastk_entry_t;

size_t    _internal_get_yastk_entry_struct_size();

typedef void(*free_func)(void*);

void       _internal_helper_call_free_func_yastk(free_func func, void* data);

void      _internal_init_yastk_entry(yastk_entry_t* entry);

void     _internal_free_yastk_entry(yastk_entry_t* entry, free_func func);
void     _internal_free_yastk_entries(yastk_entry_t* entry, free_func func);

void            _internal_set_next_yastk_entry(yastk_entry_t* entry, yastk_entry_t* next, free_func next_free_func);
yastk_entry_t* _internal_get_next_yastk_entry(yastk_entry_t* entry);

void      _internal_set_yastk_entry_data(yastk_entry_t* entry, void* data, free_func func);
void*     _internal_get_yastk_entry_data(yastk_entry_t* entry);

typedef struct yastk yastk_t;

size_t    _internal_get_yastk_struct_size();

void     _internal_init_yastk(yastk_t* stack, int opts);
void     _internal_free_yastk(yastk_t* stack, int opts);

void      _internal_yastk_push(yastk_t* stack, void* data, int opts);
void     _internal_yastk_pop (yastk_t* stack, void** out_data, int opts);

size_t    _internal_get_size_yastk(yastk_t* stack, int opts);

yastk_entry_t* _internal_get_head_yastk(yastk_t* stack, int opts);
yastk_entry_t* _internal_get_tail_yastk(yastk_t* stack, int opts);

#endif