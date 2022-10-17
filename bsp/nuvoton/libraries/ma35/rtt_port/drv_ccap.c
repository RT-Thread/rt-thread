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

#include <rtconfig.h>

#if defined(BSP_USING_CCAP)

#include <rthw.h>
#include "NuMicro.h"
#include "ccap_sensor.h"
#include "drv_ccap.h"

#define LOG_TAG    "drv.ccap"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL   LOG_LVL_INFO
#define DBG_COLOR
#include <rtdbg.h>


/* Private Typedef --------------------------------------------------------------*/

enum
{
    CCAP_START = -1,
#if defined(BSP_USING_CCAP0)
    CCAP0_IDX,
#endif
#if defined(BSP_USING_CCAP1)
    CCAP1_IDX,
#endif
    CCAP_CNT
};

struct nu_ccap
{
    struct rt_device device;
    char *name;
    CCAP_T *base;
    uint32_t rstidx;
    uint32_t modid_ccap;
    IRQn_Type irqn;

    ccap_config sConfig;
};
typedef struct nu_ccap *nu_ccap_t;

static struct nu_ccap nu_ccap_arr [] =
{
#if defined(BSP_USING_CCAP0)
    {
        .name = "ccap0",
        .base = CCAP0,
        .rstidx = CCAP0_RST,
        .modid_ccap = CCAP0_MODULE,
        .irqn = CCAP0_IRQn,
    },
#endif
#if defined(BSP_USING_CCAP1)
    {
        .name = "ccap1",
        .base = CCAP1,
        .rstidx = CCAP1_RST,
        .modid_ccap = CCAP1_MODULE,
        .irqn = CCAP1_IRQn,
    },
#endif
};

static void nu_ccap_isr(int vector, void *param)
{
    nu_ccap_t ccap = (nu_ccap_t)param;
    CCAP_T *base = ccap->base;
    uint32_t u32CapInt, u32EvtMsk;

    u32CapInt = base->INT;
    u32EvtMsk = 0;

    if ((u32CapInt & (CCAP_INT_VIEN_Msk | CCAP_INT_VINTF_Msk)) == (CCAP_INT_VIEN_Msk | CCAP_INT_VINTF_Msk))
    {
        base->INT |= CCAP_INT_VINTF_Msk;     /* Clear Frame end interrupt */
        u32EvtMsk |= NU_CCAP_FRAME_END;
    }

    if ((u32CapInt & (CCAP_INT_ADDRMIEN_Msk | CCAP_INT_ADDRMINTF_Msk)) == (CCAP_INT_ADDRMIEN_Msk | CCAP_INT_ADDRMINTF_Msk))
    {
        base->INT |= CCAP_INT_ADDRMINTF_Msk; /* Clear Address match interrupt */
        u32EvtMsk |= NU_CCAP_ADDRESS_MATCH;
    }

    if ((u32CapInt & (CCAP_INT_MEIEN_Msk | CCAP_INT_MEINTF_Msk)) == (CCAP_INT_MEIEN_Msk | CCAP_INT_MEINTF_Msk))
    {
        base->INT |= CCAP_INT_MEINTF_Msk;    /* Clear Memory error interrupt */
        u32EvtMsk |= NU_CCAP_MEMORY_ERROR;
    }

    /* Invoke callback */
    if (ccap->device.rx_indicate != RT_NULL)
        ccap->device.rx_indicate(&ccap->device, 1);

    if (ccap->sConfig.pfnEvHndler && u32EvtMsk)
        ccap->sConfig.pfnEvHndler(ccap->sConfig.pvData, u32EvtMsk);

    base->CTL = base->CTL | CCAP_CTL_UPDATE;
}

/* common device interface */
static rt_err_t ccap_init(rt_device_t dev)
{
    return RT_EOK;
}

static void ccap_sensor_setfreq(nu_ccap_t psNuCcap, uint32_t u32SensorFreq)
{
    uint32_t u32RegLockLevel = SYS_IsRegLocked();

    /* Unlock protected registers */
    if (u32RegLockLevel)
        SYS_UnlockReg();

    if (u32SensorFreq > 0)
    {
        int32_t i32Div;

        /* Specified sensor clock */
        i32Div = CLK_GetPLLClockFreq(SYSPLL) / u32SensorFreq;

        if (i32Div == 0)
            i32Div = 1;

        CLK_EnableModuleClock(psNuCcap->modid_ccap);
        if (psNuCcap->base == CCAP0)
            CLK_SetModuleClock(psNuCcap->modid_ccap, CLK_CLKSEL0_CCAP0SEL_SYSPLL, CLK_CLKDIV1_CCAP0(i32Div));
        else if (psNuCcap->base == CCAP1)
            CLK_SetModuleClock(psNuCcap->modid_ccap, CLK_CLKSEL0_CCAP1SEL_SYSPLL, CLK_CLKDIV1_CCAP1(i32Div));
        else
            return;

        LOG_I("CCAP Engine clock:%d", CLK_GetPLLClockFreq(SYSPLL));
        LOG_I("CCAP Sensor preferred clock %d, divider:%d", u32SensorFreq, i32Div);
        LOG_I("CCAP Sensor actully clock:%d", CLK_GetPLLClockFreq(SYSPLL) / i32Div);
    }
    else
    {
        CLK_DisableModuleClock(psNuCcap->modid_ccap);
    }

    /* Lock protected registers */
    if (u32RegLockLevel)
        SYS_LockReg();
}

static rt_err_t ccap_pipe_configure(nu_ccap_t psNuCcap, ccap_view_info_t psViewInfo)
{
    sensor_mode_info_t psSensorModeInfo = (sensor_mode_info_t)psViewInfo;
    ccap_config_t psCcapConf = &psNuCcap->sConfig;
    uint32_t u32PipeEnabling = 0;
    struct rt_device_rect_info *psRectCropping = &psCcapConf->sRectCropping;

    /* Set Cropping Window Vertical/Horizontal Starting Address and Cropping Window Size */
    CCAP_SetCroppingWindow(psNuCcap->base, psRectCropping->y, psRectCropping->x, psRectCropping->height, psRectCropping->width);

    if (psCcapConf->sPipeInfo_Packet.pu8FarmAddr)
    {
        uint32_t u32WM, u32WN, u32HM, u32HN;

        /* Set System Memory Packet Base Address Register */
        CCAP_SetPacketBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Packet.pu8FarmAddr);

        u32WM = u32WN = u32HM = u32HN = 0;
        /* Set Packet Scaling Vertical/Horizontal Factor Register */
        if (psCcapConf->sPipeInfo_Packet.u32Height < psRectCropping->height)
        {
            u32HN = psCcapConf->sPipeInfo_Packet.u32Height;
            u32HM = psRectCropping->height;
        }

        if (psCcapConf->sPipeInfo_Packet.u32Width < psRectCropping->width)
        {
            u32WN = psCcapConf->sPipeInfo_Packet.u32Width;
            u32WM = psRectCropping->width;
        }

        CCAP_SetPacketScaling(psNuCcap->base,
                              u32HN,
                              u32HM,
                              u32WN,
                              u32WM);

        /* Set Packet Frame Output Pixel Stride Width */
        CCAP_SetPacketStride(psNuCcap->base, psCcapConf->u32Stride_Packet);

        u32PipeEnabling |= CCAP_CTL_PKTEN;
    }

    if (psCcapConf->sPipeInfo_Planar.pu8FarmAddr)
    {
        uint32_t u32Offset = 0;
        uint32_t u32WM, u32WN, u32HM, u32HN;
        uint32_t u32Div = 0;

        if (psCcapConf->sPipeInfo_Planar.u32PixFmt  == CCAP_PAR_PLNFMT_YUV422)
        {
            /* U/V farm size equals Y/2 farm size */
            u32Div = 2;
        }
        else if (psCcapConf->sPipeInfo_Planar.u32PixFmt  == CCAP_PAR_PLNFMT_YUV420)
        {
            /* U/V farm size equals Y/4 farm size */
            u32Div = 4;
        }
        else
        {
            goto fail_ccap_pipe_configure;
        }

        /* Set System Memory Planar Y Base Address Register */
        CCAP_SetPlanarYBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Planar.pu8FarmAddr + u32Offset);

        u32Offset = psCcapConf->sPipeInfo_Planar.u32Height * psCcapConf->sPipeInfo_Planar.u32Width;

        /* Set System Memory Planar U Base Address Register */
        CCAP_SetPlanarUBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Planar.pu8FarmAddr + u32Offset);

        u32Offset += ((psCcapConf->sPipeInfo_Planar.u32Height * psCcapConf->sPipeInfo_Planar.u32Width) / u32Div);

        /* Set System Memory Planar V Base Address Register */
        CCAP_SetPlanarVBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Planar.pu8FarmAddr + u32Offset);

        u32WM = u32WN = u32HM = u32HN = 0;
        /* Set Planar Scaling Vertical/Horizontal Factor Register */
        if (psCcapConf->sPipeInfo_Planar.u32Height < psRectCropping->height)
        {
            u32HN = psCcapConf->sPipeInfo_Planar.u32Height;
            u32HM = psRectCropping->height;
        }

        if (psCcapConf->sPipeInfo_Planar.u32Width < psRectCropping->width)
        {
            u32WN = psCcapConf->sPipeInfo_Planar.u32Width;
            u32WM = psRectCropping->width;
        }

        /* Set Planar Scaling Vertical/Horizontal Factor Register */
        CCAP_SetPlanarScaling(psNuCcap->base,
                              u32HN,
                              u32HM,
                              u32WN,
                              u32WM);

        /* Set Planar Frame Output Pixel Stride Width */
        CCAP_SetPlanarStride(psNuCcap->base, psCcapConf->u32Stride_Planar);

        u32PipeEnabling |= CCAP_CTL_PLNEN;
    }

    /* Set Vsync polarity, Hsync polarity, pixel clock polarity, Sensor Format and Order */
    CCAP_Open(psNuCcap->base,
              psSensorModeInfo->u32Polarity |
              psViewInfo->u32PixFmt |
              psCcapConf->sPipeInfo_Packet.u32PixFmt |
              psCcapConf->sPipeInfo_Planar.u32PixFmt,
              u32PipeEnabling);

    return RT_EOK;

fail_ccap_pipe_configure:

    return -RT_ERROR;
}

static rt_err_t ccap_open(rt_device_t dev, rt_uint16_t oflag)
{
    nu_ccap_t psNuCcap = (nu_ccap_t)dev;

    uint32_t u32RegLockLevel = SYS_IsRegLocked();

    /* Unlock protected registers */
    if (u32RegLockLevel)
        SYS_UnlockReg();

    /* Enable clock */
    ccap_sensor_setfreq(psNuCcap, 24000000);

    /* Reset IP */
    SYS_ResetModule(psNuCcap->rstidx);

    /* Lock protected registers */
    if (u32RegLockLevel)
        SYS_LockReg();

    /* Unmask External CCAP Interrupt */
    rt_hw_interrupt_umask(psNuCcap->irqn);

    return RT_EOK;
}

static rt_err_t ccap_close(rt_device_t dev)
{
    nu_ccap_t psNuCcap = (nu_ccap_t)dev;

    /* Stop capture engine */
    CCAP_Stop(psNuCcap->base, FALSE);

    /* Disable CCAP Interrupt */
    CCAP_DisableInt(psNuCcap->base, CCAP_INT_VIEN_Msk);

    /* Mask External CCAP Interrupt */
    rt_hw_interrupt_mask(psNuCcap->irqn);

    /* Disable clock */
    ccap_sensor_setfreq(psNuCcap, 0);

    return RT_EOK;
}

static rt_err_t ccap_control(rt_device_t dev, int cmd, void *args)
{
    nu_ccap_t psNuCcap = (nu_ccap_t)dev;
    rt_err_t ret = -RT_ERROR;

    if (psNuCcap == RT_NULL)
        goto exit_ccap_control;

    switch (cmd)
    {
    case CCAP_CMD_CONFIG:
    {
        ccap_config *psCcapConf = (ccap_config *)args;
        if (args == RT_NULL)
            goto exit_ccap_control;

        rt_memcpy(&psNuCcap->sConfig, psCcapConf, sizeof(ccap_config));
    }
    break;

    case CCAP_CMD_START_CAPTURE:

        /* Enable CCAP Interrupt */
        CCAP_EnableInt(psNuCcap->base, CCAP_INT_VIEN_Msk);

        /* Start capture engine */
        CCAP_Start(psNuCcap->base);

        break;

    case CCAP_CMD_STOP_CAPTURE:

        /* Disable CCAP Interrupt */
        CCAP_DisableInt(psNuCcap->base, CCAP_INT_VIEN_Msk);

        /* Stop capture engine */
        CCAP_Stop(psNuCcap->base, FALSE);

        break;

    case CCAP_CMD_SET_SENCLK:
    {
        rt_uint32_t u32SenClk;

        RT_ASSERT(args);

        u32SenClk = *((rt_uint32_t *)args);
        if (u32SenClk > 0)
            ccap_sensor_setfreq(psNuCcap, u32SenClk);
    }
    break;

    case CCAP_CMD_SET_PIPES:
    {
        ccap_view_info_t psViewInfo;

        RT_ASSERT(args);
        psViewInfo = (ccap_view_info_t)args;

        ret = ccap_pipe_configure(psNuCcap, psViewInfo);
    }
    break;

    case CCAP_CMD_SET_OPMODE:
    {
        RT_ASSERT(args);
        int i32IsOneSutterMode = *((int *)args);

        /* Set shutter or continuous mode */
        CCAP_SET_CTL(psNuCcap->base, (i32IsOneSutterMode > 0) ? CCAP_CTL_SHUTTER_Msk : 0);
    }
    break;

    case CCAP_CMD_SET_BASEADDR:
    {
        uint32_t u32Offset = 0;
        ccap_config_t psCcapConf;

        RT_ASSERT(args);
        psCcapConf = (ccap_config_t)args;

        /* Set System Memory Packet Base Address Register */
        CCAP_SetPacketBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Packet.pu8FarmAddr);

        /* Set System Memory Planar Y Base Address Register */
        CCAP_SetPlanarYBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Planar.pu8FarmAddr + u32Offset);
        u32Offset = psCcapConf->sPipeInfo_Planar.u32Height * psCcapConf->sPipeInfo_Planar.u32Width;
        /* Set System Memory Planar U Base Address Register */
        CCAP_SetPlanarUBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Planar.pu8FarmAddr + u32Offset);
        u32Offset += ((psCcapConf->sPipeInfo_Planar.u32Height * psCcapConf->sPipeInfo_Planar.u32Width) / 2);
        /* Set System Memory Planar V Base Address Register */
        CCAP_SetPlanarVBuf(psNuCcap->base, (uint32_t)psCcapConf->sPipeInfo_Planar.pu8FarmAddr + u32Offset);
    }
    break;

    default:
        return -RT_ENOSYS;
    }

    ret = RT_EOK;

exit_ccap_control:

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
static struct rt_device_ops ccap_ops =
{
    .init = ccap_init,
    .open = ccap_open,
    .close = ccap_close,
    .read = RT_NULL,
    .write = RT_NULL,
    .control = ccap_control,
};
#endif

static rt_err_t ccap_register(struct rt_device *device, const char *name, void *user_data)
{
    RT_ASSERT(device);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &inputcapture_ops;
#else
    device->init        = ccap_init;
    device->open        = ccap_open;
    device->close       = ccap_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = ccap_control;
#endif
    device->user_data   = user_data;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_STANDALONE);
}

/**
 * Hardware CCAP Initialization
 */
int rt_hw_ccap_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (CCAP_START + 1); i < CCAP_CNT; i++)
    {
        rt_memset(&nu_ccap_arr[i].sConfig, 0, sizeof(ccap_config));

        rt_hw_interrupt_install(nu_ccap_arr[i].irqn, nu_ccap_isr, &nu_ccap_arr[i], nu_ccap_arr[i].name);

        ret = ccap_register(&nu_ccap_arr[i].device, nu_ccap_arr[i].name, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_ccap_init);

#endif
