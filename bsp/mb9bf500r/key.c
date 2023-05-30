/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date                Author       Notes
 * 2011-03-03          lgnq
 */

#include <rtthread.h>
#include "key.h"
#include "lcd.h"

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

static void key_io_init(void)
{
    /*Select CPIO function*/
    KEY_PFR &= ~KEY_MASK;
    /*Set CPIO Pull-Up function*/
    KEY_PCR |= KEY_MASK;
    /*Make button pins inputs*/
    KEY_DDR &= ~KEY_MASK;
}

static void key_thread_entry(void *parameter)
{
#ifdef RT_USING_RTGUI
    rt_time_t next_delay;
    rt_uint8_t i;

    struct rtgui_event_kbd kbd_event;

    key_io_init();

    /* init keyboard event */
    RTGUI_EVENT_KBD_INIT(&kbd_event);
    kbd_event.mod  = RTGUI_KMOD_NONE;
    kbd_event.unicode = 0;

    while (1)
    {
        next_delay = RT_TICK_PER_SECOND/10;
        kbd_event.key = RTGUIK_UNKNOWN;
        kbd_event.type = RTGUI_KEYDOWN;

        if (KEY_ENTER_GETVALUE() == 0 )
        {
            for(i=0; ; i++)
            {
                rt_thread_delay( next_delay );
                if (KEY_ENTER_GETVALUE() == 0)
                {
                    if (i>=4)
                    {
                        /* HOME key */
                        kbd_event.key  = RTGUIK_HOME;
                        next_delay = RT_TICK_PER_SECOND/5;
                        break;
                    }
                }
                else
                {
                    kbd_event.key  = RTGUIK_RETURN;
                    break;
                }
            }
        }

        if (KEY_DOWN_GETVALUE() == 0)
        {
            kbd_event.key  = RTGUIK_DOWN;
        }

        if (KEY_UP_GETVALUE() == 0)
        {
            kbd_event.key  = RTGUIK_UP;
        }

        if (KEY_RIGHT_GETVALUE() == 0)
        {
            kbd_event.key  = RTGUIK_RIGHT;
        }

        if (KEY_LEFT_GETVALUE() == 0)
        {
            kbd_event.key  = RTGUIK_LEFT;
        }

        if (kbd_event.key != RTGUIK_UNKNOWN)
        {
            /* post down event */
            rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
        }
        else
        {
            kbd_event.type = RTGUI_KEYUP;
            rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
        }
        /* wait next key press */
        rt_thread_delay(next_delay);
    }
#else
    extern struct rt_messagequeue mq;
    rt_time_t next_delay;
    struct lcd_msg msg;
    msg.type = KEY_MSG;

    key_io_init();

    while (1)
    {
        msg.key = NO_KEY;

        next_delay = RT_TICK_PER_SECOND/10;

        if (KEY_ENTER_GETVALUE() == 0 )
        {
            msg.key  = KEY_ENTER;
        }

        if (KEY_DOWN_GETVALUE() == 0)
        {
            msg.key  = KEY_DOWN;
        }

        if (KEY_UP_GETVALUE() == 0)
        {
            msg.key  = KEY_UP;
        }

        if (KEY_RIGHT_GETVALUE() == 0)
        {
            msg.key  = KEY_RIGHT;
        }

        if (KEY_LEFT_GETVALUE() == 0)
        {
            msg.key  = KEY_LEFT;
        }

        rt_mq_send(&mq, &msg, sizeof(msg));

        /* wait next key press */
        rt_thread_delay(next_delay);
    }
#endif
}

static rt_thread_t key_thread;
void rt_hw_key_init(void)
{
    key_thread = rt_thread_create("key", key_thread_entry, RT_NULL, 384, 28, 5);
    if (key_thread != RT_NULL)
        rt_thread_startup(key_thread);
}
