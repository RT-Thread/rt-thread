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
 * Program listing: This is a touch device usage routine
 * The routine exports touch_sample commands to the control terminal
 * Command invocation format: touch_sample
 * Program function: The terminal prints the coordinates of the touch point
*/
#include <rtdevice.h>
#include "drv_gt911.h"

static int touch_sample(void)
{
    gt911_input_t ctp_input;

    rt_device_t dev = rt_device_find("capt");

    RT_ASSERT(dev != RT_NULL);

    capt_t *capt = (capt_t*)dev->user_data;
    while(1)
    {
        gt911_ctp_read(&capt->gt911, &ctp_input);

        for (rt_uint8_t  i = 0; i < ctp_input.num_pos; i++)
        {
            /* Found track ID #0 */
            if (ctp_input.pos[i].id == 0)
            {
                rt_kprintf("x:%d, y:%d\r\n", capt->gt911.pos_y_max - ctp_input.pos[i].pos_y, ctp_input.pos[i].pos_x);
            }
        }

        rt_thread_mdelay(16);
    }

    return RT_EOK;
}

MSH_CMD_EXPORT(touch_sample, the capt touch test);
