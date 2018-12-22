/*
 * File      : drv_slcdc_OTM4802.c
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

#ifdef RT_USING_OTM4802

#define LCD_WIDTH       480
#define LCD_HEIGHT      320

rt_uint32_t _lcm_cmd_table[]=
{
    0x2C2C2C2C,
};


const struct slcd_data_table _lcm_data_table[] =
{
    /* LCD init code */
    {SMART_CONFIG_CMD, 0xff},   //Command 2 Enable
    {SMART_CONFIG_DATA, 0x48},
    {SMART_CONFIG_DATA, 0x02},
    {SMART_CONFIG_DATA, 0x01},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x80},
    {SMART_CONFIG_CMD, 0xff},  //ORISE Command Enable
    {SMART_CONFIG_DATA, 0x48},
    {SMART_CONFIG_DATA, 0x02},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x90},
    {SMART_CONFIG_CMD, 0xFF},  //MPU 16bit setting
    {SMART_CONFIG_DATA, 0x01},   //02-16BIT MCU,01-8BIT MCU

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x93},
    {SMART_CONFIG_CMD, 0xFF},  //SW MPU enable
    {SMART_CONFIG_DATA, 0x20},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0x51},    //Wright Display brightness
    {SMART_CONFIG_DATA, 0xf0},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0x53},   // Wright CTRL Display
    {SMART_CONFIG_DATA, 0x24},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0xb1},
    {SMART_CONFIG_CMD, 0xc5},   //VSEL setting
    {SMART_CONFIG_DATA, 0x00},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0xB0},
    {SMART_CONFIG_CMD, 0xc4},   //Gate Timing control
    {SMART_CONFIG_DATA, 0x02},
    {SMART_CONFIG_DATA, 0x08},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x00},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x90},
    {SMART_CONFIG_CMD, 0xc0},   //TCON MCLK Shift Control
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x0f},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x15},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x17},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x82},
    {SMART_CONFIG_CMD, 0xc5},  //Adjust pump phase
    {SMART_CONFIG_DATA, 0x01},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x90},
    {SMART_CONFIG_CMD, 0xc5},  //Adjust pump phase
    {SMART_CONFIG_DATA, 0x47},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0xd8},  //GVDD/NGVDD Setting
    {SMART_CONFIG_DATA, 0x58},  //58,17V
    {SMART_CONFIG_DATA, 0x58},  //58

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0xd9},  //VCOM Setting
    {SMART_CONFIG_DATA, 0xb0},  //

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x91},
    {SMART_CONFIG_CMD, 0xb3},  //Display setting
    {SMART_CONFIG_DATA, 0xC0},
    {SMART_CONFIG_DATA, 0x25},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x81},
    {SMART_CONFIG_CMD, 0xC1}, //Osillator Adjustment:70Hz
    {SMART_CONFIG_DATA, 0x77},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0xe1},   //Gamma setting(positive)
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x09},
    {SMART_CONFIG_DATA, 0x04},
    {SMART_CONFIG_DATA, 0x02},
    {SMART_CONFIG_DATA, 0x0b},
    {SMART_CONFIG_DATA, 0x0a},
    {SMART_CONFIG_DATA, 0x09},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x08},
    {SMART_CONFIG_DATA, 0x10},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x06},
    {SMART_CONFIG_DATA, 0x11},
    {SMART_CONFIG_DATA, 0x09},
    {SMART_CONFIG_DATA, 0x01},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0xe2},  //Gamma setting(negative)
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x09},
    {SMART_CONFIG_DATA, 0x04},
    {SMART_CONFIG_DATA, 0x02},
    {SMART_CONFIG_DATA, 0x0b},
    {SMART_CONFIG_DATA, 0x0a},
    {SMART_CONFIG_DATA, 0x09},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x08},
    {SMART_CONFIG_DATA, 0x10},
    {SMART_CONFIG_DATA, 0x05},
    {SMART_CONFIG_DATA, 0x06},
    {SMART_CONFIG_DATA, 0x11},
    {SMART_CONFIG_DATA, 0x09},
    {SMART_CONFIG_DATA, 0x01},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_CMD, 0x00},  //End Gamma setting
    {SMART_CONFIG_DATA, 0x00},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x80},
    {SMART_CONFIG_CMD, 0xff}, //Orise mode  command Disable
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},

    {SMART_CONFIG_CMD, 0x00},
    {SMART_CONFIG_DATA, 0x00},

    {SMART_CONFIG_CMD, 0xff}, //Command 2 Disable
    {SMART_CONFIG_DATA, 0xff},
    {SMART_CONFIG_DATA, 0xff},
    {SMART_CONFIG_DATA, 0xff},

    //{SMART_CONFIG_CMD, 0x35}, //TE ON
    //{SMART_CONFIG_DATA, 0x00},

    {SMART_CONFIG_CMD, 0x36}, //set X Y refresh direction
    {SMART_CONFIG_DATA, 0x60},

    {SMART_CONFIG_CMD, 0x3A},    //16-bit/pixe 565
    {SMART_CONFIG_DATA, 0x05},

    {SMART_CONFIG_CMD, 0x2A}, //Frame rate control   320
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, (LCD_WIDTH -1 ) >> 8},
    {SMART_CONFIG_DATA, (LCD_WIDTH -1 ) & 0xFF},

    {SMART_CONFIG_CMD, 0x2B}, //Display function control  480
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, 0x00},
    {SMART_CONFIG_DATA, (LCD_WIDTH -1 ) >> 8},
    {SMART_CONFIG_DATA, (LCD_HEIGHT -1 ) & 0xFF},

    {SMART_CONFIG_CMD, 0x11},
    {SMART_CONFIG_UDELAY, 120},
    {SMART_CONFIG_CMD, 0x29}, //display on

    {SMART_CONFIG_CMD, 0x2c},
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

int rt_hw_otm4802_init(void)
{
    rt_thread_delay(rt_tick_from_millisecond(500));

    /* Power ON */
    gpio_direction_output(GPIO_PORT_B,GPIO_Pin_16,1);   //RD = 1
    gpio_direction_output(GPIO_PORT_B,GPIO_Pin_18,1);   //CS = 1

    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, 0);
    rt_thread_delay(rt_tick_from_millisecond(20));
    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, 1);
    rt_thread_delay(rt_tick_from_millisecond(500));
    gpio_set_value(GPIO_PORT_B, GPIO_Pin_18, 0);        //CS = 0

    /* enable backlight */
    gpio_direction_output(LCD_BL_PORT, LCD_BL_PIN,1);

    /* init lcd & register lcd device */
    rt_hw_slcd_init(&_lcm_config);

    return 0;
}
#endif
