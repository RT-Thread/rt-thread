/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-04-22     ScuDays        Add VDSO functionality under the riscv64 architecture.
 */

#ifndef ASM_VDSO_SYS_H
#define ASM_VDSO_SYS_H

#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include <vdso_config.h>
#include <vdso_datapage.h>

#define __always_unused __attribute__((__unused__))
#define __maybe_unused  __attribute__((__unused__))

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define arch_counter_enforce_ordering \
    __asm__ volatile("fence rw, rw" ::: "memory")

static inline uint64_t __arch_get_hw_counter(void)
{
    uint64_t res;
    __asm__ volatile("rdtime %0" : "=r"(res));
    arch_counter_enforce_ordering;
    return res;
}

static inline uint32_t
__iter_div_u64_rem(uint64_t dividend, uint32_t divisor, uint64_t *remainder)
{
    uint32_t ret = 0;

    while (dividend >= divisor)
    {
        /* The following asm() prevents the compiler from
        optimising this loop into a modulo operation.  */
        __asm__("" : "+rm"(dividend));

        dividend -= divisor;
        ret++;
    }

    *remainder = dividend;

    return ret;
}

#define __RT_STRINGIFY(x...) #x
#define RT_STRINGIFY(x...)   __RT_STRINGIFY(x)
#define rt_hw_barrier(cmd, ...) \
    __asm__ volatile(RT_STRINGIFY(cmd) " " RT_STRINGIFY(__VA_ARGS__)::: "memory")

#define rt_hw_isb() rt_hw_barrier(fence.i)
#define rt_hw_dmb() rt_hw_barrier(fence, rw, rw)
#define rt_hw_wmb() rt_hw_barrier(fence, w, w)
#define rt_hw_rmb() rt_hw_barrier(fence, r, r)
#define rt_hw_dsb() rt_hw_barrier(fence, rw, rw)

#ifndef barrier

#define barrier() __asm__ __volatile__("fence" : : : "memory")
#endif

static inline void cpu_relax(void)
{
    __asm__ volatile("nop" ::: "memory");
}

#define __READ_ONCE_SIZE                                          \
    ({                                                            \
        switch (size)                                             \
        {                                                         \
        case 1:                                                   \
            *(__u8 *)res = *(volatile __u8 *)p;                   \
            break;                                                \
        case 2:                                                   \
            *(__u16 *)res = *(volatile __u16 *)p;                 \
            break;                                                \
        case 4:                                                   \
            *(__u32 *)res = *(volatile __u32 *)p;                 \
            break;                                                \
        case 8:                                                   \
            *(__u64 *)res = *(volatile __u64 *)p;                 \
            break;                                                \
        default:                                                  \
            barrier();                                            \
            __builtin_memcpy((void *)res, (const void *)p, size); \
            barrier();                                            \
        }                                                         \
    })

static inline void __read_once_size(const volatile void *p, void *res, int size)
{
    __READ_ONCE_SIZE;
}

#define __READ_ONCE(x, check)                                                \
    ({                                                                       \
        union {                                                              \
            typeof(x) __val;                                                 \
            char      __c[1];                                                \
        } __u;                                                               \
        if (check)                                                           \
            __read_once_size(&(x), __u.__c, sizeof(x));                      \
        smp_read_barrier_depends(); /* Enforce dependency ordering from x */ \
        __u.__val;                                                           \
    })
#define READ_ONCE(x) __READ_ONCE(x, 1)

extern struct vdso_data         _vdso_data[CS_BASES] __attribute__((visibility("hidden")));
static inline struct vdso_data *__arch_get_vdso_data(void)
{
    return _vdso_data;
}

static inline uint32_t rt_vdso_read_begin(const struct vdso_data *vd)
{
    uint32_t seq;

    while (unlikely((seq = READ_ONCE(vd->seq)) & 1))
        cpu_relax();

    rt_hw_rmb();
    return seq;
}

static inline uint32_t rt_vdso_read_retry(const struct vdso_data *vd,
                                          uint32_t                start)
{
    uint32_t seq;

    rt_hw_rmb();
    seq = READ_ONCE(vd->seq);
    return seq != start;
}

#endif
