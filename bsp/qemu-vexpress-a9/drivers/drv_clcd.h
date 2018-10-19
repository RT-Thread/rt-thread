/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef DRV_CLCD_H__
#define DRV_CLCD_H__

#include <rtthread.h>

#ifndef BSP_LCD_WIDTH
#define BSP_LCD_WIDTH   640
#endif

#ifndef BSP_LCD_HEIGHT
#define BSP_LCD_HEIGHT  480
#endif

int drv_clcd_hw_init(void);

#endif
