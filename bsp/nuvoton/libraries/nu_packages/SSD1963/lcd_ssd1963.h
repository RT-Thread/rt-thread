/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-2-23       Wayne        First version
*
******************************************************************************/

#ifndef __LCD_SSD1963_H__
#define __LCD_SSD1963_H__

#include <rtconfig.h>
#include <rtdevice.h>

#define SET_RS              rt_pin_write(BOARD_USING_SSD1963_PIN_DC, 1)
#define CLR_RS              rt_pin_write(BOARD_USING_SSD1963_PIN_DC, 0)

#define SET_RST             rt_pin_write(BOARD_USING_SSD1963_PIN_RESET, 1)
#define CLR_RST             rt_pin_write(BOARD_USING_SSD1963_PIN_RESET, 0)

#define SET_BACKLIGHT_ON    rt_pin_write(BOARD_USING_SSD1963_PIN_BACKLIGHT, 1)
#define SET_BACKLIGHT_OFF   rt_pin_write(BOARD_USING_SSD1963_PIN_BACKLIGHT, 0)

#define SET_DISP_ON         rt_pin_write(BOARD_USING_SSD1963_PIN_DISPLAY, 1)
#define SET_DISP_OFF        rt_pin_write(BOARD_USING_SSD1963_PIN_DISPLAY, 0)

//
// Physical display size
//
//#if defined(NU_PKG_SSD1963_HORIZONTAL)
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272
//#else
//    #define XSIZE_PHYS 272
//    #define YSIZE_PHYS 480
//#endif

int rt_hw_lcd_ssd1963_init(void);
void ssd1963_send_cmd(rt_uint8_t cmd);
void ssd1963_send_cmd_parameter(rt_uint8_t data);
void ssd1963_set_column(rt_uint16_t StartCol, rt_uint16_t EndCol);
void ssd1963_set_page(rt_uint16_t StartPage, rt_uint16_t EndPage);
void ssd1963_send_pixel_data(rt_uint16_t color);
void ssd1963_lcd_get_pixel(char *color, int x, int y);
void ssd1963_send_pixels(rt_uint16_t *pixels, int len);

#if defined(NU_PKG_USING_SSD1963_EBI)
    rt_err_t rt_hw_lcd_ssd1963_ebi_init(rt_uint32_t ebi_base);
#endif

#endif /* __LCD_SSD1963_H__ */
