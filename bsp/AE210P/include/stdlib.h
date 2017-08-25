#ifndef __STDLIB_H__
#define __STDLIB_H__
#include <stddef.h>
#include <string.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#if defined(CONFIG_OS_UCOS_II) || defined(CONFIG_OS_UCOS_III)
#include "kmem.h"
static inline void *malloc(size_t size)
{
	return kmalloc(size);
}

static inline void free(void *ptr)
{
	return kfree(ptr);
}
#elif defined(CONFIG_OS_FREERTOS)
extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );
#define malloc	pvPortMalloc
#define free	vPortFree
#elif defined(CONFIG_OS_THREADX)
#include "kmem.h"
static inline void *malloc(size_t size)
{
	    return kmalloc(size);
}

static inline void free(void *ptr)
{
		return kfree(ptr);
}
#elif defined(CONFIG_OS_RTTHREAD)
#include "rtdef.h"
#include "rtthread.h"
#define malloc	rt_malloc
#define free	rt_Free
#else
#  error "No valid OS is defined!"
#endif
static inline void *calloc(size_t nmemb, size_t size)
{
        int i = nmemb * size;
        unsigned char *ret = malloc(i);

	while (i >= 0)
                ret[--i] = '\0';
        return ret;
}

static inline void *realloc(void *ptr, size_t size)
{
	return NULL;
}

static inline void exit(int status)
{
}

static inline void abort(void)
{
}

void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
extern int	atoi(const char *__nptr);
#endif /* __STDLIB_H__ */
