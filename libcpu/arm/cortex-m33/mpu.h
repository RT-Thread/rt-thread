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
#include <mprotect.h>

#define MPU_MIN_REGION_SIZE 32U

#define RT_ARM_DEFAULT_MAIR_ATTR   (0xF0U)

/* MPU attributes for configuring data region permission*/
/* Privileged Read Write, Unprivileged No Access */
#define P_RW_U_NA_NON_SHAREABLE       (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x0 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RW_U_NA_OUTER_SHAREABLE     (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x0 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RW_U_NA_INNER_SHAREABLE     (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x0 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
/* Privileged Read Write, Unprivileged Read Write */
#define P_RW_U_RW_NON_SHAREABLE       (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x1 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RW_U_RW_OUTER_SHAREABLE     (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x1 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RW_U_RW_INNER_SHAREABLE     (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x1 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
/* Privileged Read Only, Unprivileged No Access */
#define P_RO_U_NA_NON_SHAREABLE       (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x2 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RO_U_NA_OUTER_SHAREABLE     (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x2 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RO_U_NA_INNER_SHAREABLE     (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x2 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
/* Privileged Read Only, Unprivileged Read Only */
#define P_RO_U_RO_NON_SHAREABLE       (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x3 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RO_U_RO_OUTER_SHAREABLE     (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x3 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)
#define P_RO_U_RO_INNER_SHAREABLE     (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x3 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk) | MPU_RBAR_XN_Msk)

/* MPU attributes for configuring code region permission */
#define P_RWX_U_NA_NON_SHAREABLE      (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x0 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RWX_U_NA_OUTER_SHAREABLE    (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x0 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RWX_U_NA_INNER_SHAREABLE    (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x0 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))

/* Privileged Read Write Execute, Unprivileged Read Write Execute */
#define P_RWX_U_RWX_NON_SHAREABLE     (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x1 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RWX_U_RWX_OUTER_SHAREABLE   (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x1 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RWX_U_RWX_INNER_SHAREABLE   (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x1 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))

/* Privileged Read Execute, Unprivileged No Access */
#define P_RX_U_NA_NON_SHAREABLE       (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x2 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RX_U_NA_OUTER_SHAREABLE     (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x2 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RX_U_NA_INNER_SHAREABLE     (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x2 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))

/* Privileged Read Execute, Unprivileged Read Execute */
#define P_RX_U_RX_NON_SHAREABLE       (((0x0 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x3 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RX_U_RX_OUTER_SHAREABLE     (((0x2 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x3 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))
#define P_RX_U_RX_INNER_SHAREABLE     (((0x3 << MPU_RBAR_SH_Pos) & MPU_RBAR_SH_Msk) | ((0x3 << MPU_RBAR_AP_Pos) & MPU_RBAR_AP_Msk))

typedef struct
{
    rt_thread_t thread;     /* Thread that triggered exception */
    void *addr;             /* Address of faulting memory access */
    rt_mem_region_t region; /* Configurations of the memory region containing the address */
    rt_uint8_t mmfsr;       /* Content of MemManage Status Register */
} rt_mem_exception_info_t;

typedef void (*rt_hw_mpu_exception_hook_t)(rt_mem_exception_info_t *);

#define RT_ARM_MEM_ATTR(perm, type) ((rt_mem_attr_t){ .rbar = (perm), .mair_attr = (type) })

/* Convenient macros for configuring data region attributes with default memory type */
#define RT_MEM_REGION_P_RW_U_NA     RT_ARM_MEM_ATTR(P_RW_U_NA_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
#define RT_MEM_REGION_P_RW_U_RW     RT_ARM_MEM_ATTR(P_RW_U_RW_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
#define RT_MEM_REGION_P_RO_U_NA     RT_ARM_MEM_ATTR(P_RO_U_NA_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
#define RT_MEM_REGION_P_RO_U_RO     RT_ARM_MEM_ATTR(P_RO_U_RO_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
/* ARM-V8M does not support P_NA_U_NA.
   For compatibility with rt_mprotect_add_exclusive_region,
   define RT_MEM_REGION_P_NA_U_NA as the lowest privilege supported.
*/
#define RT_MEM_REGION_P_NA_U_NA     RT_MEM_REGION_P_RO_U_NA

/* Convenient macros for configuring code region attributes with default memory type and shareability */
#define RT_MEM_REGION_P_RWX_U_NA    RT_ARM_MEM_ATTR(P_RWX_U_NA_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
#define RT_MEM_REGION_P_RWX_U_RWX   RT_ARM_MEM_ATTR(P_RWX_U_RWX_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
#define RT_MEM_REGION_P_RX_U_NA     RT_ARM_MEM_ATTR(P_RX_U_NA_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)
#define RT_MEM_REGION_P_RX_U_RX     RT_ARM_MEM_ATTR(P_RX_U_RX_NON_SHAREABLE, RT_ARM_DEFAULT_MAIR_ATTR)

rt_bool_t rt_hw_mpu_region_valid(rt_mem_region_t *region);
rt_err_t rt_hw_mpu_init(void);
rt_err_t rt_hw_mpu_add_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_delete_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_update_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_hw_mpu_exception_set_hook(rt_hw_mpu_exception_hook_t hook);

#endif /* RT_USING_MEM_PROTECTION */

#endif /* __MPU_H__ */
