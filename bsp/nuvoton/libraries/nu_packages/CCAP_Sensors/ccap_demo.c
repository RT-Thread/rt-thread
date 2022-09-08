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

#include "drv_ccap.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "ccap.demo"
#define DBG_COLOR
#include <rtdbg.h>

#define THREAD_NAME       "ccap_demo"
#define THREAD_PRIORITY   5
#define THREAD_STACK_SIZE 4096
#define THREAD_TIMESLICE  5

#define DEVNAME_LCD       "lcd"
#define DEF_CROP_PACKET_RECT
#define DEF_DURATION         5
#if defined(BSP_USING_CCAP0) && defined(BSP_USING_CCAP1)
    #define DEF_GRID_VIEW        1
#elif defined(BSP_USING_CCAP0) || defined(BSP_USING_CCAP1)
    #define DEF_GRID_VIEW        0
#endif

static volatile uint32_t s_u32FrameGrabbed = 0;
static rt_sem_t  preview_sem = RT_NULL;

static void nu_ccap_event_hook(void *pvData, uint32_t u32EvtMask)
{
    if (u32EvtMask & NU_CCAP_FRAME_END)
    {
        s_u32FrameGrabbed++;
        rt_sem_release(preview_sem);
    }

    if (u32EvtMask & NU_CCAP_ADDRESS_MATCH)
    {
        LOG_E("Address matched");
    }

    if (u32EvtMask & NU_CCAP_MEMORY_ERROR)
    {
        LOG_E("Access memory error");
    }
}

static rt_device_t ccap_sensor_init(ccap_config *psCcapConf, const char *pcCcapDevName, const char *pcSensorDevName)
{
    rt_err_t ret;
    ccap_view_info_t psViewInfo;
    sensor_mode_info *psSensorModeInfo;
    rt_device_t psDevSensor = RT_NULL;
    rt_device_t psDevCcap = RT_NULL;

    psDevCcap = rt_device_find(pcCcapDevName);
    if (psDevCcap == RT_NULL)
    {
        LOG_E("Can't find %s", pcCcapDevName);
        goto exit_ccap_sensor_init;
    }

    psDevSensor = rt_device_find(pcSensorDevName);
    if (psDevSensor == RT_NULL)
    {
        LOG_E("Can't find %s", pcSensorDevName);
        goto exit_ccap_sensor_init;
    }

    /* open CCAP */
    ret = rt_device_open(psDevCcap, 0);
    if (ret != RT_EOK)
    {
        LOG_E("Can't open %s", pcCcapDevName);
        goto exit_ccap_sensor_init;
    }

    /* Find suit mode for packet pipe */
    if (psCcapConf->sPipeInfo_Packet.pu8FarmAddr != RT_NULL)
    {
        /* Check view window of packet pipe */
        psViewInfo = &psCcapConf->sPipeInfo_Packet;

        if ((rt_device_control(psDevSensor, CCAP_SENSOR_CMD_GET_SUIT_MODE, (void *)&psViewInfo) != RT_EOK)
                || (psViewInfo == RT_NULL))
        {
            LOG_E("Can't get suit mode for packet.");
            goto fail_ccap_init;
        }
    }

    /* Find suit mode for planner pipe */
    if (psCcapConf->sPipeInfo_Planar.pu8FarmAddr != RT_NULL)
    {
        int recheck = 1;

        if (psViewInfo != RT_NULL)
        {
            if ((psCcapConf->sPipeInfo_Planar.u32Width <= psViewInfo->u32Width) ||
                    (psCcapConf->sPipeInfo_Planar.u32Height <= psViewInfo->u32Height))
                recheck = 0;
        }

        if (recheck)
        {
            /* Check view window of planner pipe */
            psViewInfo = &psCcapConf->sPipeInfo_Planar;

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
    if (psViewInfo->u32Width >= psCcapConf->sPipeInfo_Packet.u32Width)
    {
        /* sensor.width >= preview.width */
        psCcapConf->sRectCropping.x = (psViewInfo->u32Width - psCcapConf->sPipeInfo_Packet.u32Width) / 2;
        psCcapConf->sRectCropping.width  = psCcapConf->sPipeInfo_Packet.u32Width;
    }
    else
    {
        /* sensor.width < preview.width */
        psCcapConf->sRectCropping.x = 0;
        psCcapConf->sRectCropping.width  = psViewInfo->u32Width;
    }

    if (psViewInfo->u32Height >= psCcapConf->sPipeInfo_Packet.u32Height)
    {
        /* sensor.height >= preview.height */
        psCcapConf->sRectCropping.y = (psViewInfo->u32Height - psCcapConf->sPipeInfo_Packet.u32Height) / 2;
        psCcapConf->sRectCropping.height = psCcapConf->sPipeInfo_Packet.u32Height;
    }
    else
    {
        /* sensor.height < preview.height */
        psCcapConf->sRectCropping.y = 0;
        psCcapConf->sRectCropping.height = psViewInfo->u32Height;
    }
#else
    /* Set cropping rectangle */
    psCcapConf->sRectCropping.x      = 0;
    psCcapConf->sRectCropping.y      = 0;
    psCcapConf->sRectCropping.width  = psViewInfo->u32Width;
    psCcapConf->sRectCropping.height = psViewInfo->u32Height;
#endif

    /* Get Suitable mode. */
    psSensorModeInfo = (sensor_mode_info *)psViewInfo;

    /* Feed CCAP configuration */
    ret = rt_device_control(psDevCcap, CCAP_CMD_CONFIG, (void *)psCcapConf);
    if (ret != RT_EOK)
    {
        LOG_E("Can't feed configuration %s", pcCcapDevName);
        goto fail_ccap_init;
    }

    /* speed up pixel clock */
    if (rt_device_control(psDevCcap, CCAP_CMD_SET_SENCLK, (void *)&psSensorModeInfo->u32SenClk) != RT_EOK)
    {
        LOG_E("Can't feed setting.");
        goto fail_ccap_init;
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
        LOG_E("Can't set pipes %s", pcCcapDevName);
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

static void ccap_grabber(void *parameter)
{
    rt_err_t ret;

    rt_device_t psDevLcd;
    struct rt_device_graphic_info sLcdInfo;

    ccap_config sCcapConfig;
    rt_tick_t last_tick;
    rt_bool_t bDrawDirect;
    rt_bool_t i32PingPong = 0;

    rt_device_t psDevCcap0 = RT_NULL;
    rt_device_t psDevCcap1 = RT_NULL;

    psDevLcd = rt_device_find(DEVNAME_LCD);
    if (psDevLcd == RT_NULL)
    {
        LOG_E("Can't find %s", DEVNAME_LCD);
        goto exit_ccap_grabber;
    }

    ret = rt_device_control(psDevLcd, RTGRAPHIC_CTRL_GET_INFO, &sLcdInfo);
    if (ret != RT_EOK)
    {
        LOG_E("Can't get LCD info %s", DEVNAME_LCD);
        goto exit_ccap_grabber;
    }

    if (rt_device_control(psDevLcd, RTGRAPHIC_CTRL_PAN_DISPLAY, (void *)sLcdInfo.framebuffer) == RT_EOK)
    {
        /* Sync-type LCD panel, will draw to VRAM directly. */
        bDrawDirect = RT_TRUE;
    }
    else
    {
        /* MPU-type LCD panel, draw to shadow RAM, then flush. */
        bDrawDirect = RT_FALSE;
    }

    LOG_I("LCD Type: %s-type",   bDrawDirect ? "Sync" : "MPU");
    LOG_I("LCD Width: %d",   sLcdInfo.width);
    LOG_I("LCD Height: %d",  sLcdInfo.height);
    LOG_I("LCD bpp:%d",   sLcdInfo.bits_per_pixel);
    LOG_I("LCD pixel format:%d",   sLcdInfo.pixel_format);
    LOG_I("LCD frame buffer@0x%08x",   sLcdInfo.framebuffer);
    LOG_I("LCD frame buffer size:%d",   sLcdInfo.smem_len);

    /* Packet pipe for preview */
    if (DEF_GRID_VIEW)
    {
        sCcapConfig.sPipeInfo_Packet.pu8FarmAddr = sLcdInfo.framebuffer;
        sCcapConfig.sPipeInfo_Packet.u32Height   = sLcdInfo.height / 2;
        sCcapConfig.sPipeInfo_Packet.u32Width    = sLcdInfo.width / 2;
        sCcapConfig.sPipeInfo_Packet.u32PixFmt   = (sLcdInfo.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565) ? CCAP_PAR_OUTFMT_RGB565 : 0;
        sCcapConfig.u32Stride_Packet             = sLcdInfo.width;
    }
    else
    {
        sCcapConfig.sPipeInfo_Packet.pu8FarmAddr = sLcdInfo.framebuffer;
        sCcapConfig.sPipeInfo_Packet.u32Height   = sLcdInfo.height;
        sCcapConfig.sPipeInfo_Packet.u32Width    = sLcdInfo.width;
        sCcapConfig.sPipeInfo_Packet.u32PixFmt   = (sLcdInfo.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565) ? CCAP_PAR_OUTFMT_RGB565 : 0;
        sCcapConfig.u32Stride_Packet             = sLcdInfo.width;
    }

    /* Planar pipe for encoding */
    sCcapConfig.sPipeInfo_Planar.pu8FarmAddr = RT_NULL;
    sCcapConfig.sPipeInfo_Planar.u32Height   = 0;
    sCcapConfig.sPipeInfo_Planar.u32Width    = 0;
    sCcapConfig.sPipeInfo_Planar.u32PixFmt   = 0;
    sCcapConfig.u32Stride_Planar             = 0;

    preview_sem = rt_sem_create("cdsem", 0, RT_IPC_FLAG_FIFO);

    /* ISR Hook */
    sCcapConfig.pfnEvHndler = nu_ccap_event_hook;
    sCcapConfig.pvData      = (void *)&sCcapConfig;

    /* initial ccap0 & sensor0 */
#if defined(BSP_USING_CCAP0)
    psDevCcap0 = ccap_sensor_init(&sCcapConfig, "ccap0", "sensor0");
    if (psDevCcap0 == RT_NULL)
    {
        LOG_E("Can't init ccap and sensor");
        goto exit_ccap_grabber;
    }

    /* Start to capture */
    if (rt_device_control(psDevCcap0, CCAP_CMD_START_CAPTURE, RT_NULL) != RT_EOK)
    {
        LOG_E("Can't start ccap0 capture.");
        goto exit_ccap_grabber;
    }
#endif

    /* initial ccap1 & sensor1 */
#if defined(BSP_USING_CCAP1)
    if (DEF_GRID_VIEW)
        sCcapConfig.sPipeInfo_Packet.pu8FarmAddr += (sCcapConfig.sPipeInfo_Packet.u32Width * 2);

    psDevCcap1 = ccap_sensor_init(&sCcapConfig, "ccap1", "sensor1");
    if (psDevCcap1 == RT_NULL)
    {
        LOG_E("Can't init ccap and sensor");
        goto exit_ccap_grabber;
    }

#if !defined(BSP_USING_CCAP0) || defined(DEF_GRID_VIEW)
    /* Start to capture */
    if (rt_device_control(psDevCcap1, CCAP_CMD_START_CAPTURE, RT_NULL) != RT_EOK)
    {
        LOG_E("Can't start ccap1 capture.");
        goto exit_ccap_grabber;
    }
    if (!DEF_GRID_VIEW)
        i32PingPong = 1;
#endif

#endif

    /* open lcd */
    ret = rt_device_open(psDevLcd, 0);
    if (ret != RT_EOK)
    {
        LOG_E("Can't open %s", DEVNAME_LCD);
        goto exit_ccap_grabber;
    }

    last_tick = rt_tick_get();
    while (1)
    {
        rt_sem_take(preview_sem, RT_WAITING_FOREVER);
        if (!bDrawDirect)
        {
            //MPU type
            struct rt_device_rect_info sRectInfo;

            /* Update fullscreen region. */
            sRectInfo.x = 0;
            sRectInfo.y = 0;
            sRectInfo.height = sLcdInfo.height;
            sRectInfo.width = sLcdInfo.width;

            rt_device_control(psDevLcd, RTGRAPHIC_CTRL_RECT_UPDATE, &sRectInfo);
        }
        else
        {
            // Sync type
        }

        /* FPS */
        if ((rt_tick_get() - last_tick) >= (DEF_DURATION * 1000))
        {
            if (i32PingPong == 0)
            {
                if (!DEF_GRID_VIEW)
                    LOG_I("%s: %d FPS", psDevCcap0->parent.name, (s_u32FrameGrabbed / DEF_DURATION));
                if (!DEF_GRID_VIEW && psDevCcap0 && psDevCcap1)
                {
                    rt_device_control(psDevCcap0, CCAP_CMD_STOP_CAPTURE, RT_NULL);
                    rt_device_control(psDevCcap1, CCAP_CMD_START_CAPTURE, RT_NULL);
                }
            }
            else if (i32PingPong == 1)
            {
                if (!DEF_GRID_VIEW)
                    LOG_I("%s: %d FPS", psDevCcap1->parent.name, (s_u32FrameGrabbed / DEF_DURATION));
                if (!DEF_GRID_VIEW && psDevCcap0 && psDevCcap1)
                {
                    rt_device_control(psDevCcap1, CCAP_CMD_STOP_CAPTURE, RT_NULL);
                    rt_device_control(psDevCcap0, CCAP_CMD_START_CAPTURE, RT_NULL);
                }
            }

            if (DEF_GRID_VIEW)
                LOG_I("GridView: %s+%s: %d FPS", psDevCcap0->parent.name,
                      psDevCcap1->parent.name,
                      (s_u32FrameGrabbed / DEF_DURATION) / 2);

            /* Ping-pong rendering */
            if (!DEF_GRID_VIEW && psDevCcap0 && psDevCcap1)
                i32PingPong = (i32PingPong + 1) % 2;

            s_u32FrameGrabbed = 0;
            last_tick = rt_tick_get();
        }
    }

exit_ccap_grabber:

#if defined(BSP_USING_CCAP0)
    ccap_sensor_fini(rt_device_find("ccap0"), rt_device_find("sensor0"));
#endif


#if defined(BSP_USING_CCAP1)
    ccap_sensor_fini(rt_device_find("ccap1"), rt_device_find("sensor1"));
#endif

    rt_device_close(psDevLcd);

    return;
}

int ccap_demo(void)
{
    rt_thread_t  ccap_thread = rt_thread_find(THREAD_NAME);
    if (ccap_thread == RT_NULL)
    {
        ccap_thread = rt_thread_create(THREAD_NAME,
                                       ccap_grabber,
                                       RT_NULL,
                                       THREAD_STACK_SIZE,
                                       THREAD_PRIORITY,
                                       THREAD_TIMESLICE);

        if (ccap_thread != RT_NULL)
            rt_thread_startup(ccap_thread);
    }

    return 0;
}
MSH_CMD_EXPORT(ccap_demo, camera capture demo);
INIT_APP_EXPORT(ccap_demo);
