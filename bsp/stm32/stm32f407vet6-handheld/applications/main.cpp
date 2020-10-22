/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtthread.h>
#include "drv_spi.h"
#include "board_config.h"

#include <U8g2lib.h>

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextP age. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.

  This is a frame buffer example.
*/

#ifdef __cplusplus
extern   "C"
{
#endif


static U8G2_SH1107_PIMORONI_128X128_F_4W_HW_SPI u8g2(U8G2_R0, 
    /* cs=*/ OLED_SPI_PIN_CS, /* dc=*/ OLED_SPI_PIN_DC, /* reset=*/ OLED_SPI_PIN_RES);


// End of constructor list

//#define MINI_LOGO

static void drawLogo(void)
{
    u8g2.setFontMode(1);    // Transparent
#ifdef MINI_LOGO

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(0, 22, "U");

    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_inb19_mn);
    u8g2.drawStr(14,8,"8");

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(36,22,"g");
    u8g2.drawStr(48,22,"\xb2");

    u8g2.drawHLine(2, 25, 34);
    u8g2.drawHLine(3, 26, 34);
    u8g2.drawVLine(32, 22, 12);
    u8g2.drawVLine(33, 23, 12);
#else

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb24_mf);
    u8g2.drawStr(0, 30, "U");

    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_inb30_mn);
    u8g2.drawStr(21,8,"8");

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb24_mf);
    u8g2.drawStr(51,30,"g");
    u8g2.drawStr(67,30,"\xb2");

    u8g2.drawHLine(2, 35, 47);
    u8g2.drawHLine(3, 36, 47);
    u8g2.drawVLine(45, 32, 12);
    u8g2.drawVLine(46, 33, 12);

#endif
}

static void drawURL(void)
{
#ifndef MINI_LOGO
  u8g2.setFont(u8g2_font_4x6_tr);
  if ( u8g2.getDisplayHeight() < 59 )
  {
    u8g2.drawStr(89,20,"github.com");
    u8g2.drawStr(73,29,"/olikraus/u8g2");
  }
  else
  {
    u8g2.drawStr(1,54,"github.com/olikraus/u8g2");
  }
#endif
}

static void u8g2_full_buffer_u8g2_logo()
{
  u8g2.begin();
  u8g2.clearBuffer();
  drawLogo();
  drawURL();
  u8g2.sendBuffer();
}


static int rt_hw_spi_oled_init(void)
{
		    /* 开启OLED电源 */
    rt_pin_mode(OLED_POWER_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(OLED_POWER_PIN, PIN_HIGH);
	
    __HAL_RCC_GPIOA_CLK_ENABLE();
    rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_3);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_oled_init);







int main(void)
{
    int count = 1;

	
		rt_kprintf("hello_oled!/s");
	    /* 开启OLED电源 */
	char buf[]= "hello rt-thread!\r\n";
	
	rt_device_t dev =RT_NULL;
	
	dev =rt_device_find("vcom");
	
	if(dev)
		rt_device_open(dev,RT_DEVICE_FLAG_RDWR);
	else
		return -RT_ERROR;
			rt_kprintf("hello_oled_gui!\r\n");


//	u8g2_full_buffer_u8g2_logo();
    while (1)
    {

        rt_thread_mdelay(500);
			rt_device_write(dev,0,buf,rt_strlen(buf));
			
    }

    return RT_EOK;
}
#ifdef   __cplusplus
}
#endif
// End of main.cpp
