/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-01     bernard      first version from QiuYi's driver
 */

#include <rtthread.h>
#include <s3c24x0.h>


/* LCD driver for N3'5 */
#define LCD_WIDTH 240
#define LCD_HEIGHT 320
#define LCD_PIXCLOCK 4

#define LCD_RIGHT_MARGIN 36
#define LCD_LEFT_MARGIN 19
#define LCD_HSYNC_LEN 5

#define LCD_UPPER_MARGIN 1
#define LCD_LOWER_MARGIN 5
#define LCD_VSYNC_LEN 1

#define LCD_XSIZE  LCD_WIDTH
#define LCD_YSIZE  LCD_HEIGHT
#define SCR_XSIZE  LCD_WIDTH
#define SCR_YSIZE  LCD_HEIGHT

#define RT_HW_LCD_WIDTH     LCD_WIDTH
#define RT_HW_LCD_HEIGHT    LCD_HEIGHT

#define MVAL        (13)
#define MVAL_USED   (0)     //0=each frame   1=rate by MVAL
#define INVVDEN     (1)     //0=normal       1=inverted
#define BSWP        (0)     //Byte swap control
#define HWSWP       (1)     //Half word swap control

#define GPB1_TO_OUT()       (GPBUP &= 0xfffd, GPBCON &= 0xfffffff3, GPBCON |= 0x00000004)
#define GPB1_TO_1()         (GPBDAT |= 0x0002)
#define GPB1_TO_0()         (GPBDAT &= 0xfffd)

#define S3C2410_LCDCON1_CLKVAL(x)  ((x) << 8)
#define S3C2410_LCDCON1_MMODE      (1<<7)
#define S3C2410_LCDCON1_DSCAN4     (0<<5)
#define S3C2410_LCDCON1_STN4       (1<<5)
#define S3C2410_LCDCON1_STN8       (2<<5)
#define S3C2410_LCDCON1_TFT        (3<<5)

#define S3C2410_LCDCON1_STN1BPP    (0<<1)
#define S3C2410_LCDCON1_STN2GREY   (1<<1)
#define S3C2410_LCDCON1_STN4GREY   (2<<1)
#define S3C2410_LCDCON1_STN8BPP    (3<<1)
#define S3C2410_LCDCON1_STN12BPP   (4<<1)

#define S3C2410_LCDCON1_TFT1BPP    (8<<1)
#define S3C2410_LCDCON1_TFT2BPP    (9<<1)
#define S3C2410_LCDCON1_TFT4BPP    (10<<1)
#define S3C2410_LCDCON1_TFT8BPP    (11<<1)
#define S3C2410_LCDCON1_TFT16BPP   (12<<1)
#define S3C2410_LCDCON1_TFT24BPP   (13<<1)

#define S3C2410_LCDCON1_ENVID      (1)

#define S3C2410_LCDCON1_MODEMASK    0x1E

#define S3C2410_LCDCON2_VBPD(x)     ((x) << 24)
#define S3C2410_LCDCON2_LINEVAL(x)  ((x) << 14)
#define S3C2410_LCDCON2_VFPD(x)     ((x) << 6)
#define S3C2410_LCDCON2_VSPW(x)     ((x) << 0)

#define S3C2410_LCDCON2_GET_VBPD(x) ( ((x) >> 24) & 0xFF)
#define S3C2410_LCDCON2_GET_VFPD(x) ( ((x) >>  6) & 0xFF)
#define S3C2410_LCDCON2_GET_VSPW(x) ( ((x) >>  0) & 0x3F)

#define S3C2410_LCDCON3_HBPD(x)     ((x) << 19)
#define S3C2410_LCDCON3_WDLY(x)     ((x) << 19)
#define S3C2410_LCDCON3_HOZVAL(x)   ((x) << 8)
#define S3C2410_LCDCON3_HFPD(x)     ((x) << 0)
#define S3C2410_LCDCON3_LINEBLANK(x)((x) << 0)

#define S3C2410_LCDCON3_GET_HBPD(x) ( ((x) >> 19) & 0x7F)
#define S3C2410_LCDCON3_GET_HFPD(x) ( ((x) >>  0) & 0xFF)

#define S3C2410_LCDCON4_MVAL(x)     ((x) << 8)
#define S3C2410_LCDCON4_HSPW(x)     ((x) << 0)
#define S3C2410_LCDCON4_WLH(x)      ((x) << 0)

#define S3C2410_LCDCON4_GET_HSPW(x) ( ((x) >>  0) & 0xFF)

#define S3C2410_LCDCON5_BPP24BL     (1<<12)
#define S3C2410_LCDCON5_FRM565      (1<<11)
#define S3C2410_LCDCON5_INVVCLK     (1<<10)
#define S3C2410_LCDCON5_INVVLINE    (1<<9)
#define S3C2410_LCDCON5_INVVFRAME   (1<<8)
#define S3C2410_LCDCON5_INVVD       (1<<7)
#define S3C2410_LCDCON5_INVVDEN     (1<<6)
#define S3C2410_LCDCON5_INVPWREN    (1<<5)
#define S3C2410_LCDCON5_INVLEND     (1<<4)
#define S3C2410_LCDCON5_PWREN       (1<<3)
#define S3C2410_LCDCON5_ENLEND      (1<<2)
#define S3C2410_LCDCON5_BSWP        (1<<1)
#define S3C2410_LCDCON5_HWSWP       (1<<0)

#define S3C2410_LCDINT_FRSYNC       (1<<1)

static volatile rt_uint16_t _rt_framebuffer[RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH];
//static volatile rt_uint16_t _rt_hw_framebuffer[RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH];
static struct rt_device_graphic_info _lcd_info;

static void lcd_power_enable(int invpwren, int pwren)
{
    //GPG4 is setted as LCD_PWREN
    GPGUP  = GPGUP | (1<<4); // Pull-up disable
    GPGCON = GPGCON | (3<<8); //GPG4=LCD_PWREN

    //Enable LCD POWER ENABLE Function
    LCDCON5 = LCDCON5&(~(1<<3))|(pwren<<3);   // PWREN
    LCDCON5 = LCDCON5&(~(1<<5))|(invpwren<<5);   // INVPWREN
}

static void lcd_envid_on_off(int onoff)
{
    if(onoff==1)
        /*ENVID=ON*/
        LCDCON1|=1;
    else
        /*ENVID Off*/
        LCDCON1 =LCDCON1 & 0x3fffe;
}

//********************** BOARD LCD backlight ****************************
static void LcdBkLtSet(rt_uint32_t HiRatio)
{
#define FREQ_PWM1       1000
    if(!HiRatio)
    {
        GPBCON  = GPBCON & (~(3<<2)) | (1<<2) ;
        GPBDAT &= ~(1<<1);
        return;
    }
    GPBCON = GPBCON & (~(3<<2)) | (2<<2) ;

    if( HiRatio > 100 ) HiRatio = 100 ;

    TCON = TCON & (~(0xf<<8)) ;             // clear manual update bit, stop Timer1

    TCFG0 &= 0xffffff00;                    // set Timer 0&1 prescaler 0
    TCFG0 |= 15;                            //prescaler = 15+1

    TCFG1 &= 0xffffff0f;                    // set Timer 1 MUX 1/16
    TCFG1 |= 0x00000030;                    // set Timer 1 MUX 1/16

    TCNTB1   = ( 100000000>>8 )/FREQ_PWM1;  //if set inverter off, when TCNT2<=TCMP2, TOUT is high, TCNT2>TCMP2, TOUT is low
    TCMPB1  = ( TCNTB1*(100-HiRatio))/100 ; //if set inverter on,  when TCNT2<=TCMP2, TOUT is low,  TCNT2>TCMP2, TOUT is high

    TCON = TCON & (~(0xf<<8)) | (0x0e<<8) ;
    TCON = TCON & (~(0xf<<8)) | (0x0d<<8) ;
}

/* RT-Thread Device Interface */
static rt_err_t rt_lcd_init (rt_device_t dev)
{
    GPB1_TO_OUT();
    GPB1_TO_1();

    GPCUP  = 0x00000000;
    GPCCON = 0xaaaa02a9;

    GPDUP  = 0x00000000;
    GPDCON = 0xaaaaaaaa;

#define M5D(n)  ((n)&0x1fffff)
#define LCD_ADDR ((rt_uint32_t)_rt_framebuffer)
    LCDCON1 = (LCD_PIXCLOCK << 8) | (3 <<  5) | (12 << 1);
    LCDCON2 = (LCD_UPPER_MARGIN << 24) | ((LCD_HEIGHT - 1) << 14) | (LCD_LOWER_MARGIN << 6) | (LCD_VSYNC_LEN << 0);
    LCDCON3 = (LCD_RIGHT_MARGIN << 19) | ((LCD_WIDTH  - 1) <<  8) | (LCD_LEFT_MARGIN << 0);
    LCDCON4 = (13 <<  8) | (LCD_HSYNC_LEN << 0);
#if !defined(LCD_CON5)
    #define LCD_CON5 ((1<<11) | (1 << 9) | (1 << 8) | (1 << 3) | (1 << 0))
#endif
    LCDCON5   =  LCD_CON5;

    LCDSADDR1 = ((LCD_ADDR >> 22) << 21) | ((M5D(LCD_ADDR >> 1)) <<  0);
    LCDSADDR2 = M5D((LCD_ADDR + LCD_WIDTH * LCD_HEIGHT * 2) >> 1);
    LCDSADDR3 = LCD_WIDTH;

    LCDINTMSK |= (3);
    LPCSEL &= (~7) ;
    TPAL=0;

    LcdBkLtSet(70) ;
    lcd_power_enable(0, 1);
    lcd_envid_on_off(1);

    return RT_EOK;
}

static rt_err_t rt_lcd_control (rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;
    case RTGRAPHIC_CTRL_POWERON:
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &_lcd_info, sizeof(_lcd_info));
        break;
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int rt_hw_lcd_init(void)
{
    rt_device_t lcd = rt_malloc(sizeof(struct rt_device));
    if (lcd == RT_NULL)
            return -RT_ERROR; /* no memory yet */

    _lcd_info.bits_per_pixel = 16;
    _lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
    _lcd_info.framebuffer = (void*)_rt_framebuffer;
    _lcd_info.width = LCD_WIDTH;
    _lcd_info.height = LCD_HEIGHT;

    /* init device structure */
    lcd->type = RT_Device_Class_Unknown;
    lcd->init = rt_lcd_init;
    lcd->open = RT_NULL;
    lcd->close = RT_NULL;
    lcd->control = rt_lcd_control;
    lcd->user_data = (void*)&_lcd_info;

    /* register lcd device to RT-Thread */
    rt_device_register(lcd, "lcd", RT_DEVICE_FLAG_RDWR);
}

INIT_BOARD_EXPORT(rt_hw_lcd_init);
