/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-02-25     CYFS         first version
 */
#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "gd32vw55x_platform.h"
#include "wrapper_os.h"
#include "wifi_management.h"
#include "wifi_init.h"
#include "user_setting.h"
#include "util.h"

#ifdef RT_USING_WIFI
#define START_TASK_STACK_SIZE       512
#define START_TASK_PRIO             4

static void application_init(void)
{
    util_init();

    user_setting_init();

    if (wifi_init())
    {
        rt_kprintf("wifi init failed\r\n");
    } else {
        /* rt_kprintf("wifi init success\r\n"); */
    }
}

static rt_sem_t init_done_sem = RT_NULL;

static void start_task(void *param)
{
    (void)param;

    application_init();
    /* rt_kprintf("Start task completed, exiting.\n"); */

    /* Note: In RT-Thread, task should exit by returning, not by calling sys_task_delete(NULL).
     * When the task function returns, RT-Thread will automatically clean up the task.
     */

    rt_sem_release(init_done_sem);
}

#endif /* RT_USING_WIFI */

int wifi_app_init(void)
{

#ifdef RT_USING_WIFI
    /* Create semaphore for synchronization */
    init_done_sem = rt_sem_create("init_done", 0, RT_IPC_FLAG_PRIO);
    if (init_done_sem == RT_NULL)
    {
        rt_kprintf("Failed to create semaphore\n");
        return -RT_ERROR;
    }

    if (sys_task_create_dynamic((const uint8_t *)"start_task",
            START_TASK_STACK_SIZE, OS_TASK_PRIORITY(START_TASK_PRIO), start_task, NULL) == NULL)
            {
        rt_kprintf("Create start task failed\r\n");
        return -RT_ERROR;
    }

    /* rt_kprintf("Waiting for initialization to complete...\n"); */
    /* Wait for initialization task to complete */
    rt_sem_take(init_done_sem, RT_WAITING_FOREVER);
    /* rt_kprintf("Initialization completed, continuing...\n"); */

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

    return RT_EOK;
}

INIT_APP_EXPORT(wifi_app_init);

