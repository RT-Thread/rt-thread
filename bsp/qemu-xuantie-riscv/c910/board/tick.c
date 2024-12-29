/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/12/11     flyingcys    The first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <encoding.h>
#include <csi_core.h>
#define CORET_IRQn                  (7)

static volatile rt_uint64_t time_elapsed = 0;
static volatile unsigned long tick_cycles = 0;
static volatile uint32_t last_time_ms = 0U;
static volatile uint64_t last_time_us = 0U;

static volatile uint32_t csi_tick = 0U;
static volatile uint64_t timer_init_value = 0U;

static void csi_tick_increase(void)
{
    csi_tick ++;
}
static uint32_t csi_tick_get(void)
{
    return csi_tick;
}
int rt_hw_tick_isr(void)
{
    rt_tick_increase();
    csi_tick_increase();
    csi_coret_config((CPUTIME_TIMER_FREQ / RT_TICK_PER_SECOND), CORET_IRQn);
    return 0;
}
/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    csi_tick = 0U;
    timer_init_value = csi_coret_get_value2();
    csi_coret_reset_value2();
    csi_coret_config((CPUTIME_TIMER_FREQ / RT_TICK_PER_SECOND), CORET_IRQn);
    csi_coret_irq_enable();

    return 0;
}