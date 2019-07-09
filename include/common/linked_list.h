#ifndef H_LINKED_LIST_H
#define H_LINKED_LIST_H

typedef struct
{
    void    *b;
    size_t  sz;
} buf_t;

typedef struct list_node
{
    struct list_node *next;
    struct list_node *prev;
    buf_t            buf;
} list_node_t;

typedef struct
{
    list_node_t *head;
    list_node_t *tail;
    size_t      size;
} linked_list_t, list_t;

list_t* list_init();
err_t   list_fini(list_t *list);
err_t   list_add(list_t *list, buf_t buf);
err_t   list_insert(list *list, size_t idx, buf_t buf);
err_t   list_remove(list_t *list, size_t idx, buf_t *buf);

#endif
