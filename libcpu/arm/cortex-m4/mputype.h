/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-25     tangzz98     the first version
 * 2026-08-23     RT-Thread    add cortex-m4 support
 */

#ifndef __MPUTYPE_H__
#define __MPUTYPE_H__

#ifdef RT_USING_MEM_PROTECTION

#ifdef RT_USING_HW_STACK_GUARD
#define NUM_DYNAMIC_REGIONS (2 + NUM_CONFIGURABLE_REGIONS)
#else
#define NUM_DYNAMIC_REGIONS (NUM_CONFIGURABLE_REGIONS)
#endif

/* Cortex-M4 follows ARMv7-M, whose MPU programs the full attribute set
 * (access permission + memory type) through the single RASR register,
 * just like Cortex-M7. */
typedef struct
{
    rt_uint32_t rasr;
} rt_mem_attr_t;

#endif /* RT_USING_MEM_PROTECTION */

#endif /* __MPUTYPE_H__ */
