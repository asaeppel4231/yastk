#include "_internal_yastk.h"

#include <stdlib.h>

struct yastk_entry{
    void* data;
    struct yastk_entry* next;
};

struct yastk{
    yastk_entry_t* head;
    yastk_entry_t* tail;
    size_t size;
};


// TODO: Unpause implementing

size_t    _internal_get_yastk_entry_struct_size(){
    return sizeof(yastk_entry_t);
}

void      _internal_init_yastk_entry(yastk_entry_t* entry){
    _internal_set_yastk_entry_data(entry, NULL, NULL);
    _internal_set_next_yastk_entry(entry, NULL, NULL);
}

int       _internal_free_yastk_entry(yastk_entry_t* entry, free_func func){
    if(func != NULL){
        func(_internal_get_yastk_entry_data(entry));
    }
}

int       _internal_free_yastk_entries(yastk_entry_t* entry, free_func func){
    yastk_entry_t* current;
    yastk_entry_t* next;
    current = entry;
    while(current != NULL ){

    }
}

void            _internal_set_next_yastk_entry(yastk_entry_t* entry, yastk_entry_t* next, free_func next_free_func){
    if(next_free_func != NULL){
        void* data;
        yastk_entry_t* next;
        next = _internal_get_next_yastk_entry(entry);
        data = _internal_get_yastk_entry_data(next);
        next_free_func(data);
        
    }
    entry->next = next;
}

yastk_entry_t* _internal_get_next_yastk_entry(yastk_entry_t* entry){
    return entry->next;
}

void      _internal_set_yastk_entry_data(yastk_entry_t* entry, void* data, free_func func){
    void* tmp_data = _internal_get_yastk_entry_data(entry);
    if(func != NULL){
        func(tmp_data);
    }
    tmp_data = data;
}

void*     _internal_get_yastk_entry_data(yastk_entry_t* entry){
    return entry->data;
}

size_t    _internal_get_yastk_struct_size(){
    return sizeof(yastk_t);
}

int       _internal_init_yastk(yastk_t* stack){
    //stack->head = malloc(_internal);
}
void      _internal_free_yastk(yastk_t* stack);

int       _internal_yastk_push(yastk_t* stack, void* data, int opts);
void*     _internal_yastk_pop (yastk_t* stack, int opts);

size_t    _internal_get_yastk_size(yastk_t* stack){
    return stack->size;
}