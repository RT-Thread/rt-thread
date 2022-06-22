/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef DATAQUEUE_H__
#define DATAQUEUE_H__

#include <rtthread.h>

#define RT_DATAQUEUE_EVENT_UNKNOWN   0x00
#define RT_DATAQUEUE_EVENT_POP       0x01
#define RT_DATAQUEUE_EVENT_PUSH      0x02
#define RT_DATAQUEUE_EVENT_LWM       0x03

struct rt_data_item;

/* data queue implementation */
struct rt_data_queue
{
    rt_uint32_t magic;

    rt_uint16_t size;
    rt_uint16_t lwm;

    rt_uint16_t get_index : 15;
    rt_uint16_t is_empty  : 1;
    rt_uint16_t put_index : 15;
    rt_uint16_t is_full   : 1;

    struct rt_data_item *queue;

    rt_list_t suspended_push_list;
    rt_list_t suspended_pop_list;

    /* event notify */
    void (*evt_notify)(struct rt_data_queue *queue, rt_uint32_t event);
};

/**
 * DataQueue for DeviceDriver
 */
rt_err_t rt_data_queue_init(struct rt_data_queue *queue,
                            rt_uint16_t           size,
                            rt_uint16_t           lwm,
                            void (*evt_notify)(struct rt_data_queue *queue, rt_uint32_t event));
rt_err_t rt_data_queue_push(struct rt_data_queue *queue,
                            const void           *data_ptr,
                            rt_size_t             data_size,
                            rt_int32_t            timeout);
rt_err_t rt_data_queue_pop(struct rt_data_queue *queue,
                           const void          **data_ptr,
                           rt_size_t            *size,
                           rt_int32_t            timeout);
rt_err_t rt_data_queue_peek(struct rt_data_queue *queue,
                            const void          **data_ptr,
                            rt_size_t            *size);
void rt_data_queue_reset(struct rt_data_queue *queue);
rt_err_t rt_data_queue_deinit(struct rt_data_queue *queue);
rt_uint16_t rt_data_queue_len(struct rt_data_queue *queue);

#endif
