/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-23     godmial      Refactor to conform to RT-Thread coding style.
 */

#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#ifdef BSP_USING_SDRAM
#include <sdram_port.h>
#endif /* BSP_USING_SDRAM */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* LCD resolution and pixel format */
#define LCD_WIDTH             800
#define LCD_HEIGHT            480
#define LCD_FB_BYTE_PER_PIXEL 1

/* Timing parameters for horizontal synchronization */
#define HORIZONTAL_SYNCHRONOUS_PULSE 10
#define HORIZONTAL_BACK_PORCH        150
#define ACTIVE_WIDTH                 800
#define HORIZONTAL_FRONT_PORCH       15

/* Timing parameters for vertical synchronization */
#define VERTICAL_SYNCHRONOUS_PULSE 10
#define VERTICAL_BACK_PORCH        140
#define ACTIVE_HEIGHT              480
#define VERTICAL_FRONT_PORCH       40

/* Framebuffer address in SDRAM */
#define LCD_FRAME_BUF_ADDR 0xC0000000 /* SDRAM address for LCD frame buffer */

/* Pen color definitions (RGB565) */
#define WHITE   0xFFFF /* White */
#define BLACK   0x0000 /* Black */
#define BLUE    0x001F /* Blue */
#define BRED    0xF81F /* Blue-Red */
#define GRED    0xFFE0 /* Green-Red */
#define GBLUE   0x07FF /* Green-Blue */
#define RED     0xF800 /* Red */
#define MAGENTA 0xF81F /* Magenta */
#define GREEN   0x07E0 /* Green */
#define CYAN    0x7FFF /* Cyan */
#define YELLOW  0xFFE0 /* Yellow */
#define BROWN   0xBC40 /* Brown */
#define BRRED   0xFC07 /* Brownish red */
#define GRAY    0x8430 /* Gray */

/* GUI color definitions */
#define DARKBLUE   0x01CF /* Dark blue */
#define LIGHTBLUE  0x7D7C /* Light blue */
#define GRAYBLUE   0x5458 /* Grayish blue */
#define LIGHTGREEN 0x841F /* Light green */
#define LGRAY      0xC618 /* Light gray (panel background) */
#define LGRAYBLUE  0xA651 /* Light gray-blue (layer color) */
#define LBBLUE     0x2B12 /* Light brown-blue (selected item reverse color) */

/* Frame buffer declaration based on compiler */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
/* Keil MDK Compiler */
extern uint16_t ltdc_lcd_framebuf0[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR)));
#elif defined(__GNUC__)
/* GCC Compiler (used by RT-Thread) */
extern uint16_t ltdc_lcd_framebuf0[10][10]; /* Dummy for GCC compilation */
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Configure the LCD display controller.
 *
 * @note     This function initializes display timing and output settings.
 */
void lcd_disp_config(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_LCD_H__ */
