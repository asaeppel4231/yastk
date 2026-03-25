#include "_internal_mstack.h"

#include <stdlib.h>

struct mstack_entry{
    void* data;
    struct mstack_entry* next;
};

struct mstack{
    mstack_entry_t* head;
    mstack_entry_t* tail;
    size_t size;
};


// TODO: Unpause implementing

size_t    _internal_get_mstack_entry_struct_size(){
    return sizeof(mstack_entry_t);
}

void      _internal_init_mstack_entry(mstack_entry_t* entry){
    _internal_set_mstack_entry_data(entry, NULL, NULL);
    _internal_set_next_mstack_entry(entry, NULL, NULL);
}

int       _internal_free_mstack_entry(mstack_entry_t* entry, free_func func){
    if(func != NULL){
        func(_internal_get_mstack_entry_data(entry));
    }
}

int       _internal_free_mstack_entries(mstack_entry_t* entry, free_func func){
    mstack_entry_t* current;
    mstack_entry_t* next;
    current = entry;
    while(current != NULL ){

    }
}

void            _internal_set_next_mstack_entry(mstack_entry_t* entry, mstack_entry_t* next, free_func next_free_func){
    if(next_free_func != NULL){
        void* data;
        mstack_entry_t* next;
        next = _internal_get_next_mstack_entry(entry);
        data = _internal_get_mstack_entry_data(next);
        next_free_func(data);
        
    }
    entry->next = next;
}

mstack_entry_t* _internal_get_next_mstack_entry(mstack_entry_t* entry){
    return entry->next;
}

void      _internal_set_mstack_entry_data(mstack_entry_t* entry, void* data, free_func func){
    void* tmp_data = _internal_get_mstack_entry_data(entry);
    if(func != NULL){
        func(tmp_data);
    }
    tmp_data = data;
}

void*     _internal_get_mstack_entry_data(mstack_entry_t* entry){
    return entry->data;
}

size_t    _internal_get_mstack_struct_size(){
    return sizeof(mstack_t);
}

int       _internal_init_mstack(mstack_t* stack){
    //stack->head = malloc(_internal);
}
void      _internal_free_mstack(mstack_t* stack);

int       _internal_mstack_push(mstack_t* stack, void* data, int opts);
void*     _internal_mstack_pop (mstack_t* stack, int opts);

size_t    _internal_get_mstack_size(mstack_t* stack){
    return stack->size;
}