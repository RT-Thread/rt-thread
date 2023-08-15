/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_wdg_drv.h"

#define TICKS_1K (1024UL)
#define TICKS_1M (1024UL * TICKS_1K)
#define TICKS_1G (1024UL * TICKS_1M)
#define ONE_SECOND_TICKS_IN_NS (1000UL * 1000UL * 1000UL)

typedef struct {
    uint32_t top;
    reset_interval_t interval;
} reset_interval_map_t;

typedef struct {
    uint32_t top;
    interrupt_interval_t interval;
} interrupt_interval_map_t;

static const reset_interval_map_t k_reset_interval_map[reset_interval_out_of_range + 1U] = {
    {128UL, reset_interval_clock_period_mult_128},
    {256UL, reset_interval_clock_period_mult_256},
    {512UL, reset_interval_clock_period_mult_512},
    {1UL * TICKS_1K, reset_interval_clock_period_mult_1k},
    {2UL * TICKS_1K, reset_interval_clock_period_mult_2k},
    {4UL * TICKS_1K, reset_interval_clock_period_mult_4k},
    {8UL * TICKS_1K, reset_interval_clock_period_mult_8k},
    {16UL * TICKS_1K, reset_interval_clock_period_mult_16k},
    {0xFFFFFFFFUL, reset_interval_out_of_range},
};

static const interrupt_interval_map_t k_interrupt_interval_map[interrupt_interval_out_of_range + 1U] = {
    {64UL, interrupt_interval_clock_period_multi_64},
    {256UL, interrupt_interval_clock_period_multi_256},
    {1UL * TICKS_1K, interrupt_interval_clock_period_multi_1k},
    {2UL * TICKS_1K, interrupt_interval_clock_period_multi_2k},
    {4UL * TICKS_1K, interrupt_interval_clock_period_multi_4k},
    {8UL * TICKS_1K, interrupt_interval_clock_period_multi_8k},
    {16UL * TICKS_1K, interrupt_interval_clock_period_multi_16k},
    {32UL * TICKS_1K, interrupt_interval_clock_period_multi_32k},
    {128UL * TICKS_1K, interrupt_interval_clock_period_multi_128k},
    {512UL * TICKS_1K, interrupt_interval_clock_period_multi_512k},
    {2UL * TICKS_1M, interrupt_interval_clock_period_multi_2m},
    {8UL * TICKS_1M, interrupt_interval_clock_period_multi_8m},
    {32UL * TICKS_1M, interrupt_interval_clock_period_multi_32m},
    {128UL * TICKS_1M, interrupt_interval_clock_period_multi_128m},
    {512UL * TICKS_1M, interrupt_interval_clock_period_multi_512m},
    {2UL * TICKS_1G, interrupt_interval_clock_period_multi_2g},
    {0xFFFFFFFFUL, interrupt_interval_out_of_range}

};

/* See hpm_wdg_drv.h for more details */
hpm_stat_t wdg_init(WDG_Type *base, wdg_control_t *wdg_ctrl)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        HPM_BREAK_IF((base == NULL) || (wdg_ctrl == NULL));

        HPM_BREAK_IF((wdg_ctrl->reset_interval > reset_interval_max) ||
            (wdg_ctrl->interrupt_interval > interrupt_interval_max) ||
            (wdg_ctrl->clksrc > wdg_clksrc_pclk));

        uint32_t rst_time = (uint32_t) wdg_ctrl->reset_interval;
        uint32_t int_time = (uint32_t) wdg_ctrl->interrupt_interval;
        uint32_t reset_en = wdg_ctrl->reset_enable ? 1UL : 0UL;
        uint32_t int_en = wdg_ctrl->interrupt_enable ? 1UL : 0UL;
        uint32_t clk_src = (wdg_ctrl->clksrc == wdg_clksrc_pclk) ? 1UL : 0UL;
        uint32_t wdg_en = wdg_ctrl->wdg_enable ? 1UL : 0UL;

        uint32_t wdg_ctrl = WDG_CTRL_RSTTIME_SET(rst_time)
            | WDG_CTRL_INTTIME_SET(int_time)
            | WDG_CTRL_CLKSEL_SET(clk_src)
            | WDG_CTRL_RSTEN_SET(reset_en)
            | WDG_CTRL_INTEN_SET(int_en)
            | WDG_CTRL_EN_SET(wdg_en);

        wdg_write_enable(base);

        base->CTRL = wdg_ctrl;

        status = status_success;

    } while (false);

    return status;
}

/* See hpm_wdg_drv.h for more details */
reset_interval_t wdg_convert_reset_interval_from_us(const uint32_t src_freq, const uint32_t reset_us)
{
    reset_interval_t reset_interval = reset_interval_out_of_range;

    uint32_t src_clk_one_tick_in_ns = ONE_SECOND_TICKS_IN_NS / src_freq;
    if (src_clk_one_tick_in_ns < 1U) {
        src_clk_one_tick_in_ns = 1U;
    }

    uint32_t reset_interval_ticks = (reset_us * 1000UL) / src_clk_one_tick_in_ns;

    for (uint32_t i = 0; i < ARRAY_SIZE(k_reset_interval_map); i++) {
        if (reset_interval_ticks <= k_reset_interval_map[i].top) {
            reset_interval = k_reset_interval_map[i].interval;
            break;
        }
    }

    return reset_interval;
}

/* See hpm_wdg_drv.h for more details */
interrupt_interval_t wdg_convert_interrupt_interval_from_us(const uint32_t src_freq, uint32_t interval_us)
{
    interrupt_interval_t interrupt_interval = interrupt_interval_out_of_range;

    uint32_t src_clk_one_tick_in_ns = ONE_SECOND_TICKS_IN_NS / src_freq;
    if (src_clk_one_tick_in_ns < 1U) {
        src_clk_one_tick_in_ns = 1U;
    }

    uint32_t interrupt_interval_ticks = ((uint64_t) interval_us * 1000L) / src_clk_one_tick_in_ns;
    for (uint32_t i = 0; i < ARRAY_SIZE(k_interrupt_interval_map); i++) {
        if (interrupt_interval_ticks <= k_interrupt_interval_map[i].top) {
            interrupt_interval = k_interrupt_interval_map[i].interval;
            break;
        }
    }

    return interrupt_interval;
}

uint64_t wdg_convert_interrupt_interval_to_us(const uint32_t src_freq, interrupt_interval_t interval)
{
    uint64_t time_in_us = 0;
    if ((src_freq != 0) && (interval < interrupt_interval_out_of_range)) {
        uint32_t interrupt_interval_in_reg = (uint32_t) interval;

        double tick_in_ns = 1.0 * ONE_SECOND_TICKS_IN_NS / src_freq;
        uint64_t
            total_interval_in_ns = (uint64_t)(tick_in_ns * k_interrupt_interval_map[interrupt_interval_in_reg].top);

        time_in_us = total_interval_in_ns / 1000UL;
    }

    return time_in_us;
}

uint32_t wdg_convert_reset_interval_to_us(const uint32_t src_freq, reset_interval_t interval)
{
    uint32_t time_in_us = 0;
    if ((src_freq != 0) && (interval < reset_interval_out_of_range)) {
        uint32_t reset_interval_in_reg = (uint32_t) interval;
        double tick_in_ns = 1.0 * ONE_SECOND_TICKS_IN_NS / src_freq;
        uint64_t total_interval_in_ns = (uint64_t)(tick_in_ns * k_reset_interval_map[reset_interval_in_reg].top);

        time_in_us = (uint32_t)(total_interval_in_ns / 1000UL);
    }

    return time_in_us;
}

uint64_t wdg_get_interrupt_interval_in_us(WDG_Type *base, const uint32_t src_freq)
{
    uint64_t time_in_us = 0;
    if ((base != NULL) && (src_freq != 0)) {
        interrupt_interval_t interval = (interrupt_interval_t) WDG_CTRL_INTTIME_GET(base->CTRL);

        time_in_us = wdg_convert_interrupt_interval_to_us(src_freq, interval);
    }

    return time_in_us;
}

uint64_t wdg_get_total_reset_interval_in_us(WDG_Type *base, const uint32_t src_freq)
{
    uint64_t time_in_us = 0;
    if ((base != NULL) && (src_freq != 0)) {
        reset_interval_t reset_interval = (reset_interval_t) WDG_CTRL_RSTTIME_GET(base->CTRL);
        interrupt_interval_t interrupt_interval = (interrupt_interval_t) WDG_CTRL_INTTIME_GET(base->CTRL);
        time_in_us = wdg_convert_reset_interval_to_us(src_freq, reset_interval) +
            wdg_convert_interrupt_interval_to_us(src_freq, interrupt_interval);
    }

    return time_in_us;
}
