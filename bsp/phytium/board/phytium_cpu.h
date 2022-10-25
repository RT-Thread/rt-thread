/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: phytium_cpu.h
 * Date: 2022-10-11 14:47:20
 * LastEditTime: 2022-10-11 14:47:21
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */



#ifndef __PHYTIUM_CPU_H__
#define __PHYTIUM_CPU_H__

#include <rthw.h>
#include <rtthread.h>
#include "fparameters.h"

#define ARM_GIC_MAX_NR 1
#define MAX_HANDLERS 160
#define GIC_IRQ_START 0
#define GIC_ACK_INTID_MASK 0x000003ff


rt_uint64_t get_main_cpu_affval(void);

rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GICV3_DISTRIBUTOR_BASEADDRESS;
}

#if defined(TARGET_ARMV8_AARCH64)

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_redist_base(void)
{
    extern int phytium_cpu_id(void);

    s32 cpu_offset = 0;
#if defined(FT_GIC_REDISTRUBUTIOR_OFFSET)
    cpu_offset = FT_GIC_REDISTRUBUTIOR_OFFSET ;
#endif

#if defined(TARGET_E2000Q)
    u32 cpu_id = 0;
    cpu_id = phytium_cpu_id();

    switch (cpu_id)
    {
    case 0:
    case 1:
        cpu_offset = 2;
        break;
    case 2:
    case 3:
        cpu_offset = -2;
    default:
        break;
    }
#endif

    rt_kprintf("offset  is %x\n",  cpu_offset);
    return (GICV3_RD_BASEADDRESS + (cpu_offset) * GICV3_RD_OFFSET);
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return 0U; /* unused in gicv3 */
}

#endif


int phytium_cpu_id_mapping(int cpu_id);



#endif // !