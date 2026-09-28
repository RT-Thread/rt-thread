/*
 * Copyright (c) 2021-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     supperthomas first version
 * 2024-12-08     wumingzi     support rt_hw_us_delay
 */

#include <rtthread.h>
#include "rttypes.h"
#include "hal/systimer_hal.h"
#include "hal/systimer_ll.h"
#include "esp_private/panic_internal.h"
#include "esp_private/systimer.h"
#include "esp_private/periph_ctrl.h"
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "esp_timer.h"
#include "driver/gptimer.h"
#ifdef SOC_ESP32_S3
#include <xtensa/config/core-isa.h>       /* XCHAL_INTLEVEL1_MASK */
#endif

static systimer_hal_context_t systimer_hal;
IRAM_ATTR void rt_SysTickIsrHandler(void *arg)
{
    systimer_ll_clear_alarm_int(systimer_hal.dev, SYSTIMER_LL_ALARM_OS_TICK_CORE0);
#ifdef SOC_ESP32_S3
    /* rt_interrupt_enter()/rt_interrupt_leave() are already around the whole
     * level-1 dispatch, in rt_xt_irq_process() (libcpu/xtensa/esp32s3/cpuport.c).
     * Counting them here too would make rt_interrupt_get_nest() report two
     * interrupts for one. */
    rt_tick_increase();
#else
    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
#endif
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
#ifdef SOC_ESP32_S3
    /* SYSTIMER unit1 (the OS tick counter) has per-CPU "stall" enables that come
     * out of reset set for both CPUs. This image runs core 0 only, so core 1 is
     * never running and its stall line keeps unit1 frozen: the alarm compares
     * against a counter stuck at 0 and no tick interrupt is ever raised.
     * Free-running the counter is what light sleep would otherwise stop, and
     * this BSP does not use light sleep. */
    systimer_hal_counter_can_stall_by_cpu(&systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 0, false);
    systimer_hal_counter_can_stall_by_cpu(&systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1, false);
#else
    systimer_hal_counter_can_stall_by_cpu(&systimer_hal, 1, 0, true);
#endif
    systimer_hal_enable_alarm_int(&systimer_hal, SYSTIMER_LL_ALARM_OS_TICK_CORE0);
    systimer_hal_enable_counter(&systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK);
#ifdef SOC_ESP32_S3
    /* This BSP services level-1 interrupts only: the tick and UART0 both
     * allocate one, and its level 2-5 vectors are fatal by design. ESP-IDF's
     * startup leaves sources enabled that nothing here asked for -- on this
     * board two of them sit at level 4, one being ETS_LCD_CAM_INTR_SOURCE --
     * and an enabled source that is never serviced would reach a fatal vector.
     * Mask everything above level 1 so that cannot happen. */
    {
        uint32_t ie;

        __asm__ __volatile__("rsr %0, intenable" : "=r"(ie));
        ie &= XCHAL_INTLEVEL1_MASK;
        __asm__ __volatile__("wsr %0, intenable; rsync" :: "r"(ie) : "memory");
    }
#endif
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

static gptimer_handle_t gptimer_hw_us = NULL;

static int delay_us_init(void)
{
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1 * 1000 * 1000, /* 1MHz, 1 tick = 1us*/
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer_hw_us));
    ESP_ERROR_CHECK(gptimer_enable(gptimer_hw_us));
    return RT_EOK;
}
INIT_DEVICE_EXPORT(delay_us_init);

void rt_hw_us_delay(rt_uint32_t us)
{
    uint64_t count = 0;
    ESP_ERROR_CHECK(gptimer_start(gptimer_hw_us));
    ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer_hw_us, 0));
    /* Retrieve the timestamp at anytime*/
    while(count < (uint64_t)us)
    {
        ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer_hw_us, &count));
    }
    ESP_ERROR_CHECK(gptimer_stop(gptimer_hw_us));
}