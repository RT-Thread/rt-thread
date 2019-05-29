/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-30     flaybreak    add usb port file
 */

#include <board.h>

#define USB_SW_PIN    GET_PIN(B, 5)

int usb_otg_switch(void)
{
    rt_pin_mode(USB_SW_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(USB_SW_PIN, PIN_HIGH);

    return 0;
}
INIT_PREV_EXPORT(usb_otg_switch);
