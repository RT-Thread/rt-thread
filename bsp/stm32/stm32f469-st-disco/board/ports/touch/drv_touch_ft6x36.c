/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     solar        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "touch.h"
#include "lcd_port.h"
#include "drv_common.h"

#define DBG_TAG "ft6236"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#ifdef BSP_USING_TOUCH_FT6X36

#include "ft6236.h"

#define BSP_TOUCH_I2C_BUS_NAME "i2c1"
#define BSP_TOUCH_I2C_RESET_PIN 119 /* PH.7 */

#ifdef PKG_USING_LVGL
#include <lvgl.h>
extern void lv_port_indev_input(rt_int16_t x, rt_int16_t y, lv_indev_state_t state);
#endif /* PKG_USING_LVGL */

rt_thread_t ft6236_thread;
rt_device_t touch;

void ft6236_thread_entry(void *parameter)
{
    struct rt_touch_data *read_data;

    read_data = (struct rt_touch_data *)rt_calloc(1, sizeof(struct rt_touch_data));

    while (1)
    {
        rt_device_read(touch, 0, read_data, 1);
#ifdef PKG_USING_LVGL
        /* Since the origin of the LCD screen and the origin of the touch screen are
         * different, the parameters passed in here need to be simply converted. */
        if (read_data->event == RT_TOUCH_EVENT_DOWN)
            lv_port_indev_input(read_data->y_coordinate, read_data->x_coordinate, LV_INDEV_STATE_PR);

        if (read_data->event == RT_TOUCH_EVENT_MOVE)
            lv_port_indev_input(read_data->y_coordinate, read_data->x_coordinate, LV_INDEV_STATE_PR);

        if (read_data->event == RT_TOUCH_EVENT_UP)
            lv_port_indev_input(read_data->y_coordinate, read_data->x_coordinate, LV_INDEV_STATE_REL);
#endif /* PKG_USING_LVGL */
        if (read_data->event != RT_TOUCH_EVENT_NONE)
            LOG_I("LCD point x: %03d y: %03d", read_data->y_coordinate, LCD_HEIGHT - read_data->x_coordinate);
        rt_thread_delay(10);
    }
}

int ft6236_for_lvgl(void)
{
    struct rt_touch_config cfg;

    cfg.dev_name = BSP_TOUCH_I2C_BUS_NAME;
    rt_hw_ft6236_init("touch", &cfg, BSP_TOUCH_I2C_RESET_PIN);

    touch = rt_device_find("touch");
    rt_device_open(touch, RT_DEVICE_FLAG_RDONLY);

    ft6236_thread = rt_thread_create("touch", ft6236_thread_entry, RT_NULL, 1024, 10, 20);
    if (ft6236_thread == RT_NULL)
    {
        LOG_D("create ft6236 thread err");

        return -RT_ENOMEM;
    }
    rt_thread_startup(ft6236_thread);

    return RT_EOK;
}
INIT_ENV_EXPORT(ft6236_for_lvgl);

#endif /* BSP_USING_TOUCH_FT6X36 */
