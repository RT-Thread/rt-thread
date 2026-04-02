/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 * 2021-11-11     GuEe-GUI     modify to virtio common interface
 */

#ifndef __VIRTIO_MMIO_H__
#define __VIRTIO_MMIO_H__

#include <rtdef.h>

struct virtio_mmio_config
{
    rt_uint32_t magic;                  /* [0x00]<RO> Magic value */
    rt_uint32_t version;                /* [0x04]<RO> Device version number */
    rt_uint32_t device_id;              /* [0x08]<RO> Virtio Subsystem Device ID */
    rt_uint32_t vendor_id;              /* [0x0c]<RO> Virtio Subsystem Vendor ID */
    rt_uint32_t device_features;        /* [0x10]<RO> Flags representing features the device supports */
    rt_uint32_t device_features_sel;    /* [0x14]<WO> Device (host) features word selection. */
    rt_uint32_t res0[2];                /* [0x18] */
    rt_uint32_t driver_features;        /* [0x20]<WO> Device features understood and activated by the driver */
    rt_uint32_t driver_features_sel;    /* [0x24]<WO> Activated (guest) features word selection */
    rt_uint32_t guest_page_size;        /* [0x28]<WO> Guest page size, this value should be a power of 2 */
    rt_uint32_t res1[1];                /* [0x2c] */
    rt_uint32_t queue_sel;              /* [0x30]<WO> Virtual queue index */
    rt_uint32_t queue_num_max;          /* [0x34]<RO> Maximum virtual queue size */
    rt_uint32_t queue_num;              /* [0x38]<WO> Virtual queue size */
    rt_uint32_t queue_align;            /* [0x3c]<WO> Used Ring alignment in the virtual queue */
    rt_uint32_t queue_pfn;              /* [0x40]<RW> Guest physical page number of the virtual queue */
    rt_uint32_t queue_ready;            /* [0x44]<RW> Virtual queue ready bit */
    rt_uint32_t res2[2];                /* [0x48] */
    rt_uint32_t queue_notify;           /* [0x50]<WO> Queue notifier */
    rt_uint32_t res3[3];                /* [0x54] */
    rt_uint32_t interrupt_status;       /* [0x60]<RO> Interrupt status */
    rt_uint32_t interrupt_ack;          /* [0x64]<WO> Interrupt acknowledge */
    rt_uint32_t res4[2];                /* [0x68] */
    rt_uint32_t status;                 /* [0x70]<RW> Device status */
    rt_uint32_t res5[3];                /* [0x74] */
    rt_uint32_t queue_desc_low;         /* [0x80]<WO> Virtual queue’s Descriptor Area 64 bit long physical address */
    rt_uint32_t queue_desc_high;        /* [0x84]<WO> */
    rt_uint32_t res6[2];                /* [0x88] */
    rt_uint32_t queue_driver_low;       /* [0x90]<WO> Virtual queue’s Driver Area 64 bit long physical address */
    rt_uint32_t queue_driver_high;      /* [0x94]<WO> */
    rt_uint32_t res7[2];                /* [0x98] */
    rt_uint32_t queue_device_low;       /* [0xa0]<WO> Virtual queue’s Device Area 64 bit long physical address */
    rt_uint32_t queue_device_high;      /* [0xa4]<WO> */
    rt_uint32_t res8[21];               /* [0xa8] */
    rt_uint32_t config_generation;      /* [0xfc]<RO> Configuration atomicity value */
    rt_uint32_t config[];               /* [0x100+]<RO> Configuration space */

/*
 * According to the compiler's optimization ways, we should force compiler not
 * to optimization here, but it will cause some compilers generate memory access
 * instructions fail. So we allow user to choose a toggle of optimize here.
 */
#ifdef RT_USING_VIRTIO_MMIO_ALIGN
} __attribute__((packed));
#else
};
#endif

#endif /* __VIRTIO_MMIO_H__ */
