/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_RPMSG_H__
#define __VIRTIO_RPMSG_H__

#include <drivers/core/dm.h>

#define VIRTIO_RPMSG_F_NS               0 /* RP supports name service notifications */

#define VIRTIO_RPMSG_MAX_BUF_SIZE       512
#define VIRTIO_RPMSG_RESERVED_ADDRESSES 1024

rt_packed(struct virtio_rpmsg_hdr
{
    rt_le32_t src;
    rt_le32_t dst;
    rt_le32_t reserved;
    rt_le16_t len;
    rt_le16_t flags;
    rt_uint8_t data[];
});

#endif /* __VIRTIO_RPMSG_H__ */
