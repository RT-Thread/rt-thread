/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-4-13       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_VPOST)

#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "NuMicro.h"
#include <drv_sys.h>

/* Private typedef --------------------------------------------------------------*/

#define DEF_VPOST_BUFFER_NUMBER 3

typedef enum
{
    eVpost_LCD,
#if defined(BSP_USING_VPOST_OSD)
    eVpost_OSD,
#endif
    eVpost_Cnt
} E_VPOST_LAYER;

struct nu_vpost
{
    struct rt_device      dev;
    char                 *name;
    E_VPOST_LAYER         layer;
    IRQn_Type             irqn;
    E_SYS_IPRST           rstidx;
    E_SYS_IPCLK           clkidx;
    uint32_t              last_commit;
    struct rt_device_graphic_info info;
};
typedef struct nu_vpost *nu_vpost_t;

static volatile uint32_t s_u32VSyncBlank = 0;
static volatile uint32_t s_u32UnderRun = 0;
static struct rt_completion vsync_wq;

static struct nu_vpost nu_fbdev[eVpost_Cnt] =
{
    {
        .name = "lcd",
        .layer = eVpost_LCD,
        .irqn = IRQ_LCD,
        .rstidx = LCDRST,
        .clkidx = LCDCKEN,
    }
#if defined(BSP_USING_VPOST_OSD)
    , {
        .name = "osd",
        .layer = eVpost_OSD,
        .irqn = (IRQn_Type) - 1,
        .rstidx = SYS_IPRST_NA,
        .clkidx = SYS_IPCLK_NA,
    }
#endif
};

rt_weak void nu_lcd_backlight_on(void) { }

rt_weak void nu_lcd_backlight_off(void) { }
static rt_err_t vpost_layer_open(rt_device_t dev, rt_uint16_t oflag)
{
    nu_vpost_t psVpost = (nu_vpost_t)dev;
    RT_ASSERT(psVpost != RT_NULL);

    switch (psVpost->layer)
    {
    case eVpost_LCD:
        vpostVAStartTrigger();
        break;

#if defined(BSP_USING_VPOST_OSD)
    case eVpost_OSD:
        vpostVAStartTrigger();

        /* Set scale to 1:1 */
        vpostOSDScalingCtrl(1, 0, 0);

#if (BSP_LCD_BPP==32)
        vpostOSDSetColMask(0xff, 0xff, 0xff);
#else
        vpostOSDSetColMask(0x1f, 0x3f, 0x1f);
#endif

        /* Enable color key function */
        vpostOSDSetColKey(0, 0, 0);

        /* Configure overlay function of OSD to display OSD image */
        vpostOSDSetOverlay(DISPLAY_OSD, DISPLAY_OSD, 0);

        vpostOSDEnable();
        break;
#endif

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t vpost_layer_close(rt_device_t dev)
{
    nu_vpost_t psVpost = (nu_vpost_t)dev;
    RT_ASSERT(psVpost != RT_NULL);

    switch (psVpost->layer)
    {
    case eVpost_LCD:
#if defined(BSP_USING_VPOST_OSD)
        if (nu_fbdev[eVpost_OSD].dev.ref_count == 0)
#endif
            vpostVAStopTrigger();
        break;

#if defined(BSP_USING_VPOST_OSD)
    case eVpost_OSD:
        vpostOSDDisable();
        if (nu_fbdev[eVpost_LCD].dev.ref_count == 0)
        {
            /* Also stop displaying */
            vpostVAStopTrigger();
        }
        break;
#endif

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t vpost_layer_control(rt_device_t dev, int cmd, void *args)
{
    nu_vpost_t psVpost = (nu_vpost_t)dev;
    RT_ASSERT(psVpost != RT_NULL);

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
        rt_memcpy(args, (void *)&psVpost->info, sizeof(struct rt_device_graphic_info));
    }
    break;

    case RTGRAPHIC_CTRL_PAN_DISPLAY:
    {
        if (args != RT_NULL)
        {
            uint8_t *pu8BufPtr = (uint8_t *)args;

            psVpost->last_commit = s_u32VSyncBlank;

            /* Pan display */
            switch (psVpost->layer)
            {
            case eVpost_LCD:
                vpostSetFrameBuffer(pu8BufPtr);
                break;

#if defined(BSP_USING_VPOST_OSD)
            case eVpost_OSD:
                vpostSetOSDBuffer(pu8BufPtr);
                break;
#endif

            default:
                return -RT_ERROR;
            }

        }
        else
            return -RT_ERROR;
    }
    break;

    case RTGRAPHIC_CTRL_WAIT_VSYNC:
    {
        if (args != RT_NULL)
            psVpost->last_commit = s_u32VSyncBlank + 1;

        if (psVpost->last_commit >= s_u32VSyncBlank)
        {
            rt_completion_init(&vsync_wq);
            rt_completion_wait(&vsync_wq, RT_TICK_PER_SECOND / 60);
        }
    }
    break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t vpost_layer_init(rt_device_t dev)
{
    nu_vpost_t psVpost = (nu_vpost_t)dev;
    RT_ASSERT(psVpost != RT_NULL);

    /* Enable VPOST engine clock. */
    nu_sys_ipclk_enable(LCDCKEN);

    rt_completion_init(&vsync_wq);
    outpw(REG_LCM_INT_CS, VPOSTB_UNDERRUN_EN | VPOSTB_DISP_F_EN);
    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) | (1 << 4)));

    return RT_EOK;
}


static void nu_vpost_calculate_fps(void)
{
#define DEF_PERIOD_SEC  10
    static uint32_t u32LastTick = 0;
    static uint32_t u32VSyncBlank = 0;
    static uint32_t u32UnderRun = 0;
    uint32_t u32CurrTick = rt_tick_get();

    if ((u32CurrTick - u32LastTick) > (DEF_PERIOD_SEC * RT_TICK_PER_SECOND))
    {
        rt_kprintf("VPOST: %d FPS, URPS: %d\n",
                   (s_u32VSyncBlank - u32VSyncBlank) / DEF_PERIOD_SEC,
                   (s_u32UnderRun - u32UnderRun) / DEF_PERIOD_SEC);
        u32LastTick = u32CurrTick;
        u32VSyncBlank = s_u32VSyncBlank;
        u32UnderRun = s_u32UnderRun;
    }
}

static void nu_vpost_isr(int vector, void *param)
{
    /*
    #define VPOSTB_DISP_F_INT           ((UINT32)1<<31)
    #define VPOSTB_DISP_F_STATUS        (1<<30)
    #define VPOSTB_UNDERRUN_INT         (1<<29)
    #define VPOSTB_BUS_ERROR_INT        (1<<28)
    #define VPOSTB_FLY_ERR              (1<<27)
    #define VPOSTB_UNDERRUN_EN          (1<<1)
    #define VPOSTB_DISP_F_EN            (1)
    */

    uint32_t u32VpostIRQStatus = inpw(REG_LCM_INT_CS);
    if (u32VpostIRQStatus & VPOSTB_DISP_F_STATUS)
    {
        outpw(REG_LCM_INT_CS, inpw(REG_LCM_INT_CS) | VPOSTB_DISP_F_STATUS);

        s_u32VSyncBlank++;
        rt_completion_done(&vsync_wq);
    }
    else if (u32VpostIRQStatus & VPOSTB_UNDERRUN_INT)
    {
        s_u32UnderRun++;
        outpw(REG_LCM_INT_CS, inpw(REG_LCM_INT_CS) | VPOSTB_UNDERRUN_INT);
    }
    else if (u32VpostIRQStatus & VPOSTB_BUS_ERROR_INT)
    {
        outpw(REG_LCM_INT_CS, inpw(REG_LCM_INT_CS) | VPOSTB_BUS_ERROR_INT);
    }

    nu_vpost_calculate_fps();
}

int rt_hw_vpost_init(void)
{
    int i = -1;
    rt_err_t ret;

    VPOST_T *psVpostLcmInst = vpostLCMGetInstance(VPOST_USING_LCD_IDX);
    RT_ASSERT(psVpostLcmInst != RT_NULL);

    if ((psVpostLcmInst->u32DevWidth * psVpostLcmInst->u32DevHeight) > (480 * 272))
    {
        /* LCD clock is selected from UPLL and divide to 20MHz */
        outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0xff1f) | 0xE18);

        /* LCD clock is selected from UPLL and divide to 30MHz */
        //outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0xff1f) | 0x918);

        /* LCD clock is selected from UPLL and divide to 33.3MHz */
        //outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0xff1f) | 0x818);
    }
    else
    {
        /* LCD clock is selected from UPLL and divide to 10MHz */
        outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0xff1f) | 0xE19);
    }

    /* Initial LCM */
    vpostLCMInit(VPOST_USING_LCD_IDX);

    /* Set scale to 1:1 */
    vpostVAScalingCtrl(1, 0, 1, 0, VA_SCALE_INTERPOLATION);

    for (i = eVpost_LCD; i < eVpost_Cnt; i++)
    {
        nu_vpost_t psVpost = &nu_fbdev[i];
        rt_memset((void *)&psVpost->info, 0, sizeof(struct rt_device_graphic_info));

        /* Register VPOST information */
        psVpost->info.bits_per_pixel = BSP_LCD_BPP;
        psVpost->info.pixel_format = (BSP_LCD_BPP == 32) ? RTGRAPHIC_PIXEL_FORMAT_ARGB888 : RTGRAPHIC_PIXEL_FORMAT_RGB565;
        psVpost->info.pitch = psVpostLcmInst->u32DevWidth * (BSP_LCD_BPP / 8);
        psVpost->info.width = psVpostLcmInst->u32DevWidth;
        psVpost->info.height = psVpostLcmInst->u32DevHeight;

        /* Get pointer of video frame buffer */
        /* Set display color depth */
        /* Note: before get pointer of frame buffer, must set display color depth first */
        if (psVpost->layer == eVpost_LCD)
        {
#if (BSP_LCD_BPP==32)
            vpostSetVASrc(VA_SRC_RGB888);
#else
            vpostSetVASrc(VA_SRC_RGB565);
#endif
            psVpost->info.framebuffer = (rt_uint8_t *)vpostGetMultiFrameBuffer(DEF_VPOST_BUFFER_NUMBER);
        }
#if defined(BSP_USING_VPOST_OSD)
        else if (psVpost->layer == eVpost_OSD)
        {
            vpostOSDSetWindow(0, 0, psVpost->info.width, psVpost->info.height);

#if (BSP_LCD_BPP==32)
            vpostSetOSDSrc(OSD_SRC_RGB888);
#else
            vpostSetOSDSrc(OSD_SRC_RGB565);
#endif
            psVpost->info.framebuffer = (rt_uint8_t *)vpostGetMultiOSDBuffer(DEF_VPOST_BUFFER_NUMBER);
        }
#endif

        if (psVpost->info.framebuffer == NULL)
        {
            rt_kprintf("Fail to get VRAM buffer.\n");
            RT_ASSERT(0);
        }
        else
        {
            uint32_t u32FBSize = psVpost->info.pitch * psVpostLcmInst->u32DevHeight;
            psVpost->info.smem_len = u32FBSize * DEF_VPOST_BUFFER_NUMBER;
            rt_memset(psVpost->info.framebuffer, 0, u32FBSize);
        }

        /* Register member functions of lcd device */
        psVpost->dev.type = RT_Device_Class_Graphic;
        psVpost->dev.init = vpost_layer_init;
        psVpost->dev.open = vpost_layer_open;
        psVpost->dev.close = vpost_layer_close;
        psVpost->dev.control = vpost_layer_control;

        /* Register graphic device driver */
        ret = rt_device_register(&psVpost->dev, psVpost->name, RT_DEVICE_FLAG_RDWR);
        RT_ASSERT(ret == RT_EOK);

        if (psVpost->layer == eVpost_LCD)
        {
            rt_hw_interrupt_install(psVpost->irqn, nu_vpost_isr,  psVpost, psVpost->name);
            rt_hw_interrupt_umask(psVpost->irqn);
        }

        rt_kprintf("%s's fbmem at 0x%08x.\n", psVpost->name, psVpost->info.framebuffer);
    }

    /* For saving memory bandwidth. */
    vpostLCMDeinit();

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_vpost_init);


/* Support "vpost_set_osd_colkey" command line in msh mode */
static rt_err_t vpost_set_osd_colkey(int argc, char **argv)
{
    rt_uint32_t index, len, arg[4];

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 4) ? 4 : argc;

    for (index = 0; index < (len - 1); index ++)
    {
        arg[index] = atol(argv[index + 1]);
    }

    /* Enable color key function */
    vpostOSDSetColKey(arg[0], arg[1], arg[2]);

    /* Configure overlay function of OSD to display VIDEO image */
    vpostOSDSetOverlay(DISPLAY_VIDEO, DISPLAY_OSD, 0);

    return 0;
}
MSH_CMD_EXPORT(vpost_set_osd_colkey, e.g: vpost_set_osd_colkey R G B);

/* Support "vpost_show_layer" command line in msh mode */
static rt_err_t vpost_show_layer(int argc, char **argv)
{
    rt_uint32_t index, len, arg[2];
    nu_vpost_t psVpostLayer;

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 2) ? 2 : argc;

    for (index = 0; index < (len - 1); index ++)
    {
        arg[index] = atol(argv[index + 1]);
    }
    psVpostLayer = &nu_fbdev[arg[0]];

    return rt_device_open(&psVpostLayer->dev, RT_DEVICE_FLAG_RDWR);
}
MSH_CMD_EXPORT(vpost_show_layer, e.g: vpost_show_layer layer);

/* Support "vpost_hide_layer" command line in msh mode */
static rt_err_t vpost_hide_layer(int argc, char **argv)
{
    rt_uint32_t index, len, arg[2];
    nu_vpost_t psVpostLayer;

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 2) ? 2 : argc;

    for (index = 0; index < (len - 1); index ++)
    {
        arg[index] = atol(argv[index + 1]);
    }
    psVpostLayer = &nu_fbdev[arg[0]];

    return rt_device_close(&psVpostLayer->dev);
}
MSH_CMD_EXPORT(vpost_hide_layer, e.g: vpost_hide_layer layer);

/* Support "vpost_fill_color" command line in msh mode */
static rt_err_t vpost_fill_color(int argc, char **argv)
{
    rt_uint32_t index, len, arg[5];
    nu_vpost_t psVpostLayer;

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 5) ? 5 : argc;

    for (index = 0; index < (len - 1); index ++)
    {
        arg[index] = atol(argv[index + 1]);
    }

    psVpostLayer = &nu_fbdev[arg[0]];

    if (psVpostLayer->info.framebuffer != RT_NULL)
    {
        int i;
        uint32_t fill_num = psVpostLayer->info.height * psVpostLayer->info.width;
        uint32_t *fbmem_start = (uint32_t *)psVpostLayer->info.framebuffer;
        uint32_t color = (arg[1] << 16) | (arg[2] << 8) | arg[3] ;
        for (i = 0; i < fill_num; i++)
        {
            rt_memcpy((void *)&fbmem_start[i], &color, (psVpostLayer->info.bits_per_pixel / 8));
        }
    }
    return 0;
}
MSH_CMD_EXPORT(vpost_fill_color, e.g: vpost_fill_color layer R G B);

#endif /* if defined(BSP_USING_VPOST) */
