#include "linked_list.h"
#include "heap_mgr.h"
#include "error_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

err_t list_remove(list_t *list, size_t idx, buf_t *buf);

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

err_t list_insert(list_t *list, size_t idx, buf_t buf)
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

    if(NULL == (new_node = (list_node_t*)wmalloc(sizeof(list_node_t))))
        return NOMEM;

    new_node->next = node;
    new_node->prev = node->prev;
    new_node->buf = buf;

    if(NULL != node->prev)
        node->prev->next = new_node;
    node->prev = new_node;

    if(list->head == node)
        list->head = new_node;
    if(list->tail == node)
        list->tail = new_node;

    list->size++;
    return SUCCESS;
}

err_t list_remove(list_t *list, size_t idx, buf_t *buf)
{
    if(NULL == list)
        return FAILURE;

    list_node_t *node = list->head;

    size_t i;
    for(i = 0; i < idx; i++)
        if(NULL != node)
            node = node->next;

    if(NULL == node)
        return FAILURE;

    if(NULL != node->prev)
        node->prev->next = node->next;
    if(NULL != node->next)
        node->next->prev = node->prev;

    if(list->head == node)
        list->head = node->next;
    if(list->tail == node)
        list->tail = node->prev;

    if(NULL != buf)
        *buf = node->buf;
    else
        if(NULL != node->buf.b)
            wfree(node->buf.b);

    wfree(node);
    list->size--;
    return SUCCESS;
}

static void list_print(list_t *list)
{
    if(NULL == list)
        return;

    list_node_t *node = NULL;
    for(node = list->head; node != NULL; node = node->next)
    {
        printf("%s", (char*)node->buf.b);
        if(NULL != node->next)
            printf(" -> ");
    }
    printf("\n");
}

int main()
{
    printf("Heap space before strdup: %lu\n", getHeapSize());
    buf_t b1 = { .b=(void*)wstrdup("1") };
    buf_t b2 = { .b=(void*)wstrdup("2") };
    buf_t b3 = { .b=(void*)wstrdup("3") };
    buf_t b4 = { .b=(void*)wstrdup("4") };
    buf_t tmp;

    printf("Heap space: %lu\n", getHeapSize());
    list_t *list = list_init();
    list_print(list);
    list_add(list, b1);
    list_print(list);
    list_add(list, b2);
    list_print(list);
    list_add(list, b3);
    list_print(list);
    list_add(list, b4);
    list_print(list);
    list_remove(list, 2, &tmp);
    list_print(list);
    list_insert(list, 2, b3);
    list_print(list);
    list_remove(list, 0, &tmp);
    list_print(list);
    list_insert(list, 0, b1);
    list_print(list);
    list_remove(list, 3, &tmp);
    list_print(list);
    list_insert(list, 3, b4);
    list_print(list);
    list_fini(list);
    wfree(tmp.b);
    printf("Heap space: %lu\n", getHeapSize());
    return 0;
}

