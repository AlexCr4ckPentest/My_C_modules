#include "../include/list.h"
#include <stdlib.h>
#include <assert.h>

typedef struct s_list_node
{
    void *data;
    struct s_list_node *next;
} list_node_t;

typedef struct s_list
{
    size_t size;
    struct s_list_node *head;
    struct s_list_node *first;
    struct s_list_node *last;
} list_t;



list_node_t* list_node_create(void *data, list_node_t *next)
{
    list_node_t *new_list_node = malloc(sizeof(list_node_t));
    new_list_node->data = data;
    new_list_node->next = next;
    return new_list_node;
}



list_t* list_create(void)
{
    list_t *new_list = malloc(sizeof(list_t));

    new_list->size = 0;
    new_list->head = NULL;
    new_list->first = new_list->head;
    new_list->last = new_list->head;

    return new_list;
}



void list_delete(list_t *list)
{
    list_clear(list);
    free(list);
    list = NULL;
}



void list_clear(list_t *list)
{
    while (list->size != 0) {
        list_pop_front(list);
    }
}



void list_push_back(list_t *list, void *data)
{
    if (list->head == NULL) {
        list->head = list_node_create(data, NULL);
        list->last = list->head;
    }
    else {
        list_node_t *last_node = list->head;

        while (last_node->next != NULL) {
            last_node = last_node->next;
        }

        last_node->next = list_node_create(data, NULL);
        list->last = last_node->next;
    }

    list->size++;
}



void list_push_front(list_t *list, void *data)
{
    list->head = list_node_create(data, list->head);
    list->first = list->head;
    list->size++;
}



void list_pop_back(list_t *list)
{
    assert(list->size != 0 && "list is empty!\n");

    list_node_t *node_for_delete = list->head;
    
    while (node_for_delete->next != NULL) {
        list->last = node_for_delete;
        node_for_delete = node_for_delete->next;
    }

    free(node_for_delete);
    list->size--;
}



void list_pop_front(list_t *list)
{
    assert(list->size != 0 && "list is empty!\n");

    list_node_t *node_for_delete = list->head;
    list->head = list->head->next;
    list->first = list->head;
    free(node_for_delete);
    list->size--;
}



void list_remove_at(list_t *list, const size_t index)
{
    assert((index < list->size) || (index >= list->size) && "index out of range!\n");

    if (index == 0) {
        list_pop_front(list);
    }
    else {
        list_node_t *prev_node = list->head;
        
        for (size_t i = 0; i < index - 1; i++) {
            prev_node = prev_node->next;
        }
        if (index == list->size - 1) {
            list->last = prev_node; 
        }

        list_node_t *node_for_delete = prev_node->next;
        prev_node->next = node_for_delete->next;

        free(node_for_delete);
        list->size--;
    }
}



void list_insert(list_t *list, void *data, const size_t index)
{
    assert((index < list->size) || (index >= list->size) && "index out of range!\n");

    if (index == 0) {
        list_push_front(list, data);
    }
    else {
        list_node_t *prev_node = list->head;
        for (int i = 0; i < index - 1; i++) {
            prev_node = prev_node->next;
        }
        prev_node->next = list_node_create(data, prev_node->next);
        list->size++;
    }
}



void* list_at(list_t *list, const size_t index)
{
    assert((index < list->size) || (index >= list->size) && "index out of range!\n");

    size_t curr_node_index = 0;
    list_node_t *curr_node = list->head;
    void *ret_data = NULL;

    while (curr_node != NULL) {
        if (index == curr_node_index) {
            ret_data = curr_node->data;
        }
        curr_node = curr_node->next;
        curr_node_index++;
    }
    return ret_data;
}



inline void* list_last(list_t *list)
{
    return list->last->data;
}



inline void* list_first(list_t *list)
{
    return list->first->data;
}



inline size_t list_size(const list_t *list)
{
    return list->size;
}



inline bool list_is_empty(const list_t *list)
{
    return list->size == 0;
}



void list_print(list_t *list, const char *format, FILE *out)
{
    assert(list->head != NULL);

    list_node_t *node = list->head;
    while (node != NULL) {
        fprintf(out, format, node->data);
        node = node->next;
    }
}



void list_reverse(list_t *list)
{
    assert(list->size != 0);

    list_node_t *prev = NULL;
    list_node_t *next = NULL;
    list_node_t *curr = list->head;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    list->last = list->head;
    list->head = prev;
    list->first = list->head;
}
