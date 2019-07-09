#include "linked_list.h"
#include "heap_mgr.h"

#include <stdlib.h>

list_t* list_init()
{
    list_t *list = (list_t*)wmalloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

err_t list_fini(list_t *list)
{
    if(NULL == list)
        return FAILURE;

    while(NULL != list->head)
        if(SUCCESS != list_remove(list, 0, NULL))
            return FAILURE;
    wfree(list);
    return SUCCESS;
}

err_t list_add(list_t *list, buf_t buf)
{
    if(NULL == list)
        return FAILURE;

    list_node_t *node = NULL;
    if(NULL == (node = (list_node_t*)wmalloc(sizeof(list_node_t))))
        return NOMEM;

    node->next = NULL;
    node->prev = NULL;
    node->buf = buf;

    if(NULL == list->head)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }

    list->size++;
    return SUCCESS;
}

err_t list_insert(list_t *list, size_t idx, buf_t *buf)
{
    if(NULL == list)
        return FAILURE;

    list_node_t *new_node = NULL;
    list_node_t *node = list->head;

    size_t i;
    for(i = 0; i < idx; i++)
        if(NULL != node)
            node = node->next;

    if(NULL == node)
        return FAILURE;

    if(NULL == (new_node = (list_node_t)wmalloc(sizeof(list_node_t))))
        return NOMEM;

    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->buf = buf;

    // TODO: Finish impl
    if(NULL != node->prev)
        node->prev->next = new_node;
    if(NULL != node->next)
        node->next->prev = new_node;
    node->prev = new_node;
    new_node->next = node;

    if(list->head == node)
    {
        list->head->prev = new_node;
        new_node->next = 
    }
    else
    {

    }
}

err_t list_remove(list_t *list, size_t idx, buf_t *buf)
{

}
