#ifndef __MPPORTTYPE_H__
#define __MPPORTTYPE_H__

#ifdef RT_USING_MEM_PROTECTION

#ifdef RT_USING_HW_STACK_GUARD
#define NUM_DYNAMIC_REGIONS (2 + NUM_CONFIGURABLE_REGIONS)
#else
#define NUM_DYNAMIC_REGIONS (NUM_CONFIGURABLE_REGIONS)
#endif

typedef struct {
    rt_uint32_t rbar;
    union {
        rt_uint32_t mair_attr;
        rt_uint32_t rlar;
    };
} rt_mem_attr_t;

#endif /* RT_USING_MEM_PROTECTION */

#endif /* __MPPORTTYPE_H__ */
