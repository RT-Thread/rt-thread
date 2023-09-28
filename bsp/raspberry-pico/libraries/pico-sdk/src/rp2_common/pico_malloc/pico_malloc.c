/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include "pico.h"
#include "pico/malloc.h"

#if PICO_USE_MALLOC_MUTEX
#include "pico/mutex.h"
auto_init_mutex(malloc_mutex);
#endif

extern void *REAL_FUNC(malloc)(size_t size);
extern void *REAL_FUNC(calloc)(size_t count, size_t size);
extern void *REAL_FUNC(realloc)(void *mem, size_t size);
extern void REAL_FUNC(free)(void *mem);

extern char __StackLimit; /* Set by linker.  */

static inline void check_alloc(__unused void *mem, __unused uint size) {
#if PICO_MALLOC_PANIC
    if (!mem || (((char *)mem) + size) > &__StackLimit) {
        panic("Out of memory");
    }
#endif
}

void *WRAPPER_FUNC(malloc)(size_t size) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    void *rc = REAL_FUNC(malloc)(size);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
#if PICO_DEBUG_MALLOC
    if (!rc || ((uint8_t *)rc) + size > (uint8_t*)PICO_DEBUG_MALLOC_LOW_WATER) {
        printf("malloc %d %p->%p\n", (uint) size, rc, ((uint8_t *) rc) + size);
    }
#endif
    check_alloc(rc, size);
    return rc;
}

void *WRAPPER_FUNC(calloc)(size_t count, size_t size) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    void *rc = REAL_FUNC(calloc)(count, size);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
#if PICO_DEBUG_MALLOC
    if (!rc || ((uint8_t *)rc) + size > (uint8_t*)PICO_DEBUG_MALLOC_LOW_WATER) {
        printf("calloc %d %p->%p\n", (uint) (count * size), rc, ((uint8_t *) rc) + size);
    }
#endif
    check_alloc(rc, size);
    return rc;
}

void *WRAPPER_FUNC(realloc)(void *mem, size_t size) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    void *rc = REAL_FUNC(realloc)(mem, size);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
#if PICO_DEBUG_MALLOC
    if (!rc || ((uint8_t *)rc) + size > (uint8_t*)PICO_DEBUG_MALLOC_LOW_WATER) {
        printf("realloc %p %d->%p\n", mem, (uint) size, rc);
    }
#endif
    check_alloc(rc, size);
    return rc;
}

void WRAPPER_FUNC(free)(void *mem) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    REAL_FUNC(free)(mem);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
}
