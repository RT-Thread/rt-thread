/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     first version
 */

#ifndef __ATA_INTERFACE_H__
#define __ATA_INTERFACE_H__

typedef rt_uint8_t u8;
typedef rt_uint16_t u16;
typedef rt_uint32_t u32;
typedef rt_uint64_t u64;
typedef rt_uint64_t ulong;

typedef rt_int8_t s8;
typedef rt_int16_t s16;
typedef rt_int32_t s32;
typedef rt_int64_t s64;

typedef rt_size_t lbaint_t;

#define __iomem
#define mdelay rt_thread_mdelay
#define udelay(...) rt_thread_mdelay(1)

#define cpu_to_le32
#define cpu_to_le16
#define le32_to_cpu
#define le16_to_cpu

#define flush_cache(...)
#define invalidate_dcache_range(...)

#define ARCH_DMA_MINALIGN 1024

#define CONFIG_IS_ENABLED
#define AHCI 1

#define VADDR_TO_PHY(vaddr) (((u64)vaddr) - KSEG0BASE)
#define LOW_PHY(vaddr) ((u32)VADDR_TO_PHY(vaddr))
#define HIGH_PHY(vaddr) ((u32)((VADDR_TO_PHY(vaddr)) >> 32))

#define ALIGN_1(x, a) __ALIGN_MASK((x), (typeof(x))(a)-1)
#define ALIGN_DOWN(x, a) ALIGN_1((x) - ((a)-1), (a))
#define __ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define PTR_ALIGN(p, a) ((typeof(p))ALIGN((unsigned long)(p), (a)))
#define IS_ALIGNED(x, a) (((x) & ((typeof(x))(a)-1)) == 0)

#define ROUND(a, b) (((a) + (b)-1) & ~((b)-1))

#define PAD_COUNT(s, pad) (((s)-1) / (pad) + 1)
#define PAD_SIZE(s, pad) (PAD_COUNT(s, pad) * pad)
#define ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, pad)                         \
    char __##name[ROUND(PAD_SIZE((size) * sizeof(type), pad), align) + (align - 1)]; \
                                                                                     \
    type *name = (type *)ALIGN_1((rt_ubase_t)__##name, align)
#define ALLOC_ALIGN_BUFFER(type, name, size, align) \
    ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, 1)
#define ALLOC_CACHE_ALIGN_BUFFER_PAD(type, name, size, pad) \
    ALLOC_ALIGN_BUFFER_PAD(type, name, size, ARCH_DMA_MINALIGN, pad)
#define ALLOC_CACHE_ALIGN_BUFFER(type, name, size) \
    ALLOC_ALIGN_BUFFER(type, name, size, ARCH_DMA_MINALIGN)

static inline u32 readl(void *addr)
{
    return *((u32 *)addr);
}

static inline void writel(u32 data, void *addr)
{
    *((u32 *)addr) = data;
}

static inline int ffs(int word)
{
    int r;

    if (word == 0)
    {
        return 0;
    }

    word &= (-word);

    __asm__("clz %0, %1"
            : "=r"(r)
            : "r"(word));
    return 32 - r;
}

static inline void setbits_le32(u32 *addr, u32 value)
{
    *addr = value;
}

#endif
