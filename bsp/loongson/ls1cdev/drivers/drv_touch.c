/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     Zhangyihong  the first version
 * 2018-10-29     XY
 * 2019-04-11     sundm75      modify for ls1c300 & RTGUI
 */

#include "drv_touch.h"

#define TOUCH_I2C_NAME  "i2c1"

#ifndef TOUCH_SAMPLE_HZ
#define TOUCH_SAMPLE_HZ (50)
#endif

#ifndef TOUCH_I2C_NAME
#error "Please define touch i2c name!"
#endif

#ifdef TINA_USING_TOUCH
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

#if 0
#define TPDEBUG     rt_kprintf
#else
#define TPDEBUG(...)
#endif

static rt_slist_t _driver_list;
static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

static void post_down_event(rt_uint16_t x, rt_uint16_t y, rt_uint32_t id)
{
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
    rt_err_t result;
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.x = x;
    emouse.y = y;
#ifdef PKG_USING_GUIENGINE
    emouse.ts = rt_tick_get();
    emouse.id = id;
#endif

#ifdef PKG_USING_GUIENGINE
    do
    {
        result = rtgui_server_post_event(&emouse.parent, sizeof(emouse));
        if (result != RT_EOK)
        {
            rt_thread_delay(RT_TICK_PER_SECOND / TOUCH_SAMPLE_HZ);
        }
    }
    while (result != RT_EOK);
#else
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
#endif

    TPDEBUG("[TP] touch down [%d, %d]\n", emouse.x, emouse.y);
#endif
}

static void post_motion_event(rt_uint16_t x, rt_uint16_t y, rt_uint32_t id)
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
    emouse.id = id;
#endif
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
    TPDEBUG("[TP] touch motion [%d, %d]\n", emouse.x, emouse.y);
#endif
}

static void post_up_event(rt_uint16_t x, rt_uint16_t y, rt_uint32_t id)
{
#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
    rt_err_t result;
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
    emouse.x = x;
    emouse.y = y;
#ifdef PKG_USING_GUIENGINE
    emouse.ts = rt_tick_get();
    emouse.id = id;
#endif

#ifdef PKG_USING_GUIENGINE
    do
    {
        result = rtgui_server_post_event(&emouse.parent, sizeof(emouse));
        if (result != RT_EOK)
        {
            rt_thread_delay(RT_TICK_PER_SECOND / TOUCH_SAMPLE_HZ);
        }
    }
    while (result != RT_EOK);
#else
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
#endif

    TPDEBUG("[TP] touch up [%d, %d]\n", emouse.x, emouse.y);
#endif
}

static void touch_run(void* parameter)
{
    rt_tick_t emouse_id = 0;
    struct touch_message msg;
    rt_slist_t *driver_list = NULL;
    struct touch_driver *current_driver = RT_NULL;

    i2c_bus = rt_i2c_bus_device_find(TOUCH_I2C_NAME);
    RT_ASSERT(i2c_bus);

    if(rt_device_open(&i2c_bus->parent, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        return;
    }

    rt_slist_for_each(driver_list, &_driver_list)
    {
        current_driver = (struct touch_driver *)driver_list;
        if(current_driver->probe(i2c_bus) == RT_TRUE)
        {
            break;
        }
        current_driver = RT_NULL;
    }

    if(current_driver == RT_NULL)
    {
        rt_kprintf("[TP] No touch pad or driver.\n");
        rt_device_close((rt_device_t)i2c_bus);

        return;
    }

    current_driver->ops->init(i2c_bus);

    while (1)
    {
        if (rt_sem_take(current_driver->isr_sem, RT_WAITING_FOREVER) != RT_EOK)
        {
            continue;
        }

        if (current_driver->ops->read_point(&msg) != RT_EOK)
        {
            continue;
        }

        switch (msg.event)
        {
        case TOUCH_EVENT_MOVE:
            post_motion_event(msg.x, msg.y, emouse_id);
            break;

        case TOUCH_EVENT_DOWN:
            emouse_id = rt_tick_get();
            post_down_event(msg.x, msg.y, emouse_id);
            break;

        case TOUCH_EVENT_UP:
            post_up_event(msg.x, msg.y, emouse_id);
            break;

        default:
            break;
        }

        rt_thread_delay(RT_TICK_PER_SECOND / TOUCH_SAMPLE_HZ);
    }
}

rt_err_t rt_touch_drivers_register(touch_driver_t drv)
{
    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(drv->ops   != RT_NULL);
    RT_ASSERT(drv->probe != RT_NULL);

    rt_slist_append(&_driver_list, &drv->list);

    return RT_EOK;
}

static int rt_touch_list_init(void)
{
    rt_slist_init(&_driver_list);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_touch_list_init);

static int rt_touch_init(void)
{
    rt_thread_t thread = RT_NULL;

    thread = rt_thread_create("touch", touch_run, RT_NULL, 2048, 28, 20);
    if(thread)
    {
        return rt_thread_startup(thread);
    }

    return -RT_ERROR;
}
INIT_APP_EXPORT(rt_touch_init);

int rt_touch_read(rt_uint16_t addr, void *cmd_buf, size_t cmd_len, void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = cmd_buf;
    msgs[0].len   = cmd_len;

    msgs[1].addr  = addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = data_buf;
    msgs[1].len   = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 2) == 2)
        return 0;
    else
        return -1;
}

int rt_touch_write(rt_uint16_t addr, void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[1];

    msgs[0].addr  = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = data_buf;
    msgs[0].len   = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 1) == 1)
        return 0;
    else
        return -1;
}
#endif
