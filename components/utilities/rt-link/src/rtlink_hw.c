/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     xiangxistu   the first version
 * 2021-05-08     Sherman      Optimize the operation function on the rt_link_receive_buffer
 */

#include <rtthread.h>

#include <rtlink.h>
#include <rtlink_hw.h>
#include <rtlink_port.h>
#include <rtlink_utils.h>

#define DBG_TAG "rtlink_hw"
#ifdef USING_RT_LINK_HW_DEBUG
    #define DBG_LVL DBG_LOG
#else
    #define DBG_LVL DBG_INFO
#endif
#define DBG_COLOR
#include <rtdbg.h>

static struct rt_link_receive_buffer *rx_buffer = RT_NULL;

struct rt_link_receive_buffer *rt_link_hw_buffer_init(void *parameter)
{
    rx_buffer = rt_malloc(sizeof(struct rt_link_receive_buffer));
    if (rx_buffer != RT_NULL)
    {
        rt_memset(rx_buffer, 0, sizeof(struct rt_link_receive_buffer));
        rx_buffer->read_point = rx_buffer->data;
        rx_buffer->write_point = rx_buffer->data;
        rx_buffer->end_point = rx_buffer->data + RT_LINK_RECEIVE_BUFFER_LENGTH; /* Point to memory that has no access rights */
    }
    else
    {
        LOG_E("receive buffer alloc failed, init failed.");
    }

    return rx_buffer;
}

static rt_size_t rt_link_hw_buffer_write(void *data, rt_size_t count)
{
    int surplus = 0;
    if (rx_buffer == RT_NULL)
    {
        return 0;
    }
    /* (data)----(r)----(w)----(end) */
    if (rx_buffer->write_point >= rx_buffer->read_point)
    {
        rt_size_t w2end = rx_buffer->end_point - rx_buffer->write_point;
        surplus = RT_LINK_RECEIVE_BUFFER_LENGTH - (rx_buffer->write_point - rx_buffer->read_point);
        count = count > surplus ? surplus : count;
        if (count >= w2end)
        {
            rt_memcpy(rx_buffer->write_point, data, w2end);
            rx_buffer->write_point = rx_buffer->data;

            rt_memcpy(rx_buffer->write_point, (rt_uint8_t *)data + w2end, (count - w2end));
            rx_buffer->write_point += (count - w2end);
        }
        else
        {
            rt_memcpy(rx_buffer->write_point, data, count);
            rx_buffer->write_point += count;
        }
    }
    else    /* (data)----(w)----(r)----(end) */
    {
        surplus = rx_buffer->read_point - rx_buffer->write_point;
        count = count > surplus ? surplus : count;
        rt_memcpy(rx_buffer->write_point, data, count);
        rx_buffer->write_point += count;
    }
    return count;
}

/* increases buffer pointer by one and circle around if necessary */
void rt_link_hw_buffer_point_shift(rt_uint8_t **pointer_address, rt_size_t length)
{
    rt_uint8_t *pointer = *pointer_address + length;

    if (rx_buffer->write_point >= rx_buffer->read_point)
    {
        if (pointer >= rx_buffer->write_point)
        {
            *pointer_address = rx_buffer->write_point;
        }
        else
        {
            *pointer_address = pointer;
        }
    }
    else
    {
        if (pointer >= rx_buffer->end_point)
        {
            *pointer_address = rx_buffer->data;
            pointer = pointer - rx_buffer->end_point + rx_buffer->data;

            if (pointer >= rx_buffer->write_point)
            {
                *pointer_address = rx_buffer->write_point;
            }
            else
            {
                *pointer_address = pointer;
            }
        }
        else
        {
            *pointer_address = pointer;
        }
    }
}

/* copy data from receive buffer */
void rt_link_hw_copy(rt_uint8_t *dst, rt_uint8_t *src, rt_size_t count)
{
    rt_uint8_t *pointer = RT_NULL;

    pointer = src + count;
    if (pointer >= rx_buffer->end_point)
    {
        rt_size_t offset = 0;
        offset = rx_buffer->end_point - src;
        rt_memcpy(dst, src, offset);
        rt_memcpy(dst + offset,  rx_buffer->data, pointer - rx_buffer->end_point);
    }
    else
    {
        rt_memcpy(dst, src, count);
    }
}

/* Length of data received */
rt_size_t rt_link_hw_recv_len(struct rt_link_receive_buffer *buffer)
{
    if (buffer == RT_NULL)
    {
        return 0;
    }
    if (buffer->write_point >= buffer->read_point)
    {
        return (buffer->write_point - buffer->read_point);
    }
    else
    {
        return (RT_LINK_RECEIVE_BUFFER_LENGTH - (buffer->read_point - buffer->write_point));
    }
}

rt_err_t rt_link_reset_crc32(void)
{
#ifdef RT_LINK_USING_HW_CRC
    return rt_link_hw_crc32_reset();
#else
    return rt_link_sf_crc32_reset();
#endif
}

rt_uint32_t rt_link_crc32(rt_uint8_t *data, rt_size_t u32_size)
{
#ifdef RT_LINK_USING_HW_CRC
    return rt_link_hw_crc32(data, u32_size);
#else
    return rt_link_sf_crc32(data, u32_size);
#endif
}

rt_uint32_t rt_link_get_crc(rt_uint8_t using_buffer_ring, rt_uint8_t *data, rt_size_t size)
{
    rt_uint32_t crc32 = 0x0;
    rt_size_t surplus = 0;

    if (data == RT_NULL)
    {
        LOG_D("warning, the parameter error: %d, data: 0x%08d.", size, data);
        return 0;
    }

    rt_link_reset_crc32();
    if (using_buffer_ring == 1)
    {
        /* modify the missing character */
        surplus = rx_buffer->end_point - data;
        if (surplus >= size)
        {
            crc32 = rt_link_crc32(data, size);
        }
        else
        {
            rt_link_crc32(data, surplus);
            crc32 = rt_link_crc32(rx_buffer->data, size - surplus);
        }
    }
    else
    {
        crc32 = rt_link_crc32(data, size);
    }
    return crc32;
}

rt_size_t rt_link_hw_send(void *data, rt_size_t length)
{
    rt_size_t send_len = 0;
    send_len = rt_link_port_send(data, length);
    if (send_len <= 0)
    {
        rt_link_port_reconnect();
        send_len = rt_link_port_send(data, length);
    }
    return send_len;
}

rt_size_t rt_link_hw_write_cb(void *data, rt_size_t length)
{
    /* write real data into rtlink receive buffer */
    rt_size_t len = rt_link_hw_buffer_write(data, length);
    struct rt_link_session *scb = rt_link_get_scb();
    if (scb)
    {
        rt_event_send(&scb->event, RT_LINK_READ_CHECK_EVENT);
    }
    return len;
}

rt_err_t rt_link_hw_init(void)
{
    struct rt_link_session *scb = rt_link_get_scb();
    if ((rx_buffer != RT_NULL) || (scb == RT_NULL))
    {
        return -RT_ERROR;
    }

    /* alloc receive buffer to store data */
    if (rt_link_hw_buffer_init(RT_NULL) == RT_NULL)
    {
        return -RT_ENOMEM;
    }
    scb->rx_buffer = rx_buffer;
    scb->calculate_crc = rt_link_get_crc;

    if (RT_EOK != rt_link_port_init())
    {
        return -RT_ERROR;
    }

#ifdef LINK_LAYER_USING_HW_CRC
    /* crc hardware device for mcu and node */
    if (RT_EOK != rt_link_hw_crc32_init())
    {
        return -RT_ERROR;
    }
#endif

    LOG_I("link layer hardware environment init successful.");
    return RT_EOK;
}

rt_err_t rt_link_hw_deinit(void)
{
    if (rx_buffer)
    {
        rt_free(rx_buffer);
        rx_buffer = RT_NULL;
    }
    struct rt_link_session *scb = rt_link_get_scb();
    if (scb)
    {
        scb->rx_buffer = rx_buffer;
        scb->calculate_crc = RT_NULL;
    }
    if (RT_EOK != rt_link_port_deinit())
    {
        return -RT_ERROR;
    }

#ifdef LINK_LAYER_USING_HW_CRC
    /* crc hardware device for mcu and node */
    if (RT_EOK != rt_link_hw_crc32_deinit())
    {
        return -RT_ERROR;
    }
#endif

    LOG_I("rtlink hardware deinit successful.");
    return RT_EOK;
}
