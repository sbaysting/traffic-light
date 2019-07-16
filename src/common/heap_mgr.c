#include <stdlib.h>
#include <string.h>
#include <malloc.h>

static size_t heap_sz;

#ifdef LOG_HEAP
#define wprintf          printf
#else
#define wprintf(...)     do{}while(0)
#endif

static size_t I_getUsableSize(void *ptr)
{
    return malloc_usable_size(ptr);
}


void* wmalloc(size_t size)
{
    void *ptr = malloc(size);
    heap_sz += I_getUsableSize(ptr);
    wprintf("malloc %lu %p\n", I_getUsableSize(ptr), ptr);
    return ptr;
}

void wfree(void *ptr)
{
    wprintf("free %lu %p\n", I_getUsableSize(ptr), ptr);
    heap_sz -= I_getUsableSize(ptr);
    free(ptr);
    return;
}

void* wcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    heap_sz += I_getUsableSize(ptr);
    wprintf("calloc %lu %p\n", I_getUsableSize(ptr), ptr);
    return ptr;
}

void* wrealloc(void *ptr, size_t size)
{
    heap_sz -= I_getUsableSize(ptr);
    wprintf("free %lu %p\n", I_getUsableSize(ptr), ptr);
    ptr = realloc(ptr, size);
    heap_sz += I_getUsableSize(ptr);
    wprintf("malloc %lu %p\n", I_getUsableSize(ptr), ptr);
    return ptr;
}

char* wstrdup(const char *s)
{
    char *ptr = strdup(s);
    heap_sz += I_getUsableSize(ptr);
    wprintf("strdup %lu %p\n", I_getUsableSize(ptr), ptr);
    return ptr;
}

size_t getHeapSize()
{
    return heap_sz;
}
