/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 * 2013-05-08     Grissiom     reimplement
 * 2016-08-18     heyuanjie    add interface
 * 2021-07-20     arminker     fix write_index bug in function rt_ringbuffer_put_force
 * 2021-08-14     Jackistang   add commets for function inferface.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

rt_inline enum rt_ringbuffer_state rt_ringbuffer_status(struct rt_ringbuffer *rb)
{
    if (rb->read_index == rb->write_index)
    {
        if (rb->read_mirror == rb->write_mirror)
            return RT_RINGBUFFER_EMPTY;
        else
            return RT_RINGBUFFER_FULL;
    }
    return RT_RINGBUFFER_HALFFULL;
}

/**
 * @brief Init a ringbuffer object with a given buffer.
 *
 * @param rb        A pointer to the ringbuffer object.
 * @param pool      A pointer to the buffer.
 * @param size      Size of the buffer in bytes.
 */
void rt_ringbuffer_init(struct rt_ringbuffer *rb,
                        rt_uint8_t           *pool,
                        rt_int16_t            size)
{
    RT_ASSERT(rb != RT_NULL);
    RT_ASSERT(size > 0);

    /* initialize read and write index */
    rb->read_mirror = rb->read_index = 0;
    rb->write_mirror = rb->write_index = 0;

    /* set buffer pool and size */
    rb->buffer_ptr = pool;
    rb->buffer_size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);
}
RTM_EXPORT(rt_ringbuffer_init);

/**
 * @brief Put a block of data into the ringbuffer. If the size of ringbuffer is not enough, it will discard out-of-range data.
 *
 * @param rb            A pointer to the ringbuffer object.
 * @param ptr           A pointer to the data buffer.
 * @param length        The size of data in bytes.
 *
 * @return Return the size in bytes put into the ringbuffer actually.
 */
rt_size_t rt_ringbuffer_put(struct rt_ringbuffer *rb,
                            const rt_uint8_t     *ptr,
                            rt_uint16_t           length)
{
    rt_uint16_t size;

    RT_ASSERT(rb != RT_NULL);

    /* whether has enough space */
    size = rt_ringbuffer_space_len(rb);

    /* no space */
    if (size == 0)
        return 0;

    /* drop some data */
    if (size < length)
        length = size;

    if (rb->buffer_size - rb->write_index > length)
    {
        /* read_index - write_index = empty space */
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->write_index += length;
        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index],
           &ptr[0],
           rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0],
           &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    /* we are going into the other side of the mirror */
    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    return length;
}
RTM_EXPORT(rt_ringbuffer_put);

/**
 * @brief Put a block of data into the ringbuffer. If the size of ringbuffer is not enough, it will overwrite the existing data in the ringbuffer.
 *
 * @param rb            A pointer to the ringbuffer object.
 * @param ptr           A pointer to the data buffer.
 * @param length        The size of data in bytes.
 *
 * @return Return the size in bytes put into the ringbuffer actually.
 */
rt_size_t rt_ringbuffer_put_force(struct rt_ringbuffer *rb,
                            const rt_uint8_t     *ptr,
                            rt_uint16_t           length)
{
    rt_uint16_t space_length;

    RT_ASSERT(rb != RT_NULL);

    space_length = rt_ringbuffer_space_len(rb);

    if (length > rb->buffer_size)
    {
        ptr = &ptr[length - rb->buffer_size];
        length = rb->buffer_size;
    }

    if (rb->buffer_size - rb->write_index > length)
    {
        /* read_index - write_index = empty space */
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->write_index += length;

        if (length > space_length)
            rb->read_index = rb->write_index;

        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index],
           &ptr[0],
           rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0],
           &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    /* we are going into the other side of the mirror */
    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    if (length > space_length)
    {
        if (rb->write_index <= rb->read_index)
            rb->read_mirror = ~rb->read_mirror;
        rb->read_index = rb->write_index;
    }

    return length;
}
RTM_EXPORT(rt_ringbuffer_put_force);

/**
 * @brief Get a block of data from the ringbuffer.
 *
 * @param rb            A pointer to the ringbuffer.
 * @param ptr           A pointer to the data buffer.
 * @param length        The size of data we want to read from the ringbuffer.
 *
 * @return Return the size of data we read from the ringbuffer actually.
 */
rt_size_t rt_ringbuffer_get(struct rt_ringbuffer *rb,
                            rt_uint8_t           *ptr,
                            rt_uint16_t           length)
{
    rt_size_t size;

    RT_ASSERT(rb != RT_NULL);

    /* whether has enough data  */
    size = rt_ringbuffer_data_len(rb);

    /* no data */
    if (size == 0)
        return 0;

    /* less data */
    if (size < length)
        length = size;

    if (rb->buffer_size - rb->read_index > length)
    {
        /* copy all of data */
        memcpy(ptr, &rb->buffer_ptr[rb->read_index], length);
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->read_index += length;
        return length;
    }

    memcpy(&ptr[0],
           &rb->buffer_ptr[rb->read_index],
           rb->buffer_size - rb->read_index);
    memcpy(&ptr[rb->buffer_size - rb->read_index],
           &rb->buffer_ptr[0],
           length - (rb->buffer_size - rb->read_index));

    /* we are going into the other side of the mirror */
    rb->read_mirror = ~rb->read_mirror;
    rb->read_index = length - (rb->buffer_size - rb->read_index);

    return length;
}
RTM_EXPORT(rt_ringbuffer_get);

/**
 *  peak data from ring buffer
 */

/**
 * @brief Peak data from the ringbuffer.
 *
 * @param rb        A pointer to the ringbuffer.
 * @param ptr       When this function return, *ptr is a pointer to the first character of ringbuffer.
 *
 * @return Return the size of ringbuffer.
 */
rt_size_t rt_ringbuffer_peak(struct rt_ringbuffer *rb, rt_uint8_t **ptr)
{
    RT_ASSERT(rb != RT_NULL);

    *ptr = RT_NULL;

    /* whether has enough data  */
    rt_size_t size = rt_ringbuffer_data_len(rb);

    /* no data */
    if (size == 0)
        return 0;

    *ptr = &rb->buffer_ptr[rb->read_index];

    if(rb->buffer_size - rb->read_index > size)
    {
        rb->read_index += size;
        return size;
    }

    size = rb->buffer_size - rb->read_index;

    /* we are going into the other side of the mirror */
    rb->read_mirror = ~rb->read_mirror;
    rb->read_index = 0;

    return size;
}
RTM_EXPORT(rt_ringbuffer_peak);

/**
 * @brief Put a character into the ringbuffer. If ringbuffer is full, This operation will fail.
 *
 * @param rb        A pointer to the ringbuffer object.
 * @param ch        A character to be put into the ringbuffer.
 *
 * @return Return the size in bytes put into the ringbuffer. If return 0, it means the ringbuffer if full. If return 1, it means success.
 */
rt_size_t rt_ringbuffer_putchar(struct rt_ringbuffer *rb, const rt_uint8_t ch)
{
    RT_ASSERT(rb != RT_NULL);

    /* whether has enough space */
    if (!rt_ringbuffer_space_len(rb))
        return 0;

    rb->buffer_ptr[rb->write_index] = ch;

    /* flip mirror */
    if (rb->write_index == rb->buffer_size-1)
    {
        rb->write_mirror = ~rb->write_mirror;
        rb->write_index = 0;
    }
    else
    {
        rb->write_index++;
    }

    return 1;
}
RTM_EXPORT(rt_ringbuffer_putchar);

/**
 * @brief Put a character into the ringbuffer. If ringbuffer is full, it will discard one old data and put into a new data.
 *
 * @param rb        A pointer to the ringbuffer object.
 * @param ch        A character to be put into the ringbuffer.
 *
 * @return Return the size in bytes put into the ringbuffer. Always return 1.
 */
rt_size_t rt_ringbuffer_putchar_force(struct rt_ringbuffer *rb, const rt_uint8_t ch)
{
    enum rt_ringbuffer_state old_state;

    RT_ASSERT(rb != RT_NULL);

    old_state = rt_ringbuffer_status(rb);

    rb->buffer_ptr[rb->write_index] = ch;

    /* flip mirror */
    if (rb->write_index == rb->buffer_size-1)
    {
        rb->write_mirror = ~rb->write_mirror;
        rb->write_index = 0;
        if (old_state == RT_RINGBUFFER_FULL)
        {
            rb->read_mirror = ~rb->read_mirror;
            rb->read_index = rb->write_index;
        }
    }
    else
    {
        rb->write_index++;
        if (old_state == RT_RINGBUFFER_FULL)
            rb->read_index = rb->write_index;
    }

    return 1;
}
RTM_EXPORT(rt_ringbuffer_putchar_force);

/**
 * get a character from a ringbuffer
 */

/**
 * @brief Get a character from the ringbuffer.
 *
 * @param rb        The pointer to ringbuffer object.
 * @param ch        The buffer to store character read from ringbuffer.
 *
 * @return 0    Ringbuffer is empty.
 * @return 1    Success
 */
rt_size_t rt_ringbuffer_getchar(struct rt_ringbuffer *rb, rt_uint8_t *ch)
{
    RT_ASSERT(rb != RT_NULL);

    /* ringbuffer is empty */
    if (!rt_ringbuffer_data_len(rb))
        return 0;

    /* put character */
    *ch = rb->buffer_ptr[rb->read_index];

    if (rb->read_index == rb->buffer_size-1)
    {
        rb->read_mirror = ~rb->read_mirror;
        rb->read_index = 0;
    }
    else
    {
        rb->read_index++;
    }

    return 1;
}
RTM_EXPORT(rt_ringbuffer_getchar);

/**
 * @brief Get the size of data in the ringbuffer in bytes.
 *
 * @param rb        The pointer to ringbuffer object.
 *
 * @return Return the size of data in the ringbuffer in bytes.
 */
rt_size_t rt_ringbuffer_data_len(struct rt_ringbuffer *rb)
{
    switch (rt_ringbuffer_status(rb))
    {
    case RT_RINGBUFFER_EMPTY:
        return 0;
    case RT_RINGBUFFER_FULL:
        return rb->buffer_size;
    case RT_RINGBUFFER_HALFFULL:
    default:
        if (rb->write_index > rb->read_index)
            return rb->write_index - rb->read_index;
        else
            return rb->buffer_size - (rb->read_index - rb->write_index);
    };
}
RTM_EXPORT(rt_ringbuffer_data_len);

/**
 * @brief Reset the ringbuffer object, and clear all contents in the buffer.
 *
 * @param rb        A pointer to the ringbuffer object.
 */
void rt_ringbuffer_reset(struct rt_ringbuffer *rb)
{
    RT_ASSERT(rb != RT_NULL);

    rb->read_mirror = 0;
    rb->read_index = 0;
    rb->write_mirror = 0;
    rb->write_index = 0;
}
RTM_EXPORT(rt_ringbuffer_reset);

#ifdef RT_USING_HEAP

/**
 * @brief Create a ringbuffer object with a given size.
 *
 * @param size      Size of the buffer in bytes.
 *
 * @return Return a pointer to ringbuffer object. When the return value is RT_NULL, it means the creation failed.
 */
struct rt_ringbuffer *rt_ringbuffer_create(rt_uint16_t size)
{
    struct rt_ringbuffer *rb;
    rt_uint8_t *pool;

    RT_ASSERT(size > 0);

    size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);

    rb = (struct rt_ringbuffer *)rt_malloc(sizeof(struct rt_ringbuffer));
    if (rb == RT_NULL)
        goto exit;

    pool = (rt_uint8_t *)rt_malloc(size);
    if (pool == RT_NULL)
    {
        rt_free(rb);
        rb = RT_NULL;
        goto exit;
    }
    rt_ringbuffer_init(rb, pool, size);

exit:
    return rb;
}
RTM_EXPORT(rt_ringbuffer_create);

/**
 * @brief Destroy a ringbuffer object, which is created by rt_ringbuffer_create() .
 *
 * @param rb        A pointer to the ringbuffer object.
 */
void rt_ringbuffer_destroy(struct rt_ringbuffer *rb)
{
    RT_ASSERT(rb != RT_NULL);

    rt_free(rb->buffer_ptr);
    rt_free(rb);
}
RTM_EXPORT(rt_ringbuffer_destroy);

#endif
