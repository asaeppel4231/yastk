#include "_internal_yastack.h"

#include <stdlib.h>

struct yastack_entry{
    void* data;
    struct yastack_entry* next;
};

struct yastack{
    yastack_entry_t* head;
    yastack_entry_t* tail;
    size_t size;
};


// TODO: Unpause implementing

size_t    _internal_get_yastack_entry_struct_size(){
    return sizeof(yastack_entry_t);
}

void      _internal_init_yastack_entry(yastack_entry_t* entry){
    _internal_set_yastack_entry_data(entry, NULL, NULL);
    _internal_set_next_yastack_entry(entry, NULL, NULL);
}

int       _internal_free_yastack_entry(yastack_entry_t* entry, free_func func){
    if(func != NULL){
        func(_internal_get_yastack_entry_data(entry));
    }
}

int       _internal_free_yastack_entries(yastack_entry_t* entry, free_func func){
    yastack_entry_t* current;
    yastack_entry_t* next;
    current = entry;
    while(current != NULL ){

    }
}

void            _internal_set_next_yastack_entry(yastack_entry_t* entry, yastack_entry_t* next, free_func next_free_func){
    if(next_free_func != NULL){
        void* data;
        yastack_entry_t* next;
        next = _internal_get_next_yastack_entry(entry);
        data = _internal_get_yastack_entry_data(next);
        next_free_func(data);
        
    }
    entry->next = next;
}

yastack_entry_t* _internal_get_next_yastack_entry(yastack_entry_t* entry){
    return entry->next;
}

void      _internal_set_yastack_entry_data(yastack_entry_t* entry, void* data, free_func func){
    void* tmp_data = _internal_get_yastack_entry_data(entry);
    if(func != NULL){
        func(tmp_data);
    }
    tmp_data = data;
}

void*     _internal_get_yastack_entry_data(yastack_entry_t* entry){
    return entry->data;
}

size_t    _internal_get_yastack_struct_size(){
    return sizeof(yastack_t);
}

int       _internal_init_yastack(yastack_t* stack){
    //stack->head = malloc(_internal);
}
void      _internal_free_yastack(yastack_t* stack);

int       _internal_yastack_push(yastack_t* stack, void* data, int opts);
void*     _internal_yastack_pop (yastack_t* stack, int opts);

size_t    _internal_get_yastack_size(yastack_t* stack){
    return stack->size;
}