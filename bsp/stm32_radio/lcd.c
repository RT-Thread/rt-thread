#include "stm32f10x.h"
#include "rtthread.h"
#include "board.h"
#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

#if (LCD_VERSION == 1)
#include "fmt0371/FMT0371.h"
#endif

#if (LCD_VERSION == 2)
#include "ili9325/ili9325.h"
#endif

rt_err_t rt_hw_lcd_init(void);
void rt_hw_lcd_update(rtgui_rect_t *rect);
rt_uint8_t * rt_hw_lcd_get_framebuffer(void);
void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y);
void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y);
void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y);
void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2);
void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y);

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

extern  void   info_init(void);
extern  void   player_init(void);
void radio_rtgui_init(void)
{
    rtgui_rect_t rect;

    rtgui_system_server_init();

    /* register dock panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 240;
    rect.y2 = 25;
    rtgui_panel_register("info", &rect);

    /* register main panel */
    rect.x1 = 0;
    rect.y1 = 25;
    rect.x2 = 320;
    rect.y2 = 320;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");

    rt_hw_lcd_init();

    info_init();
    player_init();
}

#if (LCD_VERSION == 1)
void rt_hw_lcd_update(rtgui_rect_t *rect)
{
    /* nothing for none-DMA mode driver */
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
    return RT_NULL; /* no framebuffer driver */
}

void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    /* set X point */
    LCD_ADDR = 0x02;
    LCD_DATA = x;

    /* set Y point */
    LCD_ADDR = 0x03;
    LCD_DATA16(y);

    /* write pixel */
    LCD_ADDR = 0x0E;
    LCD_DATA16(p);
}

void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    /* set X point */
    LCD_ADDR = 0x02;
    LCD_DATA = x;

    /* set Y point */
    LCD_ADDR = 0x03;
    LCD_DATA16( y );

    /* read pixel */
    LCD_ADDR = 0x0F;
    /* dummy read */
    x = LCD_DATA;

    *c = rtgui_color_from_565p( LCD_DATA16_READ() );
}

void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    /* set X point */
    LCD_ADDR = 0x02;
    LCD_DATA = x1;

    /* set Y point */
    LCD_ADDR = 0x03;
    LCD_DATA16( y );

    /* write pixel */
    LCD_ADDR = 0x0E;
    while (x1 < x2)
    {
        LCD_DATA16(p);
        x1 ++;
    }
}

void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    /* set X point */
    LCD_ADDR = 0x02;
    LCD_DATA = x;

    while (y1 < y2)
    {
        /* set Y point */
        LCD_ADDR = 0x03;
        LCD_DATA16( y1 );

        /* write pixel */
        LCD_ADDR = 0x0E;
        LCD_DATA16(p);

        y1 ++;
    }
}

void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
    rt_uint16_t *ptr;

    /* get pixel */
    ptr = (rt_uint16_t*) pixels;

    /* set X point */
    LCD_ADDR = 0x02;
    LCD_DATA = x1;

    /* set Y point */
    LCD_ADDR = 0x03;
    LCD_DATA16( y );

    /* write pixel */
    LCD_ADDR = 0x0E;
    while (x1 < x2)
    {
        LCD_DATA16(*ptr);
        x1 ++;
        ptr ++;
    }
}

rt_err_t rt_hw_lcd_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    GPIO_SetBits(GPIOF,GPIO_Pin_9);

    ftm0371_port_init();
    ftm0371_init();

    //LCD GRAM test
    {
        unsigned int test_x;
        unsigned int test_y;
        unsigned short temp;

        rt_kprintf("\r\nLCD GRAM test....");

        //write
        temp = 0;
        for( test_y=0; test_y<320; test_y++)
        {
            /* set X point */
            LCD_ADDR = 0x02;
            LCD_DATA = 0;

            /* set Y point */
            LCD_ADDR = 0x03;
            LCD_DATA16( test_y );

            /* write pixel */
            LCD_ADDR = 0x0E;
            for(test_x=0; test_x<240; test_x++)
            {
                LCD_DATA16(temp++);
            }
        }

        temp = 0;
        for( test_y=0; test_y<320; test_y++)
        {
            /* set X point */
            LCD_ADDR = 0x02;
            LCD_DATA = 0;

            /* set Y point */
            LCD_ADDR = 0x03;
            LCD_DATA16( test_y );

            /* write pixel */
            LCD_ADDR = 0x0f;
            /* dummy read */
            test_x = LCD_DATA;
            for(test_x=0; test_x<240; test_x++)
            {
                if ( LCD_DATA16_READ() != temp++)
                {
                    rt_kprintf("  LCD GRAM ERR!!");
                    while(1);
                }
            }
        }
        rt_kprintf("  TEST PASS!\r\n");
    }//LCD GRAM TEST

#ifndef DRIVER_TEST
    /* add lcd driver into graphic driver */
    rtgui_graphic_driver_add(&_rtgui_lcd_driver);
#endif

    return RT_EOK;
}

#include <finsh.h>

void hline(rt_base_t x1, rt_base_t x2, rt_base_t y, rt_uint32_t pixel)
{
    rt_hw_lcd_draw_hline(&pixel, x1, x2, y);
}
FINSH_FUNCTION_EXPORT(hline, draw a hline);

void vline(int x, int y1, int y2, rt_uint32_t pixel)
{
    rt_hw_lcd_draw_vline(&pixel, x, y1, y2);
}
FINSH_FUNCTION_EXPORT(vline, draw a vline);

void cls()
{
    rt_size_t index;
    rtgui_color_t white 	= RTGUI_RGB(0xff, 0xff, 0xff);

    for (index = 0; index < 320; index ++)
        rt_hw_lcd_draw_hline(&white, 0, 240, index);
}
FINSH_FUNCTION_EXPORT(cls, clear screen);
#endif

#if (LCD_VERSION == 2)
void rt_hw_lcd_update(rtgui_rect_t *rect)
{
    /* nothing for none-DMA mode driver */
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
    return RT_NULL; /* no framebuffer driver */
}

/*  设置像素点 颜色,X,Y */
void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    unsigned short p;

    if ( (x>320)||(y>240) ) return;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);
    ili9325_SetCursor(x,y);

    ili9325_WriteRAM_Prepare();
    ili9325_WriteRAM(p);
}

/* 获取像素点颜色 */
void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    unsigned short p;
    p = ili9325_BGR2RGB( ili9325_ReadGRAM(x,y) );
    *c = rtgui_color_from_565p(p);
}

/* 画水平线 */
void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
    ili9325_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4) | (0<<3) );

    ili9325_SetCursor(x1, y);
    ili9325_WriteRAM_Prepare(); /* Prepare to write GRAM */
    while (x1 < x2)
    {
        ili9325_WriteRAM(p);
        x1++;
    }
}

/* 垂直线 */
void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
    unsigned short p;

    /* get color pixel */
    p = rtgui_color_to_565p(*c);

    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
    ili9325_WriteReg(0x0003,(1<<12)|(1<<5)|(0<<4) | (1<<3) );

    ili9325_SetCursor(x, y1);
    ili9325_WriteRAM_Prepare(); /* Prepare to write GRAM */
    while (y1 < y2)
    {
        ili9325_WriteRAM(p);
        y1++;
    }
}

/* ?? */
void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
    rt_uint16_t *ptr;

    /* get pixel */
    ptr = (rt_uint16_t*) pixels;

    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
    ili9325_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4) | (0<<3) );

    ili9325_SetCursor(x1, y);
    ili9325_WriteRAM_Prepare(); /* Prepare to write GRAM */
    while (x1 < x2)
    {
        ili9325_WriteRAM( *ptr );
        x1 ++;
        ptr ++;
    }
}

rt_err_t rt_hw_lcd_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    GPIO_SetBits(GPIOF,GPIO_Pin_9);

    ili9325_Initializtion();

    /* LCD GRAM TEST */
    {
        unsigned short temp;
        unsigned int test_x;
        unsigned int test_y;

        rt_kprintf("\r\nLCD GRAM test....");

        /* write */
        temp=0;
        /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
        ili9325_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4) | (0<<3) );
        ili9325_SetCursor(0,0);
        ili9325_WriteRAM_Prepare();
        for(test_y=0; test_y<76800; test_y++)
        {
            ili9325_WriteRAM(temp++);
        }

        /* read */
        temp=0;
        for(test_y=0; test_y<320; test_y++)
        {
            for(test_x=0; test_x<240; test_x++)
            {
                if( ili9325_BGR2RGB( ili9325_ReadGRAM(test_x,test_y) ) != temp++)
                {
                    rt_kprintf("  LCD GRAM ERR!!");
                    while(1);
                }
            }
        }
        rt_kprintf("  TEST PASS!\r\n");
    }/* LCD GRAM TEST */

#ifndef DRIVER_TEST
    /* add lcd driver into graphic driver */
    rtgui_graphic_driver_add(&_rtgui_lcd_driver);
#endif

    return RT_EOK;
}

#include <finsh.h>

void hline(rt_base_t x1, rt_base_t x2, rt_base_t y, rt_uint32_t pixel)
{
    rt_hw_lcd_draw_hline(&pixel, x1, x2, y);
}
FINSH_FUNCTION_EXPORT(hline, draw a hline);

void vline(int x, int y1, int y2, rt_uint32_t pixel)
{
    rt_hw_lcd_draw_vline(&pixel, x, y1, y2);
}
FINSH_FUNCTION_EXPORT(vline, draw a vline);

void cls()
{
    ili9325_Clear(0xF800);
}
FINSH_FUNCTION_EXPORT(cls, clear screen);
#endif
