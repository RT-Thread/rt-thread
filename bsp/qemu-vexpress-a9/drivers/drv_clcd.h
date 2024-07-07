/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */
#ifndef DRV_CLCD_H__
#define DRV_CLCD_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifndef BSP_LCD_WIDTH
#define BSP_LCD_WIDTH   640
#endif

#ifndef BSP_LCD_HEIGHT
#define BSP_LCD_HEIGHT  480
#endif

int drv_clcd_hw_init(void);

#endif
