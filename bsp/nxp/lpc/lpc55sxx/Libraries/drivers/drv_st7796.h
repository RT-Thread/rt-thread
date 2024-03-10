/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-23     Chushicheng  the first version.
 */

#ifndef DRV_ST7796_H__
#define DRV_ST7796_H__

#include <rtdevice.h>

#define LCD_DEVICE_NAME  "st7796"
typedef enum
{
    ST7796_DIR_0   = 0x08U,
    ST7796_DIR_90  = 0x68U,
    ST7796_DIR_180 = 0xC8U,
    ST7796_DIR_270 = 0xA8U,
} st7796_direction_t;

typedef enum
{
    ST7796_RGB444 = 3,
    ST7796_RGB565 = 5,
    ST7796_RGB666 = 6,
    ST7796_RGB888 = 7
} st7796_pixfmt_t;

typedef struct
{
    rt_err_t (*reset_cb)(void *handle);
    rt_err_t (*backlight_cb)(void *handle, rt_uint8_t on);
    rt_err_t (*write_cmd_cb)(void *handle, rt_uint8_t *cmd, rt_uint8_t len);
    rt_err_t (*write_data_cb)(void *handle, void *data, rt_uint32_t len);
} st7796_cb_t;

typedef struct
{
    st7796_direction_t direction;
    st7796_pixfmt_t pix_fmt;
    rt_uint8_t inversion;
    rt_uint8_t bgr_mode;
    uint8_t mirrored;
} st7796_config_t;

typedef struct
{
    void *user_data;
    st7796_cb_t cb;
    st7796_config_t config;
} st7796_lcd_t;

typedef struct
{
    struct rt_device            parent;
    st7796_lcd_t                st7796;
    struct rt_spi_device        *spi_dev;
} st7796_t;

void lcd_load(rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end, void *data);
int drv_st7796_init(void);

#endif /* DRV_ST7796_H__ */

