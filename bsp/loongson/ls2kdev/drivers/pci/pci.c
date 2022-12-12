/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-28     lizhirui     first version
 */

#include <rtthread.h>
#include <pci.h>

rt_uint64_t pci_get_device_map_addr(rt_uint64_t bus,rt_uint64_t device,rt_uint64_t function,rt_uint32_t index)
{

    rt_uint64_t device_addr = 0xFE00000000 | (bus << 16) | ((device & 0x1f) << 11) | ((function & 0x07) << 8);
    struct pci_header *p = (struct pci_header *)(0x9000000000000000UL | device_addr);
    return 0x9000000000000000UL | ((rt_uint64_t)(p -> BaseAddressRegister[index] & 0xFFFFFFF0));
}
