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

#include <rtthread.h>
#include <rthw.h>
#include <lwp_arch.h>
#include <mm_flag.h>
#include <mm_page.h>
#include <mmu.h>
#include <mm_aspace.h>
#include <utest.h>

extern rt_base_t rt_heap_lock(void);
extern void rt_heap_unlock(rt_base_t level);

/**
 * @brief During the operations, is heap still the same;
 */
#define CONSIST_HEAP(statement) do {                 \
    rt_size_t total, used, max_used;                \
    rt_size_t totala, useda, max_useda;             \
    rt_ubase_t level = rt_heap_lock();              \
    rt_memory_info(&total, &used, &max_used);       \
    statement;                                      \
    rt_memory_info(&totala, &useda, &max_useda);    \
    rt_heap_unlock(level);                          \
    uassert_true(total == totala);                  \
    uassert_true(used == useda);                    \
    uassert_true(max_used == max_useda);            \
    } while (0)

#endif /* __TEST_MM_COMMON_H__ */
