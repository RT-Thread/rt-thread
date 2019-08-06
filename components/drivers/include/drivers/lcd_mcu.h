/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-31     tyustli      the first version
 */

#ifndef _LCD_MCU_H_
#define _LCD_MCU_H_

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* lcd mcu interface ops */
struct rt_lcd_mcu_ops;

/* lcd mcu interface config */
struct rt_lcd_mcu_config
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

/* lcd mcu interface device */
struct rt_lcd_mcu
{
    struct rt_device parent;
    struct rt_lcd_mcu_config mcu_config;
    struct rt_lcd_mcu_ops *ops;
};
typedef struct rt_lcd_mcu *rt_lcd_mcu_t;

/* lcd mcu interface ops */
struct rt_lcd_mcu_ops
{
    rt_err_t (*write_cmd) (struct rt_lcd_mcu *device, void *cmd, rt_size_t len);
    rt_err_t (*write_data) (struct rt_lcd_mcu *device, void *data, rt_size_t len);
    rt_err_t (*read_data) (struct rt_lcd_mcu *device, rt_uint32_t reg, void *data);
    rt_err_t (*write_reg) (struct rt_lcd_mcu *device, rt_uint32_t reg, rt_uint32_t data);
    rt_err_t (*config) (struct rt_lcd_mcu *device, void *config);
};

/* lcd mcu interface device register */
rt_err_t rt_lcd_mcu_register(struct rt_lcd_mcu *device, const char *name, struct rt_lcd_mcu_ops *ops, void *user_data);

/* lcd mcu interface write cmd */
rt_err_t rt_lcd_write_cmd(struct rt_lcd_mcu *device, void *cmd, rt_size_t len);

/* lcd mcu interface write data */
rt_err_t rt_lcd_write_data(struct rt_lcd_mcu *device, void *write_data, rt_size_t len);

/* lcd mcu interface read data */
rt_uint32_t rt_lcd_read_data(struct rt_lcd_mcu *device, rt_uint32_t reg);

/* lcd mcu interface write reg */
rt_err_t rt_lcd_write_reg(struct rt_lcd_mcu *device, rt_uint32_t reg, rt_uint32_t data);

/* lcd mcu interface config */
rt_err_t rt_lcd_mcu_config(struct rt_lcd_mcu *device, void *config);

#ifdef __cplusplus
}
#endif

#endif /* _LCD_MCU_H_ */

/****************** end of file *******************/
