#ifndef __MM_MEMBLOCK_H__
#define __MM_MEMBLOCK_H__

#include "mm_page.h"

enum mmblk_flag
{
    MEMBLOCK_NONE		= 0x0,
	MEMBLOCK_HOTPLUG	= 0x1,
	MEMBLOCK_MIRROR		= 0x2,
	MEMBLOCK_NOMAP		= 0x4,
};

struct rt_mmblk_reg
{
    rt_ubase_t base;
    rt_size_t size;
    enum mmblk_flag flags;
};

struct rt_memblock
{
    rt_uint32_t cnt;
    rt_uint32_t max;
    struct rt_mmblk_reg *regions;
};

rt_inline rt_bool_t rt_memblock_is_hotpluggable(struct rt_mmblk_reg *m)
{
	return m->flags & MEMBLOCK_HOTPLUG;
}

rt_inline rt_bool_t rt_memblock_is_mirror(struct rt_mmblk_reg *m)
{
	return m->flags & MEMBLOCK_MIRROR;
}

rt_inline rt_bool_t rt_memblock_is_nomap(struct rt_mmblk_reg *m)
{
	return m->flags & MEMBLOCK_NOMAP;
}

#define for_each_region(i, memblock, rgn)			\
	for (i = 0, rgn = &memblock->regions[0];			\
	     i < memblock->cnt;					\
	     i++, rgn = &memblock->regions[i])

#define for_each_free_range(i, flags, p_start, p_end)   \
	for (i = 0, _next_free_region(&i, flags, p_start, p_end);\
	     i != ~(rt_uint64_t)0;\
	     _next_free_region(&i, flags, p_start, p_end))

#endif