/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-07     ZXY       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <ipc/ringbuffer.h>

#define RING_BUFFER_LEN        8
static struct ringbuffer *rb;
static char  *str = "Hello, World new ringbuffer32";
typedef struct rb_example {
    rt_uint32_t a;
    rt_uint32_t b;
    rt_uint32_t c;
} rb_example_t;


int ringbuffer_example(void)
{
    rb_example_t data = {
        .a = 1,
        .b = 2,
    };

    struct rt_ringbuffer * rb = rt_ringbuffer_create(sizeof(rb_example_t) * 2);
    RT_ASSERT(rb != RT_NULL);

    rt_kprintf("Put data to   ringbuffer, a: %d b: %d size: %d\n", data.a, data.b, sizeof(data));
    rt_ringbuffer_put(rb, (rt_uint8_t *)&data, sizeof(data));


    rb_example_t recv_data;
    rt_size_t recv = rt_ringbuffer_get(rb, (rt_uint8_t *)&recv_data, sizeof(recv_data));
    RT_ASSERT(recv == sizeof(recv_data));
    rt_kprintf("Get data from ringbuffer, a: %d b: %d size: %d\n", recv_data.a, recv_data.b, sizeof(recv_data));

    return 0;
}
MSH_CMD_EXPORT(ringbuffer_example, ringbuffer example);


int ringbuffer_force_example(void)
{
    uint8_t test[6] = {1,2,3,4,5,6};
    struct rt_ringbuffer * rb;
    rb = rt_ringbuffer_create(4);
    RT_ASSERT(rb != RT_NULL);

    rt_kprintf("Put data to   ringbuffer, %d %d %d %d %d %d\n", test[0],test[1],test[2],test[3],test[4],test[5]);
    rt_ringbuffer_put_force(rb, (rt_uint8_t *)&test, sizeof(test));


    uint8_t recv_data[4]={0};
    rt_ringbuffer_get(rb, (rt_uint8_t *)&recv_data, sizeof(test));
    rt_kprintf("Get data from ringbuffer, %d %d %d %d\n", recv_data[0],recv_data[1],recv_data[2],recv_data[3]);
    rt_kprintf("write mirror: %d read mirror: %d\n", rb->write_mirror,rb->read_mirror);
    return 0;
}
MSH_CMD_EXPORT(ringbuffer_force_example, ringbuffer example);

static void consumer_thread_entry(void *arg)
{
    char ch;
    while (1)
    {
        if (1 == rt_ringbuffer_getchar(rb, &ch))
        {
            rt_kprintf("[Consumer] <- %c\n", ch);
        }
        rt_thread_mdelay(500);
    }
}
static void ringbuffer_sample(int argc, char** argv)
{
    rt_thread_t tid;
    rt_uint16_t i = 0;
    rb = rt_ringbuffer_create(RING_BUFFER_LEN);
    if (rb == RT_NULL)
    {
        rt_kprintf("Can't create ringbffer");
        return;
    }
    tid = rt_thread_create("consumer", consumer_thread_entry, RT_NULL,
                           1024, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid == RT_NULL)
    {
        rt_ringbuffer_destroy(rb);
    }
    rt_thread_startup(tid);
    while (str[i] != '\0')
    {
        rt_kprintf("[Producer] -> %c\n", str[i]);
        rt_ringbuffer_putchar(rb, str[i++]);
        rt_thread_mdelay(500);
    }
    rt_thread_delete(tid);
    rt_ringbuffer_destroy(rb);
}
MSH_CMD_EXPORT(ringbuffer_sample, Start a producer and a consumer with a ringbuffer);
