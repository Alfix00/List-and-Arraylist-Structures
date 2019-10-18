#ifndef NODE_T
#define NODE_T
#ifndef LIST_T
#define LIST_T
#ifndef LIST_ITERATOR_T
#define LIST_ITERATOR_T
#include <stdio.h>
#include <stdlib.h>

/* STRUCT */
typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
}node_t;

typedef struct list{
    unsigned int size;
    node_t *head;
    node_t *tail;
}list_t;

typedef struct list_iterator {
    list_t* list;
    node_t* curr;
    node_t** entryp;
}list_iterator_t ;

/* FUNCTIONS DECLARATION */
int list_is_empty(list_t* l);
void list_push(list_t *list, void *data);
void list_insert_position (list_t *list, void *data, int x);
void list_delete_last(list_t *list);
void list_delete_position (list_t *list, int x);
void* list_get_element(list_t *list, int x);
int list_get_size(list_t *list);
int list_it_is_empty(list_iterator_t* it);
void* list_iterator_get(list_iterator_t* it);
void* list_iterator_next(list_iterator_t* it);
list_iterator_t* list_iterator_create(list_t* l);
list_t* list_create();
void list_delete_iterator(list_iterator_t* it);
void list_delete(list_t* list);
#endif
#endif
#endif