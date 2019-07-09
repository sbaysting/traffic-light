#ifndef H_HEAP_MGR_H
#define H_HEAP_MGR_H

#include <stdlib.h>

void* wmalloc(size_t size);
void  wfree(void *ptr);
void* wcalloc(size_t nmemb, size_t size);
void* wrealloc(void *ptr, size_t size);
size_t getHeapSize();

#endif
