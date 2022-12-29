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
#define DBG_SECTION_NAME  "ccap.saver"
#define DBG_COLOR
#include <rtdbg.h>

#define THREAD_PRIORITY   5
#define THREAD_STACK_SIZE 4096
#define THREAD_TIMESLICE  5

#define DEF_FRAME_WIDTH   640
#define DEF_FRAME_HEIGHT  480

typedef struct
{
    char *thread_name;
    char *devname_ccap;
    char *devname_sensor;
} ccap_grabber_param;
typedef ccap_grabber_param *ccap_grabber_param_t;

typedef struct
{
    ccap_config    sCcapConfig;
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
    psCcapConfig->sPipeInfo_Packet.u32Width    = DEF_FRAME_WIDTH;
    psCcapConfig->sPipeInfo_Packet.u32Height   = DEF_FRAME_HEIGHT;
    psCcapConfig->sPipeInfo_Packet.pu8FarmAddr = rt_malloc_align(psCcapConfig->sPipeInfo_Packet.u32Height * psCcapConfig->sPipeInfo_Packet.u32Width * 2, 32);
    if (psCcapConfig->sPipeInfo_Packet.pu8FarmAddr == RT_NULL)
    {
        LOG_E("Can't malloc");
        goto exit_ccap_sensor_init;
    }

    psCcapConfig->sPipeInfo_Packet.u32PixFmt   = CCAP_PAR_OUTFMT_RGB565;
    psCcapConfig->u32Stride_Packet             = psCcapConfig->sPipeInfo_Packet.u32Width;

    /* Planar pipe for encoding */
    psCcapConfig->sPipeInfo_Planar.u32Width    = psCcapConfig->sPipeInfo_Packet.u32Width;
    psCcapConfig->sPipeInfo_Planar.u32Height   = psCcapConfig->sPipeInfo_Packet.u32Height;
    psCcapConfig->sPipeInfo_Planar.pu8FarmAddr = rt_malloc_align(psCcapConfig->sPipeInfo_Planar.u32Height * psCcapConfig->sPipeInfo_Planar.u32Width * 2, 32);
    if (psCcapConfig->sPipeInfo_Planar.pu8FarmAddr == RT_NULL)
    {
        LOG_E("Can't malloc");
        goto exit_ccap_sensor_init;
    }

    psCcapConfig->sPipeInfo_Planar.u32PixFmt   = CCAP_PAR_PLNFMT_YUV422;
    psCcapConfig->u32Stride_Planar             = psCcapConfig->sPipeInfo_Planar.u32Width;

    LOG_I("Packet.FarmAddr@0x%08X", psCcapConfig->sPipeInfo_Packet.pu8FarmAddr);
    LOG_I("Packet.FarmWidth: %d", psCcapConfig->sPipeInfo_Packet.u32Width);
    LOG_I("Packet.FarmHeight: %d", psCcapConfig->sPipeInfo_Packet.u32Height);

    LOG_I("Planar.FarmAddr@0x%08X", psCcapConfig->sPipeInfo_Planar.pu8FarmAddr);
    LOG_I("Planar.FarmWidth: %d", psCcapConfig->sPipeInfo_Planar.u32Width);
    LOG_I("Planar.FarmHeight: %d", psCcapConfig->sPipeInfo_Planar.u32Height);

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

    /* Set cropping rectangle */
    psCcapConfig->sRectCropping.x      = 0;
    psCcapConfig->sRectCropping.y      = 0;
    psCcapConfig->sRectCropping.width  = psViewInfo->u32Width;
    psCcapConfig->sRectCropping.height = psViewInfo->u32Height;

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

static int ccap_save_frame(char *szFilename, const void *data, size_t size)
{
    int fd;
    int wrote_size = 0;

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

    LOG_I("Output %s", szFilename);

exit_ccap_save_planar_frame:

    if (fd >= 0)
        close(fd);

    return wrote_size;
}

static void ccap_grabber(void *parameter)
{
    ccap_grabber_param_t psGrabberParam = (ccap_grabber_param_t)parameter;
    ccap_grabber_context sGrabberContext;

    rt_device_t psDevCcap = RT_NULL;

    rt_memset((void *)&sGrabberContext, 0, sizeof(ccap_grabber_context));

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

    while (1)
    {
        if (sGrabberContext.semFrameEnd)
        {
            rt_sem_take(sGrabberContext.semFrameEnd, RT_WAITING_FOREVER);
        }

        sGrabberContext.u32FrameEnd++;
        LOG_I("%s Grabbed %d", psGrabberParam->devname_ccap, sGrabberContext.u32FrameEnd);

        if (sGrabberContext.u32FrameEnd == 30)
        {
            char szFilename[64];
            uint32_t u32Factor = 0;

            LOG_I("%s Capturing %d", psGrabberParam->devname_ccap, sGrabberContext.u32FrameEnd);

            if (sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32PixFmt == CCAP_PAR_PLNFMT_YUV420)
            {
                u32Factor = 3;
                rt_snprintf(szFilename, sizeof(szFilename), "/%08d_%dx%d.yuv420p",
                            rt_tick_get(),
                            sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Width,
                            sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Height);
            }
            else if (sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32PixFmt == CCAP_PAR_PLNFMT_YUV422)
            {
                u32Factor = 4;
                rt_snprintf(szFilename, sizeof(szFilename), "/%08d_%s_%dx%d.yuv422p",
                            rt_tick_get(),
                            psGrabberParam->devname_ccap,
                            sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Width,
                            sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Height);
            }

            if (u32Factor > 0)
            {
                /* Save YUV422 or YUV420 frame from packet pipe*/
                ccap_save_frame(szFilename, (const void *)sGrabberContext.sCcapConfig.sPipeInfo_Planar.pu8FarmAddr, sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Width * sGrabberContext.sCcapConfig.sPipeInfo_Planar.u32Height * u32Factor / 2);
            }

            /* Save RGB565 frame from packet pipe*/
            rt_snprintf(szFilename, sizeof(szFilename), "/%08d_%s_%dx%d.rgb565",
                        rt_tick_get(),
                        psGrabberParam->devname_ccap,
                        sGrabberContext.sCcapConfig.sPipeInfo_Packet.u32Width,
                        sGrabberContext.sCcapConfig.sPipeInfo_Packet.u32Height);

            ccap_save_frame(szFilename, (const void *)sGrabberContext.sCcapConfig.sPipeInfo_Packet.pu8FarmAddr, sGrabberContext.sCcapConfig.sPipeInfo_Packet.u32Width * sGrabberContext.sCcapConfig.sPipeInfo_Packet.u32Height * 2);

            break;
        }
    }

exit_ccap_grabber:

    ccap_sensor_fini(rt_device_find(psGrabberParam->devname_ccap), rt_device_find(psGrabberParam->devname_sensor));

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

int ccap_saver(void)
{
#if defined(BSP_USING_CCAP0)
    static ccap_grabber_param ccap0_grabber_param = {"grab0", "ccap0", "sensor0"};
    ccap_grabber_create(&ccap0_grabber_param);
#endif
#if defined(BSP_USING_CCAP1)
    static ccap_grabber_param ccap1_grabber_param = {"grab1", "ccap1", "sensor1"};
    ccap_grabber_create(&ccap1_grabber_param);
#endif
    return 0;
}
MSH_CMD_EXPORT(ccap_saver, camera saver demo);
#endif
