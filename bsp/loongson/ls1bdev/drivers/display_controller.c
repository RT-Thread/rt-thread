/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-09     lgnq         first version for LS1B DC
 */

#include <rtthread.h>
#include "display_controller.h"

struct vga_struct vga_mode[] =
{
    {/*"640x480_70.00"*/    28560,  640,    664,    728,    816,    480,    481,    484,    500,    },
    {/*"640x640_60.00"*/    33100,  640,    672,    736,    832,    640,    641,    644,    663,    },
    {/*"640x768_60.00"*/    39690,  640,    672,    736,    832,    768,    769,    772,    795,    },
    {/*"640x800_60.00"*/    42130,  640,    680,    744,    848,    800,    801,    804,    828,    },
    {/*"800x480_70.00"*/    35840,  800,    832,    912,    1024,   480,    481,    484,    500,    },
    {/*"800x600_60.00"*/    38220,  800,    832,    912,    1024,   600,    601,    604,    622,    },
    {/*"800x640_60.00"*/    40730,  800,    832,    912,    1024,   640,    641,    644,    663,    },
    {/*"832x600_60.00"*/    40010,  832,    864,    952,    1072,   600,    601,    604,    622,    },
    {/*"832x608_60.00"*/    40520,  832,    864,    952,    1072,   608,    609,    612,    630,    },
    {/*"1024x480_60.00"*/   38170,  1024,   1048,   1152,   1280,   480,    481,    484,    497,    },
    {/*"1024x600_60.00"*/   48960,  1024,   1064,   1168,   1312,   600,    601,    604,    622,    },
    {/*"1024x640_60.00"*/   52830,  1024,   1072,   1176,   1328,   640,    641,    644,    663,    },
    {/*"1024x768_60.00"*/   64110,  1024,   1080,   1184,   1344,   768,    769,    772,    795,    },
    {/*"1152x764_60.00"*/   71380,  1152,   1208,   1328,   1504,   764,    765,    768,    791,    },
    {/*"1280x800_60.00"*/   83460,  1280,   1344,   1480,   1680,   800,    801,    804,    828,    },
    {/*"1280x1024_55.00"*/  98600,  1280,   1352,   1488,   1696,   1024,   1025,   1028,   1057,   },
    {/*"1440x800_60.00"*/   93800,  1440,   1512,   1664,   1888,   800,    801,    804,    828,    },
    {/*"1440x900_67.00"*/   120280, 1440,   1528,   1680,   1920,   900,    901,    904,    935,    },
};

ALIGN(16)
volatile rt_uint16_t _rt_framebuffer[FB_YSIZE][FB_XSIZE];
static struct rt_device_graphic_info _dc_info;

#define abs(x) ((x<0)?(-x):x)
#define min(a,b) ((a<b)?a:b)

int caclulate_freq(long long XIN, long long PCLK)
{
    int i;
    long long clk, clk1;
    int start, end;
    int mi;
    int pll,ctrl,div,div1,frac;

    pll = PLL_FREQ;
    ctrl = PLL_DIV_PARAM;
    rt_kprintf("pll=0x%x, ctrl=0x%x\n", pll, ctrl);
//  rt_kprintf("cpu freq is %d\n", tgt_pipefreq());
    start = -1;
    end = 1;

    for (i=start; i<=end; i++)
    {
        clk = (12+i+(pll&0x3f))*33333333/2;
        div = clk/(long)PCLK/1000;
        clk1 = (12+i+1+(pll&0x3f))*33333333/2;
        div1 = clk1/(long)PCLK/1000;
        if (div!=div1)
            break;
    }

    if (div!=div1)
    {
        frac = ((PCLK*1000*div1)*2*1024/33333333 - (12+i+(pll&0x3f))*1024)&0x3ff;
        pll = (pll & ~0x3ff3f)|(frac<<8)|((pll&0x3f)+i);
        ctrl = ctrl&~(0x1f<<26)|(div1<<26)|(1<<31);
    }
    else
    {
        clk = (12+start+(pll&0x3f))*33333333/2;
        clk1 = (12+end+(pll&0x3f))*33333333/2;
        if (abs((long)clk/div/1000-PCLK)<abs((long)clk1/(div+1)/1000-PCLK))
        {
            pll = (pll & ~0x3ff3f)|((pll&0x3f)+start);
            ctrl = ctrl&~(0x1f<<26)|(div<<26)|(1<<31);
        }
        else
        {
            pll = (pll & ~0x3ff3f)|((pll&0x3f)+end);
            ctrl = ctrl&~(0x1f<<26)|((div+1)<<26)|(1<<31);
        }
    }

    rt_kprintf("new pll=0x%x, ctrl=0x%x\n", pll, ctrl);
    ctrl |= 0x2a00;
    PLL_DIV_PARAM = ctrl;
    PLL_FREQ = pll;
    rt_thread_delay(10);
//  initserial(0);
//  _probe_frequencies();
//  rt_kprintf("cpu freq is %d\n",tgt_pipefreq());
    return 0;
}

static rt_err_t rt_dc_init(rt_device_t dev)
{
    int i, out, mode=-1;
    int val;

    for (i=0; i<sizeof(vga_mode)/sizeof(struct vga_struct); i++)
    {
        if (vga_mode[i].hr == FB_XSIZE && vga_mode[i].vr == FB_YSIZE)
        {
            mode=i;
#ifdef LS1FSOC
//          out = caclulatefreq(APB_CLK/1000,vga_mode[i].pclk);
//          rt_kprintf("out=%x\n",out);
            /*inner gpu dc logic fifo pll ctrl,must large then outclk*/
//          *(volatile int *)0xbfd00414 = out+1;
            /*output pix1 clock  pll ctrl*/
//          *(volatile int *)0xbfd00410 = out;
            /*output pix2 clock pll ctrl */
//          *(volatile int *)0xbfd00424 = out;
#else
            caclulate_freq(APB_CLK/1000, vga_mode[i].pclk);
#endif
            break;
        }
    }

    if (mode<0)
    {
        rt_kprintf("\n\n\nunsupported framebuffer resolution\n\n\n");
        return;
    }

    DC_FB_CONFIG = 0x0;
    DC_FB_CONFIG = 0x3; //  // framebuffer configuration RGB565
    DC_FB_BUFFER_ADDR0 = (rt_uint32_t)_rt_framebuffer - 0x80000000;
    DC_FB_BUFFER_ADDR1 = (rt_uint32_t)_rt_framebuffer - 0x80000000;
    DC_DITHER_CONFIG = 0x0;
    DC_DITHER_TABLE_LOW = 0x0;
    DC_DITHER_TABLE_HIGH = 0x0;
    DC_PANEL_CONFIG = 0x80001311;
    DC_PANEL_TIMING = 0x0;

    DC_HDISPLAY = (vga_mode[mode].hfl<<16) | vga_mode[mode].hr;
    DC_HSYNC = 0x40000000 | (vga_mode[mode].hse<<16) | vga_mode[mode].hss;
    DC_VDISPLAY = (vga_mode[mode].vfl<<16) | vga_mode[mode].vr;
    DC_VSYNC = 0x40000000 | (vga_mode[mode].vse<<16) | vga_mode[mode].vss;

#if defined(CONFIG_VIDEO_32BPP)
    DC_FB_CONFIG = 0x00100104;
    DC_FB_BUFFER_STRIDE = FB_XSIZE*4;
#elif defined(CONFIG_VIDEO_16BPP)
    DC_FB_CONFIG = 0x00100103;
    DC_FB_BUFFER_STRIDE = (FB_XSIZE*2+255)&(~255);
#elif defined(CONFIG_VIDEO_15BPP)
    DC_FB_CONFIG = 0x00100102;
    DC_FB_BUFFER_STRIDE = FB_XSIZE*2;
#elif defined(CONFIG_VIDEO_12BPP)
    DC_FB_CONFIG = 0x00100101;
    DC_FB_BUFFER_STRIDE = FB_XSIZE*2;
#else  //640x480-32Bits
    DC_FB_CONFIG = 0x00100104;
    DC_FB_BUFFER_STRIDE = FB_XSIZE*4;
#endif //32Bits

#ifdef LS1GSOC
    /*fix ls1g dc
     *first switch to tile mode
     *change origin register to 0
     *goback nomal mode
     */
    {
        val = DC_FB_CONFIG;
        DC_FB_CONFIG = val | 0x10;
        DC_FB_BUFFER_ORIGIN = 0;
        DC_FB_BUFFER_ORIGIN;
        rt_thread_delay(10);
        DC_FB_CONFIG;
        DC_FB_CONFIG = val;
    }
#endif

    return RT_EOK;
}

static rt_err_t rt_dc_control(rt_device_t dev, int cmd, void *args)
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
    _dc_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
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
}
