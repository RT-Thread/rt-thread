/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-04-21     rcitach        init ver.
 */

#ifndef RT_VDSO_USER_INTERNAL_H
#define RT_VDSO_USER_INTERNAL_H

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>

#include <vdso_data_page.h>
#include <vdso_arch.h>

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#ifndef barrier
#define barrier() __asm__ __volatile__("" : : : "memory")
#endif

static inline void rt_vdso_read_once_size(const volatile void *ptr, void *dst, int size)
{
    switch (size)
    {
    case 1:
        *(uint8_t *)dst = *(const volatile uint8_t *)ptr;
        break;
    case 2:
        *(uint16_t *)dst = *(const volatile uint16_t *)ptr;
        break;
    case 4:
        *(uint32_t *)dst = *(const volatile uint32_t *)ptr;
        break;
    case 8:
        *(uint64_t *)dst = *(const volatile uint64_t *)ptr;
        break;
    default:
        barrier();
        __builtin_memcpy(dst, (const void *)ptr, size);
        barrier();
        break;
    }
}

#define READ_ONCE(x)                                         \
    ({                                                       \
        union                                                \
        {                                                    \
            typeof(x) value;                                 \
            char bytes[sizeof(x)];                           \
        } once;                                              \
        rt_vdso_read_once_size(&(x), once.bytes, sizeof(x)); \
        once.value;                                          \
    })

extern const struct rt_vdso_data_page __rt_vdso_data_page[] __attribute__((visibility("hidden")));

static inline const struct rt_vdso_data_page *rt_vdso_get_data_page(void)
{
    return __rt_vdso_data_page;
}

static inline uint32_t rt_vdso_data_read_begin(const struct rt_vdso_data_page *data_page)
{
    uint32_t seq;

    while (unlikely((seq = READ_ONCE(data_page->seq_counter)) & 1U))
    {
        rt_vdso_arch_cpu_relax();
    }

    rt_vdso_arch_rmb();
    return seq;
}

static inline uint32_t rt_vdso_data_read_retry(const struct rt_vdso_data_page *data_page,
                                               uint32_t start)
{
    rt_vdso_arch_rmb();
    return READ_ONCE(data_page->seq_counter) != start;
}

static inline uint64_t rt_vdso_counter_delta_to_ns(uint64_t now, uint64_t last,
                                                   uint64_t freq)
{
    if (freq == 0)
    {
        return 0;
    }

    return (now - last) * RT_VDSO_NSEC_PER_SEC / freq;
}

static inline void rt_vdso_timespec_add_nanoseconds(struct timespec *ts, uint64_t ns)
{
    ts->tv_sec += (time_t)(ns / RT_VDSO_NSEC_PER_SEC);
    ns = (uint64_t)ts->tv_nsec + (ns % RT_VDSO_NSEC_PER_SEC);
    if (ns >= RT_VDSO_NSEC_PER_SEC)
    {
        ts->tv_sec += 1;
        ns -= RT_VDSO_NSEC_PER_SEC;
    }
    ts->tv_nsec = (long)ns;
}

#endif /* RT_VDSO_USER_INTERNAL_H */
