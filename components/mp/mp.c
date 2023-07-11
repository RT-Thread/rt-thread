#include "mp.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME "MEMORY PROTECTION"
#define DBG_LEVEL DBG_ERROR
#include <rtdbg.h>
typedef struct {
    rt_thread_t owner;
    void *start;
    rt_size_t size;
} rt_mem_exclusive_region_t;

static rt_mem_exclusive_region_t exclusive_regions[NUM_EXCLUSIVE_REGIONS] = {};

static rt_mem_region_t *rt_mem_protection_find_free_region(rt_thread_t thread)
{
    rt_uint8_t i;
    rt_mem_region_t *free_region = RT_NULL;
    for (i = 0; i < NUM_DYNAMIC_REGIONS; ++i)
    {
        if (thread->mem_regions[i].size == 0)
        {
            free_region = &(thread->mem_regions[i]);
            break;
        }
    }
    
    return free_region;
}

static rt_mem_region_t *rt_mem_protection_find_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_uint8_t i;
    rt_mem_region_t *found_region = RT_NULL;
    for (i = 0; i < NUM_DYNAMIC_REGIONS; ++i)
    {
        if ((thread->mem_regions[i].start == region->start) && (thread->mem_regions[i].size == region->size))
        {
            found_region = &(thread->mem_regions[i]);
            break;
        }
    }
    
    return found_region;
}

rt_err_t rt_mem_protection_init(rt_mem_region_t *static_regions, rt_uint8_t num_static_regions)
{
    return rt_hw_mp_init(static_regions, num_static_regions);
}

rt_err_t rt_mem_protection_add_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_mem_region_t *free_region = rt_mem_protection_find_free_region(thread);
    if (free_region == RT_NULL)
    {
        LOG_E("Insufficient regions");
        return RT_ERROR;
    }
    rt_memcpy(free_region, region, sizeof(rt_mem_region_t));
    if (rt_hw_mp_add_region(thread, free_region) != RT_EOK)
    {
        rt_memset(free_region, 0, sizeof(rt_mem_region_t));
        return RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t rt_mem_protection_delete_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_mem_region_t *found_region = rt_mem_protection_find_region(thread, region);
    if (found_region == RT_NULL)
    {
        LOG_E("Region not found");
        return RT_ERROR;
    }
    rt_hw_mp_delete_region(thread, found_region);
    rt_memset(found_region, 0, sizeof(rt_mem_region_t));
}

rt_err_t rt_mem_protection_update_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_mem_region_t *old_region = rt_mem_protection_find_region(thread, region);
    if (old_region == RT_NULL)
    {
        LOG_E("Region not found");
        return RT_ERROR;
    }
    if (rt_hw_mp_update_region(thread, old_region, region) != RT_EOK)
    {
        return RT_ERROR;
    }
    rt_memcpy(old_region, region, sizeof(rt_mem_region_t));
}

rt_err_t rt_mem_protection_add_exclusive_region(void *start, rt_size_t size)
{
    return RT_EOK;
}

rt_err_t rt_mem_protection_delete_exclusive_region(void *start, rt_size_t size)
{
    return RT_EOK;
}
