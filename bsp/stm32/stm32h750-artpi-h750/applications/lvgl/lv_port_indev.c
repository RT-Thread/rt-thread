/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-01     Rudy Lo      The first version
 */

#include <lvgl.h>
#include <stdbool.h>
#include <rtdevice.h>
#include <drv_gpio.h>

#include "ft6236.h"

#define TOUCH_DEVICE_NAME    "touch_ft"    /* Touch 设备名称 */
#define TOUCH_DEVICE_I2C_BUS "i2c2"        /* SCL -> PH15(127), SDA -> PH13(125) */
#define REST_PIN             GET_PIN(A, 3)

static rt_device_t touch_dev;             /* Touch 设备句柄 */
/* 根据设备名称查找 Touch 设备，获取设备句柄 */

static rt_int16_t last_x = 0;
static rt_int16_t last_y = 0;

#define USER_BUTTON_PIN        GET_PIN(H, 4)  /* Reserve for LV_INDEV_TYPE_BUTTON */

/*
struct rt_touch_data
{
    rt_uint8_t          event;                 // The touch event of the data
    rt_uint8_t          track_id;              // Track id of point
    rt_uint8_t          width;                 // Point of width
    rt_uint16_t         x_coordinate;          // Point of x coordinate
    rt_uint16_t         y_coordinate;          // Point of y coordinate
    rt_tick_t           timestamp;             // The timestamp when the data was received
};
*/
static bool touchpad_is_pressed(void)
{
    struct rt_touch_data *read_data;
    read_data = (struct rt_touch_data *)rt_malloc(sizeof(struct rt_touch_data));

    if (rt_device_read(touch_dev, 0, read_data, 1) == 1)
    {
        if (read_data->event == RT_TOUCH_EVENT_DOWN) {
            last_x = read_data->x_coordinate;
            last_y = read_data->y_coordinate;
        }
    }
}

static void touchpad_get_xy(rt_int16_t *x, rt_int16_t *y)
{
    *x = last_x;
    *y = last_y;
}

static void touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    /*`touchpad_is_pressed` and `touchpad_get_xy` needs to be implemented by you*/
    if(touchpad_is_pressed()) {
        data->state = LV_INDEV_STATE_PRESSED;
        touchpad_get_xy(&data->point.x, &data->point.y);
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

lv_indev_t * touch_indev;

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;         /* Descriptor of a input device driver */
    lv_indev_drv_init(&indev_drv);           /* Basic initialization */
    indev_drv.type = LV_INDEV_TYPE_POINTER;  /* Touch pad is a pointer-like device */
    indev_drv.read_cb = touchpad_read;       /* Set your driver function */

    /* Register the driver in LVGL and save the created input device object */
    touch_indev = lv_indev_drv_register(&indev_drv);

    /* Register touch device */
    struct rt_touch_config config;
    config.dev_name = TOUCH_DEVICE_I2C_BUS;
    rt_hw_ft6236_init(TOUCH_DEVICE_NAME, &config, REST_PIN);

    touch_dev = rt_device_find(TOUCH_DEVICE_NAME);

    if (!rt_device_open(touch_dev, RT_DEVICE_FLAG_RDONLY)) {
        struct rt_touch_info info;
        rt_device_control(touch_dev, RT_TOUCH_CTRL_GET_INFO, &info);
        rt_kprintf("type       :%d", info.type);
        rt_kprintf("vendor     :%s", info.vendor);
        rt_kprintf("point_num  :%d", info.point_num);
        rt_kprintf("range_x    :%d", info.range_x);
        rt_kprintf("range_y    :%d", info.range_y);
    } else {
        rt_kprintf("open touch device failed.\n");
    }
}


/* f469 */
#if 0
static lv_indev_state_t last_state = LV_INDEV_STATE_REL;
static rt_int16_t last_x = 0;
static rt_int16_t last_y = 0;

static void input_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    data->point.x = last_x;
    data->point.y = last_y;
    data->state = last_state;
}

void lv_port_indev_input(rt_int16_t x, rt_int16_t y, lv_indev_state_t state)
{
    last_state = state;
    last_x = x;
    last_y = LCD_H - y;
}

lv_indev_t * button_indev;

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = input_read;

    /*Register the driver in LVGL and save the created input device object*/
    button_indev = lv_indev_drv_register(&indev_drv);
}
#endif
