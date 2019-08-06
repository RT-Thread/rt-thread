/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-31     tyustli      the first version
 */

#ifndef __LCD_H_
#define __LCD_H_

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* lcd device ops */
struct rt_lcd_ops;

/* lcd device */
struct rt_lcd_device
{
    struct rt_device                    parent;
    struct rt_lcd_mcu                   *mcu;
    struct rt_lcd_rgb                   *rgb;
    struct rt_lcd_ops                   *ops;
    void                                *user_data;
};
typedef struct rt_lcd_device *rt_lcd_t;

/* lcd device ops */
struct rt_lcd_ops
{
    rt_err_t (*init) (struct rt_lcd_device *device);
    rt_err_t (*control) (struct rt_lcd_device *device, int cmd, void *args);
};

/* lcd device register */
rt_err_t rt_lcd_device_register(struct rt_lcd_device *device, const char *name, struct rt_lcd_ops *ops, void *user_data);

/*
 * the following API is for pixel device to draw a point/picture
 */

/* set a point pixel*/
rt_err_t rt_set_pixel(struct rt_lcd_device *device, const char *pixel, int x, int y);

/* get a point pixel*/
rt_err_t rt_get_pixel(struct rt_lcd_device *device, char *pixel, int x, int y);

/* draw a horizonal line */
rt_err_t rt_draw_hline(struct rt_lcd_device *device, const char *pixel, int x1, int x2, int y);

/* draw a vertical */
rt_err_t rt_draw_vline(struct rt_lcd_device *device, const char *pixel, int x, int y1, int y2);

/* draw a blit line */
rt_err_t rt_blit_line(struct rt_lcd_device *device, const char *pixel, int x, int y, rt_size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H_ */

/****************** end of file *******************/
