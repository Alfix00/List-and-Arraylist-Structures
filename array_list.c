#include "array_list.h"

//*-> Create new array_list
//* -----> 1) Funzione per creare una lista vuota.
array_list_t* array_list_new(size_t capacity) {
    array_list_t* result = (array_list_t*) malloc(sizeof(array_list_t));
    result->array = (void**) malloc(sizeof(void*)*capacity);
    result->size = 0;
    result->capacity = capacity;
    return result;
}
//*-> Free new array_list
//* -----> 2) Funzione per distruggere una lista.
void array_list_free(array_list_t* array) {
    free(array->array);
    free(array);
    array->size = 0;
}

/*-> Destroy array_list iterator
 * -----> 3) Funzione per distruggere iteratore */
void array_delete_iterator(it_array_t* it){
    free(it->it_array);
    free(it);
    it->it_array = NULL;
}

/*-> Check if the iterator is still valid
 * --->*4) Verifica se l'iteratore è ancora valido in O(1) */
int array_it_has_next (it_array_t *it) {
    return (it->current_index < it->it_array->size);
}

/*-> Get the current element of iterator
 * --->*5) Prende l'elemento corrente dell'iteratore (a cui sta puntando) */
void* array_iterator_get(it_array_t* it){
    void* data = NULL;
    if (array_it_has_next(it)) {
        data = it->it_array->array[it->current_index];
    }
    return data;
}

/*-> Get the next element of iterator
 * --->*6) Sposta l'iteratore all'elemento successivo */
void* array_it_next (it_array_t *it) {
    if(array_it_has_next(it)){
        it->current_index++;
    }
}

/*-> Get element in position N
 * --->*7) Prendi l'elemento in posizione N */
void* array_list_get_at(array_list_t* list, int pos){
    it_array_t* it = array_it_create(list);
    while(array_it_has_next(it) && pos > 0){
        it->current_index++;
        pos--;
    }
    return array_iterator_get(it);
}

/*-> check if the array_list is empty
 * --->*8) Prendi l'elemento in posizione N */
int array_list_is_empty(array_list_t *list) {
    return list->size == 0;
}

int array_it_is_empty(it_array_t *it){
    return it->it_array == NULL;
}
//*-> Get array_list size - Prendi la dimensione della lista
size_t array_list_size(array_list_t* array) {
    return array->size;
}
//*-> Get new array_list capacity - Prendi la capacità della lista
size_t array_list_capacity(array_list_t* array) {
    return array->capacity;
}
//*-> Allocate and reallocate memory - Alloca e rialloca la memoria
void array_list_check_and_realloc(array_list_t* array) {
    if(!(array->capacity > array->size )) {
        array->capacity *= 2;
        array->array = realloc(array->array, sizeof(void*) * array->capacity);
    }
}
//*-> Insert element - Inserisce un elemento in lista
void array_list_insert(array_list_t* array, void* element) {
    array_list_check_and_realloc(array);
    size_t i;
    for( i = array_list_size(array); i > 0; --i ) {
        array->array[i] = array->array[i-1];
    }
    array->array[i] = element;
    array->size += 1;
}

/*-> Create new iterator for the list
 * --->*Creazione dell'iteratore per la lista*/
it_array_t* array_it_create (array_list_t *array) {
    it_array_t* itr = malloc(sizeof(it_array_t));
    itr->it_array = array;
    itr->current_index = 0;
}
