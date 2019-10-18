#ifndef ARRAY_LIST_T
#define ARRAY_LIST_T
#include <stdlib.h>
#include <stdio.h>


/* STRUCT */

typedef struct array_list{
    void** array;
    size_t size;
    size_t capacity;
}array_list_t;

typedef struct it_array{
    array_list_t* it_array;
    unsigned int current_index;
}it_array_t;


/* FUNCTIONS DECLARATION */
array_list_t* array_list_new(size_t capacity);
void array_list_free(array_list_t* array);
size_t array_list_capacity(array_list_t* array);
void array_list_check_and_realloc(array_list_t* array);
void array_list_insert(array_list_t* array, void* element);
size_t array_list_size(array_list_t* array);
it_array_t* array_it_create (array_list_t *array);
void* array_iterator_get(it_array_t* it);
int array_it_has_next (it_array_t *itr);
void* array_it_next (it_array_t *itr);
void array_delete_iterator(it_array_t* it);
void* array_list_get_at(array_list_t* list, int pos);
int array_list_is_empty(array_list_t* list);
int array_it_is_empty(it_array_t *it);
#endif