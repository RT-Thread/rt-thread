/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 */
#include <rtthread.h>
#define DBG_TAG    "LVGL.demo"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>
#include <lvgl.h>
#include <win32drv.h>

#ifndef LV_THREAD_STACK_SIZE
#define LV_THREAD_STACK_SIZE 4096
#endif

#ifndef LV_THREAD_PRIO
#define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*2/3)
#endif

static void lvgl_thread(void *parameter)
{
    /* initialize win32 driver; don't put this in lv_port_disp() */
    if (!lv_win32_init(GetModuleHandleW(NULL), SW_SHOW, BSP_LCD_WIDTH, BSP_LCD_HEIGHT, NULL))
    {
        LOG_E("lv_win32_init is failure!");
        return;
    }
    lv_win32_add_all_input_devices_to_group(NULL);

    /* display demo; you may replace with your LVGL application at here */
    extern void lv_demo_music(void);
    lv_demo_music();

    /* handle the tasks of LVGL */
    while (!lv_win32_quit_signal)
    {
        lv_task_handler();
        rt_thread_mdelay(1);
    }

    LOG_W("LVGL simulator window is closed!");
}

static int lvgl_demo_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("LVGL", lvgl_thread, RT_NULL, LV_THREAD_STACK_SIZE, LV_THREAD_PRIO, 10);
    if(tid == RT_NULL)
    {
        LOG_E("Fail to create 'LVGL' thread");
    }
    rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(lvgl_demo_init);
