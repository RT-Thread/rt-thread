/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-20     WangXiaoyao  Complete testcase for mm_aspace.c
 */
#ifndef __TEST_MM_COMMON_H__
#define __TEST_MM_COMMON_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <utest.h>

#include <board.h>
#include <rtthread.h>
#include <rthw.h>
#include <mmu.h>
#include <tlb.h>

#ifdef RT_USING_SMART
#include <lwp_arch.h>
#endif

#include <ioremap.h>
#include <mm_aspace.h>
#include <mm_flag.h>
#include <mm_page.h>
#include <mm_private.h>

extern rt_base_t rt_heap_lock(void);
extern void rt_heap_unlock(rt_base_t level);

#define __int_compare(a, b, operator) do{long _a = (long)(a); long _b = (long)(b); __utest_assert((_a) operator (_b), "Assertion Failed: (" #a ") "#operator" (" #b ")"); if (!((_a) operator (_b)))LOG_E("\t"#a"=%ld(0x%lx), "#b"=%ld(0x%lx)", _a, _a, _b, _b);} while (0)
#define utest_int_equal(a, b) __int_compare(a, b, ==)
#define utest_int_less(a, b) __int_compare(a, b, <)
#define utest_int_less_equal(a, b) __int_compare(a, b, <=)

/**
 * @brief During the operations, is heap still the same;
 */
#define CONSIST_HEAP(statement) do {                \
    rt_size_t total, used, max_used;                \
    rt_size_t totala, useda, max_useda;             \
    rt_ubase_t level = rt_heap_lock();              \
    rt_memory_info(&total, &used, &max_used);       \
    statement;                                      \
    rt_memory_info(&totala, &useda, &max_useda);    \
    rt_heap_unlock(level);                          \
    utest_int_equal(total, totala);               \
    utest_int_equal(used, useda);                 \
    } while (0)

#ifdef STANDALONE_TC
#define TC_ASSERT(expr)                                                        \
    ((expr)                                                                    \
         ? 0                                                                   \
         : rt_kprintf("AssertFault(%d): %s\n", __LINE__, RT_STRINGIFY(expr)))
#else
#define TC_ASSERT(expr) uassert_true(expr)
#endif

rt_inline int memtest(volatile char *buf, int value, size_t buf_sz)
{
    int ret = 0;
    for (size_t i = 0; i < buf_sz; i++)
    {
        if (buf[i] != value)
        {
            ret = -1;
            break;
        }
    }
    return ret;
}

#endif /* __TEST_MM_COMMON_H__ */
