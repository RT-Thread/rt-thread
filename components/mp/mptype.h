#ifndef __MPTYPE_H__
#define __MPTYPE_H__

#include <mpporttype.h>

typedef struct {
    void *start;
    rt_size_t size;
    rt_mem_attr_t attr;
} rt_mem_region_t;

#endif /* __MPTYPE_H__ */
