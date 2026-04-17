#include "_internal_yastk.h"

#include <stdlib.h>
#include <string.h>

// Fixes clangd errors if helpers.h not found
#ifndef LOG_FUNCTION_CALL
#define LOG_FUNCTION_CALL(fn_name)
#endif
#ifndef LOG_DEBUG
#define LOG_DEBUG(formatted_string, ...) /* NOTE: Requires C99 */
#endif

struct yastk_entry{
    void* data;
    struct yastk_entry* next;
};

struct yastk{
    yastk_entry_t* head;
    yastk_entry_t* tail;
    size_t size;
    free_func free_func;
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
    _internal_set_yastk_entry_data(entry, NULL);
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
    entry->next = next;
}

yastk_entry_t* _internal_get_next_yastk_entry(yastk_entry_t* entry){
    return entry->next;
}

void      _internal_set_yastk_entry_data(yastk_entry_t* entry, void* data){
    if(entry != NULL){
        entry->data = data;
    }
}

void*     _internal_get_yastk_entry_data(yastk_entry_t* entry){
    if(entry == NULL) return NULL;
    return entry->data;
}

size_t    _internal_get_yastk_struct_size(){
    return sizeof(yastk_t);
}

void     _internal_init_yastk(yastk_t* stack, int opts){
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    stack->free_func = NULL;
}

void     _internal_init_yastk_with_free_func(yastk_t* stack, int opts, free_func data_free_func){
    _internal_init_yastk(stack, opts);
    stack->free_func = data_free_func;
}

void     _internal_free_yastk(yastk_t* stack, int opts){
    _internal_free_yastk_entries(stack->head, stack->free_func);
    free(stack);
}

void      _internal_set_yastk_free_func(yastk_t* stack, free_func func){
    if(stack != NULL){
        stack->free_func = func;
    }
}

free_func _internal_get_yastk_free_func(yastk_t* stack){
    if(stack == NULL) return NULL;
    return stack->free_func;
}

void      _internal_yastk_push(yastk_t* stack, void* data, int opts){
#if INTERNAL_YASTK_DEBUG == 1
    LOG_FUNCTION_CALL("_internal_yastk_push");
#endif
    
    yastk_entry_t* temp = malloc(_internal_get_yastk_entry_struct_size());
    if(temp == NULL){
#if INTERNAL_YASTK_DEBUG == 1
        LOG_DEBUG("Failed to allocate memory for new entry\n");
#endif
        return;
    }

    _internal_init_yastk_entry(temp);
    _internal_set_yastk_entry_data(temp, data);
    
    if (stack->head == NULL) {
        stack->head = temp;
        stack->tail = temp;
    } else {
        _internal_set_next_yastk_entry(stack->tail, temp, NULL);
        stack->tail = temp;
    }
    
    stack->size++;
#if INTERNAL_YASTK_DEBUG == 1
    LOG_DEBUG("Pushed data at %p, stack size now %zu\n", data, stack->size);
#endif
}

void     _internal_yastk_pop(yastk_t* stack, void** out_data, int opts){
#if INTERNAL_YASTK_DEBUG == 1
    LOG_FUNCTION_CALL("_internal_yastk_pop");
#endif
    
    if (stack->size == 0 || stack->tail == NULL) {
#if INTERNAL_YASTK_DEBUG == 1
        LOG_DEBUG("Attempt to pop from empty stack\n");
#endif
        *out_data = NULL;
        return;
    }
    
    void* result = _internal_get_yastk_entry_data(stack->tail);
    
    if (stack->head == stack->tail) {
        /* Only one entry, remove it */
        _internal_free_yastk_entry(stack->tail, _internal_get_yastk_free_func(stack));
        stack->head = NULL;
        stack->tail = NULL;
    } else {
        /* Find previous node and update pointers */
        yastk_entry_t* temp = stack->head;
        while(temp != NULL && _internal_get_next_yastk_entry(temp) != stack->tail){
            temp = _internal_get_next_yastk_entry(temp);
        }
        _internal_free_yastk_entry(stack->tail, _internal_get_yastk_free_func(stack));
        stack->tail = temp;
        if (temp != NULL) {
            _internal_set_next_yastk_entry(temp, NULL, NULL);
        }
    }
    
    if (stack->size > 0) {
        stack->size--;
    }
    
#if INTERNAL_YASTK_DEBUG == 1
    LOG_DEBUG("Popped data at %p, stack size now %zu\n", result, stack->size);
#endif
    *out_data = result;
}

size_t    _internal_get_size_yastk(yastk_t* stack, int opts){
    return stack->size;
}

yastk_entry_t* _internal_get_head_yastk(yastk_t* stack, int opts){
    if(stack == NULL) return NULL;
#if INTERNAL_YASTK_DEBUG == 1
    LOG_DEBUG("Getting head entry (opts=%d)\n", opts);
#endif
    return stack->head;
}

yastk_entry_t* _internal_get_tail_yastk(yastk_t* stack, int opts){
    if(stack == NULL) return NULL;
#if INTERNAL_YASTK_DEBUG == 1
    LOG_DEBUG("Getting tail entry (opts=%d)\n", opts);
#endif
    return stack->tail;
}
