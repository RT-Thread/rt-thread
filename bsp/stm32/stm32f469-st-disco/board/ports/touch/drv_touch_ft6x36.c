/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-07     liYony       the first version
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

/* Include the package header files you are using */
#include "ft6236.h"

#define BSP_TOUCH_I2C_BUS_NAME "i2c1"
#define BSP_TOUCH_I2C_RESET_PIN 119 /* PH.7 */

#ifdef PKG_USING_LVGL
#include <lvgl.h>
#endif /* PKG_USING_LVGL */

rt_device_t touch;

void touch_common_read(lv_indev_data_t *data)
{
    struct rt_touch_data *read_data;
    read_data = (struct rt_touch_data *)rt_calloc(1, sizeof(struct rt_touch_data));

    rt_device_read(touch, 0, read_data, 1);

    /* Since the origin of the LCD screen and the origin of the touch screen are
     * different, the parameters passed in here need to be simply converted. */
    data->point.x = read_data->y_coordinate;
    data->point.y = LCD_HEIGHT - read_data->x_coordinate;

    if (read_data->event == RT_TOUCH_EVENT_DOWN)
        data->state = LV_INDEV_STATE_PR;
    if (read_data->event == RT_TOUCH_EVENT_MOVE)
        data->state = LV_INDEV_STATE_PR;
    if (read_data->event == RT_TOUCH_EVENT_UP)
        data->state = LV_INDEV_STATE_REL;
}

int touch_ft6x36_init(void)
{
    struct rt_touch_config cfg;

    cfg.dev_name = BSP_TOUCH_I2C_BUS_NAME;
    rt_hw_ft6236_init("touch", &cfg, BSP_TOUCH_I2C_RESET_PIN);

    touch = rt_device_find("touch");
    rt_device_open(touch, RT_DEVICE_FLAG_RDONLY);

    return RT_EOK;
}
INIT_ENV_EXPORT(touch_ft6x36_init);

#endif /* BSP_USING_TOUCH_FT6X36 */
