/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_INPUT_H__
#define __VIRTIO_INPUT_H__

#include <rtdef.h>

#include <virtio.h>
#include <virtio_input_event_codes.h>

#define VIRTIO_INPUT_QUEUE_EVENT        0
#define VIRTIO_INPUT_QUEUE_STATUS       1
#define VIRTIO_INPUT_EVENT_QUEUE_SIZE   64
#define VIRTIO_INPUT_STATUS_QUEUE_SIZE  8
#define VIRTIO_INPUT_QUEUE_MAX_SIZE     (VIRTIO_INPUT_EVENT_QUEUE_SIZE > VIRTIO_INPUT_STATUS_QUEUE_SIZE ? \
        VIRTIO_INPUT_EVENT_QUEUE_SIZE : VIRTIO_INPUT_STATUS_QUEUE_SIZE)

#define VIRTIO_INPUT_ABS_AXIS_X         0
#define VIRTIO_INPUT_ABS_AXIS_Y         1

enum virtio_input_type
{
    VIRTIO_INPUT_TYPE_KEYBOARD,
    VIRTIO_INPUT_TYPE_MOUSE,
    VIRTIO_INPUT_TYPE_TABLET,

    VIRTIO_INPUT_TYPE_SIZE,
};

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
    rt_uint32_t min;    /* Minimum value for the axis */
    rt_uint32_t max;    /* Maximum value for the axis */
    rt_uint32_t fuzz;   /* Fuzz value that is used to filter noise from the event stream */
    rt_uint32_t flat;   /* Within this value will be discarded by joydev interface and reported as 0 instead */
    rt_uint32_t res;    /* Resolution for the values reported for the axis */
};

struct virtio_input_devids
{
    rt_uint16_t bustype;
    rt_uint16_t vendor;
    rt_uint16_t product;
    rt_uint16_t version;
};

struct virtio_input_config
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
} __attribute__((packed));

struct virtio_input_event
{
    rt_uint16_t type;
    rt_uint16_t code;
    rt_uint32_t value;
};

#ifdef ARCH_CPU_64BIT
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define DIV_ROUND_UP(n, d)  (((n) + (d) - 1) / (d))

#define BITS_PER_BYTE       8
#define BITS_PER_TYPE(type) (sizeof(type) * BITS_PER_BYTE)
#define BITS_TO_BYTES(nr)   DIV_ROUND_UP(nr, BITS_PER_TYPE(char))
#define BITS_TO_LONGS(nr)   DIV_ROUND_UP(nr, BITS_PER_TYPE(long))

struct virtio_input_device
{
    struct rt_device parent;

    struct virtio_device virtio_dev;

    rt_ubase_t ev_bit[BITS_TO_LONGS(EV_CNT)];
    rt_ubase_t key_bit[BITS_TO_LONGS(KEY_CNT)];
    rt_ubase_t rel_bit[BITS_TO_LONGS(REL_CNT)];
    rt_ubase_t abs_bit[BITS_TO_LONGS(ABS_CNT)];

    enum virtio_input_type type;
    struct virtio_input_config *config;

    /* Broadcast events */
    struct rt_mutex rw_mutex;
    void (*bsct_handler)(struct virtio_input_event event);
    struct virtio_input_event bcst_events[VIRTIO_INPUT_EVENT_QUEUE_SIZE];

    /* Receive events */
    struct virtio_input_event recv_events[VIRTIO_INPUT_EVENT_QUEUE_SIZE];

    /* Transmit status */
    struct virtio_input_event xmit_events[VIRTIO_INPUT_STATUS_QUEUE_SIZE];
};

enum
{
    VIRTIO_DEVICE_CTRL_INPUT_GET_TYPE           = 0x20,
    VIRTIO_DEVICE_CTRL_INPUT_BIND_BSCT_HANDLER,
    VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_X_INFO,
    VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_Y_INFO,
    VIRTIO_DEVICE_CTRL_INPUT_SET_STATUS,

    VIRTIO_DEVICE_CTRL_INPUT_GET_EV_BIT,
    VIRTIO_DEVICE_CTRL_INPUT_GET_KEY_BIT,
    VIRTIO_DEVICE_CTRL_INPUT_GET_REL_BIT,
    VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_BIT,
};

rt_err_t rt_virtio_input_init(rt_ubase_t *mmio_base, rt_uint32_t irq);

#endif /* __VIRTIO_INPUT_H__ */
