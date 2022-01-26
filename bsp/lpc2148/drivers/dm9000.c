/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include "dm9000.h"

#include <netif/ethernetif.h>
#include "lwipopts.h"

#define MAX_ADDR_LEN 6
struct rt_dm9000_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];         /* hw address   */
};
static struct rt_dm9000_eth dm9000_device;

/* interrupt service routine */
void rt_dm9000_isr(int irqno)
{
    rt_uint32_t status;

    if (status) // if receive packet
    {
        rt_err_t result;

        /* a frame has been received */
        result = eth_device_ready(&(dm9000_device.parent));
        RT_ASSERT(result == RT_EOK);
    }

    if (status) // if finished packet transmission
    {
    }
}

/* RT-Thread Device Interface */
/* initialize the interface */

static rt_err_t rt_dm9000_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_dm9000_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_dm9000_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_dm9000_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_dm9000_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_dm9000_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, dm9000_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_dm9000_tx( rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;
    rt_uint32_t len;
    rt_uint8_t* ptr;

    for (q = p; q != NULL; q = q->next)
    {
        len = q->len;
        ptr = q->payload;

        /* write data to device */
    }

    return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_dm9000_rx(rt_device_t dev)
{
    struct pbuf* p;
    rt_uint32_t len;

    /* init p pointer */
    p = RT_NULL;

    if (1) // if there is packet in device
    {
        /* get one packet length */
        len = 0; // packet length

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);

        if (p != RT_NULL)
        {
            rt_uint8_t* data;
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                data = q->payload;
                len = q->len;

                /* read data from device */
            }
        }
    }
    else
    {
        /* restore interrupt */
    }

    return p;
}

void rt_hw_dm9000_init()
{
    dm9000_device.parent.parent.init       = rt_dm9000_init;
    dm9000_device.parent.parent.open       = rt_dm9000_open;
    dm9000_device.parent.parent.close      = rt_dm9000_close;
    dm9000_device.parent.parent.read       = rt_dm9000_read;
    dm9000_device.parent.parent.write      = rt_dm9000_write;
    dm9000_device.parent.parent.control    = rt_dm9000_control;
    dm9000_device.parent.parent.user_data  = RT_NULL;

    dm9000_device.parent.eth_rx     = rt_dm9000_rx;
    dm9000_device.parent.eth_tx     = rt_dm9000_tx;

    rt_device_register((rt_device_t)&dm9000_device,
        "E0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);
}
