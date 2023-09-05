
#include "mm_memblock.h"

#define INIT_REGIONS 128
#define MALLOC_REGION(new_size) \
    ((struct rt_memblock_region *)rt_malloc((new_size) * sizeof(struct rt_memblock_region)))
#define END_OF_REGION(base, size) \
    ((rt_uint8_t *)(base) + (size))

static struct rt_memblock memory = {
    .cnt = 0,
    .max = 0,
    .regions = RT_NULL,
};

static struct rt_memblock reserved = {
    .cnt = 0,
    .max = 0,
    .regions = RT_NULL,
};

rt_inline void* _min_addr(void *a, void *b)
{
    return a < b ? a : b;
}

rt_inline void* _max_addr(void *a, void *b)
{
    return a > b ? a : b;
}

rt_inline _adjust_size(void *base, rt_size_t *size)
{
    rt_ubase_t max_paddr = ~(rt_ubase_t)0;
    return *size = _min_addr(*size, max_paddr - (rt_ubase_t)base);
}   

rt_err_t _memblock_resize(struct rt_memblock *memblock, rt_size_t new_size)
{
    RT_ASSERT(memblock->cnt <= new_size);

    rt_err_t ret = RT_EOK;
    struct rt_memblock_region *new_region = MALLOC_REGION(new_size);

    if(new_region)
    {
        rt_memcpy(new_region, memblock->regions, memblock->cnt * sizeof(*new_region));
        rt_free(memblock->regions);
        memblock->regions = new_region;
    }
    else
    {
        ret = -RT_ENOMEM;
    }

    return ret;
}

rt_inline rt_err_t _memblock_insert_region(struct rt_memblock *memblock, 
                                        int idx, void *base, 
                                        rt_size_t size, 
                                        enum memblock_flags flags)
{
    struct rt_memblock_region *rgn = &memblock->regions[idx];
    rt_err_t ret = RT_EOK;

    RT_ASSERT(idx <= memblock->cnt && memblock->cnt <= memblock->max);
    
    if(memblock->cnt = memblock->max)
    {
        ret = _memblock_resize(memblock, 2*memblock->max);
        if(ret == RT_EOK)
        {
            memblock->max *= 2;
        }
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

rt_inline void _memblock_remove_region(struct rt_memblock *memblock, 
                                        rt_uint32_t idx, rt_uint32_t count)
{
    struct rt_memblock_region *rgn = &memblock->regions[idx];
    rt_err_t ret = RT_EOK;

    RT_ASSERT(idx + count <= memblock->cnt);
    
    rt_memmove(rgn, rgn + count, (memblock->cnt - idx - count) * sizeof(*rgn));
    memblock->cnt -= count;
}

rt_err_t _memblock_add_range(struct rt_memblock *memblock, void *base, rt_size_t size, enum memblock_flags flags)
{
    void *end = base + _adjust_size(base, &size);
    int merged_begin = -1, merged_cnt = 0;
    void *new_reg_beg = RT_NULL, *new_reg_end = RT_NULL;
    rt_err_t ret = RT_EOK;

    if(!size)
        return 0;

    if(memblock->regions == RT_NULL)
    {
        RT_ASSERT(memblock->cnt == 0);
        memblock->regions = MALLOC_REGION(INIT_REGIONS);
        memblock->max = INIT_REGIONS;
    }

    /* find the first region to merge and the begin paddr of merged region */
    for(int i = 0; i < memblock->cnt; i++)
    {
        if(END_OF_REGION(memblock->regions[i].base, memblock->regions[i].size) >= base)
        {   
            merged_begin = i;
            if(memblock->regions[i].base <= END_OF_REGION(base, size))
            {
                merged_cnt = 1;
                new_reg_beg = _min_addr(memblock->regions[i].base, base);
                new_reg_end = _max_addr(END_OF_REGION(memblock->regions[i].base, memblock->regions[i].size), 
                                        END_OF_REGION(base, size));    
            }
            break;
        }
    }

    /* if can be merged with other region */
    if(merged_cnt != 0)
    {
        /* find the last region to merge and the end paddr of merged region */
        for(int i = merged_begin + 1; i < memblock->cnt; i++)
        {
            if(memblock->regions[i].base > END_OF_REGION(base, size))
            {
                new_reg_end = _max_addr(END_OF_REGION(memblock->regions[i].base, memblock->regions[i].size), 
                                        END_OF_REGION(base, size));
            }
            merged_cnt++;
        }

        _memblock_remove_region(memblock, merged_begin, merged_cnt);
        ret = _memblock_insert_region(memblock, merged_begin, new_reg_beg, 
                                (rt_ubase_t)new_reg_end - (rt_ubase_t)new_reg_beg, flags);
    }
    else
    {
        ret = _memblock_insert_region(memblock, merged_begin, base, size, flags);
    }

    return ret;        
}

rt_err_t rt_memblock_add(void *base, rt_size_t size)
{
    rt_uint8_t *end = (rt_uint8_t*)base + size - 1;

	LOG_D("memblock add: [%p-%p]\n", &base, &end);

	return _memblock_add_range(&memory, base, size, 0);
}

rt_err_t rt_memblock_reserve(void *base, rt_size_t size)
{
    rt_uint8_t *end = (rt_uint8_t*)base + size - 1;

	LOG_D("memblock reverse: [%p-%p]\n", &base, &end);

	return _memblock_add_range(&reserved, base, size, 0);
}


