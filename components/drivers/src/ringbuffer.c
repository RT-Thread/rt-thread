/*
 * File      : ringbuffer.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

void rt_ringbuffer_init(struct rt_ringbuffer *rb,
                        rt_uint8_t           *pool,
                        rt_uint16_t           size)
{
    RT_ASSERT(rb != RT_NULL);

    /* initialize read and write index */
    rb->read_index = rb->write_index = 0;

    /* set buffer pool and size */
    rb->buffer_ptr = pool;
    rb->buffer_size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);
}
RTM_EXPORT(rt_ringbuffer_init);

rt_size_t rt_ringbuffer_put(struct rt_ringbuffer *rb,
                            const rt_uint8_t     *ptr,
                            rt_uint16_t           length)
{
    rt_uint16_t size;
    rt_uint16_t mask;
    rt_uint16_t write_position;

    RT_ASSERT(rb != RT_NULL);

    mask = rb->buffer_size - 1;
    /* whether has enough space */
    size = rb->buffer_size - (rb->write_index - rb->read_index);

    /* no space */
    if (size == 0)
        return 0;
    /* drop some data */
    if (size < length)
        length = size;

    write_position = (rb->write_index & mask);
    if (rb->buffer_size - write_position> length)
    {
        /* read_index - write_index = empty space */
        memcpy(&rb->buffer_ptr[write_position], ptr, length);
    }
    else
    {
        memcpy(&rb->buffer_ptr[write_position],
               ptr,
               rb->buffer_size - write_position);
        memcpy(&rb->buffer_ptr[0],
               &ptr[rb->buffer_size - write_position],
               length - (rb->buffer_size - write_position));
    }
    rb->write_index += length;

    return length;
}
RTM_EXPORT(rt_ringbuffer_put);

/**
 * put a character into ring buffer
 */
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer *rb, const rt_uint8_t ch)
{
    rt_uint16_t mask;

    RT_ASSERT(rb != RT_NULL);
    /* whether has enough space */
    mask = rb->buffer_size - 1;

    /* whether has enough space */
    if (rb->write_index - rb->read_index == rb->buffer_size)
        return 0;

    /* put character */
    rb->buffer_ptr[rb->write_index & mask] = ch;
    rb->write_index += 1;

    return 1;
}
RTM_EXPORT(rt_ringbuffer_putchar);

/**
 *  get data from ring buffer
 */
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer *rb,
                            rt_uint8_t           *ptr,
                            rt_uint16_t           length)
{
    rt_size_t size;
    rt_uint16_t mask;
    rt_uint16_t read_position;

    RT_ASSERT(rb != RT_NULL);
    /* whether has enough data  */
    mask = rb->buffer_size - 1;
    size = rb->write_index - rb->read_index;

    /* no data */
    if (size == 0)
        return 0;
    /* less data */
    if (size < length)
        length = size;

    read_position = rb->read_index & mask;
    if (rb->buffer_size - read_position >= length)
    {
        /* copy all of data */
        memcpy(ptr, &rb->buffer_ptr[read_position], length);
    }
    else
    {
        /* copy first and second */
        memcpy(ptr,
               &rb->buffer_ptr[read_position],
               rb->buffer_size - read_position);
        memcpy(&ptr[rb->buffer_size - read_position],
               &rb->buffer_ptr[0],
               length - rb->buffer_size + read_position);
    }
    rb->read_index += length;

    return length;
}
RTM_EXPORT(rt_ringbuffer_get);

/**
 * get a character from a ringbuffer
 */
rt_size_t rt_ringbuffer_getchar(struct rt_ringbuffer *rb, rt_uint8_t *ch)
{
    rt_uint16_t mask;

    RT_ASSERT(rb != RT_NULL);
    
    /* ringbuffer is empty */
    if (rb->read_index == rb->write_index)
        return 0;

    mask = rb->buffer_size - 1;

    /* put character */
    *ch = rb->buffer_ptr[rb->read_index & mask];
    rb->read_index += 1;

    return 1;
}
RTM_EXPORT(rt_ringbuffer_getchar);
