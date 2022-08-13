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

#if defined(NU_PKG_USING_FSA506_EBI)

#include <lcd_fsa506.h>
#include "drv_pdma.h"

#define FSA506_ADDR_CMD  0x0
#define FSA506_ADDR_DATA 0x0

#if defined(FSA506_EBI_16BIT)
    #define fsa506_reg_write(RegAddr)   (*((volatile uint16_t *)(s_u32AccessBase+(FSA506_ADDR_CMD))) = (RegAddr))
    #define fsa506_read_data()            (*((volatile uint16_t *)(s_u32AccessBase+(FSA506_ADDR_DATA))))
    #define fsa506_write_data(Data)     (*((volatile uint16_t *)(s_u32AccessBase+(FSA506_ADDR_DATA))) = (Data))
#else
    #define fsa506_reg_write(RegAddr)   (*((volatile uint8_t *)(s_u32AccessBase+(FSA506_ADDR_CMD))) = (RegAddr))
    #define fsa506_read_data()            (*((volatile uint8_t *)(s_u32AccessBase+(FSA506_ADDR_DATA))))
    #define fsa506_write_data(Data)     (*((volatile uint8_t *)(s_u32AccessBase+(FSA506_ADDR_DATA))) = (Data))
#endif

static rt_uint32_t s_u32AccessBase = 0;

void fsa506_send_cmd(rt_uint8_t cmd)
{
    CLR_RS;
    fsa506_reg_write(cmd);
    SET_RS;
}

void fsa506_send_cmd_parameter(rt_uint8_t data)
{
    fsa506_write_data(data);
}

void fsa506_send_cmd_done(void)
{
    CLR_RS;
    fsa506_reg_write(0x80);
    SET_RS;
}

void fsa506_write_reg(rt_uint8_t cmd, rt_uint8_t data)
{
    fsa506_send_cmd(cmd);
    fsa506_send_cmd_parameter(data);
    fsa506_send_cmd_done();
}

void fsa506_send_pixel_data(rt_uint16_t color)
{
#if 1
    // for LV_COLOR_16_SWAP
    //BGR, B is high byte
    fsa506_write_data(color & 0xffu);
    fsa506_write_data((color >> 8) & 0xffu);
#else
    //RGB, R is high byte
    fsa506_write_data((color >> 8) & 0xffu);
    fsa506_write_data(color & 0xffu);
#endif
}

void fsa506_send_pixels(rt_uint16_t *pixels, int len)
{
    int count = len / sizeof(rt_uint16_t);
    if (count < 512)
    {
        // CPU feed
        int i = 0;
        while (i < count)
        {
            fsa506_send_pixel_data(pixels[i]);
            i++;
        }
    }
    else
    {
        // PDMA-M2M feed
        // Must enable LV_COLOR_16_SWAP definition in LVGL.
        nu_pdma_mempush((void *)(s_u32AccessBase + (FSA506_ADDR_DATA)), (void *)pixels, 8, len);
    }
}

void fsa506_set_column(uint16_t StartCol, uint16_t EndCol)
{
    fsa506_write_reg(0x0, (StartCol >> 8) & 0xFF);
    fsa506_write_reg(0x1, StartCol & 0xFF);
    fsa506_write_reg(0x2, (EndCol >> 8) & 0xFF);
    fsa506_write_reg(0x3, EndCol & 0xFF);
}

void fsa506_set_page(uint16_t StartPage, uint16_t EndPage)
{
    fsa506_write_reg(0x4, (StartPage >> 8) & 0xFF);
    fsa506_write_reg(0x5, StartPage & 0xFF);
    fsa506_write_reg(0x6, (EndPage >> 8) & 0xFF);
    fsa506_write_reg(0x7, EndPage & 0xFF);
}

void fsa506_lcd_get_pixel(char *color, int x, int y)
{
    //Not supported.
    return;
}

rt_err_t rt_hw_lcd_fsa506_ebi_init(rt_uint32_t fsa506_base)
{
    s_u32AccessBase = fsa506_base;
    return RT_EOK;
}

#endif /* if defined(NU_PKG_USING_FSA506_EBI) */
