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

#ifndef __LCD_FSA506_H__
#define __LCD_FSA506_H__

#include <rtthread.h>
#include <rtdevice.h>

#define SET_RS              rt_pin_write(BOARD_USING_FSA506_PIN_DC, 1)
#define CLR_RS              rt_pin_write(BOARD_USING_FSA506_PIN_DC, 0)

#define SET_RST             rt_pin_write(BOARD_USING_FSA506_PIN_RESET, 1)
#define CLR_RST             rt_pin_write(BOARD_USING_FSA506_PIN_RESET, 0)

#define SET_BACKLIGHT_ON    rt_pin_write(BOARD_USING_FSA506_PIN_BACKLIGHT, 1)
#define SET_BACKLIGHT_OFF   rt_pin_write(BOARD_USING_FSA506_PIN_BACKLIGHT, 0)

//
// Physical display size
//
//#if defined(NU_PKG_FSA506_HORIZONTAL)
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272
//#else
//    #define XSIZE_PHYS 272
//    #define YSIZE_PHYS 480
//#endif

int rt_hw_lcd_fsa506_init(void);
void fsa506_send_cmd(rt_uint16_t cmd);
void fsa506_send_cmd_parameter(rt_uint16_t data);
void fsa506_send_cmd_done(void);
void fsa506_write_reg(rt_uint16_t cmd, rt_uint16_t data);
void fsa506_set_column(rt_uint16_t StartCol, rt_uint16_t EndCol);
void fsa506_set_page(rt_uint16_t StartPage, rt_uint16_t EndPage);
void fsa506_send_pixel_data(rt_uint16_t color);
void fsa506_lcd_get_pixel(char *color, int x, int y);
void fsa506_send_pixels(rt_uint16_t *pixels, int len);

#if defined(NU_PKG_USING_FSA506_EBI)
    rt_err_t rt_hw_lcd_fsa506_ebi_init(rt_uint32_t ebi_base);
#endif

#endif /* __LCD_FSA506_H__ */
