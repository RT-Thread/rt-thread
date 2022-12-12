#include <stdio.h>

#include <hal_mem.h>
#include "sunxi_hal_common.h"

void dma_free_coherent(void *addr)
{
    void *malloc_ptr = NULL;
    if (!addr)
    {
        return;
    }
    malloc_ptr = (void *)*(unsigned long *)((unsigned long *)addr - 1);
    hal_free(malloc_ptr);
}

void *dma_alloc_coherent(size_t size)
{
    void *fake_ptr = NULL;
    void *malloc_ptr = NULL;

    malloc_ptr = hal_malloc(size + 2 * CACHELINE_LEN);
    if ((unsigned long)malloc_ptr & (sizeof(long) - 1))
    {
        printf("error: mm_alloc not align. \r\n");
        return NULL;
    }

    if (!malloc_ptr) {
        return NULL;
    }

    fake_ptr = (void *)((unsigned long)(malloc_ptr + CACHELINE_LEN) & (~(CACHELINE_LEN - 1)));
    *(unsigned long *)((unsigned long *)fake_ptr - 1) = (unsigned long)malloc_ptr;

    return fake_ptr;
}

