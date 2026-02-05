/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-04     BruceOu      first implementation
 * 2025-07-10     WangShun     fix for GD32VW553H_EVAL
 */

#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#ifdef BSP_USING_WLAN
#include "gd32vw55x_platform.h"
#include "wrapper_os.h"
#include "wifi_management.h"
#include "wifi_init.h"
#include "user_setting.h"
#include "util.h"
#endif /* BSP_USING_WLAN */
/* LED1 ~ LED3 pin: PA4 PA5 PA6 */
#define LED1_PIN GET_PIN(A, 4)


#ifdef RT_USING_WIFI
#define START_TASK_STACK_SIZE       512
#define START_TASK_PRIO             4

static void application_init(void)
{
    util_init();

    user_setting_init();

    if (wifi_init()) {
        rt_kprintf("wifi init failed\r\n");
    } else {
        // rt_kprintf("wifi init success\r\n");
    }
}

static rt_sem_t init_done_sem = RT_NULL;

static void start_task(void *param)
{
    (void)param;

    application_init();
    // rt_kprintf("Start task completed, exiting.\n");

    /* Note: In RT-Thread, task should exit by returning, not by calling sys_task_delete(NULL).
     * When the task function returns, RT-Thread will automatically clean up the task.
     */

    rt_sem_release(init_done_sem);
}

#endif /* RT_USING_WIFI */

/* LED blink thread */
static void led_thread_entry(void *param)
{
    (void)param;

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

int main(void)
{
    rt_thread_t led_thread;

    rt_kprintf("Hello GD32VW553H\n");
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

#ifdef RT_USING_WIFI
    /* Create semaphore for synchronization */
    init_done_sem = rt_sem_create("init_done", 0, RT_IPC_FLAG_PRIO);
    if (init_done_sem == RT_NULL) {
        rt_kprintf("Failed to create semaphore\n");
        return -RT_ERROR;
    }

    if (sys_task_create_dynamic((const uint8_t *)"start_task",
            START_TASK_STACK_SIZE, OS_TASK_PRIORITY(START_TASK_PRIO), start_task, NULL) == NULL) {
        rt_kprintf("Create start task failed\r\n");
        return -RT_ERROR;
    }

    // rt_kprintf("Waiting for initialization to complete...\n");
    /* Wait for initialization task to complete */
    rt_sem_take(init_done_sem, RT_WAITING_FOREVER);
    // rt_kprintf("Initialization completed, continuing...\n");

    /* Clean up semaphore */
    rt_sem_delete(init_done_sem);
    init_done_sem = RT_NULL;

    /* set wifi work mode */
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#ifdef RT_USING_NETDEV
    rt_thread_mdelay(1000);
    extern int wifi_netdev_register(void);
    wifi_netdev_register();
#endif /* RT_USING_NETDEV */   
#endif /* RT_USING_WIFI */

    /* Create LED blink thread */
    led_thread = rt_thread_create("led",
                                   led_thread_entry,
                                   RT_NULL,
                                   1024,
                                   25,  /* Lower priority to not block shell */
                                   10);
    if (led_thread != RT_NULL) {
        rt_thread_startup(led_thread);
        rt_kprintf("LED thread started\n");
    } else {
        rt_kprintf("Failed to create LED thread\n");
    }

    /* Return from main to allow shell to work properly */
    return RT_EOK;
}
