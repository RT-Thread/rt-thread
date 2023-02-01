/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-19     Magicoe      The first version for LPC55S6x, refered github.com/Guozhanxin/RTT-BeepPlayer-pkg
 */

#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include <rtthread.h>
#include <rtdevice.h>

#define MY_BUTTON_DOWN_MS        50
#define MY_BUTTON_HOLD_MS        700

#define MY_BUTTON_SCAN_SPACE_MS  20
#define MY_BUTTON_LIST_MAX       10

typedef void (*my_button_callback)(void*);

enum my_button_event
{
    BUTTON_EVENT_CLICK_DOWN,
    BUTTON_EVENT_CLICK_UP,
    BUTTON_EVENT_HOLD,
    BUTTON_EVENT_HOLD_CYC,
    BUTTON_EVENT_HOLD_UP,
    BUTTON_EVENT_NONE
};

struct my_button
{
    rt_uint8_t  press_logic_level;
    rt_uint16_t cnt;
    rt_uint16_t hold_cyc_period;
    rt_uint16_t pin;

    enum my_button_event event;

    my_button_callback cb;
};

int my_button_register(struct my_button *button);
int my_button_start(void);


#endif
