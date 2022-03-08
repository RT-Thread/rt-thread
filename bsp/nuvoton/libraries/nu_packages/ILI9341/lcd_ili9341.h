/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#ifndef __LCD_ILI9341_H__
#define __LCD_ILI9341_H__

#include <rtconfig.h>
#include <rtdevice.h>

#define SET_RS              rt_pin_write(BOARD_USING_ILI9341_PIN_DC, 1)
#define CLR_RS              rt_pin_write(BOARD_USING_ILI9341_PIN_DC, 0)

#define SET_RST             rt_pin_write(BOARD_USING_ILI9341_PIN_RESET, 1)
#define CLR_RST             rt_pin_write(BOARD_USING_ILI9341_PIN_RESET, 0)

#define SET_BACKLIGHT_ON    rt_pin_write(BOARD_USING_ILI9341_PIN_BACKLIGHT, 1)
#define SET_BACKLIGHT_OFF   rt_pin_write(BOARD_USING_ILI9341_PIN_BACKLIGHT, 0)

//
// Physical display size
//
#if defined(NU_PKG_ILI9341_HORIZONTAL)
    #define XSIZE_PHYS 320
    #define YSIZE_PHYS 240
#else
    #define XSIZE_PHYS 240
    #define YSIZE_PHYS 320
#endif

int rt_hw_lcd_ili9341_init(void);
void ili9341_send_cmd(rt_uint8_t cmd);
void ili9341_send_cmd_parameter(rt_uint8_t data);
void ili9341_set_column(rt_uint16_t StartCol, rt_uint16_t EndCol);
void ili9341_set_page(rt_uint16_t StartPage, rt_uint16_t EndPage);
void ili9341_send_pixel_data(rt_uint16_t color);
void ili9341_lcd_get_pixel(char *color, int x, int y);
void ili9341_send_pixels(rt_uint16_t *pixels, int len);

#if defined(NU_PKG_USING_ILI9341_SPI)
    rt_err_t rt_hw_lcd_ili9341_spi_init(const char *spibusname, void *pvUserData);
#elif defined(NU_PKG_USING_ILI9341_EBI)
    rt_err_t rt_hw_lcd_ili9341_ebi_init(rt_uint32_t ebi_base);
#endif

#endif /* __LCD_ILI9341_H__ */
