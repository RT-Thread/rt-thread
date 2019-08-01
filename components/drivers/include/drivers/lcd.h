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

#ifdef __cplusplus
extern "C" {
#endif

/* lcd interface ops */
struct rt_lcd_bus_ops;

/* lcd interface device */
struct rt_lcd_bus
{
    struct rt_device parent;
    struct rt_lcd_bus_ops *ops;
};
typedef struct rt_lcd_bus *rt_lcd_bus_t;

struct rt_lcd_bus_config
{
    struct rt_device_graphic_info info;
    rt_uint32_t addr;
    rt_uint32_t channel;
    rt_uint32_t hbp;
    rt_uint32_t vbp;
    rt_uint32_t hfp;
    rt_uint32_t vfp;
    rt_uint32_t hsync;
    rt_uint32_t vsync;
};

/* lcd interface ops */
struct rt_lcd_bus_ops
{
    rt_err_t (*write_cmd) (struct rt_lcd_bus *device, void *cmd, rt_size_t len);
    rt_err_t (*write_data) (struct rt_lcd_bus *device, void *data, rt_size_t len);
    rt_err_t (*read_data) (struct rt_lcd_bus *device, rt_uint32_t reg, void *data);
    rt_err_t (*write_reg) (struct rt_lcd_bus *device, rt_uint32_t reg, rt_uint32_t data);
    rt_err_t (*config) (struct rt_lcd_bus *device, void *config);
};

/* lcd device */
struct rt_lcd_device
{
    struct rt_device                    parent;
    struct rt_lcd_bus                   *bus;
    struct rt_lcd_bus_config            config;
    void                                *user_data;
};
typedef struct rt_lcd_device *rt_lcd_t;

/* register lcd interface device */
rt_err_t rt_lcd_bus_register(struct rt_lcd_bus *device, const char *name, struct rt_lcd_bus_ops *ops, void *user_data);

/* lcd interface write cmd */
rt_err_t rt_lcd_write_cmd(struct rt_lcd_bus *device, void *cmd, rt_size_t len);

/* lcd interface write data */
rt_err_t rt_lcd_write_data(struct rt_lcd_bus *device, void *write_data, rt_size_t len);

/* lcd interface read data */
rt_uint32_t rt_lcd_read_data(struct rt_lcd_bus *device, rt_uint32_t reg);

/* lcd interface write reg */
rt_err_t rt_lcd_write_reg(struct rt_lcd_bus *device, rt_uint32_t reg, rt_uint32_t data);

/* lcd interface config */
rt_err_t rt_lcd_config(struct rt_lcd_bus *device, void *config);

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
