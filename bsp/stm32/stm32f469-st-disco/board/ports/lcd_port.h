/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2018-07-28     liu2guang      the first version for STM32F469NI-Discovery.
 */

#ifndef __DRV_LCD_H_
#define __DRV_LCD_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define  LCD_WIDTH    (800U)
#define  LCD_HEIGHT   (480U)

#define  LCD_HSYNC    (1U)
#define  LCD_HBP      (15U)
#define  LCD_HFP      (16U)
#define  LCD_VSYNC    (2U)
#define  LCD_VBP      (34U)
#define  LCD_VFP      (34U)

#endif
