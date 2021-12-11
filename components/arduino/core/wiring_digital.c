/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#include <Arduino.h>
#include "wiring_private.h"

#define DBG_TAG    "Arduino"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

void pinMode(uint8_t pin, uint8_t mode)
{
    rt_base_t rt_mode;

    if(mode == INPUT)
    {
        rt_mode = PIN_MODE_INPUT;
    }
    else if(mode == INPUT_PULLUP)
    {
        rt_mode = PIN_MODE_INPUT_PULLUP;
    }
    else if(mode == OUTPUT)
    {
        rt_mode = PIN_MODE_OUTPUT;
    }
    else
    {
        return;
    }

    rt_pin_mode(pin_map_table[pin].rt_pin, rt_mode);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    rt_base_t rt_val;

    if(val == HIGH)
    {
        rt_val = PIN_HIGH;
    }
    else if(val == LOW)
    {
        rt_val = PIN_LOW;
    }
    else
    {
        return;
    }

    rt_pin_write(pin_map_table[pin].rt_pin, rt_val);
}

int digitalRead(uint8_t pin)
{
    return (rt_pin_read(pin_map_table[pin].rt_pin) == PIN_HIGH)? HIGH : LOW;
}
