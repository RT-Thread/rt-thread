/*
 * File      : pipe.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "audio_pipe.h"

static void _rt_pipe_resume_writer(struct rt_audio_pipe *pipe)
{
    if (!rt_list_isempty(&pipe->suspended_write_list))
    {
        rt_thread_t thread;

        RT_ASSERT(pipe->flag & RT_PIPE_FLAG_BLOCK_WR);

        /* get suspended thread */
        thread = rt_list_entry(pipe->suspended_write_list.next,
                struct rt_thread,
                tlist);

        /* resume the write thread */
        rt_thread_resume(thread);

        rt_schedule();
    }
}

static rt_size_t rt_pipe_read(rt_device_t dev,
                              rt_off_t    pos,
                              void       *buffer,
                              rt_size_t   size)
{
    rt_uint32_t level;
    rt_thread_t thread;
    struct rt_audio_pipe *pipe;
    rt_size_t read_nbytes;

    pipe = (struct rt_audio_pipe *)dev;
    RT_ASSERT(pipe != RT_NULL);

    if (!(pipe->flag & RT_PIPE_FLAG_BLOCK_RD))
    {
        level = rt_hw_interrupt_disable();
        read_nbytes = rt_ringbuffer_get(&(pipe->ringbuffer), buffer, size);

        /* if the ringbuffer is empty, there won't be any writer waiting */
        if (read_nbytes)
            _rt_pipe_resume_writer(pipe);

        rt_hw_interrupt_enable(level);

        return read_nbytes;
    }

    thread = rt_thread_self();

    /* current context checking */
    RT_DEBUG_NOT_IN_INTERRUPT;

    do {
        level = rt_hw_interrupt_disable();
        read_nbytes = rt_ringbuffer_get(&(pipe->ringbuffer), buffer, size);
        if (read_nbytes == 0)
        {
            rt_thread_suspend(thread);
            /* waiting on suspended read list */
            rt_list_insert_before(&(pipe->suspended_read_list),
                                  &(thread->tlist));
            rt_hw_interrupt_enable(level);

            rt_schedule();
        }
        else
        {
            _rt_pipe_resume_writer(pipe);
            rt_hw_interrupt_enable(level);
            break;
        }
    } while (read_nbytes == 0);

    return read_nbytes;
}

static void _rt_pipe_resume_reader(struct rt_audio_pipe *pipe)
{
    if (pipe->parent.rx_indicate)
        pipe->parent.rx_indicate(&pipe->parent,
                                 rt_ringbuffer_data_len(&pipe->ringbuffer));

    if (!rt_list_isempty(&pipe->suspended_read_list))
    {
        rt_thread_t thread;

        RT_ASSERT(pipe->flag & RT_PIPE_FLAG_BLOCK_RD);

        /* get suspended thread */
        thread = rt_list_entry(pipe->suspended_read_list.next,
                struct rt_thread,
                tlist);

        /* resume the read thread */
        rt_thread_resume(thread);

        rt_schedule();
    }
}

static rt_size_t rt_pipe_write(rt_device_t dev,
                               rt_off_t    pos,
                               const void *buffer,
                               rt_size_t   size)
{
    rt_uint32_t level;
    rt_thread_t thread;
    struct rt_audio_pipe *pipe;
    rt_size_t write_nbytes;

    pipe = (struct rt_audio_pipe *)dev;
    RT_ASSERT(pipe != RT_NULL);

    if ((pipe->flag & RT_PIPE_FLAG_FORCE_WR) ||
       !(pipe->flag & RT_PIPE_FLAG_BLOCK_WR))
    {
        level = rt_hw_interrupt_disable();

        if (pipe->flag & RT_PIPE_FLAG_FORCE_WR)
            write_nbytes = rt_ringbuffer_put_force(&(pipe->ringbuffer),
                                                   buffer, size);
        else
            write_nbytes = rt_ringbuffer_put(&(pipe->ringbuffer),
                                             buffer, size);

        _rt_pipe_resume_reader(pipe);

        rt_hw_interrupt_enable(level);

        return write_nbytes;
    }

    thread = rt_thread_self();

    /* current context checking */
    RT_DEBUG_NOT_IN_INTERRUPT;

    do {
        level = rt_hw_interrupt_disable();
        write_nbytes = rt_ringbuffer_put(&(pipe->ringbuffer), buffer, size);
        if (write_nbytes == 0)
        {
            /* pipe full, waiting on suspended write list */
            rt_thread_suspend(thread);
            /* waiting on suspended read list */
            rt_list_insert_before(&(pipe->suspended_write_list),
                                  &(thread->tlist));
            rt_hw_interrupt_enable(level);

            rt_schedule();
        }
        else
        {
            _rt_pipe_resume_reader(pipe);
            rt_hw_interrupt_enable(level);
            break;
        }
    } while (write_nbytes == 0);

    return write_nbytes;
}

static rt_err_t rt_pipe_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_audio_pipe *pipe;

    pipe = (struct rt_audio_pipe *)dev;

    if (cmd == PIPE_CTRL_GET_SPACE && args)
        *(rt_size_t*)args = rt_ringbuffer_space_len(&pipe->ringbuffer);
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops audio_pipe_ops
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_pipe_read,
    rt_pipe_write,
    rt_pipe_control
};
#endif

/**
 * This function will initialize a pipe device and put it under control of
 * resource management.
 *
 * @param pipe the pipe device
 * @param name the name of pipe device
 * @param flag the attribute of the pipe device
 * @param buf  the buffer of pipe device
 * @param size the size of pipe device buffer
 *
 * @return the operation status, RT_EOK on successful
 */
rt_err_t rt_audio_pipe_init(struct rt_audio_pipe *pipe,
                      const char *name,
                      enum rt_audio_pipe_flag flag,
                      rt_uint8_t *buf,
                      rt_size_t size)
{
    RT_ASSERT(pipe);
    RT_ASSERT(buf);

    /* initialize suspended list */
    rt_list_init(&pipe->suspended_read_list);
    rt_list_init(&pipe->suspended_write_list);

    /* initialize ring buffer */
    rt_ringbuffer_init(&pipe->ringbuffer, buf, size);

    pipe->flag = flag;

    /* create pipe */
    pipe->parent.type    = RT_Device_Class_Pipe;
#ifdef RT_USING_DEVICE_OPS
    pipe->parent.ops     = &audio_pipe_ops;
#else
    pipe->parent.init    = RT_NULL;
    pipe->parent.open    = RT_NULL;
    pipe->parent.close   = RT_NULL;
    pipe->parent.read    = rt_pipe_read;
    pipe->parent.write   = rt_pipe_write;
    pipe->parent.control = rt_pipe_control;
#endif

    return rt_device_register(&(pipe->parent), name, RT_DEVICE_FLAG_RDWR);
}

/**
 * This function will detach a pipe device from resource management
 *
 * @param pipe the pipe device
 *
 * @return the operation status, RT_EOK on successful
 */
rt_err_t rt_audio_pipe_detach(struct rt_audio_pipe *pipe)
{
    return rt_device_unregister(&pipe->parent);
}

#ifdef RT_USING_HEAP
rt_err_t rt_audio_pipe_create(const char *name, enum rt_audio_pipe_flag flag, rt_size_t size)
{
    rt_uint8_t *rb_memptr = RT_NULL;
    struct rt_audio_pipe *pipe = RT_NULL;

    /* get aligned size */
    size = RT_ALIGN(size, RT_ALIGN_SIZE);
    pipe = (struct rt_audio_pipe *)rt_calloc(1, sizeof(struct rt_audio_pipe));
    if (pipe == RT_NULL)
        return -RT_ENOMEM;

    /* create ring buffer of pipe */
    rb_memptr = rt_malloc(size);
    if (rb_memptr == RT_NULL)
    {
        rt_free(pipe);
        return -RT_ENOMEM;
    }

    return rt_audio_pipe_init(pipe, name, flag, rb_memptr, size);
}

void rt_audio_pipe_destroy(struct rt_audio_pipe *pipe)
{
    if (pipe == RT_NULL)
        return;

    /* un-register pipe device */
    rt_audio_pipe_detach(pipe);

    /* release memory */
    rt_free(pipe->ringbuffer.buffer_ptr);
    rt_free(pipe);

    return;
}

#endif /* RT_USING_HEAP */
