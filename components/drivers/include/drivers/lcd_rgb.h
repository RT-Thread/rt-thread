/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-31     tyustli      the first version
 */

#ifndef _LCD_RGB_H_
#define _LCD_RGB_H_

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* lcd rgb interface ops */
struct rt_lcd_rgb_ops;

struct rt_lcd_rgb_config
{
    struct rt_device_graphic_info info;
    rt_uint32_t hbp;
    rt_uint32_t vbp;
    rt_uint32_t hfp;
    rt_uint32_t vfp;
    rt_uint32_t hsync;
    rt_uint32_t vsync;
};

struct rt_lcd_rgb
{
    struct rt_device parent;
    struct rt_lcd_rgb_config rgb_config;
    struct rt_lcd_rgb_ops *ops;
};
typedef struct rt_lcd_rgb *rt_lcd_rgb_t;

/* lcd rgb interface ops */
struct rt_lcd_rgb_ops
{
    rt_err_t (*config) (struct rt_lcd_rgb *device, void *config);
};


/* lcd rgb interface device register */
rt_err_t rt_lcd_rgb_register(struct rt_lcd_rgb *device, const char *name, struct rt_lcd_rgb_ops *ops, void *user_data);

/* lcd rgb interface device config */
rt_err_t rt_lcd_rgb_config(struct rt_lcd_rgb *device, void *config);

#ifdef __cplusplus
}
#endif

#endif /* _LCD_RGB_H_ */

/****************** end of file *******************/
