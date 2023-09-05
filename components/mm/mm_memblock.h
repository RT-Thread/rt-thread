#ifndef __MM_MEMBLOCK_H__
#define __MM_MEMBLOCK_H__

#include "mm_page.h"

enum memblock_flags
{
    MEMBLOCK_NONE		= 0x0,
	MEMBLOCK_HOTPLUG	= 0x1,
	MEMBLOCK_MIRROR		= 0x2,
	MEMBLOCK_NOMAP		= 0x4,
};

struct rt_memblock_region
{
    void *base;
    rt_size_t size;
    enum memblock_flags flags;
};

struct rt_memblock
{
    rt_uint32_t cnt;
    rt_uint32_t max;
    struct rt_memblock_region *regions;
};

#endif