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

size_t    _internal_get_yastk_entry_struct_size(){
    return sizeof(yastk_entry_t);
}

void       _internal_helper_call_free_func_yastk(free_func func, void* data){
    if(func != NULL){
        if(data != NULL){
            func(data);
        }
    }
}

void      _internal_init_yastk_entry(yastk_entry_t* entry){
    _internal_set_yastk_entry_data(entry, NULL, NULL);
    _internal_set_next_yastk_entry(entry, NULL, NULL);
}

void     _internal_free_yastk_entry(yastk_entry_t* entry, free_func func){
    _internal_helper_call_free_func_yastk(func, _internal_get_yastk_entry_data(entry));
    free(entry);
}

void     _internal_free_yastk_entries(yastk_entry_t* entry, free_func func){
    yastk_entry_t* current;
    yastk_entry_t* next;
    current = entry;
    while(current != NULL){
        next = _internal_get_next_yastk_entry(current);
        _internal_free_yastk_entry(current, func);
        current = next;   
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

void     _internal_init_yastk(yastk_t* stack, int opts){
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
}

void     _internal_free_yastk(yastk_t* stack, int opts){
    _internal_free_yastk_entries(stack->head, NULL); /* FIXME: Register a free function in the structure*/
    free(stack);
}

void      _internal_push_yastk(yastk_t* stack, void* data, int opts){
    yastk_entry_t* temp = malloc(_internal_get_yastk_entry_struct_size());
    if(temp == NULL){
        return;
    }

    _internal_init_yastk_entry(temp);
    _internal_set_yastk_entry_data(temp, data, NULL); /* FIXME: Save a free function in the structure and use that*/
    _internal_set_next_yastk_entry(stack->tail, temp, NULL);

}

void     _internal_pop_yastk(yastk_t* stack, void** out_data, int opts){
    void* result = _internal_get_yastk_entry_data(stack->tail);
    yastk_entry_t* temp = stack->head;
    while(temp != NULL && _internal_get_next_yastk_entry(temp) != stack->tail){ /* TODO: Use a helper pointer instead*/
        temp = _internal_get_next_yastk_entry(temp);
    }
    _internal_free_yastk_entry(stack->tail, NULL); /* See Line 101 and 90 */
    _internal_set_next_yastk_entry(temp, NULL, NULL);
    
    stack->tail = temp;
    
    *out_data = result;
}

size_t    _internal_get_size_yastk(yastk_t* stack, int opts){
    return stack->size;
}