/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_CONSOLE_H__
#define __VIRTIO_CONSOLE_H__

#include <rtdef.h>

#include <virtio.h>

#ifndef RT_USING_VIRTIO_CONSOLE_PORT_MAX_NR
#define RT_USING_VIRTIO_CONSOLE_PORT_MAX_NR 4
#endif

#define VIRTIO_CONSOLE_QUEUE_DATA_RX    0
#define VIRTIO_CONSOLE_QUEUE_DATA_TX    1
#define VIRTIO_CONSOLE_QUEUE_CTRL_RX    2
#define VIRTIO_CONSOLE_QUEUE_CTRL_TX    3
#define VIRTIO_CONSOLE_QUEUE_SIZE       64

/* Every port has data rx & tx, and port0 has ctrl rx & tx in multiport */
#define VIRTIO_CONSOLE_PORT_QUEUE_INDEX(id, queue)  ((id) * 2 + (!!(id)) * 2 + (queue))

#define VIRTIO_CONSOLE_PORT_BAD_ID      (~(rt_uint32_t)0)

#define VIRTIO_CONSOLE_F_SIZE           0   /* Does host provide console size? */
#define VIRTIO_CONSOLE_F_MULTIPORT      1   /* Does host provide multiple ports? */
#define VIRTIO_CONSOLE_F_EMERG_WRITE    2   /* Does host support emergency write? */

struct virtio_console_config
{
    rt_uint16_t cols;
    rt_uint16_t rows;
    rt_uint32_t max_nr_ports;
    rt_uint32_t emerg_wr;
} __attribute__((packed));

struct virtio_console_control
{
    rt_uint32_t id;     /* Port number */
    rt_uint16_t event;  /* The kind of control event */
    rt_uint16_t value;  /* Extra information for the event */
};

enum virtio_console_control_event
{
    VIRTIO_CONSOLE_DEVICE_READY = 0,
    VIRTIO_CONSOLE_PORT_ADD,
    VIRTIO_CONSOLE_PORT_REMOVE,
    VIRTIO_CONSOLE_PORT_READY,
    VIRTIO_CONSOLE_CONSOLE_PORT,
    VIRTIO_CONSOLE_RESIZE,
    VIRTIO_CONSOLE_PORT_OPEN,
    VIRTIO_CONSOLE_PORT_NAME,
};

struct virtio_console_resize
{
    rt_uint16_t cols;
    rt_uint16_t rows;
};

struct virtio_console_device
{
    struct rt_device parent;

    struct virtio_device virtio_dev;

    rt_uint32_t console_id;
    rt_size_t port_nr;
    rt_size_t max_port_nr;
    rt_list_t port_head;
    struct virtio_console_config *config;

    struct
    {
        rt_ubase_t tx_ctrl_paddr;
        struct virtio_console_control rx_ctrl, tx_ctrl;
    } info[VIRTIO_CONSOLE_QUEUE_SIZE];
};

rt_err_t rt_virtio_console_init(rt_ubase_t *mmio_base, rt_uint32_t irq);

enum
{
    VIRTIO_DEVICE_CTRL_CONSOLE_PORT_CREATE  = 0x20,
    VIRTIO_DEVICE_CTRL_CONSOLE_PORT_DESTROY,
};

#endif /* __VIRTIO_CONSOLE_H__ */
