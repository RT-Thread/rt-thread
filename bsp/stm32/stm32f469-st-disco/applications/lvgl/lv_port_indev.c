/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-07     liYony       The first version (FT6336)
 * 2022-07-08     liYony       Add FT6206
 */
#include <lvgl.h>
#include <rtdevice.h>
#include <lcd_port.h>

#define DBG_TAG    "LVGL.port.indev"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/* Add the include file of the package you are using */
#ifdef BSP_USING_TOUCH_FT6X36
#include <ft6236.h>
#elif defined(BSP_USING_TOUCH_FT6206)
#include <ft6206.h>
#endif /* BSP_USING_TOUCH_FT6X36 */

/* Touch chip connection information */
#define BSP_TOUCH_I2C_BUS_NAME      "i2c1"
#define BSP_TOUCH_I2C_RESET_PIN      119 /* PH.7 */
/* RT-Thread touch device name */
#define TOUCH_DEV_NAME "touch"

lv_indev_t * touch_indev;
rt_device_t touch_dev;
struct rt_touch_data *read_data;

static void input_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    rt_device_read(touch_dev, 0, read_data, 1);

    if (read_data->event == RT_TOUCH_EVENT_NONE)
        return;

    /* Since the origin of the LCD screen and the origin of the touch screen are
     * different, the parameters passed in here need to be simply converted. */
#ifdef BSP_USING_TOUCH_FT6X36
    data->point.x = read_data->y_coordinate;
    data->point.y = LCD_HEIGHT - read_data->x_coordinate;
#elif defined(BSP_USING_TOUCH_FT6206)
    data->point.x = read_data->x_coordinate;
    data->point.y = LCD_HEIGHT - read_data->y_coordinate;
#endif /* BSP_USING_TOUCH_FT6X36 */

    if (read_data->event == RT_TOUCH_EVENT_DOWN)
        data->state = LV_INDEV_STATE_PR;
    if (read_data->event == RT_TOUCH_EVENT_MOVE)
        data->state = LV_INDEV_STATE_PR;
    if (read_data->event == RT_TOUCH_EVENT_UP)
        data->state = LV_INDEV_STATE_REL;
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

static int lv_hw_touch_init(void)
{
    struct rt_touch_config cfg;

    cfg.dev_name = BSP_TOUCH_I2C_BUS_NAME;
#ifdef BSP_USING_TOUCH_FT6X36
    rt_hw_ft6236_init(TOUCH_DEV_NAME, &cfg, BSP_TOUCH_I2C_RESET_PIN);
#elif defined(BSP_USING_TOUCH_FT6206)
    rt_hw_ft6206_init(TOUCH_DEV_NAME, &cfg);
#endif /* BSP_USING_TOUCH_FT6X36 */

    touch_dev = rt_device_find(TOUCH_DEV_NAME);
    if (rt_device_open(touch_dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        LOG_E("Can't open touch device:%s", TOUCH_DEV_NAME);
        return -RT_ERROR;
    }

    read_data = (struct rt_touch_data *)rt_calloc(1, sizeof(struct rt_touch_data));

    return RT_EOK;
}

INIT_COMPONENT_EXPORT(lv_hw_touch_init);
