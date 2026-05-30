/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_MEMPOOL_H
#define USB_MEMPOOL_H

#include "usb_osal.h"
#include "usb_ringbuffer.h"

#ifndef CONFIG_USB_MEMPOOL_MAX_BLOCK_COUNT
#define CONFIG_USB_MEMPOOL_MAX_BLOCK_COUNT 16
#endif

struct usb_mempool {
    usb_ringbuffer_t in;
    usb_ringbuffer_t out;
    usb_osal_sem_t out_sem;

    void *block;
    uint32_t block_size;
    uint32_t block_count;
    uint8_t in_buf[sizeof(uintptr_t) * CONFIG_USB_MEMPOOL_MAX_BLOCK_COUNT];
    uint8_t out_buf[sizeof(uintptr_t) * CONFIG_USB_MEMPOOL_MAX_BLOCK_COUNT];
};

#define usb_mempool_osal_sem_create(max_count) usb_osal_sem_create_counting(max_count)
#define usb_mempool_osal_sem_delete(sem) usb_osal_sem_delete(sem)
#define usb_mempool_osal_sem_take(sem, timeout) usb_osal_sem_take(sem, timeout)
#define usb_mempool_osal_sem_give(sem) usb_osal_sem_give(sem)

#ifdef __cplusplus
extern "C" {
#endif

static inline int usb_mempool_create(struct usb_mempool *pool, void *block, uint32_t block_size, uint32_t block_count)
{
    uintptr_t *item;
    uint32_t addr;

    if (block_count > CONFIG_USB_MEMPOOL_MAX_BLOCK_COUNT) {
        return -1;
    }

    if (block_size % 4) {
        return -1;
    }

    if (usb_ringbuffer_init(&pool->in, pool->in_buf, sizeof(uintptr_t) * block_count) == -1) {
        return -1;
    }

    if (usb_ringbuffer_init(&pool->out, pool->out_buf, sizeof(uintptr_t) * block_count) == -1) {
        return -1;
    }

    pool->out_sem = usb_mempool_osal_sem_create(block_count);
    if (pool->out_sem == NULL) {
        return -1;
    }

    pool->block = block;
    pool->block_size = block_size;
    pool->block_count = block_count;

    for (uint32_t i = 0; i < pool->block_count; i++) {
        item = (uintptr_t *)((uint8_t *)pool->block + i * pool->block_size);
        addr = (uintptr_t)item;
        usb_ringbuffer_write(&pool->in, &addr, sizeof(uintptr_t));
    }

    return 0;
}

static inline void usb_mempool_delete(struct usb_mempool *pool)
{
    usb_ringbuffer_reset(&pool->in);
    usb_ringbuffer_reset(&pool->out);
    usb_mempool_osal_sem_delete(pool->out_sem);
}

static inline uintptr_t *usb_mempool_alloc(struct usb_mempool *pool)
{
    uintptr_t *addr;
    uint32_t len;

    len = usb_ringbuffer_read(&pool->in, (uintptr_t *)&addr, sizeof(uintptr_t));
    if (len == 0) {
        return NULL;
    } else {
        return addr;
    }
}

static inline int usb_mempool_free(struct usb_mempool *pool, uintptr_t *item)
{
    uintptr_t addr;

    addr = (uintptr_t)item;
    return usb_ringbuffer_write(&pool->in, &addr, sizeof(uintptr_t));
}

static inline int usb_mempool_send(struct usb_mempool *pool, uintptr_t *item)
{
    uintptr_t addr;

    addr = (uintptr_t)item;
    usb_ringbuffer_write(&pool->out, &addr, sizeof(uintptr_t));
    return usb_mempool_osal_sem_give(pool->out_sem);
}

static inline int usb_mempool_recv(struct usb_mempool *pool, uintptr_t **item, uint32_t timeout)
{
    uint32_t len;
    int ret;

    ret = usb_mempool_osal_sem_take(pool->out_sem, timeout);
    if (ret < 0) {
        return -1;
    }

    len = usb_ringbuffer_read(&pool->out, (uintptr_t *)item, sizeof(uintptr_t));
    if (len == 0) {
        return -1;
    } else {
        return 0;
    }
}

static inline void usb_mempool_reset(struct usb_mempool *pool)
{
    uintptr_t *item;

    usb_ringbuffer_reset(&pool->in);
    usb_ringbuffer_reset(&pool->out);

    for (uint32_t i = 0; i < pool->block_count; i++) {
        item = (uintptr_t *)((uint8_t *)pool->block + i * pool->block_size);
        usb_mempool_free(pool, item);
    }
}

#ifdef __cplusplus
}
#endif

#endif
