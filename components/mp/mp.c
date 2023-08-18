#include "mp.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME "MEMORY PROTECTION"
#define DBG_LEVEL DBG_ERROR
#include <rtdbg.h>

rt_mem_exclusive_region_t exclusive_regions[NUM_EXCLUSIVE_REGIONS] = {};

rt_mem_region_t *rt_mem_protection_find_free_region(rt_thread_t thread)
{
    rt_uint8_t i;
    rt_mem_region_t *free_region = RT_NULL;
    for (i = 0; i < NUM_DYNAMIC_REGIONS; i++)
    {
        if (thread->mem_regions[i].size == 0)
        {
            free_region = &(thread->mem_regions[i]);
            break;
        }
    }
    
    return free_region;
}

rt_mem_region_t *rt_mem_protection_find_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_uint8_t i;
    rt_mem_region_t *found_region = RT_NULL;
    for (i = 0; i < NUM_DYNAMIC_REGIONS; i++)
    {
        if ((thread->mem_regions[i].start == region->start) && (thread->mem_regions[i].size == region->size))
        {
            found_region = &(thread->mem_regions[i]);
            break;
        }
    }
    
    return found_region;
}

int rt_mem_protection_init()
{
    return (int)rt_hw_mp_init();
}

rt_err_t rt_mem_protection_add_region(rt_thread_t thread, rt_mem_region_t *region)
{
    if (thread == RT_NULL)
    {
        return rt_hw_mp_add_region(rt_thread_self(), region);
    }
    else
    {
        return rt_hw_mp_add_region(thread, region);
    }
}

rt_err_t rt_mem_protection_delete_region(rt_thread_t thread, rt_mem_region_t *region)
{
    if (thread == RT_NULL)
    {
        return rt_hw_mp_delete_region(rt_thread_self(), region);
    }
    else
    {
        return rt_hw_mp_delete_region(thread, region);
    }
}

rt_err_t rt_mem_protection_update_region(rt_thread_t thread, rt_mem_region_t *region)
{
    if (thread == RT_NULL)
    {
        return rt_hw_mp_update_region(rt_thread_self(), region);
    }
    else
    {
        return rt_hw_mp_update_region(thread, region);
    }
}

rt_err_t rt_mem_protection_add_exclusive_region(void *start, rt_size_t size)
{
    rt_uint8_t i;
    rt_mem_exclusive_region_t region;
    region.owner = rt_thread_self();
    region.region.start = start;
    region.region.size = size;
    region.region.attr = RT_MEM_REGION_P_NA_U_NA;
    if (rt_hw_mp_add_region(RT_NULL, (rt_mem_region_t *)(&(region.region))) != RT_EOK)
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

rt_err_t rt_mem_protection_delete_exclusive_region(void *start, rt_size_t size)
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

INIT_BOARD_EXPORT(rt_mem_protection_init);
