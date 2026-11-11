/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef RT_VDSO_DATA_PAGE_H
#define RT_VDSO_DATA_PAGE_H

#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include "vdso_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RT_VDSO_CLOCK_ID_MAX 16
#define RT_VDSO_NSEC_PER_SEC 1000000000ULL
#define RT_VDSO_FLAG_REALTIME_VALID (1ULL << 0)

enum rt_vdso_clock_data_index
{
    RT_VDSO_CLOCK_REALTIME_INDEX = 0,
    RT_VDSO_CLOCK_MONOTONIC_INDEX,
    RT_VDSO_CLOCK_DATA_COUNT,
};

struct rt_vdso_data_page
{
    uint32_t seq_counter;
    uint32_t reserved0;
    uint64_t flags;
    uint64_t counter_last;
    uint64_t counter_freq;
    struct timespec base_time[RT_VDSO_CLOCK_DATA_COUNT];
};

#ifdef __cplusplus
}
#endif

#endif /* RT_VDSO_DATA_PAGE_H */
