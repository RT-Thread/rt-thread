/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2011-08-09     lgnq         first version for LS1B DC
 * 2015-07-06    chinesebear   modified for loongson 1c
 * 2018-01-06    sundm75       modified for smartloong
 */
 #include <rtthread.h>

#include "display_controller.h"
#include "../../libraries/ls1c_pwm.h"
#include "../../libraries/ls1c_public.h"
#include "../../libraries/ls1c_gpio.h"
#include "../../libraries/ls1c_pin.h"

#if (defined PKG_USING_GUIENGINE) || (defined RT_USING_RTGUI)
struct vga_struct vga_mode[] =
{
    {/*"480x272_60.00"*/    111000,   480,    482,    523,    525,    272,    274,    284,    286,    },
    {/*"640x480_70.00"*/    28560,  640,    664,    728,    816,    480,    481,    484,    500,    },
    {/*"640x640_60.00"*/    33100,    640,    672,    736,    832,    640,    641,    644,    663,    },
    {/*"640x768_60.00"*/    39690,    640,    672,    736,    832,    768,    769,    772,    795,    },
    {/*"640x800_60.00"*/    42130,    640,    680,    744,    848,    800,    801,    804,    828,    },
    {/*"800x480_70.00"*/    35840,  800,    832,    912,    1024,   480,    481,    484,    500,    },
    {/*"800x600_60.00"*/    38220,    800,    832,    912,    1024,    600,    601,    604,    622,    },
    {/*"800x640_60.00"*/    40730,    800,    832,    912,    1024,    640,    641,    644,    663,    },
    {/*"832x600_60.00"*/    40010,    832,    864,    952,    1072,    600,    601,    604,    622,    },
    {/*"832x608_60.00"*/    40520,    832,    864,    952,    1072,    608,    609,    612,    630,    },
    {/*"1024x480_60.00"*/    38170,    1024,    1048,    1152,    1280,    480,    481,    484,    497,    },
    {/*"1024x600_60.00"*/    48960,    1024,    1064,    1168,    1312,    600,    601,    604,    622,    },
    {/*"1024x640_60.00"*/    52830,    1024,    1072,    1176,    1328,    640,    641,    644,    663,    },
    {/*"1024x768_60.00"*/    64110,    1024,    1080,    1184,    1344,    768,    769,    772,    795,    },
    {/*"1152x764_60.00"*/   71380,  1152,   1208,   1328,   1504,   764,    765,    768,    791,    },
    {/*"1280x800_60.00"*/   83460,  1280,   1344,   1480,   1680,   800,    801,    804,    828,    },
    {/*"1280x1024_55.00"*/  98600,  1280,   1352,   1488,   1696,   1024,   1025,   1028,   1057,   },
    {/*"1440x800_60.00"*/   93800,  1440,   1512,   1664,   1888,   800,    801,    804,    828,    },
    {/*"1440x900_67.00"*/   120280, 1440,   1528,   1680,   1920,   900,    901,    904,    935,    },
};

static volatile int fb_index = 0;

rt_align(16)
volatile rt_uint16_t _rt_framebuffer[FB_YSIZE][FB_XSIZE];
volatile rt_uint16_t _rt_framebuffer0[FB_YSIZE][FB_XSIZE];
volatile rt_uint16_t _rt_framebuffer1[FB_YSIZE][FB_XSIZE];
static struct rt_device_graphic_info _dc_info;

static void pwminit(void)
{
    pwm_info_t pwm_info;
    pwm_info.gpio = LS1C_PWM0_GPIO06;           // pwm引脚位gpio06
    pwm_info.mode = PWM_MODE_NORMAL;            // 正常模式--连续输出pwm波形
    pwm_info.duty = 0.85;                       // pwm占空比 85%
    pwm_info.period_ns = 5*1000*1000;            // pwm周期5ms

    /*pwm初始化，初始化后立即产生pwm波形*/
    pwm_init(&pwm_info);

    /* 使能pwm */
    pwm_enable(&pwm_info);
}
int caclulate_freq(rt_uint32_t  XIN, rt_uint32_t PCLK)
{
    rt_uint32_t divider_int;
    rt_uint32_t needed_pixclk;
    rt_uint32_t  pll_clk, pix_div;
    rt_uint32_t  regval;


    pll_clk = PLL_FREQ; // 读CPU的 PLL及SDRAM 分频系数
    pll_clk =( pll_clk>>8 )& 0xff;
    pll_clk = XIN *  pll_clk / 4 ;
    pix_div = PLL_DIV_PARAM;//读CPU的 CPU/CAMERA/DC 分频系数
    pix_div = (pix_div>>24)&0xff;
    rt_kprintf("old pll_clk=%d, pix_div=%d\n", pll_clk, pix_div);

    divider_int = pll_clk/(1000000) *PCLK/1000;
    if(divider_int%1000>=500)
        divider_int = divider_int/1000+1;
    else
        divider_int = divider_int/1000;
    rt_kprintf("divider_int = %d\n", divider_int);

    /* check whether divisor is too small. */
    if (divider_int < 1) {
        rt_kprintf("Warning: clock source is too slow.Try smaller resolution\n");
        divider_int = 1;
    }
    else if(divider_int > 100) {
        rt_kprintf("Warning: clock source is too fast.Try smaller resolution\n");
        divider_int = 100;
    }
    /* 配置分频寄存器 */
    {
        rt_uint32_t regval = 0;
        regval = PLL_DIV_PARAM;
        /*首先需要把分频使能位清零 */
        regval &= ~0x80000030;    //PIX_DIV_VALID  PIX_SEL  置0
        regval &= ~(0x3f<<24);    //PIX_DIV 清零
        regval |= divider_int << 24;
        PLL_DIV_PARAM = regval;
        regval |= 0x80000030;    //PIX_DIV_VALID  PIX_SEL  置1
        PLL_DIV_PARAM = regval;
    }
    rt_kprintf("new PLL_FREQ=0x%x, PLL_DIV_PARAM=0x%x\n", PLL_FREQ, PLL_DIV_PARAM);
    rt_thread_delay(10);
    return 0;
}

static rt_err_t rt_dc_init(rt_device_t dev)
{
    int i, out, mode=-1;
    int val;

    rt_kprintf("PWM initied\n");
    /* Set the back light PWM. */
    pwminit();

    for (i=0; i<sizeof(vga_mode)/sizeof(struct vga_struct); i++)
    {
        if (vga_mode[i].hr == FB_XSIZE && vga_mode[i].vr == FB_YSIZE)
        {
            mode=i;
            /* 计算时钟 配置频率*/
            caclulate_freq(OSC, vga_mode[i].pclk);
            break;
        }
    }

    if (mode<0)
    {
        rt_kprintf("\n\n\nunsupported framebuffer resolution\n\n\n");
        return -RT_ERROR;
    }

    DC_FB_CONFIG = 0x0;
    DC_FB_CONFIG = 0x3; //    // framebuffer configuration RGB565
    DC_DITHER_CONFIG = 0x0;  //颜色抖动配置寄存器
    DC_DITHER_TABLE_LOW = 0x0; //颜色抖动查找表低位寄存器
    DC_DITHER_TABLE_HIGH = 0x0; //颜色抖动查找表高位寄存器
    DC_PANEL_CONFIG = 0x80001311; //液晶面板配置寄存器
    DC_PANEL_TIMING = 0x0;

    DC_HDISPLAY = (vga_mode[mode].hfl<<16) | vga_mode[mode].hr;
    DC_HSYNC = 0x40000000 | (vga_mode[mode].hse<<16) | vga_mode[mode].hss;
    DC_VDISPLAY = (vga_mode[mode].vfl<<16) | vga_mode[mode].vr;
    DC_VSYNC = 0x40000000 | (vga_mode[mode].vse<<16) | vga_mode[mode].vss;

#if defined(CONFIG_VIDEO_32BPP)
    DC_FB_CONFIG = 0x00100105;
    DC_FB_BUFFER_STRIDE = FB_XSIZE*4;
#elif defined(CONFIG_VIDEO_24BPP)
    DC_FB_CONFIG = 0x00100104;
    DC_FB_BUFFER_STRIDE = (FB_XSIZE*4+255)&(~255);
#elif defined(CONFIG_VIDEO_16BPP)// 使用这个选项
    DC_FB_CONFIG = 0x00100103;
    DC_FB_BUFFER_STRIDE = (FB_XSIZE*2+0x7f)&(~0x7f);
#elif defined(CONFIG_VIDEO_15BPP)
    DC_FB_CONFIG = 0x00100102;
    DC_FB_BUFFER_STRIDE =  (FB_XSIZE*2+255)&(~255);
#elif defined(CONFIG_VIDEO_12BPP)
    DC_FB_CONFIG = 0x00100101;
    DC_FB_BUFFER_STRIDE =  (FB_XSIZE*2+255)&(~255);
#else
    DC_FB_CONFIG = 0x00100104;
    DC_FB_BUFFER_STRIDE = (FB_XSIZE*4+255)&(~255);
#endif
    return RT_EOK;
}

static rt_err_t rt_dc_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        if (fb_index == 0)
        {
            DC_FB_BUFFER_ADDR0 = (rt_uint32_t)_rt_framebuffer1 - 0x80000000;
            DC_FB_BUFFER_ADDR1 = (rt_uint32_t)_rt_framebuffer1 - 0x80000000;
            rt_memcpy((void *)_rt_framebuffer1, (const void *)_rt_framebuffer, sizeof(_rt_framebuffer));
            rt_memcpy((void *)_rt_framebuffer1, (const void *)_rt_framebuffer, sizeof(_rt_framebuffer));
            fb_index =1;
        }
        else
        {
            DC_FB_BUFFER_ADDR0 = (rt_uint32_t)_rt_framebuffer0 - 0x80000000;
            DC_FB_BUFFER_ADDR1 = (rt_uint32_t)_rt_framebuffer0 - 0x80000000;
            rt_memcpy((void *)_rt_framebuffer0, (const void *)_rt_framebuffer, sizeof(_rt_framebuffer));
            rt_memcpy((void *)_rt_framebuffer0, (const void *)_rt_framebuffer, sizeof(_rt_framebuffer));
            fb_index =0;
        }
        break;
    }
    case RTGRAPHIC_CTRL_POWERON:
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &_dc_info, sizeof(_dc_info));
        break;
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

void rt_hw_dc_init(void)
{
    rt_device_t dc = rt_malloc(sizeof(struct rt_device));
    if (dc == RT_NULL)
    {
        rt_kprintf("dc == RT_NULL\n");
        return; /* no memory yet */
    }

    _dc_info.bits_per_pixel = 16;
    _dc_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    _dc_info.framebuffer = (rt_uint8_t*)HW_FB_ADDR;
    _dc_info.width = FB_XSIZE;
    _dc_info.height = FB_YSIZE;

    /* init device structure */
    dc->type = RT_Device_Class_Graphic;
    dc->init = rt_dc_init;
    dc->open = RT_NULL;
    dc->close = RT_NULL;
    dc->control = rt_dc_control;
    dc->user_data = (void*)&_dc_info;

    /* register Display Controller device to RT-Thread */
    rt_device_register(dc, "dc", RT_DEVICE_FLAG_RDWR);

    rt_device_init(dc);
}

#include <rtgui/driver.h>
#include "display_controller.h"

/* initialize for gui driver */
int rtgui_lcd_init(void)
{
    rt_device_t dc;
    rt_kprintf("DC initied\n");

    pin_set_purpose(76, PIN_PURPOSE_OTHER);
    pin_set_remap(76, PIN_REMAP_DEFAULT);

     /* init Display Controller */
    rt_hw_dc_init();

    /* find Display Controller device */
    dc = rt_device_find("dc");

    /* set Display Controller device as rtgui graphic driver */
    rtgui_graphic_set_device(dc);

    return 0;
}

INIT_DEVICE_EXPORT(rtgui_lcd_init);

#endif
