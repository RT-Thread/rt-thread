/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-07     liYony       The first version
 */
#include <lvgl.h>
#include <rtdevice.h>

#include <lcd_port.h>

lv_indev_t *touch_indev;

static void input_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    /* You must create the drv_touch_xxx.c file in the board/ports/touch directory
     * according to your own touch driver, and implement "touch_common_read()" */
    extern void touch_common_read(lv_indev_data_t * data);
    touch_common_read(data);
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = input_read;

    /*Register the driver in LVGL and save the created input device object*/
    touch_indev = lv_indev_drv_register(&indev_drv);
}
