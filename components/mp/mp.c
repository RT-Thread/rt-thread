#include "mp.h"

typedef struct {
    rt_thread_t owner;
    void *start;
    rt_size_t size;
} rt_mem_exclusive_region_t;

rt_err_t rt_mem_protection_init(rt_mem_region_t *static_regions, rt_uint8_t num_static_regions)
{
    return RT_EOK;
}

rt_err_t rt_mem_protection_add_region(rt_thread_t thread, rt_mem_region_t *region)
{
    return RT_EOK;
}

rt_err_t rt_mem_protection_delete_region(rt_thread_t thread, rt_mem_region_t *region)
{
    return RT_EOK;
}

rt_err_t rt_mem_protection_update_region(rt_thread_t thread, rt_mem_region_t *region)
{
    return RT_EOK;
}

rt_err_t rt_mem_protection_add_exclusive_region(void *start, rt_size_t size)
{
    return RT_EOK;
}

rt_err_t rt_mem_protection_delete_exclusive_region(void *start, rt_size_t size)
{
    return RT_EOK;
}
