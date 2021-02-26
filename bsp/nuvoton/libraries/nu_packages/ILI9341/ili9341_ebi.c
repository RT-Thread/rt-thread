/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_ILI9341_EBI)

#include <lcd_ili9341.h>

#define ILI9341_ADDR_CMD  0x0
#define ILI9341_ADDR_DATA 0x0030000

#define ili9341_reg_write(u32RegAddr)   (*((volatile unsigned short *)(g_uint32_ili9341_base+(ILI9341_ADDR_CMD))) = (u32RegAddr))
#define ili9341_read_data()             (*((volatile unsigned short *)(g_uint32_ili9341_base+(ILI9341_ADDR_DATA))))
#define ili9341_write_data(u32Data)     (*((volatile unsigned short *)(g_uint32_ili9341_base+(ILI9341_ADDR_DATA))) = (u32Data))

static rt_uint32_t g_uint32_ili9341_base = 0;

void ili9341_send_cmd(rt_uint8_t cmd)
{
    CLR_RS;
    ili9341_reg_write(cmd);
    SET_RS;
}

void ili9341_send_cmd_parameter(rt_uint8_t data)
{
    ili9341_write_data(data);
}

void ili9341_send_pixel_data(rt_uint16_t color)
{
    ili9341_write_data(color);
}

void ili9341_send_pixels(rt_uint16_t *pixels, int len)
{
    int i = 0;
    int size = len / sizeof(rt_uint16_t);

    while (i < size)
        ili9341_write_data(pixels[i]);
}

void ili9341_set_column(uint16_t StartCol, uint16_t EndCol)
{
    ili9341_send_cmd(0x2A);
    ili9341_write_data((StartCol >> 8) & 0xFF);
    ili9341_write_data(StartCol & 0xFF);
    ili9341_write_data((EndCol >> 8) & 0xFF);
    ili9341_write_data(EndCol & 0xFF);
}

void ili9341_set_page(uint16_t StartPage, uint16_t EndPage)
{
    ili9341_send_cmd(0x2B);
    ili9341_write_data((StartPage >> 8) & 0xFF);
    ili9341_write_data(StartPage & 0xFF);
    ili9341_write_data((EndPage >> 8) & 0xFF);
    ili9341_write_data(EndPage & 0xFF);
}

void ili9341_lcd_get_pixel(char *color, int x, int y)
{
    rt_uint16_t red = 0;
    rt_uint16_t green = 0;
    rt_uint16_t blue = 0;

    if (x >= XSIZE_PHYS || y >= YSIZE_PHYS)
    {
        *(rt_uint16_t *)color = 0;
        return;
    }

    ili9341_set_column(x, x);
    ili9341_set_page(y, y);
    ili9341_send_cmd(0x2E);

    ili9341_read_data();           // Dummy
    red = ili9341_read_data();     // Red[4:0]@D15~D11
    blue = ili9341_read_data();    // Blue[4:0]@D15~D11
    green = ili9341_read_data();   // Green[5:0]@D15~D10

    //BGR565: B in High byte, R in low byte
    //*(rt_uint16_t *)color = (((blue >> 11) << 11) | ((green >> 10) << 5) | (red >> 11));

    //RGB565: R in High byte, B in low byte
    *(rt_uint16_t *)color = (((red >> 11) << 11) | ((green >> 10) << 5) | (blue >> 11));
}

rt_err_t rt_hw_lcd_ili9341_ebi_init(rt_uint32_t ili9341_base)
{
    g_uint32_ili9341_base = ili9341_base;
    return RT_EOK;
}

#endif /* if defined(NU_PKG_USING_ILI9341_EBI) */
