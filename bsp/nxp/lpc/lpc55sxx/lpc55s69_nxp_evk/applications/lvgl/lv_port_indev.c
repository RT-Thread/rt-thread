/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-30     Chushicheng  First version
 */
#include <lvgl.h>
#include <rtdevice.h>
#include "drv_gt911.h"

#define LCD_W    480
#define LCD_H    320

lv_indev_t *touch_indev;

static lv_indev_state_t last_state = LV_INDEV_STATE_REL;
static rt_int16_t last_x = 0;
static rt_int16_t last_y = 0;

static gt911_input_t ctp_input;
static capt_t *capt = RT_NULL;

static void input_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    gt911_ctp_read(&capt->gt911, &ctp_input);

    if (ctp_input.num_pos > 0)
    {
        last_x = 480 - ctp_input.pos[0].pos_y;
        last_y = ctp_input.pos[0].pos_x;
        last_state = LV_INDEV_STATE_PR;
    }
    else
    {
        last_state = LV_INDEV_STATE_REL;
    }
    data->point.x = last_x;
    data->point.y = last_y;
    data->state = last_state;
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    rt_device_t dev = rt_device_find("capt");
    RT_ASSERT(dev != RT_NULL);
    capt = (capt_t*)dev->user_data;

    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = input_read;

    /*Register the driver in LVGL and save the created input device object*/
    touch_indev = lv_indev_drv_register(&indev_drv);
}
