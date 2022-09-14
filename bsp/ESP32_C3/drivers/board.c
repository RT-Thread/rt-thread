/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     supperthomas first version
 */

#include <rtthread.h>
#include "hal/systimer_hal.h"
#include "hal/systimer_ll.h"
#include "esp_private/panic_internal.h"
#include "esp_private/systimer.h"
#include "esp_private/periph_ctrl.h"
#include "esp_intr_alloc.h"
#include "esp_attr.h"

static systimer_hal_context_t systimer_hal;
IRAM_ATTR void rt_SysTickIsrHandler(void *arg)
{
    systimer_ll_clear_alarm_int(systimer_hal.dev, SYSTIMER_LL_ALARM_OS_TICK_CORE0);
    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

void rt_hw_systick_init(void)
{
    esp_intr_alloc(ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE, ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL1, rt_SysTickIsrHandler, &systimer_hal, NULL);
    periph_module_enable(PERIPH_SYSTIMER_MODULE);
    systimer_hal_init(&systimer_hal);
    systimer_hal_tick_rate_ops_t ops = {
            .ticks_to_us = systimer_ticks_to_us,
            .us_to_ticks = systimer_us_to_ticks,
    };
    systimer_hal_set_tick_rate_ops(&systimer_hal, &ops);
    systimer_ll_set_counter_value(systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0);
    systimer_ll_apply_counter_value(systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK);
    systimer_hal_connect_alarm_counter(&systimer_hal, SYSTIMER_LL_ALARM_OS_TICK_CORE0, SYSTIMER_LL_COUNTER_OS_TICK);
    systimer_hal_set_alarm_period(&systimer_hal, SYSTIMER_LL_ALARM_OS_TICK_CORE0, 1000000UL / RT_TICK_PER_SECOND);
    systimer_hal_select_alarm_mode(&systimer_hal, SYSTIMER_LL_ALARM_OS_TICK_CORE0, SYSTIMER_ALARM_MODE_PERIOD);
    systimer_hal_counter_can_stall_by_cpu(&systimer_hal, 1, 0, true);
    systimer_hal_enable_alarm_int(&systimer_hal, SYSTIMER_LL_ALARM_OS_TICK_CORE0);
    systimer_hal_enable_counter(&systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK);
}

void rt_hw_board_init(void)
{
    rt_hw_systick_init();
    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
