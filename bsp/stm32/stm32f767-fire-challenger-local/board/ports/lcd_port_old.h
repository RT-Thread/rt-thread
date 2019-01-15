/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-22     greedyhao    first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

#include "drv_gpio.h"

#define LCD_WIDTH       ((uint16_t)800)
#define LCD_HEIGHT      ((uint16_t)480)
#define LCD_HFP         ((uint16_t)22)
#define LCD_VFP         ((uint16_t)22)
#define LCD_HBP         ((uint16_t)46)
#define LCD_VBP         ((uint16_t)23)
#define LCD_HSW         ((uint16_t)1)
#define LCD_VSW         ((uint16_t)1)
#define LCD_BL_PIN      GET_PIN(D,7)
#define LCD_DISP_PIN    GET_PIN(D,4)

#endif /* __LCD_PORT_H__ */
