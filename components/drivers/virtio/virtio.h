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

#ifdef RT_USING_SMART
#include <mmu.h>
#include <ioremap.h>
#endif

#if RT_NAME_MAX < 16
#error "Please set RT_NAME_MAX to at lest 16"
#endif

#ifdef RT_USING_VIRTIO10
#define RT_USING_VIRTIO_VERSION 0x1
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

#ifdef RT_USING_SMART
#define VIRTIO_VA2PA(vaddr)         ((rt_ubase_t)rt_kmem_v2p(vaddr))
#define VIRTIO_PA2VA(paddr)         ((rt_ubase_t)rt_ioremap((void *)paddr, ARCH_PAGE_SIZE))
#else
#define VIRTIO_VA2PA(vaddr)         ((rt_ubase_t)vaddr)
#define VIRTIO_PA2VA(paddr)         ((rt_ubase_t)paddr)
#endif /* RT_USING_SMART */
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
    /* virtio 1.2 */
    VIRTIO_DEVICE_ID_AUDIO          = 25,   /* Audio device */
    VIRTIO_DEVICE_ID_FS             = 26,   /* File system device */
    VIRTIO_DEVICE_ID_PMEM           = 27,   /* PMEM device */
    VIRTIO_DEVICE_ID_RPMB           = 28,   /* RPMB device */
    VIRTIO_DEVICE_ID_MAC80211_HWSIM = 29,   /* Mac80211 hwsim wireless simulation device */
    VIRTIO_DEVICE_ID_VIDEO_ENCODER  = 30,   /* Video encoder device */
    VIRTIO_DEVICE_ID_VIDEO_DECODER  = 31,   /* Video decoder device */
    VIRTIO_DEVICE_ID_SCMI           = 32,   /* SCMI device */
    VIRTIO_DEVICE_ID_NITRO_SEC_MOD  = 33,   /* NitroSecureModule */
    VIRTIO_DEVICE_ID_I2C_ADAPTER    = 34,   /* I2C adapter */
    VIRTIO_DEVICE_ID_WATCHDOG       = 35,   /* Watchdog */
    VIRTIO_DEVICE_ID_CAN            = 36,   /* CAN device */
    VIRTIO_DEVICE_ID_DMABUF         = 37,   /* Virtio dmabuf */
    VIRTIO_DEVICE_ID_PARAM_SERV     = 38,   /* Parameter Server */
    VIRTIO_DEVICE_ID_AUDIO_POLICY   = 39,   /* Audio policy device */
    VIRTIO_DEVICE_ID_BT             = 40,   /* Bluetooth device */
    VIRTIO_DEVICE_ID_GPIO           = 41,   /* GPIO device */
    VIRTIO_DEVICE_ID_RDMA           = 42,   /* RDMA device */

    VIRTIO_DEVICE_TYPE_SIZE
};

struct virtio_device
{
    rt_uint32_t irq;

    struct virtq *queues;
    rt_size_t queues_num;

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
void virtio_interrupt_ack(struct virtio_device *dev);
rt_bool_t virtio_has_feature(struct virtio_device *dev, rt_uint32_t feature_bit);

rt_err_t virtio_queues_alloc(struct virtio_device *dev, rt_size_t queues_num);
void virtio_queues_free(struct virtio_device *dev);
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
