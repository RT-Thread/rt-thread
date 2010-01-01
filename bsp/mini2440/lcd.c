/*
 * File      : lcd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2007-11-17     Yi.Qiu
 */

#include <rtthread.h>

#include <s3c24x0.h>

#define MVAL		(13)
#define MVAL_USED 	(0)		//0=each frame   1=rate by MVAL
#define INVVDEN		(1)		//0=normal       1=inverted
#define BSWP		(0)		//Byte swap control
#define HWSWP		(1)		//Half word swap control

#define M5D(n) ((n) & 0x1fffff)	// To get lower 21bits

//TFT 240320
#define LCD_XSIZE_TFT_240320 	(240)
#define LCD_YSIZE_TFT_240320 	(320)

#define SCR_XSIZE_TFT_240320 	(240)
#define SCR_YSIZE_TFT_240320 	(320)

//TFT 240320
#define HOZVAL_TFT_240320	(LCD_XSIZE_TFT_240320-1)
#define LINEVAL_TFT_240320	(LCD_YSIZE_TFT_240320-1)

//Timing parameter for NEC3.5"
#define VBPD_240320		(1)		//垂直同步信号的后肩
#define VFPD_240320		(5)		//垂直同步信号的前肩
#define VSPW_240320		(1)		//垂直同步信号的脉宽

#define HBPD_240320		(36)	//水平同步信号的后肩
#define HFPD_240320		(19)	//水平同步信号的前肩
#define HSPW_240320		(5)		//水平同步信号的脉宽

#define CLKVAL_TFT_240320	(2)

#define GPB1_TO_OUT()		(GPBUP &= 0xfffd, GPBCON &= 0xfffffff3, GPBCON |= 0x00000004)
#define GPB1_TO_1()			(GPBDAT |= 0x0002)
#define GPB1_TO_0()			(GPBDAT &= 0xfffd)

#define RT_HW_LCD_WIDTH		LCD_XSIZE_TFT_240320
#define RT_HW_LCD_HEIGHT	SCR_YSIZE_TFT_240320

#define S3C2410_LCDCON1_CLKVAL(x)  ((x) << 8)
#define S3C2410_LCDCON1_MMODE	   (1<<7)
#define S3C2410_LCDCON1_DSCAN4	   (0<<5)
#define S3C2410_LCDCON1_STN4	   (1<<5)
#define S3C2410_LCDCON1_STN8	   (2<<5)
#define S3C2410_LCDCON1_TFT	       (3<<5)

#define S3C2410_LCDCON1_STN1BPP	   (0<<1)
#define S3C2410_LCDCON1_STN2GREY   (1<<1)
#define S3C2410_LCDCON1_STN4GREY   (2<<1)
#define S3C2410_LCDCON1_STN8BPP	   (3<<1)
#define S3C2410_LCDCON1_STN12BPP   (4<<1)

#define S3C2410_LCDCON1_TFT1BPP	   (8<<1)
#define S3C2410_LCDCON1_TFT2BPP	   (9<<1)
#define S3C2410_LCDCON1_TFT4BPP	   (10<<1)
#define S3C2410_LCDCON1_TFT8BPP	   (11<<1)
#define S3C2410_LCDCON1_TFT16BPP   (12<<1)
#define S3C2410_LCDCON1_TFT24BPP   (13<<1)

#define S3C2410_LCDCON1_ENVID	   (1)

#define S3C2410_LCDCON1_MODEMASK    0x1E

#define S3C2410_LCDCON2_VBPD(x)	    ((x) << 24)
#define S3C2410_LCDCON2_LINEVAL(x)  ((x) << 14)
#define S3C2410_LCDCON2_VFPD(x)	    ((x) << 6)
#define S3C2410_LCDCON2_VSPW(x)	    ((x) << 0)

#define S3C2410_LCDCON2_GET_VBPD(x) ( ((x) >> 24) & 0xFF)
#define S3C2410_LCDCON2_GET_VFPD(x) ( ((x) >>  6) & 0xFF)
#define S3C2410_LCDCON2_GET_VSPW(x) ( ((x) >>  0) & 0x3F)

#define S3C2410_LCDCON3_HBPD(x)	    ((x) << 19)
#define S3C2410_LCDCON3_WDLY(x)	    ((x) << 19)
#define S3C2410_LCDCON3_HOZVAL(x)   ((x) << 8)
#define S3C2410_LCDCON3_HFPD(x)	    ((x) << 0)
#define S3C2410_LCDCON3_LINEBLANK(x)((x) << 0)

#define S3C2410_LCDCON3_GET_HBPD(x) ( ((x) >> 19) & 0x7F)
#define S3C2410_LCDCON3_GET_HFPD(x) ( ((x) >>  0) & 0xFF)

#define S3C2410_LCDCON4_MVAL(x)	    ((x) << 8)
#define S3C2410_LCDCON4_HSPW(x)	    ((x) << 0)
#define S3C2410_LCDCON4_WLH(x)	    ((x) << 0)

#define S3C2410_LCDCON4_GET_HSPW(x) ( ((x) >>  0) & 0xFF)

#define S3C2410_LCDCON5_BPP24BL	    (1<<12)
#define S3C2410_LCDCON5_FRM565	    (1<<11)
#define S3C2410_LCDCON5_INVVCLK	    (1<<10)
#define S3C2410_LCDCON5_INVVLINE    (1<<9)
#define S3C2410_LCDCON5_INVVFRAME   (1<<8)
#define S3C2410_LCDCON5_INVVD	    (1<<7)
#define S3C2410_LCDCON5_INVVDEN	    (1<<6)
#define S3C2410_LCDCON5_INVPWREN    (1<<5)
#define S3C2410_LCDCON5_INVLEND	    (1<<4)
#define S3C2410_LCDCON5_PWREN	    (1<<3)
#define S3C2410_LCDCON5_ENLEND	    (1<<2)
#define S3C2410_LCDCON5_BSWP	    (1<<1)
#define S3C2410_LCDCON5_HWSWP	    (1<<0)

#define LCDCON1_VALUE S3C2410_LCDCON1_TFT16BPP | \
				S3C2410_LCDCON1_TFT | \
				S3C2410_LCDCON1_CLKVAL(0x04)

#define LCDCON2_VALUE S3C2410_LCDCON2_VBPD(1) | \
				S3C2410_LCDCON2_LINEVAL(319) | \
				S3C2410_LCDCON2_VFPD(5) | \
				S3C2410_LCDCON2_VSPW(1)

#define LCDCON3_VALUE	S3C2410_LCDCON3_HBPD(36) | \
				S3C2410_LCDCON3_HOZVAL(239) | \
				S3C2410_LCDCON3_HFPD(19)

#define LCDCON4_VALUE	S3C2410_LCDCON4_MVAL(13) | \
				S3C2410_LCDCON4_HSPW(5)

#define LCDCON5_VALUE	S3C2410_LCDCON5_FRM565 | \
				S3C2410_LCDCON5_INVVLINE | \
				S3C2410_LCDCON5_INVVFRAME | \
				S3C2410_LCDCON5_PWREN | \
				S3C2410_LCDCON5_HWSWP

#define	S3C2410_LCDINT_FRSYNC	(1<<1)

volatile rt_uint16_t _rt_hw_framebuffer[RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH];

void lcd_power_enable(int invpwren,int pwren)
{
	/* GPG4 is setted as LCD_PWREN */
	GPGUP=(GPGUP&(~(1<<4)))|(1<<4); 			/* Pull-up disable */
	GPGCON=(GPGCON&(~(3<<8)))|(3<<8); 			/* GPG4=LCD_PWREN */
	GPGDAT = GPGDAT | (1<<4) ;

	/* Enable LCD POWER ENABLE Function */
	LCDCON5=(LCDCON5&(~(1<<3)))|(pwren<<3);   	/* PWREN */
	LCDCON5=(LCDCON5&(~(1<<5)))|(invpwren<<5);	/* INVPWREN */
}

void lcd_envid_on_off(int onoff)
{
	if(onoff==1)
		/*ENVID=ON*/
		LCDCON1|=1;
	else
		/*ENVID Off*/
		LCDCON1 =LCDCON1 & 0x3fffe;
}

//********************** BOARD LCD backlight ****************************
void LcdBkLtSet(rt_uint32_t HiRatio)
{
#define FREQ_PWM1		1000

	if(!HiRatio)
	{
		GPBCON  = GPBCON & (~(3<<2)) | (1<<2) ;	//GPB1设置为output
		GPBDAT &= ~(1<<1);
		return;
	}
	GPBCON = GPBCON & (~(3<<2)) | (2<<2) ;

	if( HiRatio > 100 ) HiRatio = 100 ;

	TCON = TCON & (~(0xf<<8)) ;			    // clear manual update bit, stop Timer1

	TCFG0 &= 0xffffff00;					// set Timer 0&1 prescaler 0
	TCFG0 |= 15;							//prescaler = 15+1

	TCFG1 &= 0xffffff0f;					// set Timer 1 MUX 1/16
	TCFG1 |= 0x00000030;					// set Timer 1 MUX 1/16

	TCNTB1	 = ( 100000000>>8 )/FREQ_PWM1;  //if set inverter off, when TCNT2<=TCMP2, TOUT is high, TCNT2>TCMP2, TOUT is low
	TCMPB1  = ( TCNTB1*(100-HiRatio))/100 ;	//if set inverter on,  when TCNT2<=TCMP2, TOUT is low,  TCNT2>TCMP2, TOUT is high

	TCON = TCON & (~(0xf<<8)) | (0x0e<<8) ;
	TCON = TCON & (~(0xf<<8)) | (0x0d<<8) ;
}

#ifdef RT_USING_RTGUI

#include <rtgui/driver.h>
#include <rtgui/color.h>

void rt_hw_lcd_update(rtgui_rect_t *rect)
{
	/* nothing */
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
	return (rt_uint8_t *)_rt_hw_framebuffer;
}

void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    if (x < SCR_XSIZE_TFT_240320 && y < SCR_YSIZE_TFT_240320)
	{
		_rt_hw_framebuffer[(y)][(x)] = rtgui_color_to_565p(*c);
	}
}

void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    if (x < SCR_XSIZE_TFT_240320 && y < SCR_YSIZE_TFT_240320)
	{
		*c = rtgui_color_from_565p(_rt_hw_framebuffer[(y)][(x)]);
	}

    return ;
}

void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint32_t idx;
	rt_uint16_t color;

	/* get color pixel */
	color = rtgui_color_to_565p(*c);

	for (idx = x1; idx < x2; idx ++)
	{
		_rt_hw_framebuffer[y][idx] = color;
	}
}

void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
    rt_uint32_t idy;
	rt_uint16_t color;

	/* get color pixel */
	color = rtgui_color_to_565p(*c);

	for (idy = y1; idy < y2; idy ++)
	{
		_rt_hw_framebuffer[idy][x] = color;
	}
}

void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
    rt_memcpy((void*)&_rt_hw_framebuffer[y][x1], pixels, (x2 - x1) * 2);
}

struct rtgui_graphic_driver _rtgui_lcd_driver =
{
	"lcd",
	2,
	240,
	320,
	rt_hw_lcd_update,
	rt_hw_lcd_get_framebuffer,
	rt_hw_lcd_set_pixel,
	rt_hw_lcd_get_pixel,
	rt_hw_lcd_draw_hline,
	rt_hw_lcd_draw_vline,
	rt_hw_lcd_draw_raw_hline
};

#include "finsh.h"
void hline(rt_uint32_t c, int x1, int x2, int y)
{
    rtgui_color_t color = (rtgui_color_t)c;
    rt_hw_lcd_draw_hline(&color, x1, x2, y);
}
FINSH_FUNCTION_EXPORT(hline, draw a hline);

void vline(rt_uint32_t c, int x, int y1, int y2)
{
    rtgui_color_t color = (rtgui_color_t)c;
    rt_hw_lcd_draw_vline(&color, x, y1, y2);
}
FINSH_FUNCTION_EXPORT(vline, draw a vline);

void clear()
{
    int y;

    for (y = 0; y < 320; y ++)
    {
        rt_hw_lcd_draw_hline((rtgui_color_t*)&white, 0, 239, y);
    }
}
FINSH_FUNCTION_EXPORT(clear, clear screen);

void rt_hw_lcd_init()
{
	GPB1_TO_OUT();
	GPB1_TO_1();

	GPCUP  = 0x00000000;
	GPCCON = 0xaaaa02a9;

	GPDUP  = 0x00000000;
	GPDCON = 0xaaaaaaaa;

	LCDCON1 = LCDCON1_VALUE;
	LCDCON2 = LCDCON2_VALUE;
	LCDCON3 = LCDCON3_VALUE;
	LCDCON4 = LCDCON4_VALUE;
	LCDCON5 = LCDCON5_VALUE;

	LCDSADDR1=(((rt_uint32_t)_rt_hw_framebuffer>>22)<<21)|M5D((rt_uint32_t)_rt_hw_framebuffer>>1);
	LCDSADDR2=M5D( ((rt_uint32_t)_rt_hw_framebuffer+(SCR_XSIZE_TFT_240320*LCD_YSIZE_TFT_240320*2))>>1 );
	LCDSADDR3=(((SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320)/1)<<11)|(LCD_XSIZE_TFT_240320/1);

	LCDINTMSK|=(3);
	LPCSEL &= (~7) ;
	TPAL=0;

	LcdBkLtSet( 70 ) ;
	lcd_power_enable(0, 1);
	lcd_envid_on_off(1);

	/* add lcd driver into graphic driver */
	rtgui_graphic_driver_add(&_rtgui_lcd_driver);
}

#endif
