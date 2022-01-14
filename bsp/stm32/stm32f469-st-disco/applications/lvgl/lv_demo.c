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
#include <lvgl.h>
#include <lv_port_indev.h>
#define DBG_TAG    "LVGL.demo"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifndef LV_THREAD_STACK_SIZE
    #define LV_THREAD_STACK_SIZE 4096
#endif

#ifndef LV_THREAD_PRIO
    #define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX * 2 / 8)
#endif

static struct rt_thread lvgl_thread;
static rt_uint8_t lvgl_thread_stack[LV_THREAD_STACK_SIZE];

static void lvgl_entry(void *parameter)
{
    extern void lv_demo_music(void);
    lv_demo_music();

    while(1)
    {
        lv_task_handler();
        rt_thread_mdelay(5);
    }
}

static int lvgl_demo_init(void)
{
    rt_thread_t tid;

    rt_thread_init(&lvgl_thread,
                   "LVGL",
                   lvgl_entry,
                   RT_NULL,
                   &lvgl_thread_stack[0],
                   sizeof(lvgl_thread_stack),
                   LV_THREAD_PRIO,
                   10);
    rt_thread_startup(&lvgl_thread);

    return 0;
}
INIT_APP_EXPORT(lvgl_demo_init);
