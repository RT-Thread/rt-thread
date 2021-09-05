/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-09     Zero-Free    first implementation
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_PM

#define WAKEUP_EVENT_BUTTON                 (1 << 0)
#define PIN_LED_R                           GET_PIN(E, 7)
#define WAKEUP_PIN                          GET_PIN(C, 13)
#define WAKEUP_APP_THREAD_STACK_SIZE        1024

static rt_event_t wakeup_event;

static void wakeup_callback(void *args)
{
    rt_event_send(wakeup_event, WAKEUP_EVENT_BUTTON);
}

static void wakeup_init(void)
{
    rt_pin_mode(WAKEUP_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(WAKEUP_PIN, PIN_IRQ_MODE_FALLING, wakeup_callback, RT_NULL);
    rt_pin_irq_enable(WAKEUP_PIN, 1);
}

static void wakeup_app_entry(void *parameter)
{
    wakeup_init();
    rt_pm_request(PM_SLEEP_MODE_DEEP);

    while (1)
    {
        if (rt_event_recv(wakeup_event,
                          WAKEUP_EVENT_BUTTON,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, RT_NULL) == RT_EOK)
        {
            rt_pm_request(PM_SLEEP_MODE_NONE);

            rt_pin_mode(PIN_LED_R, PIN_MODE_OUTPUT);
            rt_pin_write(PIN_LED_R, 0);
            rt_thread_delay(rt_tick_from_millisecond(500));
            rt_pin_write(PIN_LED_R, 1);

            rt_pm_release(PM_SLEEP_MODE_NONE);
        }
    }
}

static int wakeup_app(void)
{
    rt_thread_t tid;

    wakeup_event = rt_event_create("wakup", RT_IPC_FLAG_PRIO);
    RT_ASSERT(wakeup_event != RT_NULL);

    tid = rt_thread_create("wakeup_app", wakeup_app_entry, RT_NULL,
                           WAKEUP_APP_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(tid != RT_NULL);

    rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(wakeup_app);

#endif
