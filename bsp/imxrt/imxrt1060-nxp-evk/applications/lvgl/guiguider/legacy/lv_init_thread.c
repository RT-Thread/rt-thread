/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 * 2022-05-13     Meco Man      support LVGL8.2.0 legacy version
 */
#include <rtthread.h>
#include <lvgl.h>

#ifndef PKG_LVGL_THREAD_STACK_SIZE
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#endif

#ifndef PKG_LVGL_THREAD_PRIO
#define PKG_LVGL_THREAD_PRIO (RT_THREAD_PRIORITY_MAX * 2 / 3)
#endif

extern void lv_user_gui_init(void);

static struct rt_thread lvgl_thread;
static rt_uint8_t lvgl_thread_stack[PKG_LVGL_THREAD_STACK_SIZE];

static void lvgl_thread_entry(void *parameter)
{
    lv_user_gui_init();

    while(1)
    {
        lv_task_handler();
        rt_thread_mdelay(5);
    }
}

static int lvgl_thread_init(void)
{
    rt_thread_init(&lvgl_thread,
                   "LVGL",
                   lvgl_thread_entry,
                   RT_NULL,
                   &lvgl_thread_stack[0],
                   sizeof(lvgl_thread_stack),
                   PKG_LVGL_THREAD_PRIO,
                   10);
    rt_thread_startup(&lvgl_thread);

    return 0;
}
INIT_ENV_EXPORT(lvgl_thread_init);
