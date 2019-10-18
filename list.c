#include "list.h"

/*-> Verify if the list is empty
 * ---->* 1) Verifica se la lista è vuota in O(1) */
int list_is_empty(list_t* l){
    return (l->size == 0);
}
/*-> Insert a new data into the list (push tail).
/*---->*2) Inserimento in coda alla lista in O(1) */

void list_push(list_t *list, void *data){
    if(list->size){
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->data = data;
        new_node->next = NULL;
        if((list->head == NULL) && (list->tail == NULL)){
            list->head = list->tail = new_node;
            new_node->prev = new_node->next = NULL;
        }else{
            new_node->prev = list->tail;
            new_node->next = NULL;
            list->tail->next = new_node;
            list->tail = new_node;
        }
        list->size++;
    }else{
        //if the list doesn't exist, create and allocate a new one! (with the new node)
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->data = data;
        list->head = list->tail = new_node;
        new_node->prev = new_node->next = NULL;
        list->size++;
    }
}

/*-> Insert a new node into n position
 * --->*3) Inserimento di un elemento nella posizione i-esima della lista in O(n).*/

void list_insert_position (list_t *list, void *data, int x){
    if(x >= list->size){
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        node_t **entryp = &list->head;
        new_node->data = data;
        new_node->next = list->head->next;
        *entryp = new_node;
        list->size++;
    }else{
        node_t *current = list->head;
        node_t **entryp = &list->head;
        while(x-- && current){
            entryp = &current->next;
            current = current->next;
        }
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->data = data;
        new_node->next = current;
        *entryp = new_node;
        list->size++;
    }
}

/*-> Delete the last element of the list in O(1)
 * --->*4) Cancellazione dell'elemento in coda alla lista in O(1).*/

void list_delete_last(list_t *list){
    if(list->tail->prev){
        node_t *current = list->tail;
        node_t *prev = list->tail->prev;
        prev->next = NULL;
        free(current);
        list->tail = prev;
        list->size--;
    }else{
        // delete list
        node_t *temp = list->head;
        free(temp);
        list->head = NULL;
        list->size = 0;
    }
}

/*-> Delete the element position of the list, O(N)
 * --->*5) Cancellazione elemento in posizione 'n' della lista in O(1).*/
void list_delete_position (list_t *list, int x){
    if(list->size < 1 && x >= list->size){
        node_t *current = list->tail;
        node_t *prev = list->tail->prev;
        prev->next = NULL;
        free(current);
        list->tail = prev;
        list->size--;
    }else{
        node_t *current = list->head;
        node_t **entryp = &list->head;
        while(x-- && current){
            entryp = &current->next;
            current = current->next;
        }
        node_t *new_node = current->next;
        node_t *tmp = current;
        *entryp = new_node;
        free(tmp);
        list->size--;
    }

}

/*-> Get the element in the n position of the list (without cancell any element of the list) O(N)
 * --->*6) Recupero dell'elemento in posizione i-esima nella lista (senza cancellare l'elemento dalla lista) in O(n).*/
void* list_get_element(list_t *list, int x){
    if(x > 0 && x < list->size){
        node_t *current = list->head;
        while(x--){
            current = current->next;
        }
        void *element = current->data;
        return element;
    }else if(x == 0 && list->size) {
        void *element = list->head->data;
        return element;
    }else{
        return NULL;
    }
}

/*-> Get the list size in O(1)
 * --->*7) Recupero della dimensione della lista in O(1). */
int list_get_size(list_t *list){
    return (list->size);
}

/*-> Verify if the iterator is still valid in O(1);
 * --->8) Verifica se l'iteratore è ancora valido in O(1) */

int list_it_is_empty(list_iterator_t *it) {
    return it->curr == NULL;
}

/*-> Get the current element in O(1) ;
 * --->9) Recupera l'elemento corrente in O(1) */

void* list_iterator_get(list_iterator_t* it){
    void* data = NULL;
    if (it->curr) {
        data = it->curr->data;
    }
    return data;
}

/*-> Move the iterator in the next element in O(1) ;
 * --->10) Sposta l'iteratore all'elemento successivo in O(1) */

void* list_iterator_next(list_iterator_t* it) {
    void* data = NULL;
    if (it->curr->next) {
        data = it->curr->next->data;
        it->entryp = &it->curr->next;
        it->curr = it->curr->next;
    }
    return data;
}

/*-> Create iterator                                    */
list_iterator_t* list_iterator_create(list_t* l){
    list_iterator_t* it = malloc(sizeof(list_iterator_t));
    it->list = l;
    it->curr = l->head;
    it->entryp = &l->head;
    return it;
}

/*-> Create the list and set the head == NULL     */
list_t* list_create(){
    list_t* l = malloc(sizeof(list_t));
    if(l) {
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
    }
    return l;
}

/*-> Delete the list */
void list_delete(list_t* list){
    node_t *pointer = list->head;
    while(list->size){
        list->size--;
        free(pointer);
        pointer = pointer->next;
    }
    free(pointer);
}

/*-> Delete the list */
void list_delete_iterator(list_iterator_t* it){
    free(it->list);
    free(it->curr);
    free(it->entryp);
    it->curr = NULL;
}
