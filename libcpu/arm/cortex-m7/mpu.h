/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-25     tangzz98     the first version
 */

#ifndef __MPU_H__
#define __MPU_H__

#ifdef RT_USING_MEM_PROTECTION

#include <board.h>

#define MPU_MIN_REGION_SIZE 32U

/* MPU attributes for configuring data region permission */
/* Privileged No Access, Unprivileged No Access */
#define P_NA_U_NA       ((0x0 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk | MPU_RASR_XN_Msk)
/* Privileged Read Write, Unprivileged No Access */
#define P_RW_U_NA       ((0x1 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk | MPU_RASR_XN_Msk)
/* Privileged Read Write, Unprivileged Read Only */
#define P_RW_U_RO       ((0x2 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk | MPU_RASR_XN_Msk)
/* Privileged Read Write, Unprivileged Read Write */
#define P_RW_U_RW       ((0x3 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk | MPU_RASR_XN_Msk)
/* Privileged Read Only, Unprivileged No Access */
#define P_RO_U_NA       ((0x5 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk | MPU_RASR_XN_Msk)
/* Privileged Read Only, Unprivileged Read Only */
#define P_RO_U_RO       ((0x6 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk | MPU_RASR_XN_Msk)

/* MPU attributes for configuring code region permission */
/* Privileged Read Write Execute, Unprivileged Read Write Execute */
#define P_RWX_U_RWX     ((0x3 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write Execute, Unprivileged Read Execute */
#define P_RWX_U_RX      ((0x2 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write Execute, Unprivileged No Access */
#define P_RWX_U_NA      ((0x1 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Execute, Unprivileged Read Execute */
#define P_RX_U_RX       ((0x6 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Execute, Unprivileged No Access */
#define P_RX_U_NA       ((0x5 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)

/* MPU attributes for configuring memory type, cacheability and shareability */
#define STRONGLY_ORDERED_SHAREABLE      MPU_RASR_S_Msk
#define DEVICE_SHAREABLE                (MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_THROUGH_SHAREABLE \
        (MPU_RASR_C_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_THROUGH_NON_SHAREABLE  MPU_RASR_C_Msk
#define NORMAL_OUTER_INNER_WRITE_BACK_SHAREABLE \
        (MPU_RASR_C_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_BACK_NON_SHAREABLE \
        (MPU_RASR_C_Msk | MPU_RASR_B_Msk)
#define NORMAL_OUTER_INNER_NON_CACHEABLE_SHAREABLE \
        ((1 << MPU_RASR_TEX_Pos) | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_NON_CACHEABLE_NON_SHAREABLE \
        (1 << MPU_RASR_TEX_Pos)
#define NORMAL_OUTER_INNER_WRITE_BACK_WRITE_READ_ALLOCATE_SHAREABLE \
    ((1 << MPU_RASR_TEX_Pos) |\
     MPU_RASR_C_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_BACK_WRITE_READ_ALLOCATE_NON_SHAREABLE \
    ((1 << MPU_RASR_TEX_Pos) | MPU_RASR_C_Msk | MPU_RASR_B_Msk)
#define DEVICE_NON_SHAREABLE            (2 << MPU_RASR_TEX_Pos)
#define RESERVED                        ((2 << MPU_RASR_TEX_Pos) | MPU_RASR_B_Msk)

typedef struct
{
    rt_thread_t thread;     /* Thread that triggered exception */
    void *addr;             /* Address of faulting memory access */
    rt_mem_region_t region; /* Configurations of the memory region containing the address */
    rt_uint8_t mmfsr;       /* Content of MemManage Status Register */
} rt_mem_exception_info_t;

typedef void (*rt_hw_mpu_exception_hook_t)(rt_mem_exception_info_t *);

#define RT_ARM_MEM_ATTR(perm, type) ((rt_mem_attr_t){ (perm) | (type)})

/* Convenient macros for configuring data region attributes with default memory type */
#define RT_MEM_REGION_P_NA_U_NA RT_ARM_MEM_ATTR(P_NA_U_NA, RESERVED)
#define RT_MEM_REGION_P_RW_U_RW RT_ARM_MEM_ATTR(P_RW_U_RW, RESERVED)
#define RT_MEM_REGION_P_RW_U_RO RT_ARM_MEM_ATTR(P_RW_U_RO, RESERVED)
#define RT_MEM_REGION_P_RW_U_NA RT_ARM_MEM_ATTR(P_RW_U_NA, RESERVED)
#define RT_MEM_REGION_P_RO_U_RO RT_ARM_MEM_ATTR(P_RO_U_RO, RESERVED)
#define RT_MEM_REGION_P_RO_U_NA RT_ARM_MEM_ATTR(P_RO_U_NA, RESERVED)

/* Convenient macros for configuring code region attributes with default memory type */
#define RT_MEM_REGION_P_RWX_U_RWX   RT_ARM_MEM_ATTR(P_RWX_U_RWX, RESERVED)
#define RT_MEM_REGION_P_RWX_U_RX    RT_ARM_MEM_ATTR(P_RWX_U_RX, RESERVED)
#define RT_MEM_REGION_P_RWX_U_NA    RT_ARM_MEM_ATTR(P_RWX_U_NA, RESERVED)
#define RT_MEM_REGION_P_RX_U_RX     RT_ARM_MEM_ATTR(P_RX_U_RX, RESERVED)
#define RT_MEM_REGION_P_RX_U_NA     RT_ARM_MEM_ATTR(P_RX_U_NA, RESERVED)

rt_bool_t rt_hw_mpu_region_valid(rt_mem_region_t *region);
rt_err_t rt_hw_mpu_init(void);
rt_err_t rt_hw_mpu_add_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_delete_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_update_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_exception_set_hook(rt_hw_mpu_exception_hook_t hook);

#endif /* RT_USING_MEM_PROTECTION */

#endif /* __MPU_H__ */
