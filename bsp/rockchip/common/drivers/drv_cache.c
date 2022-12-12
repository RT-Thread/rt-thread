/**
  * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_cache.c
  * @version V0.1
  * @brief   cpu cache interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-04-01     Cliff.Chen      first implementation
  *
  ******************************************************************************
  */

/** @addtogroup RKBSP_Driver_Reference
 *  @{
 */

/** @addtogroup Cache
 *  @{
 */

/** @defgroup Cache_How_To_Use How To Use
 *  @{

The Cache driver use to keeping data coherent between cpu and device, it can be used in the following three scenarios:

- **The cpu want to read the latest data that has been modified by device**:
    - The device modify the data;
    - The cpu invalidate the data by rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE,
           addr, size);
    - The cpu read the latest data;

- **The device want to read the latest data that was modified by cpu**:
    - The cpu modify the data;
    - The device flush the data by rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr, size);
    - The device read the latest data;

- **The cpu want to execute two code section on the same memory**:
    - Loading the code A in the memory from start address of ADDR;
    - Executing the code A;
    - Loading the code B in the memory from start address of ADDR;
    - Invalidating by rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, ADDR, size);
    - Executing the code B

 @} */

#include <rthw.h>
#include "drv_cache.h"
#include "hal_base.h"

#if defined(ARCH_ARM_CORTEX_M)

#ifdef RT_USING_CMBACKTRACE
#include "cm_backtrace.h"
#endif

/********************* Private MACRO Definition ******************************/
/** @defgroup CACHE_Private_Macro Private Macro
 *  @{
 */

/** @} */  // CACHE_Private_Macro

/********************* Private Structure Definition **************************/
/** @defgroup CACHE_Private_Structure Private Structure
 *  @{
 */

/** @} */  // CACHE_Private_Structure

/********************* Private Variable Definition ***************************/
/** @defgroup CACHE_Private_Variable Private Variable
 *  @{
 */

/** @} */  // CACHE_Private_Variable

/********************* Private Function Definition ***************************/
/** @defgroup CACHE_Private_Function Private Function
 *  @{
 */

/** @} */  // CACHE_Private_Function

/********************* Public Function Definition ****************************/

/** @defgroup CACHE_Public_Functions Public Functions
 *  @{
 */

/**
 * @brief  Enable the icache of cpu.
 * @attention The cache will be enabled when board initialization, do not dynamically switch cache
 *      unless specifically required.
 */
void rt_hw_cpu_icache_enable(void)
{
    HAL_ICACHE_Enable();
}

/**
 * @brief  Disable the icache of cpu.
 * @attention The cache will be enabled when board initialization, do not dynamically switch cache
 *      unless specifically required.
 */
void rt_hw_cpu_icache_disable(void)
{
    HAL_ICACHE_Disable();
}

/**
 * @brief  Get icache status.
 * @return 0
 * @attention Not yet implemnted.
 */
rt_base_t rt_hw_cpu_icache_status(void)
{
    return 0;
}

/**
 * @brief  Icache maintain operation.
 * @param ops: RT_HW_CACHE_INVALIDATE for cache invalidate.
 * @param addr: The start address of memory you want maintain.
 * @param size: The length of memory you want maintain.
 */
void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops & RT_HW_CACHE_INVALIDATE)
    {
        HAL_ICACHE_InvalidateByRange((uint32_t)addr, size);
    }
}

/**
 * @brief  Enable the dcache of cpu.
 * @attention The cache will be enabled when board initialization, do not dynamically switch cache
 *      unless specifically required.
 */
void rt_hw_cpu_dcache_enable(void)
{
    HAL_DCACHE_Enable();
}

/**
 * @brief  Disable the dcache of cpu.
 * @attention The cache will be enabled when board initialization, do not dynamically switch cache
 *      unless specifically required.
 */
void rt_hw_cpu_dcache_disable(void)
{
    HAL_DCACHE_Disable();
}

/**
 * @brief  Get dcache status.
 * @return 0
 * @attention Not yet implemnted.
 */
rt_base_t rt_hw_cpu_dcache_status(void)
{
    return 0;
}

/**
 * @brief  Dcache maintain operation.
 * @param ops: RT_HW_CACHE_INVALIDATE for cache invalidate,
 *      RT_HW_CACHE_FLUSH for cache clean.
 * @param addr: The start address of memory you want maintain.
 * @param size: The length of memory you want maintain.
 */
void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if ((ops & RT_HW_CACHE_FLUSH) && (ops & RT_HW_CACHE_INVALIDATE))
    {
        HAL_DCACHE_CleanInvalidateByRange((uint32_t)addr, size);
    }
    else if (ops & RT_HW_CACHE_FLUSH)
    {
        HAL_DCACHE_CleanByRange((uint32_t)addr, size);
    }
    else if (ops & RT_HW_CACHE_INVALIDATE)
    {
        HAL_DCACHE_InvalidateByRange((uint32_t)addr, size);
    }
    else
    {
        RT_ASSERT(0);
    }
}

/**
 * @brief  Dump ahb error occur in icache & dcache, it called by cache interrupt.
 * @param fault_handler_lr: The value of LR register.
 * @param fault_handler_sp: The value of SP register.
 */
void cache_dump_ahb_error(uint32_t fault_handler_lr, uint32_t fault_handler_sp)
{
    uint32_t addr;

    if (HAL_ICACHE_GetInt())
    {
        addr = HAL_ICACHE_GetErrAddr();
        rt_kprintf("a ahb bus error occur in icache, addr=%p\n", (void *)addr);
        HAL_ICACHE_ClearInt();
    }

    if (HAL_DCACHE_GetInt())
    {
        addr = HAL_DCACHE_GetErrAddr();
        rt_kprintf("a ahb bus error occur in dcache, addr=%p\n", (void *)addr);
        HAL_DCACHE_ClearInt();
    }

#ifdef RT_USING_CMBACKTRACE
    cm_backtrace_fault(fault_handler_lr, fault_handler_sp);
#endif
}

extern void CACHE_IRQHandler(void);

/**
 * @brief  Enable cache interrupt and register the handler, it called by board initialization.
 * @return RT_EOK
 */
int rt_hw_cpu_cache_init(void)
{
#if defined(ICACHE) || defined(DCACHE)
    HAL_ICACHE_EnableInt();
    HAL_DCACHE_EnableInt();
#if defined(RKMCU_PISCES) || defined(RKMCU_RK2108)
    rt_hw_interrupt_install(CACHE_IRQn, (rt_isr_handler_t)CACHE_IRQHandler, RT_NULL, RT_NULL);
    rt_hw_interrupt_umask(CACHE_IRQn);
#elif defined(RKMCU_RK2206)
    rt_hw_interrupt_install(CACHE0_I_IRQn, (rt_isr_handler_t)CACHE_IRQHandler, RT_NULL, RT_NULL);
    rt_hw_interrupt_install(CACHE0_D_IRQn, (rt_isr_handler_t)CACHE_IRQHandler, RT_NULL, RT_NULL);
    rt_hw_interrupt_umask(CACHE0_I_IRQn);
    rt_hw_interrupt_umask(CACHE0_D_IRQn);
#endif
#endif
    return RT_EOK;
}

/** @} */  // CACHE_Public_Functions

#else

rt_weak void rt_hw_cpu_icache_enable(void)
{
}

rt_weak void rt_hw_cpu_icache_disable(void)
{
}

rt_weak rt_base_t rt_hw_cpu_icache_status(void)
{
    return 0;
}

rt_weak void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
}

rt_weak void rt_hw_cpu_dcache_enable(void)
{
}

rt_weak void rt_hw_cpu_dcache_disable(void)
{
}

rt_weak rt_base_t rt_hw_cpu_dcache_status(void)
{
    return 0;
}

rt_weak void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
}

#endif

/** @} */  // Cache

/** @} */  // RKBSP_Driver_Reference
