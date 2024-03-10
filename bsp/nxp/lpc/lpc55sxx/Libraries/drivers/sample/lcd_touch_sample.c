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
 * Program Listing: This is an LCD device touch usage routine
 * The routine exports lcd_touch_sample commands to the control terminal
 * Command invocation format: lcd_touch_sample
 * Program functions: draw the trajectory of the touch on the screen and print the coordinates of the touch point on the terminal
*/
#include <rtdevice.h>
#include "drv_st7796.h"
#include "drv_gt911.h"

static void lcd_touch_sample(void)
{
    static rt_uint16_t white[319*2];
    rt_uint16_t green[4*4*2];
    st7796_t *lcd_obj = (st7796_t *)rt_device_find("lcd");
    rt_device_t dev = rt_device_find("capt");
    capt_t *capt = (capt_t*)dev->user_data;
    gt911_input_t ctp_input;

    for (rt_uint32_t i = 0; i < 319*2; i++)
    {
        white[i] = 0xffff;
    }
    for (rt_uint32_t i = 0; i < 4*4*2; i++)
    {
        green[i] = 0x07;
    }
    for (rt_uint16_t i = 0; i < 159; i++)
    {
        lcd_load(i, i, 0, 319, white);
    }
    for (rt_uint16_t i = 159; i < 318; i++)
    {
        lcd_load(i, i, 0, 319, white);
    }
    for (rt_uint16_t i = 318; i < 479; i++)
    {
        lcd_load(i, i, 0, 319, white);
    }

    while(1)
    {
        gt911_ctp_read(&capt->gt911, &ctp_input);
        for (rt_uint8_t  i = 0; i < ctp_input.num_pos; i++)
        {
            /* Found track ID #0 */
            if (ctp_input.pos[i].id == 0)
            {
                lcd_load(capt->gt911.pos_y_max - ctp_input.pos[i].pos_y, capt->gt911.pos_y_max - ctp_input.pos[i].pos_y+4, ctp_input.pos[i].pos_x, ctp_input.pos[i].pos_x+4, green);
                rt_kprintf("x:%d, y:%d\r\n", capt->gt911.pos_y_max - ctp_input.pos[i].pos_y , ctp_input.pos[i].pos_x);
            }
        }
    }
}
MSH_CMD_EXPORT(lcd_touch_sample, lcd sample);
