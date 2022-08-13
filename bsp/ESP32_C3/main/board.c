/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     supperthomas first version
 */

#include <stdio.h>

#include "esp_private/panic_internal.h"
#include "hal/uart_hal.h"
#include "driver/timer.h"
#include "soc/periph_defs.h"
#include "hal/systimer_hal.h"
#include "hal/systimer_ll.h"
#include "esp_intr_alloc.h"

#include "rtthread.h"
#include "rthw.h"
#include "drv_gpio.h"
#include "drv_uart.h"
#include "shell.h"

#ifdef RT_USING_COMPONENTS_INIT
/*
 * Components Initialization will initialize some driver and components as following
 * order:
 * rti_start         --> 0
 * BOARD_EXPORT      --> 1
 * rti_board_end     --> 1.end
 *
 * DEVICE_EXPORT     --> 2
 * COMPONENT_EXPORT  --> 3
 * FS_EXPORT         --> 4
 * ENV_EXPORT        --> 5
 * APP_EXPORT        --> 6
 *
 * rti_end           --> 6.end
 *
 * These automatically initialization, the driver or component initial function must
 * be defined with:
 * INIT_BOARD_EXPORT(fn);
 * INIT_DEVICE_EXPORT(fn);
 * ...
 * INIT_APP_EXPORT(fn);
 * etc.
 */
static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_start(void)
{
    return 0;
}
INIT_EXPORT(rti_board_start, "0.end");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.end");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end, "6.end");

/**
 * @brief  Onboard components initialization. In this function, the board-level
 *         initialization function will be called to complete the initialization
 *         of the on-board peripherals.
 */
void rt_components_board_init(void)
{
#if RT_DEBUG_INIT
    int result;
    const struct rt_init_desc *desc;
    for (desc = &__rt_init_desc_rti_board_start; desc < &__rt_init_desc_rti_board_end; desc ++)
    {
        rt_kprintf("rt_components_board_init initialize %s", desc->fn_name);
        result = desc->fn();
        rt_kprintf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_board_start; fn_ptr < &__rt_init_rti_board_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
#endif /* RT_DEBUG_INIT */
}

/**
 * @brief  RT-Thread Components Initialization.
 */
void rt_components_init(void)
{
#if RT_DEBUG_INIT
    int result;
    const struct rt_init_desc *desc;

    rt_kprintf("do components initialization.\n");
    for (desc = &__rt_init_desc_rti_board_end; desc < &__rt_init_desc_rti_end; desc ++)
    {
        rt_kprintf("rt_components_init initialize %s", desc->fn_name);
        result = desc->fn();
        rt_kprintf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_board_end; fn_ptr < &__rt_init_rti_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
#endif /* RT_DEBUG_INIT */
}
#endif /* RT_USING_COMPONENTS_INIT */




void main_thread_entry(void *parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* RT-Thread components initialization */
    rt_components_init();
#endif /* RT_USING_COMPONENTS_INIT */

    extern int rtt_main();
    rtt_main();

}

void rt_application_init(void)
{
    rt_thread_t tid;

#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10

    tid = rt_thread_create("main", main_thread_entry, RT_NULL,
                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(tid != RT_NULL);

    rt_thread_startup(tid);
}

//component
static uint32_t uwTick = 0;
static systimer_hal_context_t systimer_hal;
IRAM_ATTR void rt_SysTickIsrHandler(void *arg)
{
    systimer_ll_clear_alarm_int(systimer_hal.dev, 1);
    rt_interrupt_enter();

    rt_tick_increase();
    uwTick++;
    /* leave interrupt */
    rt_interrupt_leave();
    systimer_ll_is_alarm_int_fired(systimer_hal.dev, 1);
}

void rt_hw_systick_init(void)
{
    uint8_t system_timer_counter=1;

    //rt_hw_interrupt_enable(0);
    esp_intr_alloc(ETS_SYSTIMER_TARGET1_EDGE_INTR_SOURCE, ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL1, rt_SysTickIsrHandler, &systimer_hal, NULL);
    systimer_hal_init(&systimer_hal);
    systimer_ll_set_counter_value(systimer_hal.dev, system_timer_counter, 0);
    systimer_ll_apply_counter_value(systimer_hal.dev, system_timer_counter);
    uint32_t alarm_id = 1 ;
    systimer_hal_connect_alarm_counter(&systimer_hal, alarm_id, system_timer_counter);
    systimer_hal_set_alarm_period(&systimer_hal, alarm_id, 1000000UL / 1000);
    systimer_hal_select_alarm_mode(&systimer_hal, alarm_id, SYSTIMER_ALARM_MODE_PERIOD);
    systimer_hal_counter_can_stall_by_cpu(&systimer_hal, 1, 0, true);
    systimer_hal_enable_alarm_int(&systimer_hal, alarm_id);

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

static void rtthread_startup(void)
{
    rt_hw_interrupt_disable();
    /* init board */
    rt_hw_board_init();

    /* timer system initialization */
    rt_system_timer_init();

    /* create init_thread */
    rt_application_init();

    /* timer thread initialization */
    rt_system_timer_thread_init();

    /* idle thread initialization */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();
    /* init scheduler system */
    rt_hw_pin_init();
    rt_hw_uart_init();
    finsh_system_init();
    /* never reach here */
    return ;
}

void app_main(void)
{
    /* startup RT-Thread RTOS */
    rtthread_startup();
    return;
}
