/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-8-11       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_DISP)

#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "NuMicro.h"
#include <drv_sys.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if !defined(DISP_USING_LCD_IDX)
    #define DISP_USING_LCD_IDX eDispLcd_1024x600
#endif

#if !defined(BSP_LCD_BPP)
    #define BSP_LCD_BPP 32
#endif

#if !defined(DISP_USING_OVERLAY)
    #define DISP_USING_OVERLAY
#endif

#define DEF_VPOST_BUFFER_NUMBER 3

/* Private typedef --------------------------------------------------------------*/
struct nu_disp
{
    struct rt_device      dev;
    char                 *name;
    E_DISP_LAYER          layer;
    uint32_t              last_commit;
    uint32_t              ref_count;
    struct rt_device_graphic_info info;
    rt_uint8_t            *pu8FBDMABuf;
};
typedef struct nu_disp *nu_disp_t;

static volatile uint32_t g_u32VSyncBlank = 0;
static struct rt_completion vsync_wq;

#if defined(DISP_USING_OVERLAY)
static rt_mutex_t disp_lock;
#endif

static struct nu_disp nu_fbdev[eLayer_Cnt] =
{
    {
        .name  = "lcd",
        .layer = eLayer_Video,
        .ref_count = 0,
    }
#if defined(DISP_USING_OVERLAY)
    , {
        .name  = "overlay",
        .layer = eLayer_Overlay,
        .ref_count = 0,
    }
#endif
};

rt_weak void nu_lcd_backlight_on(void) { }

rt_weak void nu_lcd_backlight_off(void) { }

static void nu_disp_isr(int vector, void *param)
{
    /* Get DISP INTSTS */
    if (DISP_GET_INTSTS())
    {
        g_u32VSyncBlank++;
        rt_completion_done(&vsync_wq);
    }
}

static rt_err_t disp_layer_open(rt_device_t dev, rt_uint16_t oflag)
{
    nu_disp_t psDisp = (nu_disp_t)dev;
    RT_ASSERT(psDisp != RT_NULL);

#if defined(DISP_USING_OVERLAY)
    rt_mutex_take(disp_lock, RT_WAITING_FOREVER);
#endif

    psDisp->ref_count++;

#if defined(DISP_USING_OVERLAY)
    if (psDisp->layer == eLayer_Overlay)    // Depend on video layer
    {
        nu_fbdev[eLayer_Video].ref_count++;
    }
#endif

    if (nu_fbdev[eLayer_Video].ref_count == 1)
    {
        DISP_SetTransparencyMode(eLayer_Video, eMASK);
        DISP_ENABLE_INT();
        DISP_Trigger(eLayer_Video, 1);
    }

#if defined(DISP_USING_OVERLAY)
    if (nu_fbdev[eLayer_Overlay].ref_count == 1)
    {
        DISP_SetTransparencyMode(eLayer_Overlay, eOPAQUE);
        DISP_Trigger(eLayer_Overlay, 1);
    }
#endif

#if defined(DISP_USING_OVERLAY)
    rt_mutex_release(disp_lock);
#endif

    return RT_EOK;
}

static rt_err_t disp_layer_close(rt_device_t dev)
{
    nu_disp_t psDisp = (nu_disp_t)dev;
    RT_ASSERT(psDisp != RT_NULL);

#if defined(DISP_USING_OVERLAY)
    rt_mutex_take(disp_lock, RT_WAITING_FOREVER);
#endif

    psDisp->ref_count--;

#if defined(DISP_USING_OVERLAY)
    if (psDisp->layer == eLayer_Overlay)    // Depend on video layer
    {
        nu_fbdev[eLayer_Video].ref_count--;
    }

    if (nu_fbdev[eLayer_Overlay].ref_count == 0)
    {
        DISP_Trigger(eLayer_Overlay, 0);
    }
#endif

    if (nu_fbdev[eLayer_Video].ref_count == 0)
    {
        DISP_DISABLE_INT();
        DISP_Trigger(eLayer_Video, 0);
    }

#if defined(DISP_USING_OVERLAY)
    rt_mutex_release(disp_lock);
#endif

    return RT_EOK;
}

static rt_err_t disp_layer_control(rt_device_t dev, int cmd, void *args)
{
    nu_disp_t psDisp = (nu_disp_t)dev;
    RT_ASSERT(psDisp != RT_NULL);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_POWERON:
    {
        nu_lcd_backlight_on();
    }
    break;

    case RTGRAPHIC_CTRL_POWEROFF:
    {
        nu_lcd_backlight_off();
    }
    break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *) args;
        RT_ASSERT(info != RT_NULL);
        rt_memcpy(args, (void *)&psDisp->info, sizeof(struct rt_device_graphic_info));
    }
    break;

    case RTGRAPHIC_CTRL_SET_MODE:
    {
        int pixfmt, bpp;
        E_FB_FMT eFBFmt;

        RT_ASSERT(args);
        pixfmt = *((int *)args);

        switch (pixfmt)
        {
        case RTGRAPHIC_PIXEL_FORMAT_RGB565:
            eFBFmt = eFBFmt_R5G6B5;
            bpp = 16;
            break;
        case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
            eFBFmt = eFBFmt_A8R8G8B8;
            bpp = 32;
            break;
        case RTGRAPHIC_PIXEL_FORMAT_MONO:
        case RTGRAPHIC_PIXEL_FORMAT_GRAY4:
        case RTGRAPHIC_PIXEL_FORMAT_GRAY16:
        case RTGRAPHIC_PIXEL_FORMAT_RGB332:
        case RTGRAPHIC_PIXEL_FORMAT_RGB444:
        case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        case RTGRAPHIC_PIXEL_FORMAT_RGB666:
        case RTGRAPHIC_PIXEL_FORMAT_RGB888:
        case RTGRAPHIC_PIXEL_FORMAT_BGR888:
        case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        case RTGRAPHIC_PIXEL_FORMAT_RESERVED:
        default:
            return -RT_ERROR;
        }
        psDisp->info.bits_per_pixel = bpp;
        psDisp->info.pixel_format = pixfmt;
        psDisp->info.pitch = psDisp->info.width * (bpp >> 3U);

        /* Initial LCD */
        DISP_SetFBFmt(psDisp->layer, eFBFmt, psDisp->info.pitch);
    }
    break;

    case RTGRAPHIC_CTRL_GET_MODE:
    {
        RT_ASSERT(args);
        *((int *)args) = psDisp->info.pixel_format;
    }
    break;

    case RTGRAPHIC_CTRL_PAN_DISPLAY:
    {
        if (args != RT_NULL)
        {
            uint32_t u32BufPtr = (uint32_t)args;
            psDisp->last_commit = g_u32VSyncBlank;

            /* Pan display */
            return (DISP_SetFBAddr(psDisp->layer, u32BufPtr) == 0) ? RT_EOK : -RT_ERROR;
        }
        else
            return -RT_ERROR;
    }
    break;

    case RTGRAPHIC_CTRL_WAIT_VSYNC:
    {
        if (args != RT_NULL)
            psDisp->last_commit = g_u32VSyncBlank + 1;

        if (psDisp->last_commit >= g_u32VSyncBlank)
        {
            rt_completion_init(&vsync_wq);
            rt_completion_wait(&vsync_wq, RT_TICK_PER_SECOND / DISP_LCDTIMING_GetFPS(RT_NULL));
        }
    }
    break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t disp_layer_init(rt_device_t dev)
{
    nu_disp_t psDisp = (nu_disp_t)dev;
    RT_ASSERT(psDisp != RT_NULL);

    rt_completion_init(&vsync_wq);
    return RT_EOK;
}

int rt_hw_disp_init(void)
{
    int i;
    rt_err_t ret;

    /* Get LCD panel instance by ID. */
    const DISP_LCD_INFO *psDispLcdInstance = DISP_GetLCDInst(DISP_USING_LCD_IDX);
    RT_ASSERT(psDispLcdInstance != RT_NULL);

    /* Initial LCD */
    DISP_LCDInit(psDispLcdInstance);

    for (i = eLayer_Video;
#if defined(DISP_USING_OVERLAY)
            i < eLayer_Cnt;
#else
            i < eLayer_Overlay;
#endif
            i++)
    {
        E_FB_FMT eFbFmt;
        nu_disp_t psDisp = &nu_fbdev[i];
        rt_memset((void *)&psDisp->info, 0, sizeof(struct rt_device_graphic_info));

        /* Register Disp device information */
        psDisp->info.bits_per_pixel = BSP_LCD_BPP;
        psDisp->info.pixel_format = (BSP_LCD_BPP == 32) ? RTGRAPHIC_PIXEL_FORMAT_ARGB888 : RTGRAPHIC_PIXEL_FORMAT_RGB565;
        psDisp->info.pitch = psDispLcdInstance->u32ResolutionWidth * (BSP_LCD_BPP / 8);
        psDisp->info.width = psDispLcdInstance->u32ResolutionWidth;
        psDisp->info.height = psDispLcdInstance->u32ResolutionHeight;

        /* Get pointer of video frame buffer */
        rt_uint8_t *pu8FBDMABuf = rt_malloc_align(psDisp->info.pitch * psDisp->info.height * DEF_VPOST_BUFFER_NUMBER, 128);
        if (pu8FBDMABuf == NULL)
        {
            rt_kprintf("Fail to get VRAM buffer for %s layer.\n", psDisp->name);
            RT_ASSERT(0);
        }
        else
        {
            /* Register non-cacheable DMA address to upper layer. */
            psDisp->info.framebuffer = (rt_uint8_t *)((uint32_t)pu8FBDMABuf | UNCACHEABLE);

            uint32_t u32FBSize = psDisp->info.pitch * psDispLcdInstance->u32ResolutionHeight;
            psDisp->info.smem_len = u32FBSize * DEF_VPOST_BUFFER_NUMBER;
            rt_memset(psDisp->info.framebuffer, 0, psDisp->info.smem_len);
        }

        eFbFmt = (psDisp->info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888) ? eFBFmt_A8R8G8B8 : eFBFmt_R5G6B5 ;
        ret = (rt_err_t)DISP_SetFBConfig(i, eFbFmt, psDisp->info.width, psDisp->info.height, (uint32_t)pu8FBDMABuf);
        RT_ASSERT(ret == RT_EOK);
        psDisp->pu8FBDMABuf = pu8FBDMABuf;

        /* Register member functions of lcd device */
        psDisp->dev.type    = RT_Device_Class_Graphic;
        psDisp->dev.init    = disp_layer_init;
        psDisp->dev.open    = disp_layer_open;
        psDisp->dev.close   = disp_layer_close;
        psDisp->dev.control = disp_layer_control;

        /* register graphic device driver */
        ret = rt_device_register(&psDisp->dev, psDisp->name, RT_DEVICE_FLAG_RDWR);
        RT_ASSERT(ret == RT_EOK);

        rt_kprintf("%s's fbdev video memory at 0x%08x.\n", psDisp->name, psDisp->info.framebuffer);
    }

#if defined(DISP_USING_OVERLAY)
    /* Initial display lock */
    disp_lock = rt_mutex_create("displock", RT_IPC_FLAG_FIFO);
    RT_ASSERT(disp_lock);
#endif

    /* Register ISR */
    rt_hw_interrupt_install(DISP_IRQn, nu_disp_isr, RT_NULL, "DISP");

    /* Enable interrupt. */
    rt_hw_interrupt_umask(DISP_IRQn);

    rt_kprintf("LCD panel timing is %d FPS.\n", DISP_LCDTIMING_GetFPS(&psDispLcdInstance->sLcdTiming));

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_disp_init);

static void lcd_show_video_layer(void)
{
    rt_device_open(&nu_fbdev[eLayer_Video].dev, RT_DEVICE_FLAG_RDWR);
}
MSH_CMD_EXPORT(lcd_show_video_layer, show video layer);

static void lcd_hide_video_layer(void)
{
    rt_device_close(&nu_fbdev[eLayer_Video].dev);
}
MSH_CMD_EXPORT(lcd_hide_video_layer, hide video layer);

#if defined(DISP_USING_OVERLAY)

int nu_overlay_set_colkey(uint32_t u32Low, uint32_t u32High)
{
    DISP_SetColorKeyValue(u32Low, u32High);
    DISP_SetTransparencyMode(eLayer_Overlay, eKEY);
    return 0;
}
RTM_EXPORT(nu_overlay_set_colkey);

/* Support "lcd_set_overlay_colkey" command line in msh mode */
static rt_err_t lcd_set_overlay_colkey(int argc, char **argv)
{
    unsigned int index, len, arg[2];

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 3) ? 3 : argc;

    for (index = 0; index < (len - 1); index ++)
    {
        if (rt_sscanf(argv[index + 1], "%x", &arg[index]) != 1)
            return -1;
    }
    rt_kprintf("colkeylow:0x%08x colkeyhigh:0x%08x\n", arg[0], arg[1]);
    nu_overlay_set_colkey(arg[0], arg[1]);

    return 0;
}
MSH_CMD_EXPORT(lcd_set_overlay_colkey, e.g: lcd_set_overlay_colkey colkeylow colkeyhigh);

static void lcd_show_overlay_layer(void)
{
    rt_device_open(&nu_fbdev[eLayer_Overlay].dev, RT_DEVICE_FLAG_RDWR);
}

static void lcd_hide_overlay_layer(void)
{
    rt_device_close(&nu_fbdev[eLayer_Overlay].dev);
}
MSH_CMD_EXPORT(lcd_show_overlay_layer, show overlay layer);
MSH_CMD_EXPORT(lcd_hide_overlay_layer, hide overlay layer);

static void lcd_fill_layer_color(void)
{
    nu_disp_t psDispLayer;
    int idx;
    for (idx = eLayer_Overlay; //eLayer_Video;
#if defined(DISP_USING_OVERLAY)
            idx < eLayer_Cnt;
#else
            idx < eLayer_Overlay;
#endif
            idx++)
    {
        psDispLayer = &nu_fbdev[idx];
        if (psDispLayer->info.framebuffer != RT_NULL)
        {
            int i;
            uint32_t fill_num = psDispLayer->info.height * psDispLayer->info.width;
            uint32_t *fbmem_start = (uint32_t *)psDispLayer->info.framebuffer;
            uint32_t color = (0x3F << 24) | (rand() % 0x1000000) ;
            rt_kprintf("fill color=0x%08x on %s layer\n", color, psDispLayer->name);
            for (i = 0; i < fill_num; i++)
            {
                rt_memcpy((void *)&fbmem_start[i], &color, (psDispLayer->info.bits_per_pixel / 8));
            }
        }
    }
}
MSH_CMD_EXPORT(lcd_fill_layer_color, fill random color on overlay layer);

static rt_err_t lcd_set_alphablend_opmode(int argc, char **argv)
{
    unsigned int index, len, arg[1];

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 2) ? 2 : argc;

    for (index = 0; index < (len - 1); index ++)
    {
        if (rt_sscanf(argv[index + 1], "%x", &arg[index]) != 1)
            return -1;
    }

    rt_kprintf("opmode:0x%08x\n", arg[0]);

    if (arg[0] <= DC_BLEND_MODE_SRC_OUT)
        DISP_SetBlendOpMode(arg[0], eGloAM_NORMAL, eGloAM_NORMAL);

    return 0;
}
MSH_CMD_EXPORT(lcd_set_alphablend_opmode, Set alpha blending opmode);
#endif

#endif /* if defined(BSP_USING_DISP) */
