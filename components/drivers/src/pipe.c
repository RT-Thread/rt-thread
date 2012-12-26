/*
 * File      : pipe.c
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

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

static rt_size_t rt_pipe_read(rt_device_t dev,
                              rt_off_t    pos,
                              void       *buffer,
                              rt_size_t   size)
{
    rt_uint32_t level;
    rt_thread_t thread;
    struct rt_pipe_device *pipe;
    rt_size_t read_nbytes;

    pipe = PIPE_DEVICE(dev);
    RT_ASSERT(pipe != RT_NULL);

    thread = rt_thread_self();

    /* current context checking */
    RT_DEBUG_NOT_IN_INTERRUPT;

    do 
    {
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
            if (!rt_list_isempty(&pipe->suspended_write_list))
            {
                /* get suspended thread */
                thread = rt_list_entry(pipe->suspended_write_list.next,
                                       struct rt_thread,
                                       tlist);

                /* resume the write thread */
                rt_thread_resume(thread);
                rt_hw_interrupt_enable(level);

                rt_schedule();
            }
            else
            {
                rt_hw_interrupt_enable(level);
            }
            break;
        }
    } while (read_nbytes == 0);

    return read_nbytes;
}

struct rt_pipe_device *_pipe = RT_NULL;
static rt_size_t rt_pipe_write(rt_device_t dev,
                               rt_off_t    pos,
                               const void *buffer,
                               rt_size_t   size)
{
    rt_uint32_t level;
    rt_thread_t thread;
    struct rt_pipe_device *pipe;
    rt_size_t write_nbytes;

    pipe = PIPE_DEVICE(dev);
    RT_ASSERT(pipe != RT_NULL);
    if (_pipe == RT_NULL)
        _pipe = pipe;

    thread = rt_thread_self();

    /* current context checking */
    RT_DEBUG_NOT_IN_INTERRUPT;

    do
    {
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
            if (!rt_list_isempty(&pipe->suspended_read_list))
            {
                /* get suspended thread */
                thread = rt_list_entry(pipe->suspended_read_list.next,
                                       struct rt_thread,
                                       tlist);

                /* resume the read thread */
                rt_thread_resume(thread);
                rt_hw_interrupt_enable(level);

                rt_schedule();
            }
            else
            {
                rt_hw_interrupt_enable(level);
            }
            break;
        }
    }while (write_nbytes == 0);

    return write_nbytes;
}

static rt_err_t rt_pipe_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    return RT_EOK;
}

rt_err_t rt_pipe_create(const char *name, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint8_t *rb_memptr = RT_NULL;
    struct rt_pipe_device *pipe = RT_NULL;

    /* get aligned size */
    size = RT_ALIGN(size, RT_ALIGN_SIZE);
    pipe = (struct rt_pipe_device *)rt_calloc(1, sizeof(struct rt_pipe_device));
    if (pipe != RT_NULL)
    {
        /* create ring buffer of pipe */
        rb_memptr = rt_malloc(size);
        if (rb_memptr == RT_NULL)
        {
            result = -RT_ENOMEM;
            goto __exit;
        }
        /* initialize suspended list */
        rt_list_init(&pipe->suspended_read_list);
        rt_list_init(&pipe->suspended_write_list);

        /* initialize ring buffer */
        rt_ringbuffer_init(&pipe->ringbuffer, rb_memptr, size);

        /* create device */
        pipe->parent.type    = RT_Device_Class_Char;
        pipe->parent.init    = RT_NULL;
        pipe->parent.open    = RT_NULL;
        pipe->parent.close   = RT_NULL;
        pipe->parent.read    = rt_pipe_read;
        pipe->parent.write   = rt_pipe_write;
        pipe->parent.control = rt_pipe_control;

        return rt_device_register(&(pipe->parent), name, RT_DEVICE_FLAG_RDWR);
    }
    else
    {
        result = -RT_ENOMEM;
    }

__exit:
    if (pipe != RT_NULL)
        rt_free(pipe);
    if (rb_memptr != RT_NULL)
        rt_free(rb_memptr);

    return result;
}
RTM_EXPORT(rt_pipe_create);

void rt_pipe_destroy(struct rt_pipe_device *pipe)
{
    if (pipe == RT_NULL)
        return;

    /* un-register pipe device */
    rt_device_unregister(&(pipe->parent));

    /* release memory */
    rt_free(pipe->ringbuffer.buffer_ptr);
    rt_free(pipe);

    return;
}
RTM_EXPORT(rt_pipe_destroy);
