/*
 * File      : drv_slcdc_ili9488.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê5ÔÂ6ÈÕ     Urey         the first version
 */

#include <rtthread.h>
#include <cache.h>

#include "board.h"
#include "drv_slcdc.h"
#include <drv_gpio.h>

#ifdef RT_USING_ILI9488

#define LCD_WIDTH       480
#define LCD_HEIGHT      320

const rt_uint32_t _lcm_cmd_table[]=
{
    0x2C2C2C2C,
};


const struct slcd_data_table _lcm_data_table[] =
{
    /* LCD init code */
    {SMART_CONFIG_CMD, 0xE0}, //P-Gamma
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,0x07},
    {SMART_CONFIG_DATA,0x0f},
    {SMART_CONFIG_DATA,0x07},
    {SMART_CONFIG_DATA,0x15},
    {SMART_CONFIG_DATA,0x09},
    {SMART_CONFIG_DATA,0x3c},
    {SMART_CONFIG_DATA,0x99},
    {SMART_CONFIG_DATA,0x4b},
    {SMART_CONFIG_DATA,0x09},
    {SMART_CONFIG_DATA,0x10},
    {SMART_CONFIG_DATA,0x0d},
    {SMART_CONFIG_DATA,0x1c},
    {SMART_CONFIG_DATA,0x1e},
    {SMART_CONFIG_DATA,0x0f},

    {SMART_CONFIG_CMD, 0xE1}, //N-Gamma
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,0x20},
    {SMART_CONFIG_DATA,0x23},
    {SMART_CONFIG_DATA,0x02},
    {SMART_CONFIG_DATA,0x0f},
    {SMART_CONFIG_DATA,0x06},
    {SMART_CONFIG_DATA,0x34},
    {SMART_CONFIG_DATA,0x45},
    {SMART_CONFIG_DATA,0x43},
    {SMART_CONFIG_DATA,0x04},
    {SMART_CONFIG_DATA,0x0a},
    {SMART_CONFIG_DATA,0x08},
    {SMART_CONFIG_DATA,0x30},
    {SMART_CONFIG_DATA,0x37},
    {SMART_CONFIG_DATA,0x0f},

    {SMART_CONFIG_CMD, 0xC0},   //Power Control 1
    {SMART_CONFIG_DATA, 0x17}, //Vreg1out
    {SMART_CONFIG_DATA, 0x15}, //Verg2out

    {SMART_CONFIG_CMD, 0xC1},   //Power Control 2
    {SMART_CONFIG_DATA, 0x41}, //VGH,VGL

    {SMART_CONFIG_CMD, 0xC5},   //Power Control 3
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,0x12},
    {SMART_CONFIG_DATA,0x80},

    {SMART_CONFIG_CMD,0x36},        //MemoryAccess
    {SMART_CONFIG_DATA,0xE8},       //[ÊúÆÁ]0x48 0x88    [ºáÆÁ]0x28 0xE8  0x68 //0x08

    {SMART_CONFIG_CMD,0x3A},        //InterfacePixelFormat
    {SMART_CONFIG_DATA,0x55},       //07 24bpp ,06 18bpp,05 16bpp


    {SMART_CONFIG_CMD,0xB0},        //Interface Mode Control
    {SMART_CONFIG_DATA,0x08},
    {SMART_CONFIG_CMD,0xB1},        //Frame rate 60HZ
    {SMART_CONFIG_DATA,0xA0},
    {SMART_CONFIG_DATA,0x11},
    {SMART_CONFIG_CMD,0xB4},
    {SMART_CONFIG_DATA,0x02},
    {SMART_CONFIG_CMD,0xB6},        //RGB/MCU Interface Control
    {SMART_CONFIG_DATA,0x02},
    {SMART_CONFIG_DATA,0x02},

    {SMART_CONFIG_CMD,0xBE},
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,0x04},

    {SMART_CONFIG_CMD,0xE9},
    {SMART_CONFIG_DATA,0x00},

    {SMART_CONFIG_CMD,0xF7},
    {SMART_CONFIG_DATA,0xA9},
    {SMART_CONFIG_DATA,0x51},
    {SMART_CONFIG_DATA,0x2C},
    {SMART_CONFIG_DATA,0x82},

    {SMART_CONFIG_CMD,0x11},
    {SMART_CONFIG_UDELAY, 120000},
    {SMART_CONFIG_CMD,0x29},

    //Set Window
    {SMART_CONFIG_CMD,0x2A},        //Set X
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,(LCD_WIDTH - 1) >> 8},
    {SMART_CONFIG_DATA,(LCD_WIDTH - 1) & 0xFF},

    {SMART_CONFIG_CMD,0x2B},        //Set Y
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,0x00},
    {SMART_CONFIG_DATA,(LCD_HEIGHT - 1) >> 8},
    {SMART_CONFIG_DATA,(LCD_HEIGHT - 1) & 0xFF},


//    {SMART_CONFIG_CMD, 0x2C}
     {SMART_CONFIG_CMD,0x35},
     {SMART_CONFIG_DATA,0x00}
};

struct slcd_configure _lcm_config =
{
    .rsply_cmd_high    = 0,
    .csply_active_high = 0,
    .newcfg_fmt_conv   = 1,

    .width              = LCD_WIDTH,
    .height             = LCD_HEIGHT,

    .fmt                = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .bpp                = 16,
    .bus_width          = 8,
    .reg_width          = 8,
    .refresh            = 60,
    .data_table         = &_lcm_data_table[0],
    .data_table_num     = sizeof(_lcm_data_table)/sizeof(_lcm_data_table[0]),

    .cmd_table          = &_lcm_cmd_table[0],
    .cmd_table_num      = sizeof(_lcm_cmd_table)/sizeof(_lcm_cmd_table[0])
};

int rt_hw_ili9488_init(void)
{
    rt_thread_delay(rt_tick_from_millisecond(500));

    /* Power ON */
//    gpio_direction_output(GPIO_PORT_B,GPIO_Pin_16,1);   //RD = 1
//    gpio_direction_output(GPIO_PORT_B,GPIO_Pin_18,1);   //CS = 1
//
//    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, 0);
//    rt_thread_delay(rt_tick_from_millisecond(20));
//    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, 1);
//    rt_thread_delay(rt_tick_from_millisecond(500));
//    gpio_set_value(GPIO_PORT_B, GPIO_Pin_18, 0);        //CS = 0

    /* enable backlight */
    gpio_direction_output(LCD_BL_PORT, LCD_BL_PIN,1);

    /* init lcd & register lcd device */
    rt_hw_slcd_init(&_lcm_config);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_ili9488_init);

#endif
