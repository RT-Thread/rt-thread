#include <rtdef.h>
#include <mp.h>
#include "mpport.h"

rt_err_t rt_hw_mp_init(rt_mem_region_t *static_regions, rt_uint8_t num_regions)
{
    return RT_EOK;
}

rt_err_t rt_hw_mp_add_region(rt_thread_t thread, rt_mem_region_t *region)
{
    return RT_EOK;
}

rt_err_t rt_hw_mp_delete_region(rt_thread_t thread, rt_mem_region_t *region)
{
    return RT_EOK;
}

rt_err_t rt_hw_mp_update_region(rt_thread_t thread, rt_mem_region_t *region)
{
    return RT_EOK;
}

rt_err_t rt_hw_mp_exception_set_hook(rt_mem_exception_info_t *info)
{
    return RT_EOK;
}

void rt_hw_mp_table_switch(rt_thread_t thread)
{
    
}
