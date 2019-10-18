#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "array_list.h"
#include "list.h"
typedef int (*CompFunction)(void*, void*);

/* FUNCTIONS DECLARATION */
array_list_t* merge_array(array_list_t* array_a, array_list_t* array_b, CompFunction compare);
list_t* merge(list_t* list_1, list_t* list_2, CompFunction compare);

