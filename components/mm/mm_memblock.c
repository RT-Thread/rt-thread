
#include "mm_memblock.h"
#include "mm_page.h"
#include "mm_aspace.h"

#define DBG_TAG "mm.memblock"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define INIT_MEMORY_REGIONS 128
#define INIT_RESERVED_REGIONS 128

#define PHYS_ADDR_MAX (~(rt_ubase_t)0)

static struct rt_mmblk_reg memory_init_regions[INIT_MEMORY_REGIONS];
static struct rt_mmblk_reg reserved_init_regions[INIT_RESERVED_REGIONS];

static struct rt_memblock memory = {
    .cnt = 0,
    .max = INIT_MEMORY_REGIONS,
    .regions = memory_init_regions,
};

static struct rt_memblock reserved = {
    .cnt = 0,
    .max = INIT_MEMORY_REGIONS,
    .regions = reserved_init_regions,
};

rt_inline rt_size_t _adjust_size(rt_ubase_t base, rt_size_t *size)
{
    return *size = MIN(*size, PHYS_ADDR_MAX - base);
}

rt_inline rt_err_t _memblock_insert_region(struct rt_memblock *memblock, 
                                        int idx, rt_ubase_t base, 
                                        rt_size_t size, 
                                        enum mmblk_flag flags)
{
    struct rt_mmblk_reg *rgn = &memblock->regions[idx];
    rt_err_t ret = RT_EOK;

    RT_ASSERT(idx <= memblock->cnt && memblock->cnt <= memblock->max);
    
    if(memblock->cnt == memblock->max)
    {
        LOG_E("No enough space to store region!");
        ret = -RT_ENOMEM;
    }

    if(ret == RT_EOK)
    {
        rt_memmove(rgn + 1, rgn, (memblock->cnt - idx)*sizeof(*rgn));
        rgn->flags = flags;
        rgn->base = base;
        rgn->size = size;
        memblock->cnt++;
    }

    return ret;
}

static void _memblock_merge_regions(struct rt_memblock *memblock)
{
	int i = 0;

	/* cnt never goes below 1 */
	while (i < memblock->cnt - 1) {
		struct rt_mmblk_reg *this = &memblock->regions[i];
		struct rt_mmblk_reg *next = &memblock->regions[i + 1];
        
        RT_ASSERT(this->base + this->size <= next->base);
		
        if (this->base + this->size != next->base ||
		    this->flags != next->flags) {
			i++;
			continue;
		}

		this->size += next->size;
		/* move forward from next + 1, index of which is i + 2 */
		memmove(next, next + 1, (memblock->cnt - (i + 2)) * sizeof(*next));
		memblock->cnt--;
	}
}

static rt_err_t _memblock_add_range(struct rt_memblock *memblock,
                                    rt_ubase_t base, rt_size_t size, 
                                    enum mmblk_flag flags)
{   
    rt_err_t ret = RT_EOK;
    rt_ubase_t end = base + _adjust_size(base, &size);
    struct rt_mmblk_reg *reg = RT_NULL;
    int i = 0;

    if(!size)
        return 0;

    for_each_region(i, memblock, reg)
    {
        rt_ubase_t rbase = reg->base;
        rt_ubase_t rend = rbase + reg->size;

        if(rbase >= end)
            break;
        if(rend <= base)
            continue;

        /* region to add overlaps with reg */
        if(rbase > base)
        {
            if(flags != reg->flags)
                LOG_W("range [%p-%p] with flags %d overlaps region [%p-%p] with flags %d",\
                            (void*)obase, (void*)(obase+size), flags, \
                            (void*)rbase, (void*)(rbase+rend), reg->flags);
            ret = _memblock_insert_region(memblock, i++, base, rbase - base, flags);
        }
        base = MIN(rend, end);
    }

    /* insert the remaining portion */
    if(base < end)
    {
        ret = _memblock_insert_region(memblock, i, base, end - base, flags);
    }
        
    _memblock_merge_regions(memblock);
    return ret;        
}

static int _memblock_isolate_range(struct rt_memblock *memblock,
					rt_ubase_t base, rt_ubase_t size,
					int *start_reg, int *end_reg)
{
    rt_ubase_t end = base + _adjust_size(base, &size);
    int idx = 0, ret = RT_EOK;
    struct rt_mmblk_reg *reg;

    *start_reg = *end_reg = 0;

    if(!size)
        return 0;
    
    for_each_region(idx, memblock, reg)
    {
        rt_ubase_t rbase = reg->base;
        rt_ubase_t rend = rbase + reg->size;

        if (rbase >= end)
			break;
		if (rend <= base)
			continue;
        
        if(rbase < base)
        {
            reg->base = base;
            reg->size -= base - rbase;
            ret = _memblock_insert_region(memblock, idx, rbase, base - rbase, reg->flags);
        }
        else if (rend > end)
        {
            reg->base = end;
			reg->size -= end - rbase;
			ret = _memblock_insert_region(memblock, idx--, rbase, end - rbase, reg->flags);
        }
        else
        {
            if(!*end_reg)
                *start_reg = idx;
            *end_reg = idx + 1;
        }
    }

    return ret;
}

static int _memblock_setclr_flag(rt_ubase_t base,
				rt_ubase_t size, rt_bool_t set, int flag)
{
	int i, ret, start_rgn, end_rgn;

	ret = _memblock_isolate_range(&memory, base, size, &start_rgn, &end_rgn);
	if (ret != RT_EOK)
		return ret;

	for (i = start_rgn; i < end_rgn; i++) {
		struct rt_mmblk_reg *reg = &(memory.regions[i]);

		if (set)
			reg->flags |= flag;
		else
			reg->flags &= ~flag;
	}

	_memblock_merge_regions(&memory);
	return 0;
}

static rt_ubase_t _memblock_size(struct rt_memblock *memblock)
{
    rt_ubase_t mmblk_size = 0;

    for(int i = 0; i < memblock->cnt; i++)
    {
        mmblk_size += memblock->regions[i].size;
    }

    return mmblk_size;
}

static void _memblock_dump(struct rt_memblock *memblock)
{
    int idx;
    struct rt_mmblk_reg *reg;
    rt_ubase_t reg_end;

    for_each_region(idx, memblock, reg)
    {
        reg_end = reg->base + reg->size - 1;
        rt_kprintf("[0x%x]\t[%p-%p] size: 0x%xBytes flags:0x%x\n",
            idx, (void*)reg->base, (void*)reg_end, reg->size, reg->flags);
    }
}

static void _next_free_region(rt_uint64_t *idx, enum mmblk_flag flags,
				      rt_ubase_t *out_start, rt_ubase_t *out_end)
{
	rt_uint32_t idx_memory = *idx & 0xffffffff;
	rt_uint32_t idx_reserved = *idx >> 32;

    /* memory related data */
    struct rt_mmblk_reg *m = RT_NULL;
    rt_ubase_t m_start = 0;
    rt_ubase_t m_end = 0;

    /* reserved related data */
    struct rt_mmblk_reg *r = RT_NULL;
    rt_ubase_t r_start = 0;
    rt_ubase_t r_end = 0;

	for (; idx_memory < memory.cnt; idx_memory++) {
        m = &memory.regions[idx_memory];
        
        if(m->flags != flags)
        {
            continue;
        }
            
        m_start = m->base;
        m_end = m->base + m->size;

        for(; idx_reserved < reserved.cnt+1; idx_reserved++)
        {
            /*
             * Find the complement of reserved memblock.
             * For example, if reserved memblock is following:
             * 
             *  0:[8-16), 1:[32-48), 2:[128-130)
             * 
             * The upper 32bit indexes the following regions.
             *
             *	0:[0-8), 1:[16-32), 2:[48-128), 3:[130-MAX)
             * 
             * So we can find intersecting region other than excluding.
             */
            r = &reserved.regions[idx_reserved];
            r_start = idx_reserved ? r[-1].base + r[-1].size : 0;
            r_end = idx_reserved < reserved.cnt ? r->base : PHYS_ADDR_MAX;

            /* reserved */
            if(r_start >= m_end)
            {
                break;
            }
                
            /* freed memory */
            if(m_start < r_end)
            {
                *out_start = MAX(m_start, r_start);
                *out_end = MIN(m_end, r_end);

                if(m_end <= r_end)
                {
                    idx_memory++;
                }
                else
                {
                    idx_reserved++;
                }
                *idx = idx_memory | (rt_uint64_t)idx_reserved << 32;
                return;
            }
        }
    }

    /* found all regions */
  	*idx = ~(rt_uint64_t)0;
}


rt_err_t rt_memblock_add(rt_ubase_t base, rt_size_t size)
{
	LOG_D("memblock add: [%p-%p]\n", base, base + size - 1);

	return _memblock_add_range(&memory, base, size, 0);
}

rt_err_t rt_memblock_reserve(rt_ubase_t base, rt_size_t size)
{
	LOG_D("memblock reverse: [%p-%p]\n", base, base + size - 1);

	return _memblock_add_range(&reserved, base, size, 0);
}

rt_ubase_t rt_memblock_mem_size()
{
    return _memblock_size(&memory);
}

rt_ubase_t rt_memblock_reserved_size()
{
    return _memblock_size(&reserved);
}

rt_ubase_t rt_memblock_end()
{
    rt_uint64_t i = 0;
    rt_bool_t init = RT_TRUE;
    rt_region_t reg;
    rt_ubase_t mem = 0;
    
    /* make sure region is compact */
    _memblock_merge_regions(&memory);

    for_each_free_range(i, MEMBLOCK_NONE, &reg.start, &reg.end)
    {
        reg.start -= PV_OFFSET;
        reg.end -= PV_OFFSET;

        if(init)
        {
            rt_page_init(reg);
            init = RT_FALSE;
        }
        else
        {
            rt_page_install(reg);
        }
        LOG_D("region [%p-%p] added to buddy system", reg.start, reg.end);
        mem += reg.end - reg.start;
    }

    LOG_D("%p bytes memory added to buddy system");
    return mem;
}

void rt_memblock_dump()
{
    rt_kprintf("Memory info:\n");
    _memblock_dump(&memory);
    rt_kprintf("\n\nReserved memory info:\n");
    _memblock_dump(&reserved);
}

/**
 * memblock_mark_hotplug - Mark hotpluggable memory with flag MEMBLOCK_HOTPLUG.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -errno on failure.
 */
int rt_memblock_mark_hotplug(rt_ubase_t base, rt_ubase_t size)
{
	return _memblock_setclr_flag(base, size, 1, MEMBLOCK_HOTPLUG);
}

/**
 * memblock_clear_hotplug - Clear flag MEMBLOCK_HOTPLUG for a specified region.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -errno on failure.
 */
int rt_memblock_clear_hotplug(rt_ubase_t base, rt_ubase_t size)
{
	return _memblock_setclr_flag(base, size, 0, MEMBLOCK_HOTPLUG);
}

/**
 * memblock_mark_mirror - Mark mirrored memory with flag MEMBLOCK_MIRROR.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -errno on failure.
 */
int rt_memblock_mark_mirror(rt_ubase_t base, rt_ubase_t size)
{
	return _memblock_setclr_flag(base, size, 1, MEMBLOCK_MIRROR);
}

/**
 * memblock_mark_nomap - Mark a memory region with flag MEMBLOCK_NOMAP.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -errno on failure.
 */
int rt_memblock_mark_nomap(rt_ubase_t base, rt_ubase_t size)
{
	return _memblock_setclr_flag(base, size, 1, MEMBLOCK_NOMAP);
}

/**
 * memblock_clear_nomap - Clear flag MEMBLOCK_NOMAP for a specified region.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -errno on failure.
 */
int rt_memblock_clear_nomap(rt_ubase_t base, rt_ubase_t size)
{
	return _memblock_setclr_flag(base, size, 0, MEMBLOCK_NOMAP);
}