/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <cpuport.h>

#include "virtio_mmio.h"

void virtio_mmio_print_configs(uint32_t *device_base)
{
    rt_kprintf("MagicValue:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_MAGIC_VALUE));
    rt_kprintf("Version:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_VERSION));
    rt_kprintf("DeviceID:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_DEVICE_ID));
    rt_kprintf("VendorID:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_VENDOR_ID));
    rt_kprintf("DeviceFeatures0:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_HOST_FEATURES));
    rt_kprintf("DeviceFeaturesSel0:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_HOST_FEATURES_SEL));

    virtio_mmio_write32(device_base, VIRTIO_MMIO_HOST_FEATURES_SEL, 1);
    rt_hw_dsb();

    rt_kprintf("DeviceFeatures1:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_HOST_FEATURES));
    rt_kprintf("DriverFeatures:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_GUEST_FEATURES));
    rt_kprintf("DriverFeaturesSel:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_GUEST_FEATURES_SEL));
    rt_kprintf("PageSize:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_GUEST_PAGE_SIZE));

    virtio_mmio_write32(device_base, VIRTIO_MMIO_QUEUE_SEL, 0);
    rt_hw_dsb();

    rt_kprintf("QueueSel:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_SEL));
    rt_kprintf("QueueNumMax:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_NUM_MAX));
    rt_kprintf("QueueNum:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_NUM));

    virtio_mmio_write32(device_base, VIRTIO_MMIO_QUEUE_SEL, 1);
    rt_hw_dsb();

    rt_kprintf("QueueSel:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_SEL));
    rt_kprintf("QueueNumMax1:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_NUM_MAX));
    rt_kprintf("QueueNum1:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_NUM));
    rt_kprintf("QueueAlign:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_ALIGN));
    rt_kprintf("QueuePFN:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_PFN));
    rt_kprintf("QueueReady:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_READY));
    rt_kprintf("QueueNotify:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_NOTIFY));
    rt_kprintf("InterruptStatus:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_INTERRUPT_STATUS));
    rt_kprintf("InterruptACK:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_INTERRUPT_ACK));
    rt_kprintf("Status:\t\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_STATUS));
    rt_kprintf("QueueDescLow:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_DESC_LOW));
    rt_kprintf("QueueDescHigh:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_DESC_HIGH));
    rt_kprintf("QueueDriverLow:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_AVAIL_LOW));
    rt_kprintf("QueueDriverHigh:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_AVAIL_HIGH));
    rt_kprintf("QueueDeviceLow:\t\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_USED_LOW));
    rt_kprintf("QueueDeviceHigh:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_QUEUE_USED_HIGH));
    rt_kprintf("ConfigGeneration:\t 0x%x\n", virtio_mmio_read32(device_base, VIRTIO_MMIO_CONFIG_GENERATION));
    rt_kprintf("Config:\t\t\t 0x%x\n", virtio_mmio_read32(device_base,VIRTIO_MMIO_CONFIG));
}
