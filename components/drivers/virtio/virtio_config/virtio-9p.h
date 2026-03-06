/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_9P_H__
#define __VIRTIO_9P_H__

#include <drivers/core/dm.h>

#define VIRTIO_9P_F_MOUNT_TAG   0

rt_packed(struct virtio_9p_config
{
    /* length of the tag name */
    rt_le16_t tag_len;
    /* non-NULL terminated tag name */
    rt_uint8_t tag[];
});

#endif /* __VIRTIO_9P_H__ */
