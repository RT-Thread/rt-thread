/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-2-23       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_SSD1963_EBI)

#include <lcd_ssd1963.h>
#include "drv_pdma.h"

#define SSD1963_ADDR_CMD  0x0
#define SSD1963_ADDR_DATA 0x0

#define ssd1963_reg_write(u32RegAddr)   (*((volatile unsigned short *)(g_uint32_ssd1963_base+(SSD1963_ADDR_CMD))) = (u32RegAddr))
#define ssd1963_read_data()             (*((volatile unsigned short *)(g_uint32_ssd1963_base+(SSD1963_ADDR_DATA))))
#define ssd1963_write_data(u32Data)     (*((volatile unsigned short *)(g_uint32_ssd1963_base+(SSD1963_ADDR_DATA))) = (u32Data))

static rt_uint32_t g_uint32_ssd1963_base = 0;

void ssd1963_send_cmd(rt_uint8_t cmd)
{
    CLR_RS;
    ssd1963_reg_write(cmd);
    SET_RS;
}

void ssd1963_send_cmd_parameter(rt_uint8_t data)
{
    ssd1963_write_data(data);
}

void ssd1963_send_pixel_data(rt_uint16_t color)
{
    ssd1963_write_data(color);
}

void ssd1963_send_pixels(rt_uint16_t *pixels, int len)
{
    int count = len / sizeof(rt_uint16_t);
    if (count < 1024)
    {
        // CPU feed
        int i = 0;
        while (i < count)
        {
            ssd1963_write_data(pixels[i]);
            i++;
        }
    }
    else
    {
        // PDMA-M2M feed
        nu_pdma_mempush((void *)(g_uint32_ssd1963_base + (SSD1963_ADDR_DATA)), (void *)pixels, 16, count);
    }
}

void ssd1963_set_column(uint16_t StartCol, uint16_t EndCol)
{
    ssd1963_send_cmd(0x2A);
    ssd1963_write_data((StartCol >> 8) & 0xFF);
    ssd1963_write_data(StartCol & 0xFF);
    ssd1963_write_data((EndCol >> 8) & 0xFF);
    ssd1963_write_data(EndCol & 0xFF);
}

void ssd1963_set_page(uint16_t StartPage, uint16_t EndPage)
{
    ssd1963_send_cmd(0x2B);
    ssd1963_write_data((StartPage >> 8) & 0xFF);
    ssd1963_write_data(StartPage & 0xFF);
    ssd1963_write_data((EndPage >> 8) & 0xFF);
    ssd1963_write_data(EndPage & 0xFF);
}

void ssd1963_lcd_get_pixel(char *color, int x, int y)
{
    rt_uint16_t red = 0;
    rt_uint16_t green = 0;
    rt_uint16_t blue = 0;

    if (x >= XSIZE_PHYS || y >= YSIZE_PHYS)
    {
        *(rt_uint16_t *)color = 0;
        return;
    }

    ssd1963_set_column(x, x);
    ssd1963_set_page(y, y);
    ssd1963_send_cmd(0x2E);

    ssd1963_read_data();           // Dummy
    red = ssd1963_read_data();     // Red[4:0]@D15~D11
    blue = ssd1963_read_data();    // Blue[4:0]@D15~D11
    green = ssd1963_read_data();   // Green[5:0]@D15~D10

    //BGR565: B in High byte, R in low byte
    //*(rt_uint16_t *)color = (((blue >> 11) << 11) | ((green >> 10) << 5) | (red >> 11));

    //RGB565: R in High byte, B in low byte
    *(rt_uint16_t *)color = (((red >> 11) << 11) | ((green >> 10) << 5) | (blue >> 11));
}

rt_err_t rt_hw_lcd_ssd1963_ebi_init(rt_uint32_t ssd1963_base)
{
    g_uint32_ssd1963_base = ssd1963_base;
    return RT_EOK;
}

#endif /* if defined(NU_PKG_USING_SSD1963_EBI) */
