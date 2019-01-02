/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     Zhangyihong  the first version
 */
 
#include <rtthread.h>
#include <drivers/pin.h>

#include <rthw.h>
 
#include "drv_touch.h"
#ifdef TINA_USING_TOUCH
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif
#define BSP_TOUCH_SAMPLE_HZ    (50)
static rt_list_t driver_list;

extern void touch_down(void);
extern void touch_mo(void);
extern void touch_up(void);

void rt_touch_drivers_register(touch_drv_t drv)
{
    rt_list_insert_before(&driver_list, &drv->list);
}

static void post_down_event(rt_uint16_t x, rt_uint16_t y, rt_tick_t ts)
{
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.x = x;
    emouse.y = y;
#ifdef PKG_USING_GUIENGINE
    emouse.ts = rt_tick_get();
    emouse.id = ts;
#endif
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
    rt_kprintf("touch down x:%d,y%d,id:%d\r\n", x, y, ts);
    touch_down();
#endif
}

static void post_motion_event(rt_uint16_t x, rt_uint16_t y, rt_tick_t ts)
{
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
    emouse.x = x;
    emouse.y = y;
#ifdef PKG_USING_GUIENGINE
    emouse.ts = rt_tick_get();
    emouse.id = ts;
#endif
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
    rt_kprintf("touch motion x:%d,y%d,id:%d\r\n", x, y, ts);
	touch_mo();
#endif
}

static void post_up_event(rt_uint16_t x, rt_uint16_t y, rt_tick_t ts)
{
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
    emouse.x = x;
    emouse.y = y;
#ifdef PKG_USING_GUIENGINE
    emouse.ts = rt_tick_get();
    emouse.id = ts;
#endif
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
    rt_kprintf("touch up x:%d,y%d,id:%d\r\n", x, y, ts);
	touch_up();
#endif
}

static void touch_thread_entry(void *parameter)
{
    touch_drv_t touch = (touch_drv_t)parameter;
    struct touch_message msg;
    rt_tick_t emouse_id = 0;
    touch->ops->isr_enable(RT_TRUE);
    while (1)
    {

        if (rt_sem_take(touch->isr_sem, RT_WAITING_FOREVER) != RT_EOK)
        {
            continue;
        }
        if (touch->ops->read_point(&msg) != RT_EOK)
        {
            touch->ops->isr_enable(RT_TRUE);
            continue;
        }
        switch (msg.event)
        {
        case TOUCH_EVENT_UP:
            post_up_event(msg.x, msg.y, emouse_id);
            break;
        case TOUCH_EVENT_DOWN:
            emouse_id = rt_tick_get();
            post_down_event(msg.x, msg.y, emouse_id);
            break;
        case TOUCH_EVENT_MOVE:
            post_motion_event(msg.x, msg.y, emouse_id);
            break;
        default:
            break;
        }
        rt_thread_delay(RT_TICK_PER_SECOND / BSP_TOUCH_SAMPLE_HZ);
        touch->ops->isr_enable(RT_TRUE);
    }
}

int rt_touch_driver_init(void)
{
	rt_kprintf("\r\n%s \r\n", __FUNCTION__);
    rt_list_init(&driver_list);
    return 0;
}
INIT_BOARD_EXPORT(rt_touch_driver_init);

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;
static int rt_touch_thread_init(void)
{
    rt_list_t *l;
    touch_drv_t current_driver;
    rt_thread_t tid = RT_NULL;
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("i2c1");
    RT_ASSERT(i2c_bus);
    current_driver = RT_NULL;
    if (rt_device_open((rt_device_t)i2c_bus, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
        return -1;
    for (l = driver_list.next; l != &driver_list; l = l->next)
    {
        if (rt_list_entry(l, struct touch_drivers, list)->probe(i2c_bus))
        {
            current_driver = rt_list_entry(l, struct touch_drivers, list);
            break;
        }
    }
    if (current_driver == RT_NULL)
    {
        rt_kprintf("no touch screen or do not have driver\r\n");
        rt_device_close((rt_device_t)i2c_bus);
        return -1;
    }
    current_driver->ops->init(i2c_bus);
    rt_kprintf("touch screen found driver\r\n");
    tid = rt_thread_create("touch", touch_thread_entry, current_driver, 2048, 27, 20);
    if (tid == RT_NULL)
    {
        current_driver->ops->deinit();
        rt_device_close((rt_device_t)i2c_bus);
        return -1;
    }
    rt_thread_startup(tid);
    return 0;
}

static void touch_init_thread_entry(void *parameter)
{
    rt_touch_thread_init();
}
static int touc_bg_init(void)
{
    rt_thread_t tid = RT_NULL;
    tid = rt_thread_create("touchi", touch_init_thread_entry, RT_NULL, 2048, 28, 20);
    if (tid == RT_NULL)
    {
        return -1;
    }
    rt_thread_startup(tid);
    return 0;
}
INIT_APP_EXPORT(touc_bg_init);


#endif
