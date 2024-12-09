/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-14     Jackistang   add comments for function interface.
 */
#ifndef RINGBUFFER_H__
#define RINGBUFFER_H__

#include <rtdef.h>
#include <rtconfig.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ring buffer */
struct rt_ringbuffer
{
    rt_uint8_t *buffer_ptr;
    /* use the msb of the {read,write}_index as mirror bit. You can see this as
     * if the buffer adds a virtual mirror and the pointers point either to the
     * normal or to the mirrored buffer. If the write_index has the same value
     * with the read_index, but in a different mirror, the buffer is full.
     * While if the write_index and the read_index are the same and within the
     * same mirror, the buffer is empty. The ASCII art of the ringbuffer is:
     *
     *          mirror = 0                    mirror = 1
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Full
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     *  read_idx-^                   write_idx-^
     *
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Empty
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * read_idx-^ ^-write_idx
     */

    rt_uint32_t read_mirror : 1;
    rt_uint32_t read_index : 31;
    rt_uint32_t write_mirror : 1;
    rt_uint32_t write_index : 31;
    /* as we use msb of index as mirror bit, the size should be signed and
     * could only be positive. */
    rt_int32_t buffer_size;
};

enum rt_ringbuffer_state
{
    RT_RINGBUFFER_EMPTY,
    RT_RINGBUFFER_FULL,
    /* half full is neither full nor empty */
    RT_RINGBUFFER_HALFFULL,
};

/**
 * RingBuffer for DeviceDriver
 *
 * Please note that the ring buffer implementation of RT-Thread
 * has no thread wait or resume feature.
 */
void rt_ringbuffer_init(struct rt_ringbuffer *rb, rt_uint8_t *pool, rt_int32_t size);
void rt_ringbuffer_reset(struct rt_ringbuffer *rb);
rt_size_t rt_ringbuffer_put(struct rt_ringbuffer *rb, const rt_uint8_t *ptr, rt_uint32_t length);
rt_size_t rt_ringbuffer_put_force(struct rt_ringbuffer *rb, const rt_uint8_t *ptr, rt_uint32_t length);
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer *rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_putchar_force(struct rt_ringbuffer *rb, const rt_uint8_t ch);
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer *rb, rt_uint8_t *ptr, rt_uint32_t length);
rt_size_t rt_ringbuffer_peek(struct rt_ringbuffer *rb, rt_uint8_t **ptr);
rt_size_t rt_ringbuffer_getchar(struct rt_ringbuffer *rb, rt_uint8_t *ch);
rt_size_t rt_ringbuffer_data_len(struct rt_ringbuffer *rb);

#ifdef RT_USING_HEAP
struct rt_ringbuffer* rt_ringbuffer_create(rt_uint32_t length);
void rt_ringbuffer_destroy(struct rt_ringbuffer *rb);
#endif

/**
 * @brief Get the buffer size of the ring buffer object.
 *
 * @param rb        A pointer to the ring buffer object.
 *
 * @return  Buffer size.
 */
rt_inline rt_uint32_t rt_ringbuffer_get_size(struct rt_ringbuffer *rb)
{
    RT_ASSERT(rb != RT_NULL);
    return rb->buffer_size;
}

/** return the size of empty space in rb */
#define rt_ringbuffer_space_len(rb) ((rb)->buffer_size - rt_ringbuffer_data_len(rb))


#ifdef __cplusplus
}
#endif

#endif
