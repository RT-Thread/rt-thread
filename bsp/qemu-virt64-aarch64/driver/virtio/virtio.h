/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 * 2021-11-11     GuEe-GUI     modify to virtio common interface
 */

#ifndef __VIRTIO_H__
#define __VIRTIO_H__

#include <rthw.h>
#include <rtdef.h>

#ifndef RT_USING_VIRTIO_VERSION
#define RT_USING_VIRTIO_VERSION 0x1
#endif

#ifndef RT_USING_VIRTIO_QUEUE_MAX_NR
#define RT_USING_VIRTIO_QUEUE_MAX_NR 4
#endif

#include <virtio_mmio.h>
#include <virtio_queue.h>

#define VIRTIO_MAGIC_VALUE          0x74726976 /* "virt" */

#define VIRTIO_STATUS_ACKNOWLEDGE   (1 << 0)
#define VIRTIO_STATUS_DRIVER        (1 << 1)
#define VIRTIO_STATUS_DRIVER_OK     (1 << 2)
#define VIRTIO_STATUS_FEATURES_OK   (1 << 3)
#define VIRTIO_STATUS_NEEDS_RESET   (1 << 6)
#define VIRTIO_STATUS_FAILED        (1 << 7)

#define VIRTIO_F_NOTIFY_ON_EMPTY    24
#define VIRTIO_F_ANY_LAYOUT         27
#define VIRTIO_F_RING_INDIRECT_DESC 28
#define VIRTIO_F_RING_EVENT_IDX     29
#define VIRTIO_F_VERSION_1          32
#define VIRTIO_F_RING_PACKED        34

#define VIRTIO_VA2PA(vaddr)         ((rt_ubase_t)vaddr)
#define VIRTIO_PAGE_SHIFT           12
#define VIRTIO_PAGE_SIZE            (1 << VIRTIO_PAGE_SHIFT)
#define VIRTIO_PAGE_ALIGN(addr)     (RT_ALIGN(addr, VIRTIO_PAGE_SIZE))

enum
{
    /* virtio 1.0 */
    VIRTIO_DEVICE_ID_INVALID        = 0,    /* Invalid device */
    VIRTIO_DEVICE_ID_NET            = 1,    /* Net */
    VIRTIO_DEVICE_ID_BLOCK          = 2,    /* Block */
    VIRTIO_DEVICE_ID_CONSOLE        = 3,    /* Console */
    VIRTIO_DEVICE_ID_RNG            = 4,    /* Rng */
    VIRTIO_DEVICE_ID_BALLOON        = 5,    /* Balloon */
    VIRTIO_DEVICE_ID_IOMEM          = 6,    /* IO memory */
    VIRTIO_DEVICE_ID_RPMSG          = 7,    /* Remote processor messaging */
    VIRTIO_DEVICE_ID_SCSI           = 8,    /* SCSI */
    VIRTIO_DEVICE_ID_9P             = 9,    /* 9p console */
    VIRTIO_DEVICE_ID_MAC80211_WLAN  = 10,   /* Mac80211 wlan */
    VIRTIO_DEVICE_ID_RPROC_SERIAL   = 11,   /* Remoteproc serial link */
    VIRTIO_DEVICE_ID_CAIF           = 12,   /* CAIF */
    VIRTIO_DEVICE_ID_MEM_BALLOON    = 13,   /* Memory balloon */
    VIRTIO_DEVICE_ID_GPU            = 16,   /* GPU */
    VIRTIO_DEVICE_ID_TIME           = 17,   /* Timer/clock device */
    VIRTIO_DEVICE_ID_INPUT          = 18,   /* Input */
    /* virtio 1.1 */
    VIRTIO_DEVICE_ID_SOCKET         = 19,   /* Socket device */
    VIRTIO_DEVICE_ID_CRYPTO         = 20,   /* Crypto device */
    VIRTIO_DEVICE_ID_SIG_DIS_MOD    = 21,   /* Signal Distribution Module */
    VIRTIO_DEVICE_ID_PSTORE         = 22,   /* Pstore device */
    VIRTIO_DEVICE_ID_IOMMU          = 23,   /* IOMMU device */
    VIRTIO_DEVICE_ID_MEM            = 24,   /* Memory device */

    VIRTIO_DEVICE_TYPE_SIZE
};

struct virtio_device
{
    rt_uint32_t irq;

    struct virtq queues[RT_USING_VIRTIO_QUEUE_MAX_NR];
    union
    {
        rt_ubase_t *mmio_base;
        struct virtio_mmio_config *mmio_config;
    };

#ifdef RT_USING_SMP
    struct rt_spinlock spinlock;
#endif

    void *priv;
};

typedef rt_err_t (*virtio_device_init_handler)(rt_ubase_t *mmio_base, rt_uint32_t irq);

void virtio_reset_device(struct virtio_device *dev);
void virtio_status_acknowledge_driver(struct virtio_device *dev);
void virtio_status_driver_ok(struct virtio_device *dev);
void virtio_interrupt_ack(struct virtio_device *dev, rt_uint32_t ack);

rt_err_t virtio_queue_init(struct virtio_device *dev, rt_uint32_t queue_index, rt_size_t ring_size);
void virtio_queue_destroy(struct virtio_device *dev, rt_uint32_t queue_index);
void virtio_queue_notify(struct virtio_device *dev, rt_uint32_t queue_index);

void virtio_submit_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index);

rt_uint16_t virtio_alloc_desc(struct virtio_device *dev, rt_uint32_t queue_index);
void virtio_free_desc(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index);
rt_err_t virtio_alloc_desc_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_size_t count,
        rt_uint16_t *indexs);
void virtio_free_desc_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index);
void virtio_fill_desc(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index,
        rt_uint64_t addr, rt_uint32_t len, rt_uint16_t flags, rt_uint16_t next);

#endif /* __VIRTIO_H__ */
