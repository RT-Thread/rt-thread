/*
 * File      : drv_gpio_keyboard.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

/*********************************************************************************************************
**   Include Files
*********************************************************************************************************/
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_gpio.h"
#include "board_key.h"

#ifdef RT_USING_AUDIO_PLAYER
#include <player_app.h>
#endif

#define KEY_DEBUG

#ifdef KEY_DEBUG
#define KEY_DBG(...) rt_kprintf("[KEY]"),rt_kprintf(__VA_ARGS__)
#else
#define KEY_DBG(...)
#endif

static keyboard_event_handler_t _handler = RT_NULL;


#if defined(BOARD_HALLEY2)
/* 4 keys
 * SW1          SW2         SW3         SW5
 * Vol-         Vol+        Play/Pause  Mode/Config
 * PA10         PA11        PB28        PB31
 */
static struct keyboard_io_def keyboard_io_tbl[] =
{
    //Vol-/Next Song
    {
      GPIO_PORT_A, GPIO_Pin_10 ,
      KEY_NEXT, KEY_VOLDEC, 
    },

    //Vol+/Prev Song
    {
      GPIO_PORT_A, GPIO_Pin_11 ,
      KEY_PREV, KEY_VOLINC, 
    },

    //Play_Pause
    {
      GPIO_PORT_B, GPIO_Pin_28 ,
      KEY_UNKNOWN, KEY_PLAY_PAUSE, 
    },

    //Mode/Config
    {
      GPIO_PORT_B, GPIO_Pin_31,
      KEY_CONFIG, KEY_NETWORK_MODE, 
    },
};
#elif defined(BOARD_HALLEY2_REALBOARD)
/* 6 keys
 * 11           12          21          22          31         32
 * ON/OFF       MODE        V+          V-          BT/MUTE    WIFI
 */
static struct keyboard_io_def keyboard_io_tbl[] =
{
    //ON/OFF
    {
        GPIO_PORT_B, GPIO_Pin_31,
        KEY_UNKNOWN, KEY_PWROFF,
    },
    //V+
    {
        GPIO_PORT_B, GPIO_Pin_25,
        KEY_UNKNOWN, KEY_VOLINC,
    },
    //V-
    {
        GPIO_PORT_B, GPIO_Pin_2,
        KEY_UNKNOWN, KEY_VOLDEC,
    },
    //BT/MUTE
    {
        GPIO_PORT_B, GPIO_Pin_3,
        KEY_SOURCE, KEY_MUTE,
    },
    //WIFI
    {
        GPIO_PORT_B, GPIO_Pin_28,
        KEY_UNKNOWN, KEY_CONFIG,
    },
};
#elif defined(BOARD_HALLEY2_REALBOARD_V2)
struct keyboard_io_def keyboard_io_tbl[] =
{
    //ON/OFF
    {
        GPIO_PORT_D, GPIO_Pin_0,
        KEY_UNKNOWN, KEY_UNKNOWN,
    },
    //V+
    {
        GPIO_PORT_B, GPIO_Pin_28,
        KEY_UNKNOWN, KEY_UNKNOWN,
    },
    //V-
    {
        GPIO_PORT_B, GPIO_Pin_31,
        KEY_UNKNOWN, KEY_UNKNOWN,
    },
    //WIFI config
    {
        GPIO_PORT_D, GPIO_Pin_2,
        KEY_UNKNOWN, KEY_UNKNOWN,
    },
};

#else
struct keyboard_io_def keyboard_io_tbl[] =
{
    //PWRKEY KEY
    {
        GPIO_PORT_B, GPIO_Pin_31,
        KEY_UNKNOWN, KEY_UNKNOWN
    },
};
#endif
#define CFG_MAX_KEY_NBR sizeof(keyboard_io_tbl)/sizeof(keyboard_io_tbl[0])

static struct rt_mailbox* _keyMb = RT_NULL;

void keyboard_irq_callback(void *param)
{
    KEY_DBG("%d\n", (int)param);
    if (_keyMb)
    {
        struct keyboard_io_def* key;
        int value = (int)param;

        key = &keyboard_io_tbl[value];
        if(rt_mb_send(_keyMb, (rt_uint32_t)param) == RT_EOK)
            gpio_mask_irq(key->port, key->pin);
    }
}

#define KEY_EVENT_DOWN      0x01
#define KEY_EVENT_HOLD      0x02
#define KEY_EVENT_UP        0x04

#define KEY_SCAN_STEP_TIME              10
#define KEY_SCAN_HOLD_THRESHOLD     2000

//Scan the single key
rt_uint8_t key_scan(struct keyboard_io_def *keyIO)
{
    static rt_uint8_t keyTrigger    = 0;
    static rt_uint8_t keyRelease    = 0;
    static rt_uint8_t keyHold       = 0;

    rt_uint8_t keyValue = 0;

    //elimination buffeting
    do
    {
        keyValue = gpio_get_value(keyIO->port,keyIO->pin);
        rt_thread_delay(rt_tick_from_millisecond(KEY_SCAN_STEP_TIME));
    }while(keyValue != gpio_get_value(keyIO->port,keyIO->pin));

    keyValue   ^= 0x01;
    keyTrigger  = keyValue &(keyValue ^ keyHold);
    keyRelease  = (keyValue ^ keyTrigger ^ keyHold);
    keyHold     = keyValue;

//  KEY_DBG("keyValue = %x\n,keyTrigger = %x\n,keyRelese = %x\n,keyHold = %x\n",keyValue,keyTrigger,keyRelease,keyHold);

    if(keyTrigger != 0)
        return KEY_EVENT_DOWN;
    else if(keyHold != 0)
        return KEY_EVENT_HOLD;

    return KEY_EVENT_UP;
}

void kbd_thread(void* parameter)
{
    int keyId;
    rt_uint8_t keyEvent;
    rt_uint8_t keyValue;
    rt_uint32_t keyHoldTime;
    _keyMb = rt_mb_create("key", 4, RT_IPC_FLAG_FIFO);

    while (1)
    {
        if(rt_mb_recv(_keyMb, (rt_ubase_t*)&keyId, RT_TICK_PER_SECOND) != RT_EOK)
        {
            //if no key pressed,check power key...
            keyId = 0;
        }
		
        {
            struct keyboard_io_def* key;

            // Check key ID
            if(keyId >= CFG_MAX_KEY_NBR)
            {
                rt_kprintf("keyID error\n");
                continue;
            }

            key = &keyboard_io_tbl[keyId];

            keyEvent = key_scan(key);
            /* No key input */
            if(keyEvent == KEY_EVENT_UP)
            {
                gpio_unmask_irq(key->port, key->pin);
                continue;
            }
            KEY_DBG("key %d down\n", keyId);

            //Wait for key RELEASE
            keyHoldTime = 0;
            do
            {
                keyEvent = key_scan(key);
                if(keyEvent == KEY_EVENT_HOLD)
                {
                    keyHoldTime += KEY_SCAN_STEP_TIME;

                    if(keyHoldTime > KEY_SCAN_HOLD_THRESHOLD)
                        break;
                }

            } while (keyEvent != KEY_EVENT_UP);
            KEY_DBG("key %d up,hold time = %dms\n", keyId,keyHoldTime);

            if(keyHoldTime > KEY_SCAN_HOLD_THRESHOLD)
                keyValue = key->longKey;
            else
                keyValue = key->shortKey;

            //send key event
            if (_handler) _handler(EVENT_KEY_DOWN | keyValue);

            //Wait for KEYUP
            while (keyEvent != KEY_EVENT_UP)
            {
                keyEvent = key_scan(key);
                rt_thread_delay(RT_TICK_PER_SECOND / 10);
            }

            if (_handler) _handler(EVENT_KEY_UP | keyValue);

            gpio_unmask_irq(key->port, key->pin);
        }
    }
}

void rt_hw_keyboard_set_handler(keyboard_event_handler_t handler)
{
    _handler = handler;
}

void rt_hw_keyboard_init(void)
{
    int i;
    rt_thread_t tid;

    tid = rt_thread_create("key", kbd_thread, RT_NULL, 2048, 16, 10);
    if (tid)
        rt_thread_startup(tid);

    /* initialize all IO for keyboard */
    for (i = 0; i < CFG_MAX_KEY_NBR; ++i)
    {
        gpio_set_func(keyboard_io_tbl[i].port,keyboard_io_tbl[i].pin,GPIO_INPUT_PULL | GPIO_INT_FE);

        gpio_set_irq_callback(keyboard_io_tbl[i].port,keyboard_io_tbl[i].pin,keyboard_irq_callback, (void*)i);

        gpio_unmask_irq(keyboard_io_tbl[i].port,keyboard_io_tbl[i].pin);
    }
}
