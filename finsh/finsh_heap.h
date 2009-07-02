#include <finsh.h>

#ifndef __FINSH_HEAP_H__
#define __FINSH_HEAP_H__

int finsh_heap_init(void);
void* finsh_heap_allocate(size_t size);
void  finsh_heap_free(void*ptr);

#endif
