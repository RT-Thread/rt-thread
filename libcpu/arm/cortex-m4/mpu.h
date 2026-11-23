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

#ifndef __MPU_H__
#define __MPU_H__

#ifdef RT_USING_MEM_PROTECTION

#include <board.h>

#define MPU_MIN_REGION_SIZE 32U

/* MPU attributes for configuring data region permission.
 * These are identical to Cortex-M7 because both cores implement the
 * ARMv7-M MPU with the same AP/XN bit layout in the RASR register. */
/* Privileged No Access, Unprivileged No Access */
#define P_NA_U_NA (((0x0 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk) | MPU_RASR_XN_Msk)
/* Privileged Read Write, Unprivileged No Access */
#define P_RW_U_NA (((0x1 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk) | MPU_RASR_XN_Msk)
/* Privileged Read Write, Unprivileged Read Only */
#define P_RW_U_RO (((0x2 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk) | MPU_RASR_XN_Msk)
/* Privileged Read Write, Unprivileged Read Write */
#define P_RW_U_RW (((0x3 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk) | MPU_RASR_XN_Msk)
/* Privileged Read Only, Unprivileged No Access */
#define P_RO_U_NA (((0x5 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk) | MPU_RASR_XN_Msk)
/* Privileged Read Only, Unprivileged Read Only */
#define P_RO_U_RO (((0x6 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk) | MPU_RASR_XN_Msk)

/* MPU attributes for configuring code region permission */
/* Privileged Read Write Execute, Unprivileged Read Write Execute */
#define P_RWX_U_RWX ((0x3 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write Execute, Unprivileged Read Execute */
#define P_RWX_U_RX ((0x2 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write Execute, Unprivileged No Access */
#define P_RWX_U_NA ((0x1 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Execute, Unprivileged Read Execute */
#define P_RX_U_RX ((0x6 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Execute, Unprivileged No Access */
#define P_RX_U_NA ((0x5 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)

/* MPU attributes for configuring memory type, cacheability and shareability.
 *
 * Unlike Cortex-M7, Cortex-M4 has no L1 cache, so the cacheability bits in
 * RASR only control memory ordering (strongly-ordered / device / normal)
 * rather than an actual cache. The full write-through / write-back taxonomy
 * used on M7 is therefore not needed here and is reduced to three types. */
#define STRONGLY_ORDERED_SHAREABLE     MPU_RASR_S_Msk
#define STRONGLY_ORDERED_NON_SHAREABLE 0U
#define DEVICE_SHAREABLE               (MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define DEVICE_NON_SHAREABLE           MPU_RASR_B_Msk
#define NORMAL_NON_CACHEABLE_SHAREABLE (MPU_RASR_C_Msk | MPU_RASR_S_Msk)
#define NORMAL_NON_CACHEABLE           MPU_RASR_C_Msk
/* Sentinel marking an attribute that only carries the permission bits and
 * therefore needs the default memory type filled in later. */
#define RESERVED ((2 << MPU_RASR_TEX_Pos) | MPU_RASR_B_Msk)

typedef struct
{
    rt_thread_t thread;     /* Thread that triggered exception */
    void *addr;             /* Address of faulting memory access */
    rt_mem_region_t region; /* Configurations of the memory region containing the address */
    rt_uint8_t mmfsr;       /* Content of MemManage Status Register */
} rt_mem_exception_info_t;

typedef void (*rt_hw_mpu_exception_hook_t)(rt_mem_exception_info_t *);

#define RT_ARM_MEM_ATTR(perm, type) ((rt_mem_attr_t){ (perm) | (type) })

/* Convenient macros for configuring data region attributes with default memory type */
#define RT_MEM_REGION_P_NA_U_NA RT_ARM_MEM_ATTR(P_NA_U_NA, RESERVED)
#define RT_MEM_REGION_P_RW_U_RW RT_ARM_MEM_ATTR(P_RW_U_RW, RESERVED)
#define RT_MEM_REGION_P_RW_U_RO RT_ARM_MEM_ATTR(P_RW_U_RO, RESERVED)
#define RT_MEM_REGION_P_RW_U_NA RT_ARM_MEM_ATTR(P_RW_U_NA, RESERVED)
#define RT_MEM_REGION_P_RO_U_RO RT_ARM_MEM_ATTR(P_RO_U_RO, RESERVED)
#define RT_MEM_REGION_P_RO_U_NA RT_ARM_MEM_ATTR(P_RO_U_NA, RESERVED)

/* Convenient macros for configuring code region attributes with default memory type */
#define RT_MEM_REGION_P_RWX_U_RWX RT_ARM_MEM_ATTR(P_RWX_U_RWX, RESERVED)
#define RT_MEM_REGION_P_RWX_U_RX  RT_ARM_MEM_ATTR(P_RWX_U_RX, RESERVED)
#define RT_MEM_REGION_P_RWX_U_NA  RT_ARM_MEM_ATTR(P_RWX_U_NA, RESERVED)
#define RT_MEM_REGION_P_RX_U_RX   RT_ARM_MEM_ATTR(P_RX_U_RX, RESERVED)
#define RT_MEM_REGION_P_RX_U_NA   RT_ARM_MEM_ATTR(P_RX_U_NA, RESERVED)

rt_bool_t rt_hw_mpu_region_valid(rt_mem_region_t *region);
rt_err_t rt_hw_mpu_init(void);
rt_err_t rt_hw_mpu_add_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_delete_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_update_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_exception_set_hook(rt_hw_mpu_exception_hook_t hook);
void rt_hw_mpu_table_switch(rt_thread_t thread);

#endif /* RT_USING_MEM_PROTECTION */

#endif /* __MPU_H__ */
