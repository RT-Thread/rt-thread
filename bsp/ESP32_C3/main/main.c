/*
 * Copyright (c) 2021-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-24     supperthomas first version
 */
#include <stdio.h>
#include "driver/gpio.h"


#include "esp_private/panic_internal.h"
#include "hal/uart_hal.h"
#include "driver/timer.h"
#include "soc/periph_defs.h"
#include "hal/systimer_hal.h"
#include "hal/systimer_ll.h"
#include "esp_intr_alloc.h"

#include "rtthread.h"
#include "rthw.h"


void main_thread_entry(void *parameter)
{
#define BLINK_GPIO 12
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(BLINK_GPIO, 1);
        rt_thread_mdelay(1000);
        gpio_set_level(BLINK_GPIO, 0);
        rt_thread_mdelay(1000);
    }
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

    extern int __heap_start__;
    extern int __heap_end__;
    printf("%s:%d__heap_start__:%p,__heap_end__:%p\n",__func__,__LINE__,&__heap_start__,&__heap_end__);
    rt_system_heap_init((void *)&__heap_start__, (void *)&__heap_end__);

}

static void rtthread_startup(void)
{
    rt_hw_interrupt_disable();
    /* init board */
    rt_hw_board_init();
    /* show RT-Thread version */
    rt_show_version();

    /* timer system initialization */
    rt_system_timer_init();

    /* scheduler system initialization */
    rt_system_scheduler_init();

    /* create init_thread */
    rt_application_init();

    /* timer thread initialization */
    rt_system_timer_thread_init();

    /* idle thread initialization */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();
    /* init scheduler system */

    /* never reach here */
    return ;
}

void app_main(void)
{
    /* startup RT-Thread RTOS */
    rtthread_startup();
    return;

}
