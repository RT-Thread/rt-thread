/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-26     Chushicheng  the first version
 */
/*
 * Program Checklist: This is an LCD device usage routine
 * The routine exports lcd_sample commands to the control terminal
 * Command invocation format: lcd_sample
 * Program function: Full screen refresh display
*/
#include <rtdevice.h>
#include "drv_st7796.h"

static void lcd_sample(void)
{
    static rt_uint16_t orange[319*2];
    static rt_uint16_t green[319*2];
    static rt_uint16_t blue[319*2];
    st7796_t *lcd_obj = (st7796_t *)rt_device_find("lcd");

    for (rt_uint32_t i = 0; i < 319*2; i++)
    {
        orange[i] = 0xFD;
    }
    for (rt_uint32_t i = 0; i < 319*2; i++)
    {
        green[i] = 0x07;
    }
    for (rt_uint32_t i = 0; i < 319*2; i++)
    {
        blue[i] = 0xFF1F;
    }

    while (1)
    {
        for (rt_uint16_t i = 0; i < 159; i++)
        {
            lcd_load(i, i, 0, 319, orange);
        }
        for (rt_uint16_t i = 159; i < 318; i++)
        {
            lcd_load(i, i, 0, 319, blue);
        }
        for (rt_uint16_t i = 318; i < 479; i++)
        {
            lcd_load(i, i, 0, 319, green);
        }

        for (rt_uint16_t i = 479; i > 318; i--)
        {
            lcd_load(i, i, 0, 319, blue);
        }
        for (rt_uint16_t i = 318; i > 159; i--)
        {
            lcd_load(i, i, 0, 319, orange);
        }
        for (rt_uint16_t i = 159; i > 0; i--)
        {
            lcd_load(i, i, 0, 319, green);
        }
    }
}
MSH_CMD_EXPORT(lcd_sample, lcd sample);
