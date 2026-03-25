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

#ifndef __VIRTIO_INPUT_H__
#define __VIRTIO_INPUT_H__

#include <drivers/core/dm.h>

enum virtio_input_config_select
{
    VIRTIO_INPUT_CFG_UNSET      = 0x00,
    VIRTIO_INPUT_CFG_ID_NAME    = 0x01,
    VIRTIO_INPUT_CFG_ID_SERIAL  = 0x02,
    VIRTIO_INPUT_CFG_ID_DEVIDS  = 0x03,
    VIRTIO_INPUT_CFG_PROP_BITS  = 0x10,
    VIRTIO_INPUT_CFG_EV_BITS    = 0x11,
    VIRTIO_INPUT_CFG_ABS_INFO   = 0x12,
};

struct virtio_input_absinfo
{
    rt_le32_t min;  /* Minimum value for the axis */
    rt_le32_t max;  /* Maximum value for the axis */
    rt_le32_t fuzz; /* Fuzz value that is used to filter noise from the event stream */
    rt_le32_t flat; /* Within this value will be discarded by joydev interface and reported as 0 instead */
    rt_le32_t res;  /* Resolution for the values reported for the axis */
};

struct virtio_input_devids
{
    rt_le16_t bustype;
    rt_le16_t vendor;
    rt_le16_t product;
    rt_le16_t version;
};

rt_packed(struct virtio_input_config
{
    rt_uint8_t select;
    rt_uint8_t subsel;
    rt_uint8_t size;
    rt_uint8_t reserved[5];

    union
    {
        char string[128];
        rt_uint8_t bitmap[128];
        struct virtio_input_absinfo abs;
        struct virtio_input_devids ids;
    };
});

struct virtio_input_event
{
    rt_le16_t type;
    rt_le16_t code;
    rt_le32_t value;
};

#endif /* __VIRTIO_INPUT_H__ */
