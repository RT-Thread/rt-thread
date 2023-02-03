#ifndef __CPU_OPS_COMMON_H__
#define __CPU_OPS_COMMON_H__

#include <rthw.h>
#include <rtthread.h>
#include <mmu.h>
#include "entry_point.h"

static inline rt_uint64_t get_secondary_entry_pa(void)
{
    rt_uint64_t secondary_entry_pa = (rt_uint64_t)rt_kmem_v2p(_secondary_cpu_entry);

    if (!secondary_entry_pa)
    {
        LOG_E("Failed to translate 'secondary_entry_pa' to physical address");
        return 0;
    }
    return secondary_entry_pa;
}

#endif /* __CPU_OPS_COMMON_H__ */