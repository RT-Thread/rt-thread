/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-11     Wangyuqiang  first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdef.h>
#include <cp15.h>
#include <hal_data.h>

#define RZ_SRAM_SIZE    1536 /* The SRAM size of the chip needs to be modified */
#define RZ_SRAM_END     (0x10000000 + RZ_SRAM_SIZE * 1024 - 1)

#ifdef __ARMCC_VERSION
extern int Image$$RAM_END$$ZI$$Base;
#define HEAP_BEGIN  ((void *)&Image$$RAM_END$$ZI$$Base)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end__;
#define HEAP_BEGIN      ((void *)&__bss_end__)
#endif

#define HEAP_END        RZ_SRAM_END

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MAX_HANDLERS BSP_VECTOR_TABLE_MAX_ENTRIES
#define GIC_IRQ_START   0
#define GIC_ACK_INTID_MASK  (0x000003FFU)
/* number of interrupts on board */
#define ARM_GIC_NR_IRQS     (448)
/* only one GIC available */
#define ARM_GIC_MAX_NR      1
/*  end defined */

#define GICV3_DISTRIBUTOR_BASE_ADDR     (0x100000)

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    rt_uint32_t gic_base;

    __get_cp(15, 1, gic_base, 15, 3, 0);
    return gic_base + GICV3_DISTRIBUTOR_BASE_ADDR;
}

#ifdef __cplusplus
}
#endif

#endif
