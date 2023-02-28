/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-8-16       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(BSP_USING_CCAP)

#include "drv_ccap.h"
#include <dfs_posix.h>

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "ccap.demo"
#define DBG_COLOR
#include <rtdbg.h>

#define THREAD_PRIORITY   5
#define THREAD_STACK_SIZE 4096
#define THREAD_TIMESLICE  5

#define DEF_CROP_PACKET_RECT
#define DEF_ENABLE_PLANAR_PIPE  0

#define DEF_DURATION         10
#if defined(BSP_USING_CCAP0) && defined(BSP_USING_CCAP1)
    #define DEF_GRID_VIEW        1
#elif defined(BSP_USING_CCAP0) || defined(BSP_USING_CCAP1)
    #define DEF_GRID_VIEW        0
#endif

typedef struct
{
    char *thread_name;
    char *devname_ccap;
    char *devname_sensor;
    char *devname_lcd;
} ccap_grabber_param;
typedef ccap_grabber_param *ccap_grabber_param_t;

typedef struct
{
    ccap_config    sCcapConfig;
    struct rt_device_graphic_info sLcdInfo;
    uint32_t       u32CurFBPointer;
    uint32_t       u32FrameEnd;
    rt_sem_t       semFrameEnd;
} ccap_grabber_context;
typedef ccap_grabber_context *ccap_grabber_context_t;

static void nu_ccap_event_hook(void *pvData, uint32_t u32EvtMask)
{
    ccap_grabber_context_t psGrabberContext = (ccap_grabber_context_t)pvData;

    if (u32EvtMask & NU_CCAP_FRAME_END)
    {
        rt_sem_release(psGrabberContext->semFrameEnd);
    }

    if (u32EvtMask & NU_CCAP_ADDRESS_MATCH)
    {
        LOG_I("Address matched");
    }

    if (u32EvtMask & NU_CCAP_MEMORY_ERROR)
    {
        LOG_E("Access memory error");
    }
}

static rt_device_t ccap_sensor_init(ccap_grabber_context_t psGrabberContext, ccap_grabber_param_t psGrabberParam)
{
    rt_err_t ret;
    ccap_view_info_t psViewInfo;
    sensor_mode_info *psSensorModeInfo;
    rt_device_t psDevSensor = RT_NULL;
    rt_device_t psDevCcap = RT_NULL;
    struct rt_device_graphic_info *psLcdInfo = &psGrabberContext->sLcdInfo;
    ccap_config_t    psCcapConfig = &psGrabberContext->sCcapConfig;

    psDevCcap = rt_device_find(psGrabberParam->devname_ccap);
    if (psDevCcap == RT_NULL)
    {
        LOG_E("Can't find %s", psGrabberParam->devname_ccap);
        goto exit_ccap_sensor_init;
    }

    psDevSensor = rt_device_find(psGrabberParam->devname_sensor);
    if (psDevSensor == RT_NULL)
    {
        LOG_E("Can't find %s", psGrabberParam->devname_sensor);
        goto exit_ccap_sensor_init;
    }

    /* Packet pipe for preview */
    if (DEF_GRID_VIEW)
    {
        psCcapConfig->sPipeInfo_Packet.u32Width    = psLcdInfo->width / 2;
        psCcapConfig->sPipeInfo_Packet.u32Height   = psLcdInfo->height / 2;
        psCcapConfig->sPipeInfo_Packet.u32PixFmt   = (psLcdInfo->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565) ? CCAP_PAR_OUTFMT_RGB565 : 0;
        psCcapConfig->u32Stride_Packet             = psLcdInfo->width;
        if (!rt_strcmp(psGrabberParam->devname_ccap, "ccap1"))
            psCcapConfig->sPipeInfo_Packet.pu8FarmAddr = psLcdInfo->framebuffer + (psCcapConfig->sPipeInfo_Packet.u32Width * 2);
        else
            psCcapConfig->sPipeInfo_Packet.pu8FarmAddr = psLcdInfo->framebuffer;
    }
    else
    {
        psCcapConfig->sPipeInfo_Packet.pu8FarmAddr = psLcdInfo->framebuffer;
        psCcapConfig->sPipeInfo_Packet.u32Height   = psLcdInfo->height;
        psCcapConfig->sPipeInfo_Packet.u32Width    = psLcdInfo->width;
        psCcapConfig->sPipeInfo_Packet.u32PixFmt   = (psLcdInfo->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565) ? CCAP_PAR_OUTFMT_RGB565 : 0;
        psCcapConfig->u32Stride_Packet             = psLcdInfo->width;
    }

    /* Planar pipe for encoding */
#if DEF_ENABLE_PLANAR_PIPE
    psCcapConfig->sPipeInfo_Planar.u32Width    = psLcdInfo->width / 2;
    psCcapConfig->sPipeInfo_Planar.u32Height   = psLcdInfo->height / 2;
    psCcapConfig->sPipeInfo_Planar.pu8FarmAddr = rt_malloc_align(psCcapConfig->sPipeInfo_Planar.u32Height * psCcapConfig->sPipeInfo_Planar.u32Width * 2, 32);
    psCcapConfig->sPipeInfo_Planar.u32PixFmt   = CCAP_PAR_PLNFMT_YUV420; //CCAP_PAR_PLNFMT_YUV422;
    psCcapConfig->u32Stride_Planar             = psCcapConfig->sPipeInfo_Planar.u32Width;

    if (psCcapConfig->sPipeInfo_Planar.pu8FarmAddr == RT_NULL)
    {
        psCcapConfig->sPipeInfo_Planar.u32Height = 0;
        psCcapConfig->sPipeInfo_Planar.u32Width  = 0;
        psCcapConfig->sPipeInfo_Planar.u32PixFmt = 0;
        psCcapConfig->u32Stride_Planar           = 0;
    }

    LOG_I("Planar.FarmAddr@0x%08X", psCcapConfig->sPipeInfo_Planar.pu8FarmAddr);
    LOG_I("Planar.FarmWidth: %d", psCcapConfig->sPipeInfo_Planar.u32Width);
    LOG_I("Planar.FarmHeight: %d", psCcapConfig->sPipeInfo_Planar.u32Height);
#endif

    /* open CCAP */
    ret = rt_device_open(psDevCcap, 0);
    if (ret != RT_EOK)
    {
        LOG_E("Can't open %s", psGrabberParam->devname_ccap);
        goto exit_ccap_sensor_init;
    }

    /* Find suit mode for packet pipe */
    if (psCcapConfig->sPipeInfo_Packet.pu8FarmAddr != RT_NULL)
    {
        /* Check view window of packet pipe */
        psViewInfo = &psCcapConfig->sPipeInfo_Packet;

        if ((rt_device_control(psDevSensor, CCAP_SENSOR_CMD_GET_SUIT_MODE, (void *)&psViewInfo) != RT_EOK)
                || (psViewInfo == RT_NULL))
        {
            LOG_E("Can't get suit mode for packet.");
            goto fail_ccap_init;
        }
    }

    /* Find suit mode for planner pipe */
    if (psCcapConfig->sPipeInfo_Planar.pu8FarmAddr != RT_NULL)
    {
        int recheck = 1;

        if (psViewInfo != RT_NULL)
        {
            if ((psCcapConfig->sPipeInfo_Planar.u32Width <= psViewInfo->u32Width) ||
                    (psCcapConfig->sPipeInfo_Planar.u32Height <= psViewInfo->u32Height))
                recheck = 0;
        }

        if (recheck)
        {
            /* Check view window of planner pipe */
            psViewInfo = &psCcapConfig->sPipeInfo_Planar;

            /* Find suit mode */
            if ((rt_device_control(psDevSensor, CCAP_SENSOR_CMD_GET_SUIT_MODE, (void *)&psViewInfo) != RT_EOK)
                    || (psViewInfo == RT_NULL))
            {
                LOG_E("Can't get suit mode for planner.");
                goto exit_ccap_sensor_init;
            }
        }
    }

#if defined(DEF_CROP_PACKET_RECT)
    /* Set cropping rectangle */
    if (psViewInfo->u32Width >= psCcapConfig->sPipeInfo_Packet.u32Width)
    {
        /* sensor.width >= preview.width */
        psCcapConfig->sRectCropping.x = (psViewInfo->u32Width - psCcapConfig->sPipeInfo_Packet.u32Width) / 2;
        psCcapConfig->sRectCropping.width  = psCcapConfig->sPipeInfo_Packet.u32Width;
    }
    else
    {
        /* sensor.width < preview.width */
        psCcapConfig->sRectCropping.x = 0;
        psCcapConfig->sRectCropping.width  = psViewInfo->u32Width;
    }

    if (psViewInfo->u32Height >= psCcapConfig->sPipeInfo_Packet.u32Height)
    {
        /* sensor.height >= preview.height */
        psCcapConfig->sRectCropping.y = (psViewInfo->u32Height - psCcapConfig->sPipeInfo_Packet.u32Height) / 2;
        psCcapConfig->sRectCropping.height = psCcapConfig->sPipeInfo_Packet.u32Height;
    }
    else
    {
        /* sensor.height < preview.height */
        psCcapConfig->sRectCropping.y = 0;
        psCcapConfig->sRectCropping.height = psViewInfo->u32Height;
    }
#else
    /* Set cropping rectangle */
    psCcapConfig->sRectCropping.x      = 0;
    psCcapConfig->sRectCropping.y      = 0;
    psCcapConfig->sRectCropping.width  = psViewInfo->u32Width;
    psCcapConfig->sRectCropping.height = psViewInfo->u32Height;
#endif

    /* ISR Hook */
    psCcapConfig->pfnEvHndler = nu_ccap_event_hook;
    psCcapConfig->pvData      = (void *)psGrabberContext;

    /* Get Suitable mode. */
    psSensorModeInfo = (sensor_mode_info *)psViewInfo;

    /* Feed CCAP configuration */
    ret = rt_device_control(psDevCcap, CCAP_CMD_CONFIG, (void *)psCcapConfig);
    if (ret != RT_EOK)
    {
        LOG_E("Can't feed configuration %s", psGrabberParam->devname_ccap);
        goto fail_ccap_init;
    }

    {
        int i32SenClk = psSensorModeInfo->u32SenClk;
        if (DEF_GRID_VIEW && DEF_ENABLE_PLANAR_PIPE)
            i32SenClk = 45000000; /* Bandwidth limitation: Slow down sensor clock */

        /* speed up pixel clock */
        if (rt_device_control(psDevCcap, CCAP_CMD_SET_SENCLK, (void *)&i32SenClk) != RT_EOK)
        {
            LOG_E("Can't feed setting.");
            goto fail_ccap_init;
        }
    }

    /* Initial CCAP sensor */
    if (rt_device_open(psDevSensor, 0) != RT_EOK)
    {
        LOG_E("Can't open sensor.");
        goto fail_sensor_init;
    }

    /* Feed settings to sensor */
    if (rt_device_control(psDevSensor, CCAP_SENSOR_CMD_SET_MODE, (void *)psSensorModeInfo) != RT_EOK)
    {
        LOG_E("Can't feed setting.");
        goto fail_sensor_init;
    }

    ret = rt_device_control(psDevCcap, CCAP_CMD_SET_PIPES, (void *)psViewInfo);
    if (ret != RT_EOK)
    {
        LOG_E("Can't set pipes %s", psGrabberParam->devname_ccap);
        goto fail_ccap_init;
    }

    return psDevCcap;

fail_sensor_init:

    if (psDevSensor)
        rt_device_close(psDevSensor);

fail_ccap_init:

    if (psDevCcap)
        rt_device_close(psDevCcap);

exit_ccap_sensor_init:

    psDevCcap = psDevSensor = RT_NULL;

    return psDevCcap;
}

static void ccap_sensor_fini(rt_device_t psDevCcap, rt_device_t psDevSensor)
{
    if (psDevSensor)
        rt_device_close(psDevSensor);

    if (psDevCcap)
        rt_device_close(psDevCcap);
}

#if DEF_ENABLE_PLANAR_PIPE
static int ccap_save_planar_frame(char *name, rt_tick_t timestamp, const void *data, size_t size)
{
    int fd;
    char szFilename[32];
    int wrote_size = 0;

    rt_snprintf(szFilename, sizeof(szFilename), "/%s-%08d.yuv", name, timestamp);
    fd = open(szFilename, O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        LOG_E("Could not open %s for writing.", szFilename);
        goto exit_ccap_save_planar_frame;
    }

    if ((wrote_size = write(fd, data, size)) != size)
    {
        LOG_E("Could not write to %s (%d != %d).", szFilename, wrote_size, size);
        goto exit_ccap_save_planar_frame;
    }

    wrote_size = size;

exit_ccap_save_planar_frame:

    if (fd >= 0)
        close(fd);

    return wrote_size;
}
#endif

static void ccap_grabber(void *parameter)
{
    rt_err_t ret;
    ccap_grabber_param_t psGrabberParam = (ccap_grabber_param_t)parameter;
    ccap_grabber_context sGrabberContext;

    rt_device_t psDevCcap = RT_NULL;
    rt_device_t psDevLcd = RT_NULL;

    rt_tick_t last, now;
    rt_bool_t bDrawDirect;

    rt_memset((void *)&sGrabberContext, 0, sizeof(ccap_grabber_context));

    psDevLcd = rt_device_find(psGrabberParam->devname_lcd);
    if (psDevLcd == RT_NULL)
    {
        LOG_E("Can't find %s", psGrabberParam->devname_lcd);
        goto exit_ccap_grabber;
    }

    /* Get LCD Info */
    ret = rt_device_control(psDevLcd, RTGRAPHIC_CTRL_GET_INFO, &sGrabberContext.sLcdInfo);
    if (ret != RT_EOK)
    {
        LOG_E("Can't get LCD info %s", psGrabberParam->devname_lcd);
        goto exit_ccap_grabber;
    }

    /* Check panel type */
    if (rt_device_control(psDevLcd, RTGRAPHIC_CTRL_PAN_DISPLAY, (void *)sGrabberContext.sLcdInfo.framebuffer) == RT_EOK)
    {
        /* Sync-type LCD panel, will draw to VRAM directly. */
        int pixfmt = RTGRAPHIC_PIXEL_FORMAT_RGB565;
        bDrawDirect = RT_TRUE;
        rt_device_control(psDevLcd, RTGRAPHIC_CTRL_SET_MODE, (void *)&pixfmt);
    }
    else
    {
        /* MPU-type LCD panel, draw to shadow RAM, then flush. */
        bDrawDirect = RT_FALSE;
    }

    ret = rt_device_control(psDevLcd, RTGRAPHIC_CTRL_GET_INFO, &sGrabberContext.sLcdInfo);
    if (ret != RT_EOK)
    {
        LOG_E("Can't get LCD info %s", psGrabberParam->devname_lcd);
        goto exit_ccap_grabber;
    }

    LOG_I("LCD Type: %s-type",   bDrawDirect ? "Sync" : "MPU");
    LOG_I("LCD Width: %d",   sGrabberContext.sLcdInfo.width);
    LOG_I("LCD Height: %d",  sGrabberContext.sLcdInfo.height);
    LOG_I("LCD bpp:%d",   sGrabberContext.sLcdInfo.bits_per_pixel);
    LOG_I("LCD pixel format:%d",   sGrabberContext.sLcdInfo.pixel_format);
    LOG_I("LCD frame buffer@0x%08x",   sGrabberContext.sLcdInfo.framebuffer);
    LOG_I("LCD frame buffer size:%d",   sGrabberContext.sLcdInfo.smem_len);

    sGrabberContext.semFrameEnd = rt_sem_create(psGrabberParam->devname_ccap, 0, RT_IPC_FLAG_FIFO);
    if (sGrabberContext.semFrameEnd == RT_NULL)
    {
        LOG_E("Can't allocate sem resource %s", psGrabberParam->devname_ccap);
        goto exit_ccap_grabber;
    }

    /* initial ccap & sensor*/
    psDevCcap = ccap_sensor_init(&sGrabberContext, psGrabberParam);
    if (psDevCcap == RT_NULL)
    {
        LOG_E("Can't init %s and %s", psGrabberParam->devname_ccap, psGrabberParam->devname_sensor);
        goto exit_ccap_grabber;
    }

    /* Start to capture */
    if (rt_device_control(psDevCcap, CCAP_CMD_START_CAPTURE, RT_NULL) != RT_EOK)
    {
        LOG_E("Can't start %s", psGrabberParam->devname_ccap);
        goto exit_ccap_grabber;
    }

    /* open lcd */
    ret = rt_device_open(psDevLcd, 0);
    if (ret != RT_EOK)
    {
        LOG_E("Can't open %s", psGrabberParam->devname_lcd);
        goto exit_ccap_grabber;
    }

    last = now = rt_tick_get();
    while (1)
    {
        if (sGrabberContext.semFrameEnd)
        {
            rt_sem_take(sGrabberContext.semFrameEnd, RT_WAITING_FOREVER);
        }

        if (!bDrawDirect)
        {
            //MPU type
            struct rt_device_rect_info sRectInfo;

            /* Update fullscreen region. */
            sRectInfo.x = 0;
            sRectInfo.y = 0;
            sRectInfo.height = sGrabberContext.sLcdInfo.height;
            sRectInfo.width = sGrabberContext.sLcdInfo.width;

            rt_device_control(psDevLcd, RTGRAPHIC_CTRL_RECT_UPDATE, &sRectInfo);
        }
        else if (!DEF_GRID_VIEW)
        {
            int i32FBSize = sGrabberContext.sLcdInfo.width * sGrabberContext.sLcdInfo.height * (sGrabberContext.sLcdInfo.bits_per_pixel >> 3);
            int i32VRAMPiece = sGrabberContext.sLcdInfo.smem_len / i32FBSize;
            ccap_config sCcapConfig = {0};

            uint32_t u32BufPtr = (uint32_t)sGrabberContext.sCcapConfig.sPipeInfo_Packet.pu8FarmAddr
                                 + (sGrabberContext.u32FrameEnd % i32VRAMPiece) * i32FBSize;

            /* Pan to valid frame address. */
            rt_device_control(psDevLcd, RTGRAPHIC_CTRL_PAN_DISPLAY, (void *)u32BufPtr);

            sCcapConfig.sPipeInfo_Packet.pu8FarmAddr = sGrabberContext.sCcapConfig.sPipeInfo_Packet.pu8FarmAddr
                    + ((sGrabberContext.u32FrameEnd + 1) % i32VRAMPiece) * i32FBSize ;

#if DEF_ENABLE_PLANAR_PIPE
            sCcapConfig.sPipeInfo_Planar.pu8FarmAddr = sGrabberContext.sCcapConfig.sPipeInfo_Planar.pu8FarmAddr;
            sCcapConfig.sPipeInfo_Planar.u32Width = sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Width;
            sCcapConfig.sPipeInfo_Planar.u32Height = sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Height;
            sCcapConfig.sPipeInfo_Planar.u32PixFmt = sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32PixFmt;
#endif

            rt_device_control(psDevCcap, CCAP_CMD_SET_BASEADDR, &sCcapConfig);

#if DEF_ENABLE_PLANAR_PIPE
            {
                int OpModeShutter = 1;
                /* One-shot mode, trigger next frame */
                rt_device_control(psDevCcap, CCAP_CMD_SET_OPMODE, &OpModeShutter);
            }
#endif
        }

        sGrabberContext.u32FrameEnd++;

        /* FPS */
        now = rt_tick_get();
        if ((now - last) >= (DEF_DURATION * 1000))
        {
#if DEF_ENABLE_PLANAR_PIPE
            {
                uint32_t u32Factor = 0;
                if (sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32PixFmt == CCAP_PAR_PLNFMT_YUV420)
                    u32Factor = 3;
                else if (sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32PixFmt == CCAP_PAR_PLNFMT_YUV422)
                    u32Factor = 4;

                if (u32Factor > 0)
                {
                    ccap_save_planar_frame(psGrabberParam->thread_name, now, (const void *)sGrabberContext.sCcapConfig.sPipeInfo_Planar.pu8FarmAddr, sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Width * sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Height * u32Factor / 2);
                }
            }
#endif
            LOG_I("%s: %d FPS", psGrabberParam->devname_ccap, sGrabberContext.u32FrameEnd / DEF_DURATION);
            sGrabberContext.u32FrameEnd = 0;
            last = now;
        }
    }

exit_ccap_grabber:

    ccap_sensor_fini(rt_device_find(psGrabberParam->devname_ccap), rt_device_find(psGrabberParam->devname_sensor));

    if (psDevLcd != RT_NULL)
        rt_device_close(psDevLcd);

    return;
}

static void ccap_grabber_create(ccap_grabber_param_t psGrabberParam)
{
    rt_thread_t ccap_thread = rt_thread_find(psGrabberParam->thread_name);
    if (ccap_thread == RT_NULL)
    {
        ccap_thread = rt_thread_create(psGrabberParam->thread_name,
                                       ccap_grabber,
                                       psGrabberParam,
                                       THREAD_STACK_SIZE,
                                       THREAD_PRIORITY,
                                       THREAD_TIMESLICE);

        if (ccap_thread != RT_NULL)
            rt_thread_startup(ccap_thread);
    }
}

int ccap_demo(void)
{
#if defined(BSP_USING_CCAP0)
    static ccap_grabber_param ccap0_grabber_param = {"grab0", "ccap0", "sensor0", "lcd"};
    ccap_grabber_create(&ccap0_grabber_param);
#endif
#if defined(BSP_USING_CCAP1)
    static ccap_grabber_param ccap1_grabber_param = {"grab1", "ccap1", "sensor1", "lcd"};
    ccap_grabber_create(&ccap1_grabber_param);
#endif
    return 0;
}
MSH_CMD_EXPORT(ccap_demo, camera capture demo);
//INIT_ENV_EXPORT(ccap_demo);
#endif
