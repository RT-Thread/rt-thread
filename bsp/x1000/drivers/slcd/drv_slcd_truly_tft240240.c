/*
 * File      : drv_slcd_truly240240.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê4ÔÂ28ÈÕ     Urey         the first version
 */

#include <rtthread.h>
#include <cache.h>

#include "board.h"
#include "drv_slcdc.h"
#include <drv_gpio.h>

#ifdef RT_USING_TRULY_TFT240240

rt_uint32_t _truly_tft240240_cmd_table[]=
{
    0x2c2c0000,
};


struct slcd_data_table _truly_tft240240_data_table[] =
{
    /* LCD init code */
    {SMART_CONFIG_CMD, 0x01},  //soft reset, 120 ms = 120 000 us
    {SMART_CONFIG_UDELAY, 20},
    {SMART_CONFIG_CMD, 0x11},
    {SMART_CONFIG_UDELAY, 10},    /* sleep out 50 ms  */

    {SMART_CONFIG_CMD, 0x36},
#ifdef CONFIG_TRULY_240X240_ROTATE_180
    {SMART_CONFIG_DATA, 0xd0}, //40
#else
    {SMART_CONFIG_DATA, 0x00}, //40
#endif

    {SMART_CONFIG_CMD,  0x2a},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0xef},

    {SMART_CONFIG_CMD, 0x2b},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0xef},

    {SMART_CONFIG_CMD, 0x3a},
#if defined(CONFIG_SLCD_TRULY_18BIT)  //if 18bit/pixel unusual. try to use 16bit/pixel
    {SMART_CONFIG_DATA, 0x06}, //6-6-6
#else
    {SMART_CONFIG_DATA, 0x05}, //5-6-5
#endif
    // {SMART_CONFIG_DATA, 0x55},

    {SMART_CONFIG_CMD, 0xb2},
    {SMART_CONFIG_DATA, 0x7f},
    {SMART_CONFIG_DATA, 0x7f},
    {SMART_CONFIG_DATA, 0x01},
    {SMART_CONFIG_DATA, 0xde},
    {SMART_CONFIG_DATA, 0x33},

    {SMART_CONFIG_CMD, 0xb3},
    {SMART_CONFIG_DATA, 0x10},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x0f},

    {SMART_CONFIG_CMD, 0xb4},
    {SMART_CONFIG_DATA, 0x0b},

    {SMART_CONFIG_CMD, 0xb7},
    {SMART_CONFIG_DATA, 0x35},

    {SMART_CONFIG_CMD, 0xbb},
    {SMART_CONFIG_DATA, 0x28}, //23

    {SMART_CONFIG_CMD, 0xbc},
    {SMART_CONFIG_DATA, 0xec},

    {SMART_CONFIG_CMD, 0xc0},
    {SMART_CONFIG_DATA, 0x2c},

    {SMART_CONFIG_CMD, 0xc2},
    {SMART_CONFIG_DATA, 0x01},

    {SMART_CONFIG_CMD, 0xc3},
    {SMART_CONFIG_DATA, 0x1e}, //14

    {SMART_CONFIG_CMD, 0xc4},
    {SMART_CONFIG_DATA, 0x20},

    {SMART_CONFIG_CMD, 0xc6},
    {SMART_CONFIG_DATA, 0x14},

    {SMART_CONFIG_CMD, 0xd0},
    {SMART_CONFIG_DATA, 0xa4},
    {SMART_CONFIG_DATA, 0xa1},

    {SMART_CONFIG_CMD, 0xe0},
    {SMART_CONFIG_DATA, 0xd0},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x08},
    {SMART_CONFIG_DATA, 0x07},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x29},
    {SMART_CONFIG_DATA, 0x54},
    {SMART_CONFIG_DATA, 0x41},
    {SMART_CONFIG_DATA, 0x3c},
    {SMART_CONFIG_DATA, 0x17},
    {SMART_CONFIG_DATA, 0x15},
    {SMART_CONFIG_DATA, 0x1a},
    {SMART_CONFIG_DATA, 0x20},

    {SMART_CONFIG_CMD, 0xe1},
    {SMART_CONFIG_DATA, 0xd0},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x08},
    {SMART_CONFIG_DATA, 0x07},
    {SMART_CONFIG_DATA, 0x04},
    {SMART_CONFIG_DATA, 0x29},
    {SMART_CONFIG_DATA, 0x44},
    {SMART_CONFIG_DATA, 0x42},
    {SMART_CONFIG_DATA, 0x3b},
    {SMART_CONFIG_DATA, 0x16},
    {SMART_CONFIG_DATA, 0x15},
    {SMART_CONFIG_DATA, 0x1b},
    {SMART_CONFIG_DATA, 0x1f},

    {SMART_CONFIG_CMD, 0x35}, // TE on
    {SMART_CONFIG_DATA, 0x00}, // TE mode: 0, mode1; 1, mode2
    //  {SMART_CONFIG_CMD, 0x34}, // TE off

    {SMART_CONFIG_CMD, 0x29}, //Display ON

    /* set window size*/
    // {SMART_CONFIG_CMD, 0xcd},
    {SMART_CONFIG_CMD, 0x2a},
    {SMART_CONFIG_DATA, 0},
    {SMART_CONFIG_DATA, 0},
    {SMART_CONFIG_DATA, (239>> 8) & 0xff},
    {SMART_CONFIG_DATA, 239 & 0xff},
#ifdef CONFIG_TRULY_240X240_ROTATE_180
    {SMART_CONFIG_CMD, 0x2b},
    {SMART_CONFIG_DATA, ((320-240)>>8)&0xff},
    {SMART_CONFIG_DATA, ((320-240)>>0)&0xff},
    {SMART_CONFIG_DATA, ((320-1)>>8) & 0xff},
    {SMART_CONFIG_DATA, ((320-1)>>0) & 0xff},
#else
    {SMART_CONFIG_CMD, 0x2b},
    {SMART_CONFIG_DATA, 0},
    {SMART_CONFIG_DATA, 0},
    {SMART_CONFIG_DATA, (239>> 8) & 0xff},
    {SMART_CONFIG_DATA, 239 & 0xff},
#endif

    {SMART_CONFIG_CMD,  0X2C}, //GRAM start writing
};

struct slcd_configure _truly_tft240240_config =
{
    .width              = 240,
    .height             = 240,

    .fmt                = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .bpp                = 16,
    .bus_width          = 8,
    .reg_width          = 8,
    .refresh            = 60,

    .reg_write_twice    = 0,
    .rsply_cmd_high     = 0,
    .csply_active_high  = 0,
    /* write graphic ram command, in word, for example 8-bit bus, write_gram_cmd=C3C2C1C0. */
    .newcfg_fmt_conv    = 1,
    .data_table         = &_truly_tft240240_data_table[0],
    .data_table_num     = sizeof(_truly_tft240240_data_table)/sizeof(_truly_tft240240_data_table[0]),

    .cmd_table          = &_truly_tft240240_cmd_table[0],
    .cmd_table_num      = sizeof(_truly_tft240240_cmd_table)/sizeof(_truly_tft240240_cmd_table[0])
};


int truly_tft240240_init(void)
{
    /* reset lcd pane */
    gpio_direction_output(LCD_RST_PORT, LCD_RST_PIN, 0);        //reset
    rt_thread_delay(rt_tick_from_millisecond(50));
    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, 1);
    rt_thread_delay(rt_tick_from_millisecond(50));

    /* enable backlight */
    gpio_direction_output(LCD_BLEN_PORT, LCD_BLEN_PIN,1);
    gpio_direction_output(LCD_BLPWM_PORT, LCD_BLPWM_PIN,1);

    /* init lcd & register lcd device */
    rt_hw_slcd_init(&_truly_tft240240_config);

    return 0;
}

#endif
