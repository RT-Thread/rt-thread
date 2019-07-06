/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli      the first version
 */

#ifndef __LCD_H_
#define __LCD_H_

#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_LCD_DISPLAY_TYPE_FRAMEBUFFER                   (0x00)
#define RT_LCD_DISPLAT_TYPE_PIXEL                         (0x01)

#define RT_LCD_BACKLIGHT_TYPE_PIN                         (0x00)
#define RT_LCD_BACKLIGHT_TYPE_PWM                         (0x01)

#define RT_LCD_DIRECTION_HORIZON                          (0x00)
#define RT_LCD_DIRECTION_VERTIAL                          (0x01)

/**
 * LCD interface sections
 */
struct rt_lcd_intf;
struct rt_lcd_intf_ops
{
    rt_err_t (*wtire_cmd) (struct rt_lcd_intf *device, rt_uint16_t cmd);
    rt_err_t (*write_data) (struct rt_lcd_intf *device, rt_uint16_t write_data);
    rt_err_t (*read_data) (struct rt_lcd_intf *device, rt_uint16_t reg, rt_uint16_t *read_data);
    rt_err_t (*write_reg) (struct rt_lcd_intf *device, rt_uint16_t reg, rt_uint16_t write_data);
};

struct rt_lcd_intf
{
    struct rt_device parent;
    struct rt_lcd_intf_ops *ops;
};
typedef struct rt_lcd_intf *rt_lcd_intf_t;

rt_err_t rt_lcd_intf_register(struct rt_lcd_intf *intf, const char *name, struct rt_lcd_intf_ops *ops, void *user_data);
rt_err_t rt_lcd_intf_write_cmd(struct rt_lcd_intf *device, rt_uint16_t cmd);
rt_err_t rt_lcd_intf_write_data(struct rt_lcd_intf *device, rt_uint16_t write_data);
rt_uint16_t rt_lcd_intf_read_data(struct rt_lcd_intf *device, rt_uint16_t reg);
rt_err_t rt_lcd_intf_write_reg(struct rt_lcd_intf *device, rt_uint16_t reg, rt_uint16_t write_data);

/**
 * LCD device sections
 */
struct rt_lcd_hw_info
{
    rt_uint8_t  dir;
    rt_uint8_t  lcd_type;
    rt_uint8_t  bl_type;
    rt_uint16_t id;
    rt_base_t   bl_pin;
    void        *user_data;
};

struct rt_lcd_config
{
    struct rt_lcd_hw_info hw_info;
    struct rt_device_graphic_info gra_info;
    char  *dev_name;
};

struct rt_lcd_device
{
    struct rt_device                    parent;
    struct rt_lcd_intf                  *intf;
    struct rt_lcd_config                config;
    struct rt_semaphore                 lcd_lock;
    struct rt_lcd_device_ops            *ops;
};
typedef struct rt_lcd_device *rt_lcd_t;

struct rt_lcd_device_ops
{
    rt_err_t (*lcd_control)(struct rt_lcd_device *lcd, int cmd, void *arg);
};

int rt_lcd_device_register(rt_lcd_t      lcd,
                           const char    *name,
                           rt_uint16_t   flag,
                           void          *data);

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H_ */
