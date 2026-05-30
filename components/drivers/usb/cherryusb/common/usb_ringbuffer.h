/*
 * Copyright (c) 2022, Egahp
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_RINGBUFFER_H
#define USB_RINGBUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t in;   /*!< Define the write pointer.               */
    uint32_t out;  /*!< Define the read pointer.                */
    uint32_t mask; /*!< Define the write and read pointer mask. */
    void *pool;    /*!< Define the memory pointer.              */
} usb_ringbuffer_t;

/*****************************************************************************
* @brief        init ringbuffer
*
* @param[in]    rb          ringbuffer instance
* @param[in]    pool        memory pool address
* @param[in]    size        memory size in byte,
*                           must be power of 2 !!!
*
* @retval int               0:Success -1:Error
*****************************************************************************/
static inline int usb_ringbuffer_init(usb_ringbuffer_t *rb, void *pool, uint32_t size)
{
    if (NULL == rb) {
        return -1;
    }

    if (NULL == pool) {
        return -1;
    }

    if ((size < 2) || (size & (size - 1))) {
        return -1;
    }

    rb->in = 0;
    rb->out = 0;
    rb->mask = size - 1;
    rb->pool = pool;

    return 0;
}

/*****************************************************************************
* @brief        reset ringbuffer, clean all data,
*               should be add lock in multithread
*
* @param[in]    rb          ringbuffer instance
*
*****************************************************************************/
static inline void usb_ringbuffer_reset(usb_ringbuffer_t *rb)
{
    rb->in = 0;
    rb->out = 0;
}

/*****************************************************************************
* @brief        reset ringbuffer, clean all data,
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
*
*****************************************************************************/
static inline void usb_ringbuffer_reset_read(usb_ringbuffer_t *rb)
{
    rb->out = rb->in;
}

/*****************************************************************************
* @brief        get ringbuffer total size in byte
*
* @param[in]    rb          ringbuffer instance
*
* @retval uint32_t          total size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_get_size(usb_ringbuffer_t *rb)
{
    return rb->mask + 1;
}

/*****************************************************************************
* @brief        get ringbuffer used size in byte
*
* @param[in]    rb          ringbuffer instance
*
* @retval uint32_t          used size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_get_used(usb_ringbuffer_t *rb)
{
    return rb->in - rb->out;
}

/*****************************************************************************
* @brief        get ringbuffer free size in byte
*
* @param[in]    rb          ringbuffer instance
*
* @retval uint32_t          free size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_get_free(usb_ringbuffer_t *rb)
{
    return (rb->mask + 1) - (rb->in - rb->out);
}

/*****************************************************************************
* @brief        check if ringbuffer is full
*
* @param[in]    rb          ringbuffer instance
*
* @retval true              full
* @retval false             not full
*****************************************************************************/
static inline bool usb_ringbuffer_check_full(usb_ringbuffer_t *rb)
{
    return usb_ringbuffer_get_used(rb) > rb->mask;
}

/*****************************************************************************
* @brief        check if ringbuffer is empty
*
* @param[in]    rb          ringbuffer instance
*
* @retval true              empty
* @retval false             not empty
*****************************************************************************/
static inline bool usb_ringbuffer_check_empty(usb_ringbuffer_t *rb)
{
    return rb->in == rb->out;
}

/*****************************************************************************
* @brief        write one byte to ringbuffer,
*               should be add lock in multithread,
*               in single write thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    byte        data
*
* @retval true              Success
* @retval false             ringbuffer is full
*****************************************************************************/
static inline bool usb_ringbuffer_write_byte(usb_ringbuffer_t *rb, uint8_t byte)
{
    if (usb_ringbuffer_check_full(rb)) {
        return false;
    }

    ((uint8_t *)(rb->pool))[rb->in & rb->mask] = byte;
    rb->in++;
    return true;
}

/*****************************************************************************
* @brief        overwrite one byte to ringbuffer, drop oldest data,
*               should be add lock always
*
* @param[in]    rb          ringbuffer instance
* @param[in]    byte        data
*
* @retval true              Success
* @retval false             always return true
*****************************************************************************/
static inline bool usb_ringbuffer_overwrite_byte(usb_ringbuffer_t *rb, uint8_t byte)
{
    if (usb_ringbuffer_check_full(rb)) {
        rb->out++;
    }

    ((uint8_t *)(rb->pool))[rb->in & rb->mask] = byte;
    rb->in++;
    return true;
}

/*****************************************************************************
* @brief        peek one byte from ringbuffer,
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    byte        pointer to save data
*
* @retval true              Success
* @retval false             ringbuffer is empty
*****************************************************************************/
static inline bool usb_ringbuffer_peek_byte(usb_ringbuffer_t *rb, uint8_t *byte)
{
    if (usb_ringbuffer_check_empty(rb)) {
        return false;
    }

    *byte = ((uint8_t *)(rb->pool))[rb->out & rb->mask];
    return true;
}

/*****************************************************************************
* @brief        read one byte from ringbuffer,
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    byte        pointer to save data
*
* @retval true              Success
* @retval false             ringbuffer is empty
*****************************************************************************/
static inline bool usb_ringbuffer_read_byte(usb_ringbuffer_t *rb, uint8_t *byte)
{
    bool ret;
    ret = usb_ringbuffer_peek_byte(rb, byte);
    rb->out += ret;
    return ret;
}

/*****************************************************************************
* @brief        drop one byte from ringbuffer,
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
*
* @retval true              Success
* @retval false             ringbuffer is empty
*****************************************************************************/
static inline bool usb_ringbuffer_drop_byte(usb_ringbuffer_t *rb)
{
    if (usb_ringbuffer_check_empty(rb)) {
        return false;
    }

    rb->out += 1;
    return true;
}

/*****************************************************************************
* @brief        write data to ringbuffer,
*               should be add lock in multithread,
*               in single write thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    data        data pointer
* @param[in]    size        size in byte
*
* @retval uint32_t          actual write size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_write(usb_ringbuffer_t *rb, void *data, uint32_t size)
{
    uint32_t unused;
    uint32_t offset;
    uint32_t remain;

    unused = (rb->mask + 1) - (rb->in - rb->out);

    if (size > unused) {
        size = unused;
    }

    offset = rb->in & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > size ? size : remain;

    memcpy(((uint8_t *)(rb->pool)) + offset, data, remain);
    memcpy(rb->pool, (uint8_t *)data + remain, size - remain);

    rb->in += size;

    return size;
}

/*****************************************************************************
* @brief        write data to ringbuffer,
*               should be add lock always
*
* @param[in]    rb          ringbuffer instance
* @param[in]    data        data pointer
* @param[in]    size        size in byte
*
* @retval uint32_t          actual write size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_overwrite(usb_ringbuffer_t *rb, void *data, uint32_t size)
{
    uint32_t unused;
    uint32_t offset;
    uint32_t remain;

    unused = (rb->mask + 1) - (rb->in - rb->out);

    if (size > unused) {
        if (size > (rb->mask + 1)) {
            size = rb->mask + 1;
        }

        rb->out += size - unused;
    }

    offset = rb->in & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > size ? size : remain;

    memcpy(((uint8_t *)(rb->pool)) + offset, data, remain);
    memcpy(rb->pool, (uint8_t *)data + remain, size - remain);

    rb->in += size;

    return size;
}

/*****************************************************************************
* @brief        peek data from ringbuffer
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    data        data pointer
* @param[in]    size        size in byte
*
* @retval uint32_t          actual peek size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_peek(usb_ringbuffer_t *rb, void *data, uint32_t size)
{
    uint32_t used;
    uint32_t offset;
    uint32_t remain;

    used = rb->in - rb->out;
    if (size > used) {
        size = used;
    }

    offset = rb->out & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > size ? size : remain;

    memcpy(data, ((uint8_t *)(rb->pool)) + offset, remain);
    memcpy((uint8_t *)data + remain, rb->pool, size - remain);

    return size;
}

/*****************************************************************************
* @brief        read data from ringbuffer
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    data        data pointer
* @param[in]    size        size in byte
*
* @retval uint32_t          actual read size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_read(usb_ringbuffer_t *rb, void *data, uint32_t size)
{
    size = usb_ringbuffer_peek(rb, data, size);
    rb->out += size;
    return size;
}

/*****************************************************************************
* @brief        drop data from ringbuffer
*               should be add lock in multithread,
*               in single read thread not need lock
*
* @param[in]    rb          ringbuffer instance
* @param[in]    size        size in byte
*
* @retval uint32_t          actual drop size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_drop(usb_ringbuffer_t *rb, uint32_t size)
{
    uint32_t used;

    used = rb->in - rb->out;
    if (size > used) {
        size = used;
    }

    rb->out += size;
    return size;
}

/*****************************************************************************
* @brief        linear write setup, get write pointer and max linear size.
*
* @param[in]    rb          ringbuffer instance
* @param[in]    size        pointer to store max linear size in byte
*
* @retval void*             write memory pointer
*****************************************************************************/
static inline void *usb_ringbuffer_linear_write_setup(usb_ringbuffer_t *rb, uint32_t *size)
{
    uint32_t unused;
    uint32_t offset;
    uint32_t remain;

    unused = (rb->mask + 1) - (rb->in - rb->out);

    offset = rb->in & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > unused ? unused : remain;

    if (remain) {
        *size = remain;
        return ((uint8_t *)(rb->pool)) + offset;
    } else {
        *size = unused - remain;
        return rb->pool;
    }
}

/*****************************************************************************
* @brief        linear read setup, get read pointer and max linear size.
*
* @param[in]    rb          ringbuffer instance
* @param[in]    size        pointer to store max linear size in byte
*
* @retval void*
*****************************************************************************/
static inline void *usb_ringbuffer_linear_read_setup(usb_ringbuffer_t *rb, uint32_t *size)
{
    uint32_t used;
    uint32_t offset;
    uint32_t remain;

    used = rb->in - rb->out;

    offset = rb->out & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > used ? used : remain;

    if (remain) {
        *size = remain;
        return ((uint8_t *)(rb->pool)) + offset;
    } else {
        *size = used - remain;
        return rb->pool;
    }
}

/*****************************************************************************
* @brief        linear write done, add write pointer only
*
* @param[in]    rb          ringbuffer instance
* @param[in]    size        write size in byte
*
* @retval uint32_t          actual write size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_linear_write_done(usb_ringbuffer_t *rb, uint32_t size)
{
    uint32_t unused;

    unused = (rb->mask + 1) - (rb->in - rb->out);
    if (size > unused) {
        size = unused;
    }
    rb->in += size;

    return size;
}

/*****************************************************************************
* @brief        linear read done, add read pointer only
*
* @param[in]    rb          ringbuffer instance
* @param[in]    size        read size in byte
*
* @retval uint32_t          actual read size in byte
*****************************************************************************/
static inline uint32_t usb_ringbuffer_linear_read_done(usb_ringbuffer_t *rb, uint32_t size)
{
    return usb_ringbuffer_drop(rb, size);
}

#ifdef __cplusplus
}
#endif

#endif
