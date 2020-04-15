/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-08     zylx         first version
 */

#ifndef __LCD_PORT_DSI_H__
#define __LCD_PORT_DSI_H__

#define LCD_HEIGHT              390
#define LCD_WIDTH               390
#define LCD_BITS_PER_PIXEL      24
#define LCD_PIXEL_FORMAT        RTGRAPHIC_PIXEL_FORMAT_ARGB888
#define LCD_DSI_BUF_SIZE        608400
#define LCD_DSI_BUF_SIZE_ROUND  365040

#define LAYER_ADDRESS           GFXMMU_VIRTUAL_BUFFER0_BASE
#define BRIGHTNESS_MIN          50
#define BRIGHTNESS_NORMAL       200

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO_NUM         GET_PIN(B, 14)

#endif /* __LCD_PORT_DSI_H__ */
