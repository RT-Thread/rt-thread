/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#ifndef __VIRTIO_CONSOLE_H__
#define __VIRTIO_CONSOLE_H__

#include <drivers/core/dm.h>

#define VIRTIO_CONSOLE_F_SIZE           0   /* Does host provide console size? */
#define VIRTIO_CONSOLE_F_MULTIPORT      1   /* Does host provide multiple ports? */
#define VIRTIO_CONSOLE_F_EMERG_WRITE    2   /* Does host support emergency write? */

rt_packed(struct virtio_console_config
{
    rt_le16_t cols;
    rt_le16_t rows;
    rt_le32_t max_nr_ports;
    rt_le32_t emerg_wr;
});

rt_packed(struct virtio_console_resize
{
    rt_le16_t cols;
    rt_le16_t rows;
});

rt_packed(struct virtio_console_control
{
#define VIRTIO_CONSOLE_BAD_ID       (~(rt_uint32_t)0)
    rt_le32_t id;       /* Port number */

#define VIRTIO_CONSOLE_DEVICE_READY 0
#define VIRTIO_CONSOLE_PORT_ADD     1
#define VIRTIO_CONSOLE_PORT_REMOVE  2
#define VIRTIO_CONSOLE_PORT_READY   3
#define VIRTIO_CONSOLE_CONSOLE_PORT 4
#define VIRTIO_CONSOLE_RESIZE       5
#define VIRTIO_CONSOLE_PORT_OPEN    6
#define VIRTIO_CONSOLE_PORT_NAME    7
    rt_le16_t event;    /* The kind of control event */
    rt_le16_t value;    /* Extra information for the event */
});

rt_packed(struct virtio_console_control_ext
{
    struct virtio_console_control ctrl;

    union
    {
        struct virtio_console_resize resize;
        rt_uint8_t data[64];
    };
});

#endif /* __VIRTIO_CONSOLE_H__ */
