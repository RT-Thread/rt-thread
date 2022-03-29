/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#include <rtthread.h>

#include <virtio.h>
#ifdef BSP_USING_VIRTIO_BLK
#include <virtio_blk.h>
#endif

#include <board.h>

static virtio_device_init_handler virtio_device_init_handlers[] =
{
#ifdef BSP_USING_VIRTIO_BLK
    [VIRTIO_DEVICE_ID_BLOCK]    = rt_virtio_blk_init,
#endif
};

int rt_virtio_devices_init(void)
{
    int i;
    rt_uint32_t irq = VIRTIO_IRQ_BASE;
    rt_ubase_t mmio_base = VIRTIO_MMIO_BASE;
    struct virtio_mmio_config *mmio_config;
    virtio_device_init_handler init_handler;

    if (sizeof(virtio_device_init_handlers) == 0)
    {
        /* The compiler will optimize the codes after here. */
        return 0;
    }

    for (i = 0; i < VIRTIO_MAX_NR; ++i, ++irq, mmio_base += VIRTIO_MMIO_SIZE)
    {
        mmio_config = (struct virtio_mmio_config *)mmio_base;

        if (mmio_config->magic != VIRTIO_MAGIC_VALUE ||
            mmio_config->version != RT_USING_VIRTIO_VERSION ||
            mmio_config->vendor_id != VIRTIO_VENDOR_ID)
        {
            continue;
        }

        init_handler = virtio_device_init_handlers[mmio_config->device_id];

        if (init_handler != RT_NULL)
        {
            init_handler((rt_ubase_t *)mmio_base, irq);
        }
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_virtio_devices_init);
