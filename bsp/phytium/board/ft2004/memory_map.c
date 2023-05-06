/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-27     huanghe      first version
 *
 */

#include "rtconfig.h"
#include <board.h>
#include <mmu.h>

/* mmu config */
struct mem_desc platform_mem_desc[] =
{
    {
        0x80000000,
        0xFFFFFFFF,
        0x80000000,
        DDR_MEM
    },
    {
        0, //< QSPI
        0x1FFFFFFF,
        0,
        DEVICE_MEM
    },
    {
        0x20000000, //<! LPC
        0x27FFFFFF,
        0x20000000,
        DEVICE_MEM
    },
    {
        FT_DEV_BASE_ADDR, //<! Device register
        FT_DEV_END_ADDR,
        FT_DEV_BASE_ADDR,
        DEVICE_MEM
    },
    {
        0x30000000, //<! debug
        0x39FFFFFF,
        0x30000000,
        DEVICE_MEM
    },
    {
        0x3A000000, //<! Internal register space in the on-chip network
        0x3AFFFFFF,
        0x3A000000,
        DEVICE_MEM
    },
    {
        FT_PCI_CONFIG_BASEADDR,
        FT_PCI_CONFIG_BASEADDR + FT_PCI_CONFIG_REG_LENGTH,
        FT_PCI_CONFIG_BASEADDR,
        DEVICE_MEM
    },
    {
        FT_PCI_IO_CONFIG_BASEADDR,
        FT_PCI_IO_CONFIG_BASEADDR + FT_PCI_IO_CONFIG_REG_LENGTH,
        FT_PCI_IO_CONFIG_BASEADDR,
        DEVICE_MEM
    },
    {
        FT_PCI_MEM32_BASEADDR,
        FT_PCI_MEM32_BASEADDR + FT_PCI_MEM32_REG_LENGTH,
        FT_PCI_MEM32_BASEADDR,
        DEVICE_MEM
    }
#if defined(TARGET_ARMV8_AARCH64)
    {
        0x1000000000,
        0x1000000000 + 0x1000000000,
        0x1000000000,
        DEVICE_MEM
    },
    {
        0x2000000000,
        0x2000000000 + 0x2000000000,
        0x2000000000,
        NORMAL_MEM
    },
#endif
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);
