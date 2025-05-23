/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#ifndef __PIC_RISCV_IMSIC_H__
#define __PIC_RISCV_IMSIC_H__

#include <drivers/ofw.h>
#include <drivers/misc.h>
#include <drivers/core/dm.h>

#define IMSIC_MMIO_PAGE_SHIFT   12
#define IMSIC_MMIO_PAGE_SZ      RT_BIT(IMSIC_MMIO_PAGE_SHIFT)
#define IMSIC_MMIO_PAGE_LE      0x00
#define IMSIC_MMIO_PAGE_BE      0x04

#define IMSIC_MIN_ID            63
#define IMSIC_MAX_ID            2048

#define IMSIC_EIDELIVERY        0x70

#define IMSIC_EITHRESHOLD       0x72

#define IMSIC_EIP0              0x80
#define IMSIC_EIP63             0xbf
#define IMSIC_EIPx_BITS         32

#define IMSIC_EIE0              0xc0
#define IMSIC_EIE63             0xff
#define IMSIC_EIEx_BITS         32

#define IMSIC_FIRST             IMSIC_EIDELIVERY
#define IMSIC_LAST              IMSIC_EIE63

#define IMSIC_MMIO_SETIPNUM_LE  0x00
#define IMSIC_MMIO_SETIPNUM_BE  0x04

struct imsic_local_config
{
    void *msi;
    rt_uint64_t msi_phy;
};

struct imsic_global_config
{
    /*
     * MSI Target Address Scheme
     *
     * XLEN-1                                                12    0
     * |                                                     |     |
     * -------------------------------------------------------------
     * |xxxxxx|Group Index|xxxxxxxxxxx|HART Index|Guest Index|  0  |
     * -------------------------------------------------------------
     */

    /* Bits representing Guest index, HART index, and Group index */
    rt_uint32_t guest_index_bits;
    rt_uint32_t hart_index_bits;
    rt_uint32_t group_index_bits;
    rt_uint32_t group_index_shift;

    /* Global base address matching all target MSI addresses */
    rt_ubase_t base_addr;

    /* Number of interrupt identities */
    rt_uint32_t nr_ids;

    /* Number of guest interrupt identities */
    rt_uint32_t nr_guest_ids;

    /* IMSIC addresses */
    struct imsic_local_config local[RT_CPUS_NR];
};

const struct imsic_global_config *imsic_global_config_read(struct rt_ofw_node *np);
rt_err_t imsic_ofw_probe(struct rt_ofw_node *np,
        struct rt_ofw_node *ic_np, const struct rt_ofw_node_id *ic_id);

#endif /* __PIC_RISCV_IMSIC_H__ */
