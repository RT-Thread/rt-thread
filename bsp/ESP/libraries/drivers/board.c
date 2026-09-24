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

#ifdef SOC_ESP32_C6
#include "esp_cpu.h"
#include "riscv/csr.h"
#include "riscv/interrupt.h"

extern void esprv_intc_int_enable(uint32_t unmask);
extern void esprv_intc_int_set_priority(int intr_num, int pri);

static void c6_move_intr(int from, int to, volatile uint32_t *map)
{
    intr_handler_t handler = intr_handler_get(from);
    void *arg = intr_handler_get_arg(from);

    if (handler == 0)
    {
        return;
    }
    esp_cpu_intr_set_handler(to, (esp_cpu_intr_handler_t)handler, arg);
    esprv_intc_int_set_priority(to, 3);
    esprv_intc_int_enable(1u << to);
    *map = (uint32_t)to;
}

static void c6_bind_interrupts(void)
{
    RV_WRITE_CSR(mideleg, 0);
    /* Lines 3 and 4 stay disabled on this chip. Source 57 is systimer
     * target0; source 43 is UART0. */
    c6_move_intr(3, 16, (volatile uint32_t *)0x600100e4);
    c6_move_intr(4, 9, (volatile uint32_t *)0x600100ac);
    systimer_ll_clear_alarm_int(systimer_hal.dev, SYSTIMER_LL_ALARM_OS_TICK_CORE0);
}
#endif

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
#ifdef SOC_ESP32_C6
    c6_bind_interrupts();
#endif
}

#ifdef SOC_ESP32_C6
#include "esp_rom_sys.h"

void rt_hw_us_delay(rt_uint32_t us)
{
    esp_rom_delay_us(us);
}
#else
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
    while (count < (uint64_t)us)
    {
        ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer_hw_us, &count));
    }
    ESP_ERROR_CHECK(gptimer_stop(gptimer_hw_us));
}
#endif
