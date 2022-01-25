/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "lcdc.h"
#include <sep4020.h>

#define writel(DATA,ADDRESS)  *((volatile rt_off_t *) ADDRESS)= DATA;

unsigned long pVideoBuffer;


rt_err_t sep4020_lcd_init(void)
{
    pVideoBuffer =(unsigned long)rt_malloc(LCDWIDTH * LCDHEIGHT * 2);

    *(RP)GPIO_PORTC_SEL  |= 0X0008;      //Portc8设置为通用口
    *(RP)GPIO_PORTC_DIR  &= (~0X0008);   //Portc8设置为输出
    *(RP)GPIO_PORTC_DATA |= 0X0008;      //Portc8输出高电平

    writel(0x00000000,LCDC_LECR);     //禁用LCDC
    writel(pVideoBuffer,LCDC_SSA);    //lcd数据帧的起始地址
    writel(YMAX | XMAX,LCDC_SIZE);
    writel(TFT|COLOR|PBSIZE|BPIX|PIXPOL|FLMPOL|LPPOL|CLKPOL|OEPOL|END_SEL|ACD_SEL|ACD|PCD,LCDC_PCR);
    writel(H_WIDTH|H_WAIT_1|H_WAIT_2,LCDC_HCR);
    writel(V_WIDTH|PASS_FRAME_WAIT|V_WAIT_1|V_WAIT_2,LCDC_VCR);
    writel(SCR|CC_EN|PW,LCDC_PWMR);
    writel(BL|HM|TM,LCDC_DMACR);
    writel(0x00000001,LCDC_LECR);         //使能LCDC
    writel(0x00000000,LCDC_LCDISREN);     //中断在加载帧的最后一个或第一个数据时设置，到LCD之间会有一个延时

    return RT_EOK;
}

void lcd_set_pixel(rtgui_color_t *c, int x, int y)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    *(unsigned short *)(pVideoBuffer + 2*y*LCDWIDTH + 2*x) = p;
}

void lcd_get_pixel(rtgui_color_t *c, int x, int y)
{
    *c = rtgui_color_from_565p( *(unsigned short *)(pVideoBuffer+2*y*LCDWIDTH+2*x));
}

void lcd_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    while (x1 < x2)
    {
        *(unsigned short *)(pVideoBuffer+2*y*LCDWIDTH+2*x1)=p;
        x1 ++;
    }
}

void lcd_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    while (y1 < y2)
    {
        *(unsigned short *)(pVideoBuffer+2*y1*LCDWIDTH+2*x)=p;
        y1 ++;
    }
}

void lcd_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
    rt_uint16_t *ptr;

    /* get pixel */
    ptr = (rt_uint16_t*) pixels;

    while (x1 < x2)
    {
        *(unsigned short *)(pVideoBuffer+2*y*LCDWIDTH+2*x1)=*ptr;
        x1 ++;
        ptr ++;
    }
}

void lcd_update(rtgui_rect_t *rect)
{
    /* nothing for none-DMA mode driver */
}

rt_uint8_t *lcd_get_framebuffer(void)
{
    return RT_NULL; /* no framebuffer driver */
}
