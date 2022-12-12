/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>
#include "cpuusage.h"
#include "lcd.h"

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#endif

#define CPU_USAGE_CALC_TICK 10
#define CPU_USAGE_LOOP      100

static rt_uint8_t  cpu_usage_major = 0, cpu_usage_minor= 0;
static rt_uint32_t total_count = 0;

static void cpu_usage_idle_hook()
{
    rt_tick_t tick;
    rt_uint32_t count;
    volatile rt_uint32_t loop;

    if (total_count == 0)
    {
        loop = 0;

        /* get total count */
        rt_enter_critical();
        tick = rt_tick_get();
        while(rt_tick_get() - tick < CPU_USAGE_CALC_TICK)
        {
            total_count ++;
            while (loop < CPU_USAGE_LOOP) loop ++;
        }
        rt_exit_critical();
    }

    count = 0;
    loop  = 0;
    /* get CPU usage */
    tick = rt_tick_get();
    while (rt_tick_get() - tick < CPU_USAGE_CALC_TICK)
    {
        count ++;
        while (loop < CPU_USAGE_LOOP) loop ++;
    }

    /* calculate major and minor */
    if (count < total_count)
    {
        count = total_count - count;
        cpu_usage_major = (count * 100) / total_count;
        cpu_usage_minor = ((count * 100) % total_count) * 100 / total_count;
    }
    else
    {
        total_count = count;

        /* no CPU usage */
        cpu_usage_major = 0;
        cpu_usage_minor = 0;
    }
}

void cpu_usage_get(rt_uint8_t *major, rt_uint8_t *minor)
{
    RT_ASSERT(major != RT_NULL);
    RT_ASSERT(minor != RT_NULL);

    *major = cpu_usage_major;
    *minor = cpu_usage_minor;
}

void cpu_usage_init()
{
    /* set idle thread hook */
    rt_thread_idle_sethook(cpu_usage_idle_hook);
}
extern struct rt_messagequeue mq;
extern rt_thread_t info_tid;
static void cpu_thread_entry(void *parameter)
{
#ifdef RT_USING_RTGUI
    struct rtgui_event_command ecmd;

    RTGUI_EVENT_COMMAND_INIT(&ecmd);
    ecmd.type = RTGUI_CMD_USER_INT;
    ecmd.command_id = CPU_UPDATE;
#else
    struct lcd_msg msg;
#endif

    while (1)
    {
#ifdef RT_USING_RTGUI
        rtgui_thread_send(info_tid, &ecmd.parent, sizeof(ecmd));
#else
        msg.type = CPU_MSG;
        msg.major = cpu_usage_major;
        msg.minor = cpu_usage_minor;
        rt_mq_send(&mq, &msg, sizeof(msg));
#endif
        rt_thread_delay(20);
    }
}

static rt_thread_t cpu_thread;
void rt_hw_cpu_init(void)
{
    cpu_usage_init();
    cpu_thread = rt_thread_create("cpu", cpu_thread_entry, RT_NULL, 384, 27, 5);
    if(cpu_thread != RT_NULL)
        rt_thread_startup(cpu_thread);
}
