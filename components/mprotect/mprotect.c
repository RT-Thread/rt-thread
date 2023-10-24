/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-25     tangzz98     the first version
 */

#include "mprotect.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME "MEMORY PROTECTION"
#define DBG_LEVEL DBG_ERROR
#include <rtdbg.h>

rt_mem_exclusive_region_t exclusive_regions[NUM_EXCLUSIVE_REGIONS] = {};

rt_mem_region_t *rt_mprotect_find_free_region(rt_thread_t thread)
{
    rt_uint8_t i;
    rt_mem_region_t *free_region = RT_NULL;
    if (thread->mem_regions != RT_NULL)
    {
        for (i = 0U; i < NUM_DYNAMIC_REGIONS; i++)
        {
            if (((rt_mem_region_t *)thread->mem_regions)[i].size == 0)
            {
                free_region = &(((rt_mem_region_t *)thread->mem_regions)[i]);
                break;
            }
        }
    }

    return free_region;
}

rt_mem_region_t *rt_mprotect_find_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_uint8_t i;
    rt_mem_region_t *found_region = RT_NULL;
    if (thread->mem_regions != RT_NULL)
    {
        for (i = 0U; i < NUM_DYNAMIC_REGIONS; i++)
        {
            if ((((rt_mem_region_t *)thread->mem_regions)[i].start == region->start) && (((rt_mem_region_t *)thread->mem_regions)[i].size == region->size))
            {
                found_region = &(((rt_mem_region_t *)thread->mem_regions)[i]);
                break;
            }
        }
    }

    return found_region;
}

/**
 * @brief    This function will initialize memory protection.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           When the return value is any other values, it means the initialization failed.
 */
int rt_mprotect_init(void)
{
    return (int)rt_hw_mpu_init();
}

/**
 * @brief    The function will add a memory region configuraiton for a thread.
 *
 * @param    thread is the thread that the memory region configuration will apply to.
 *
 * @param    region is the configuration for the  memory region to add.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it represents the operation failed.
 */
rt_err_t rt_mprotect_add_region(rt_thread_t thread, rt_mem_region_t *region)
{
    if (thread == RT_NULL)
    {
        thread = rt_thread_self();
    }
    if (thread->mem_regions == RT_NULL)
    {
        thread->mem_regions = RT_KERNEL_MALLOC(NUM_DYNAMIC_REGIONS * sizeof(rt_mem_region_t));
        if (thread->mem_regions == RT_NULL)
        {
            return RT_ERROR;
        }
        rt_memset(thread->mem_regions, 0U, sizeof(rt_mem_region_t ) * NUM_DYNAMIC_REGIONS);
    }
    return rt_hw_mpu_add_region(thread, region);
}

/**
 * @brief    The function will delete an existing memory region configuraiton for a thread.
 *
 * @param    thread is the thread that the memory region configuration will apply to.
 *
 * @param    region is the configuration for the memory region to delete.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it represents the operation failed.
 */
rt_err_t rt_mprotect_delete_region(rt_thread_t thread, rt_mem_region_t *region)
{
    if (thread == RT_NULL)
    {
        thread = rt_thread_self();
    }
    return rt_hw_mpu_delete_region(thread, region);
}

/**
 * @brief    The function will update an existing memory region configuraiton for a thread.
 *
 * @param    thread is the thread that the memory region configuration will apply to.
 *
 * @param    region is the new configuration for the  memory region.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it represents the operation failed.
 */
rt_err_t rt_mprotect_update_region(rt_thread_t thread, rt_mem_region_t *region)
{
    if (thread == RT_NULL)
    {
        thread = rt_thread_self();
    }
    return rt_hw_mpu_update_region(thread, region);
}

/**
 * @brief    The function will add a memory region that is only accessible by the calling thread.
 *
 * @param    start is the start address of the memory region.
 *
 * @param    size is the size of the memory region.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it represents the operation failed.
 */
rt_err_t rt_mprotect_add_exclusive_region(void *start, rt_size_t size)
{
    rt_uint8_t i;
    rt_mem_exclusive_region_t region;
    region.owner = rt_thread_self();
    region.region.start = start;
    region.region.size = size;
    region.region.attr = RT_MEM_REGION_P_NA_U_NA;
    if (rt_hw_mpu_add_region(RT_NULL, (rt_mem_region_t *)(&(region.region))) != RT_EOK)
    {
        return RT_ERROR;
    }
    rt_enter_critical();
    for (i = 0; i < NUM_EXCLUSIVE_REGIONS; i++)
    {
        if (exclusive_regions[i].owner == RT_NULL)
        {
            rt_memcpy(&(exclusive_regions[i]), &region, sizeof(rt_mem_exclusive_region_t));
            rt_exit_critical();
            return RT_EOK;
        }
    }
    rt_exit_critical();
    LOG_E("Insufficient regions");
    return RT_ERROR;
}

/**
 * @brief    The function will delete a memory region that is only accessible by the calling thread.
 *           The deleted region will be accessible by other threads.
 *
 * @param    start is the start address of the memory region.
 *
 * @param    size is the size of the memory region.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           If the return value is any other values, it represents the operation failed.
 */
rt_err_t rt_mprotect_delete_exclusive_region(void *start, rt_size_t size)
{
    rt_uint8_t i;
    rt_enter_critical();
    for (i = 0; i < NUM_EXCLUSIVE_REGIONS; i++)
    {
        if (exclusive_regions[i].owner == rt_thread_self() && exclusive_regions[i].region.start == start && exclusive_regions[i].region.size == size)
        {
            exclusive_regions[i].owner = RT_NULL;
            rt_exit_critical();
            return RT_EOK;
        }
    }
    rt_exit_critical();
    LOG_E("Region not found");
    return RT_ERROR;
}

INIT_BOARD_EXPORT(rt_mprotect_init);
