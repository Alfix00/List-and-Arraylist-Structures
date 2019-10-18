#include "merge_sort.h"

/* MERGE LIST */

list_t* merge(list_t* list_1, list_t* list_2, CompFunction compare){
    list_t* new_list = list_create();
    list_iterator_t* it_1 = list_iterator_create(list_1);
    list_iterator_t* it_2 = list_iterator_create(list_2);
    int size_1 = list_get_size(list_1);
    int size_2 = list_get_size(list_2);
    while(size_1 && size_2){
        if(compare(list_iterator_get(it_1),list_iterator_get(it_2)) <= 0){
            list_push(new_list,list_iterator_get(it_1));
            list_iterator_next(it_1);
            size_1--;
        } else{
            list_push(new_list,list_iterator_get(it_2));
            list_iterator_next(it_2);
            size_2--;
        }
    }
    if(size_1 > 0 && !size_2){
        while(size_1){
            list_push(new_list,list_iterator_get(it_1));
            list_iterator_next(it_1);
            size_1--;
        }
    }
    if(size_2 > 0 && !size_1){
        while(size_2){
            list_push(new_list,list_iterator_get(it_2));
            list_iterator_next(it_2);
            size_2--;
        }
    }
    return new_list;
}

/* MERGE ARRAY_LIST */

array_list_t* merge_array(array_list_t* array_1, array_list_t* array_b, CompFunction compare){
    it_array_t* it_1 = array_it_create(array_1);
    it_array_t* it_2 = array_it_create(array_b);
    size_t index_a = array_1->size;
    size_t index_b = array_b->size;
    array_list_t* new_array = array_list_new(index_a+index_b);
    while(index_a && index_b ){
        if(compare(array_iterator_get(it_1),array_iterator_get(it_2)) > 0){
            array_list_insert(new_array,array_iterator_get(it_1));
            array_it_next(it_1);
            index_a--;
        } else{
            array_list_insert(new_array,array_iterator_get(it_2));
            array_it_next(it_2);
            index_b--;
        }
    }
    if(index_a > 0 && !index_b){
        while(index_a){
            array_list_insert(new_array,array_iterator_get(it_1));
            array_it_next(it_1);
            index_a--;
        }
    }
    if(index_b > 0 && !index_a){
        while(index_b){
            array_list_insert(new_array,array_iterator_get(it_2));
            array_it_next(it_2);
            index_b--;
        }
    }
    array_delete_iterator(it_1);
    array_delete_iterator(it_2);
    return new_array;
}