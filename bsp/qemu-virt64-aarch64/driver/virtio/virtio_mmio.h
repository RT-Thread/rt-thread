/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 */

#ifndef VIRTIO_MMIO_H
#define VIRTIO_MMIO_H

#include <stdint.h>
#include <stddef.h>

#define VIRTIO_MMIO_MAGIC               0x74726976
#define VIRTIO_MMIO_VENDOR              0x554d4551

#define VIRTIO_MMIO_MAGIC_VALUE         0x000   /* VIRTIO_MMIO_MAGIC */
#define VIRTIO_MMIO_VERSION             0x004   /* version: 1 is legacy */
#define VIRTIO_MMIO_DEVICE_ID           0x008   /* device type: 1 is net, 2 is disk */
#define VIRTIO_MMIO_VENDOR_ID           0x00c   /* VIRTIO_MMIO_VENDOR */
#define VIRTIO_MMIO_DEVICE_FEATURES     0x010
#define VIRTIO_MMIO_DRIVER_FEATURES     0x020
#define VIRTIO_MMIO_HOST_FEATURES       0x010
#define VIRTIO_MMIO_HOST_FEATURES_SEL   0x014
#define VIRTIO_MMIO_GUEST_FEATURES      0x020
#define VIRTIO_MMIO_GUEST_FEATURES_SEL  0x024
#define VIRTIO_MMIO_GUEST_PAGE_SIZE     0x028   /* version 1 only */
#define VIRTIO_MMIO_QUEUE_SEL           0x030
#define VIRTIO_MMIO_QUEUE_NUM_MAX       0x034
#define VIRTIO_MMIO_QUEUE_NUM           0x038
#define VIRTIO_MMIO_QUEUE_ALIGN         0x03c   /* version 1 only */
#define VIRTIO_MMIO_QUEUE_PFN           0x040   /* version 1 only */
#define VIRTIO_MMIO_QUEUE_READY         0x044   /* requires version 2 */
#define VIRTIO_MMIO_QUEUE_NOTIFY        0x050
#define VIRTIO_MMIO_INTERRUPT_STATUS    0x060
#define VIRTIO_MMIO_INTERRUPT_ACK       0x064
#define VIRTIO_MMIO_STATUS              0x070
#define VIRTIO_MMIO_QUEUE_DESC_LOW      0x080   /* requires version 2 */
#define VIRTIO_MMIO_QUEUE_DESC_HIGH     0x084   /* requires version 2 */
#define VIRTIO_MMIO_QUEUE_AVAIL_LOW     0x090   /* requires version 2 */
#define VIRTIO_MMIO_QUEUE_AVAIL_HIGH    0x094   /* requires version 2 */
#define VIRTIO_MMIO_QUEUE_USED_LOW      0x0a0   /* requires version 2 */
#define VIRTIO_MMIO_QUEUE_USED_HIGH     0x0a4   /* requires version 2 */
#define VIRTIO_MMIO_CONFIG_GENERATION   0x100   /* requires version 2 */
#define VIRTIO_MMIO_CONFIG              0x100
#define VIRTIO_MMIO_INT_VRING           (1 << 0)
#define VIRTIO_MMIO_INT_CONFIG          (1 << 1)
#define VIRTIO_MMIO_VRING_ALIGN         4096

static inline uint32_t virtio_mmio_read32(uint32_t *base, size_t offset)
{
    return *((volatile uint32_t*) (((uintptr_t) base) + offset));
}

static inline uint16_t virtio_mmio_read16(uint32_t *base, size_t offset)
{
    return *((volatile uint16_t*) (((uintptr_t) base) + offset));
}

static inline uint8_t virtio_mmio_read8(uint32_t *base, size_t offset)
{
    return *((volatile uint8_t*) (((uintptr_t) base) + offset));
}

static inline void virtio_mmio_write32(uint32_t *base, size_t offset, uint32_t val)
{
    *((volatile uint32_t*) (((uintptr_t) base) + offset)) = val;
}

void virtio_mmio_print_configs(uint32_t *device_base);

#endif /* VIRTIO_MMIO_H */
