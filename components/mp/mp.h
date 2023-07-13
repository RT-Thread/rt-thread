#ifndef __MP_H__
#define __MP_H__

#include <rtdef.h>
#include <mpport.h>

#define ADDR_IN_REGION(addr, region) (((rt_size_t)(addr) >= (rt_size_t)((region)->start)) && ((rt_size_t)(addr) < (rt_size_t)((region)->start) + (rt_size_t)((region)->start) + (region)->size))

typedef struct {
    rt_mem_region_t region;
    rt_thread_t owner;
} rt_mem_exclusive_region_t;

rt_err_t rt_mem_protection_init(rt_mem_region_t *static_regions, rt_uint8_t num_static_regions);
rt_err_t rt_mem_protection_add_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_mem_protection_delete_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_mem_protection_update_region(rt_thread_t thread, rt_mem_region_t *region);
rt_err_t rt_mpu_get_info(rt_thread_t thread, rt_uint32_t type, void *arg);
/* owner of region is calling thread */
rt_err_t rt_mem_protection_add_exclusive_region(void *start, rt_size_t size);
rt_err_t rt_mem_protection_delete_exclusive_region(void *start, rt_size_t size);

#endif /* __MP_H__ */
