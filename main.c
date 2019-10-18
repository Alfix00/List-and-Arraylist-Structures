#include "unity.h"
#include "unity_internals.h"
#include "list.h"
#include "array_list.h"
#include "merge_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* new_int(int value) {
    int* elem = (int*) malloc(sizeof(int));
    *elem = value;
    return elem;
}


/* Create build for List And ArrayList */

array_list_t* build_fixture() {
    array_list_t* array = array_list_new(5);
    array_list_insert(array, new_int(10));
    array_list_insert(array, new_int(7));
    array_list_insert(array, new_int(4));
    array_list_insert(array, new_int(1));
    return array;
}

list_t* build_fixture_list(){
    list_t* list = list_create();
    list_push(list,new_int(0));
    list_push(list,new_int(1));
    list_push(list,new_int(2));
    list_push(list,new_int(3));
    list_push(list,new_int(4));
    return list;
}

/* Compare function for list and dynamic arrays (compare the current element with the next element) */

int compare_int(void* ptr1, void* ptr2) {
    int i1 =  *(int*)ptr1;
    int i2 =  *(int*)ptr2;
    if(i1<i2) {
        return -1;
    }
    if(i1==i2) {
        return 0;
    }
    return 1;
}


/* UNIT TEST MERGE_SORT ON LIST */

void test_merge_list_new_not_null(){
    list_t* list_1 = list_create();
    list_t* list_2 = list_create();
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_1));
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_2));
    list_t* list_3 = merge(list_1,list_2,compare_int);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_3));
    list_delete(list_1);
    list_delete(list_2);
    list_delete(list_3);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_1));
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_2));
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_2));
}

void test_merge_two_lists() {
    list_t* list_1 = list_create();
    list_t* list_2 = list_create();
    list_push(list_1,new_int(0));
    list_push(list_1,new_int(2));
    list_push(list_1,new_int(4));
    list_push(list_1,new_int(6));
    list_push(list_1,new_int(8));
    TEST_ASSERT_EQUAL_INT(0,list_is_empty(list_1));
    TEST_ASSERT_EQUAL_INT(5, list_get_size(list_1));
    list_push(list_2,new_int(1));
    list_push(list_2,new_int(3));
    list_push(list_2,new_int(5));
    list_push(list_2,new_int(7));
    list_push(list_2,new_int(9));
    TEST_ASSERT_EQUAL_INT(0,list_is_empty(list_2));
    TEST_ASSERT_EQUAL_INT(5, list_get_size(list_2));
    // test with same list size:            (list_1 = 5)  ==  (list_2 = 8)
    list_t* list_3 = merge(list_1,list_2,compare_int);
    for(int i=0; i<(list_3->size)-1; i++) {
        assert(*(int*)list_get_element(list_3,i) <= *(int*)list_get_element(list_3,i+1));
    }
    TEST_ASSERT_EQUAL_INT(10, list_get_size(list_3));
    TEST_ASSERT_EQUAL_INT(0,*(int*)list_get_element(list_1,0));
    TEST_ASSERT_EQUAL_INT(2,*(int*)list_get_element(list_1,1));
    TEST_ASSERT_EQUAL_INT(4,*(int*)list_get_element(list_1,2));
    TEST_ASSERT_EQUAL_INT(6,*(int*)list_get_element(list_1,3));
    TEST_ASSERT_EQUAL_INT(8,*(int*)list_get_element(list_1,4));
    list_delete(list_1);
    list_delete(list_2);
    list_delete(list_3);
    TEST_ASSERT_EQUAL_INT(1,list_is_empty(list_1));
    TEST_ASSERT_EQUAL_INT(1,list_is_empty(list_2));
    TEST_ASSERT_EQUAL_INT(1,list_is_empty(list_3));
}

void test_merge_two_lists_diff_size(){
    list_t* list_1 = list_create();
    list_t* list_2 = list_create();
    list_push(list_1,new_int(0));
    list_push(list_1,new_int(2));
    list_push(list_1,new_int(4));
    list_push(list_1,new_int(6));
    list_push(list_1,new_int(8));
    TEST_ASSERT_EQUAL_INT(0,list_is_empty(list_1));
    TEST_ASSERT_EQUAL_INT(5, list_get_size(list_1));
    list_push(list_2,new_int(1));
    list_push(list_2,new_int(3));
    list_push(list_2,new_int(5));
    list_push(list_2,new_int(7));
    list_push(list_2,new_int(9));
    list_push(list_2,new_int(10));
    list_push(list_2,new_int(11));
    list_push(list_2,new_int(12));
    TEST_ASSERT_EQUAL_INT(0,list_is_empty(list_2));
    TEST_ASSERT_EQUAL_INT(8, list_get_size(list_2));
    // test with different size:            (list_1 = 5)  <  (list_2 = 8)
    list_t* list_3 = merge(list_1,list_2,compare_int);
    for(int i=0; i<(list_3->size)-1; i++) {
        assert(*(int*)list_get_element(list_3,i) <= *(int*)list_get_element(list_3,i+1));
    }
    TEST_ASSERT_EQUAL_INT(13, list_get_size(list_3));
    list_push(list_1,new_int(13));
    list_push(list_1,new_int(14));
    list_push(list_1,new_int(15));
    list_push(list_1,new_int(16));
    // test with different size reverse:    (list_1 = 9)  >  (list_2 = 8)
    TEST_ASSERT_EQUAL_INT(9, list_get_size(list_1));
    list_3 = merge(list_1,list_2,compare_int);
    for(int i=0; i<(list_3->size)-1; i++) {
        assert(*(int*)list_get_element(list_3,i) <= *(int*)list_get_element(list_3,i+1));
    }
    list_delete(list_1);
    list_delete(list_2);
    list_delete(list_3);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_1));
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_2));
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list_3));
}

/* UNIT TEST MERGE_SORT ON ARRAY_LIST */

void test_merge_array_new_not_null(){
    array_list_t* array_1 = array_list_new(0);
    array_list_t* array_2 = array_list_new(0);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_1));
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_2));
    array_list_t* array_3 = merge_array(array_1,array_2,compare_int);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_3));
    array_list_free(array_1);
    array_list_free(array_2);
    array_list_free(array_3);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_1));
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_2));
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_3));
}

void test_merge_two_arrays(){
    array_list_t* array_1 = array_list_new(5);
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_1));
    array_list_insert(array_1,new_int(0));
    array_list_insert(array_1,new_int(2));
    array_list_insert(array_1,new_int(4));
    array_list_insert(array_1,new_int(6));
    array_list_insert(array_1,new_int(8));
    TEST_ASSERT_EQUAL_INT(0,array_list_is_empty(array_1));
    TEST_ASSERT_EQUAL_INT(5, array_list_size(array_1));
    array_list_t* array_2 = array_list_new(5);
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_2));
    array_list_insert(array_2,new_int(1));
    array_list_insert(array_2,new_int(3));
    array_list_insert(array_2,new_int(5));
    array_list_insert(array_2,new_int(7));
    array_list_insert(array_2,new_int(9));
    TEST_ASSERT_EQUAL_INT(0,array_list_is_empty(array_2));
    TEST_ASSERT_EQUAL_INT(5, array_list_size(array_2));
    array_list_t* array_3 = merge_array(array_1,array_2,compare_int);
    for(int i=0; i<(array_3->size)-1; i++) {
        assert(*(int*)array_list_get_at(array_3,i) <= *(int*)array_list_get_at(array_3,i+1));
    }
    //With 'merge' the arrays still not ordered, but 'array_3' is ordered!
    TEST_ASSERT_EQUAL_INT(9, *(int*)array_list_get_at(array_2,0));
    TEST_ASSERT_EQUAL_INT(7, *(int*)array_list_get_at(array_2,1));
    TEST_ASSERT_EQUAL_INT(5, *(int*)array_list_get_at(array_2,2));
    TEST_ASSERT_EQUAL_INT(3, *(int*)array_list_get_at(array_2,3));
    TEST_ASSERT_EQUAL_INT(1, *(int*)array_list_get_at(array_2,4));
    array_list_free(array_1);
    array_list_free(array_2);
    array_list_free(array_3);
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_1));
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_2));
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_3));
}

void test_merge_two_arrays_diff_size(){
    array_list_t* array_1 = array_list_new(5);
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_1));
    array_list_insert(array_1,new_int(1));
    array_list_insert(array_1,new_int(2));
    array_list_insert(array_1,new_int(4));
    array_list_insert(array_1,new_int(6));
    array_list_insert(array_1,new_int(8));
    array_list_insert(array_1,new_int(10));
    array_list_insert(array_1,new_int(11));
    TEST_ASSERT_EQUAL_INT(0,array_list_is_empty(array_1));
    TEST_ASSERT_EQUAL_INT(7, array_list_size(array_1));
    array_list_t* array_2 = array_list_new(5);
    TEST_ASSERT_EQUAL_INT(1,array_list_is_empty(array_2));
    array_list_insert(array_2,new_int(0));
    array_list_insert(array_2,new_int(3));
    array_list_insert(array_2,new_int(5));
    array_list_insert(array_2,new_int(7));
    array_list_insert(array_2,new_int(9));
    TEST_ASSERT_EQUAL_INT(0,array_list_is_empty(array_2));
    TEST_ASSERT_EQUAL_INT(5, array_list_size(array_2));
    // test with different size:            (array_1 = 7)  >  (array_2 = 5)
    array_list_t* array_3 = merge_array(array_1,array_2,compare_int);
    for(int i=0; i<(array_3->size)-1; i++) {
        assert(*(int*)array_list_get_at(array_3,i) <= *(int*)array_list_get_at(array_3,i+1));
    }
    array_list_insert(array_2,new_int(12));
    array_list_insert(array_2,new_int(13));
    array_list_insert(array_2,new_int(14));
    TEST_ASSERT_EQUAL_INT(8, array_list_size(array_2));
    // test with different size reverse:            (array_1 = 5)  <  (array_2) = 8)
    array_3 = merge_array(array_1,array_2,compare_int);
    for(int i=0; i<(array_3->size)-1; i++) {
        assert(*(int*)array_list_get_at(array_3,i) <= *(int*)array_list_get_at(array_3,i+1));
    }
    array_list_free(array_1);
    array_list_free(array_2);
    array_list_free(array_3);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_1));
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_2));
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array_3));
}

/* UNIT TEST ARRAY_LIST */

 void test_array_new_not_null() {
    array_list_t* array = array_list_new(10);
    TEST_ASSERT_NOT_NULL(array);
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_new_capacity_is_correct() {
    array_list_t* array = array_list_new(10);
    TEST_ASSERT_EQUAL_INT(10, array_list_capacity(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_new_size_zero() {
    array_list_t* array = array_list_new(10);
    TEST_ASSERT_EQUAL_INT(0, array_list_size(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_free() {
    array_list_t* array = array_list_new(10);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
    array_list_insert(array,new_int(1));
     TEST_ASSERT_EQUAL_INT(0, array_list_is_empty(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_size() {
    array_list_t* array = build_fixture();
    TEST_ASSERT_EQUAL_INT(4, array_list_size(array));
    TEST_ASSERT_EQUAL_INT(0, array_list_is_empty(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_empty() {
    array_list_t* array = array_list_new(10);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
    array_list_insert(array,new_int(1));
    TEST_ASSERT_EQUAL_INT(0, array_list_is_empty(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_realloc() {
    array_list_t* array = build_fixture();
    size_t old_capacity = array_list_capacity(array);
    array_list_insert(array, new_int(10));
    array_list_insert(array, new_int(3));
    TEST_ASSERT_EQUAL_INT(1, array_list_capacity(array) > old_capacity);
    TEST_ASSERT_EQUAL_INT(1, array_list_capacity(array) >= array_list_capacity(array));
    TEST_ASSERT_EQUAL_INT(0, array_list_is_empty(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_at_pos() {
    array_list_t* array = build_fixture();
    TEST_ASSERT_EQUAL_INT(1,  *(int*)array_list_get_at(array, 0) );
    TEST_ASSERT_EQUAL_INT(4,  *(int*)array_list_get_at(array, 1) );
    TEST_ASSERT_EQUAL_INT(7,  *(int*)array_list_get_at(array, 2) );
    TEST_ASSERT_EQUAL_INT(10,  *(int*)array_list_get_at(array, 3) );
    TEST_ASSERT_EQUAL_INT(0, array_list_is_empty(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

 void test_array_insert() {
    array_list_t* array = build_fixture();
    array_list_insert(array, new_int(0));
    TEST_ASSERT_EQUAL_INT(5, array_list_size(array));
    TEST_ASSERT_EQUAL_INT(0, *(int*)array_list_get_at(array, 0));
    TEST_ASSERT_EQUAL_INT(0, array_list_is_empty(array));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
}

void test_array_iterator_next(){
    array_list_t* array = build_fixture();
    array_list_insert(array, new_int(0));
    TEST_ASSERT_EQUAL_INT(5, array_list_size(array));
    TEST_ASSERT_EQUAL_INT(1, *(int*)array_iterator_get(array_it_next(array_it_create(array))));
    it_array_t* it = array_it_create(array);
    TEST_ASSERT_NOT_NULL(it);
    TEST_ASSERT_EQUAL_INT(0, array_it_is_empty(it));
    array_delete_iterator(it);
    TEST_ASSERT_EQUAL_INT(1, array_it_is_empty(it));
    array_list_free(array);
    TEST_ASSERT_EQUAL_INT(1, array_list_is_empty(array));
 }

/* UNIT TEST LIST */
void test_list_new_not_null(){
    list_t* list = list_create();
    TEST_ASSERT_NOT_NULL(list);
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_empty(){
    list_t* list = list_create();
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_new_size_zero(){
    list_t* list = list_create();
    TEST_ASSERT_EQUAL_INT(0, list_get_size(list));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_free() {
    list_t* list = build_fixture_list();
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_insert_at_pos(){
    list_t* list = build_fixture_list();
    list_insert_position(list,new_int(2),2);
    TEST_ASSERT_EQUAL_INT(0, list_is_empty(list));
    TEST_ASSERT_EQUAL_INT(2,*(int*)list_get_element(list,2));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_delete_last(){
    list_t* list = build_fixture_list();
    TEST_ASSERT_EQUAL_INT(5, list_get_size(list));
    list_delete_last(list);
    TEST_ASSERT_EQUAL_INT(4, list_get_size(list));
    TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_element(list, 3));
    TEST_ASSERT_EQUAL_INT(0, list_is_empty(list));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_delete_pos(){
    list_t* list = build_fixture_list();
    TEST_ASSERT_EQUAL_INT(5, list_get_size(list));
    TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_element(list, 2));
    list_delete_position(list,2);
    TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_element(list, 2));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_iterator_create(){
    list_t* list = build_fixture_list();
    TEST_ASSERT_NOT_NULL(list_iterator_get(list_iterator_create(list)));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

void test_list_iterator_is_valid(){
    list_t* list = build_fixture_list();
    list_iterator_t* it = list_iterator_create(list);
    TEST_ASSERT_EQUAL_INT(0, list_it_is_empty(it));
    TEST_ASSERT_EQUAL_INT(1,*(int*)list_iterator_next(it));
    TEST_ASSERT_EQUAL_INT(0, list_it_is_empty(it));
    list_delete_iterator(it);
    TEST_ASSERT_EQUAL_INT(1, list_it_is_empty(it));
    list_delete(list);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
}

int main() {
    UNITY_BEGIN();
    printf("\nLIST TEST: \n");
    RUN_TEST(test_list_new_not_null);
    RUN_TEST(test_list_empty);
    RUN_TEST(test_list_new_size_zero);
    RUN_TEST(test_list_free);
    RUN_TEST(test_list_insert_at_pos);
    RUN_TEST(test_list_delete_last);
    RUN_TEST(test_list_delete_pos);
    RUN_TEST(test_list_iterator_create);
    RUN_TEST(test_list_iterator_is_valid);
    printf("ARRAY TEST: \n");
    RUN_TEST(test_array_new_not_null);
    RUN_TEST(test_array_empty);
    RUN_TEST(test_array_new_size_zero);
    RUN_TEST(test_array_free);
    RUN_TEST(test_array_at_pos);
    RUN_TEST(test_array_size);
    RUN_TEST(test_array_realloc);
    RUN_TEST(test_array_insert);
    RUN_TEST(test_array_new_capacity_is_correct);
    RUN_TEST(test_array_iterator_next);
    printf("MERGE TEST LIST: \n");
    RUN_TEST(test_merge_list_new_not_null);
    RUN_TEST(test_merge_two_lists);
    RUN_TEST(test_merge_two_lists_diff_size);
    printf("MERGE TEST ARRAY_LIST: \n");
    RUN_TEST(test_merge_array_new_not_null);
    RUN_TEST(test_merge_two_arrays);
    RUN_TEST(test_merge_two_arrays_diff_size);
    UNITY_END();
}