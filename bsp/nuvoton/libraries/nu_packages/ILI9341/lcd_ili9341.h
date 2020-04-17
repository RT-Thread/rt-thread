/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#define XSIZE_PHYS 240
#define YSIZE_PHYS 320

int rt_hw_lcd_ili9341_init(void);
void ili9341_send_cmd(rt_uint8_t cmd);
void ili9341_send_cmd_parameter(rt_uint8_t data);
void ili9341_set_column(rt_uint16_t StartCol, rt_uint16_t EndCol);
void ili9341_set_page(rt_uint16_t StartPage, rt_uint16_t EndPage);
void ili9341_send_pixel_data(rt_uint16_t color);
void ili9341_lcd_get_pixel(char *color, int x, int y);

#if defined(NU_PKG_USING_ILI9341_SPI)
    rt_err_t rt_hw_lcd_ili9341_spi_init(const char *spibusname);
#elif defined(NU_PKG_USING_ILI9341_EBI)
    rt_err_t rt_hw_lcd_ili9341_ebi_init(rt_uint32_t ebi_base);
#endif

#endif /* __LCD_ILI9341_H__ */
