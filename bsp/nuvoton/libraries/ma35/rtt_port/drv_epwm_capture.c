/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-10-19      Wayne            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_EPWM_CAPTURE)

#include <rtdevice.h>
#include "drv_sys.h"
#include "drv_common.h"

/* Private typedef --------------------------------------------------------------*/
enum
{
    EPWM_START = -1,
#if defined(BSP_USING_EPWM0_CAPTURE)
    EPWM0I0_IDX,
    EPWM0I1_IDX,
    EPWM0I2_IDX,
    EPWM0I3_IDX,
    EPWM0I4_IDX,
    EPWM0I5_IDX,
#endif
#if defined(BSP_USING_EPWM1_CAPTURE)
    EPWM1I0_IDX,
    EPWM1I1_IDX,
    EPWM1I2_IDX,
    EPWM1I3_IDX,
    EPWM1I4_IDX,
    EPWM1I5_IDX,
#endif
#if defined(BSP_USING_EPWM2_CAPTURE)
    EPWM2I0_IDX,
    EPWM2I1_IDX,
    EPWM2I2_IDX,
    EPWM2I3_IDX,
    EPWM2I4_IDX,
    EPWM2I5_IDX,
#endif
    EPWM_CNT
};

struct nu_epwmcap
{
    struct rt_inputcapture_device   parent;
    EPWM_T      *base;
    char        *name;
    IRQn_Type    irqn;
    uint32_t     rstidx;
    uint32_t     modid;

    uint8_t     u8Channel;
    uint32_t    u32CurrentRisingCnt;
    uint32_t    u32CurrentFallingCnt;
    rt_bool_t   input_data_level;
};
typedef struct nu_epwmcap *nu_epwmcap_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_epwmcap_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_epwmcap_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_epwmcap_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_epwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static struct nu_epwmcap nu_epwmcap_arr [] =
{
#if defined(BSP_USING_EPWM0_CAPTURE)
    {  .base = EPWM0, .name = "epwm0i0", .irqn = EPWM0P0_IRQn, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
    {  .base = EPWM0, .name = "epwm0i1", .irqn = EPWM0P0_IRQn, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
    {  .base = EPWM0, .name = "epwm0i2", .irqn = EPWM0P1_IRQn, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
    {  .base = EPWM0, .name = "epwm0i3", .irqn = EPWM0P1_IRQn, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
    {  .base = EPWM0, .name = "epwm0i4", .irqn = EPWM0P2_IRQn, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
    {  .base = EPWM0, .name = "epwm0i5", .irqn = EPWM0P2_IRQn, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
#endif
#if defined(BSP_USING_EPWM1_CAPTURE)
    {  .base = EPWM1, .name = "epwm1i0", .irqn = EPWM1P0_IRQn, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
    {  .base = EPWM1, .name = "epwm1i1", .irqn = EPWM1P0_IRQn, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
    {  .base = EPWM1, .name = "epwm1i2", .irqn = EPWM1P1_IRQn, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
    {  .base = EPWM1, .name = "epwm1i3", .irqn = EPWM1P1_IRQn, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
    {  .base = EPWM1, .name = "epwm1i4", .irqn = EPWM1P2_IRQn, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
    {  .base = EPWM1, .name = "epwm1i5", .irqn = EPWM1P2_IRQn, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
#endif
#if defined(BSP_USING_EPWM2_CAPTURE)
    {  .base = EPWM2, .name = "epwm2i0", .irqn = EPWM2P0_IRQn, .rstidx = EPWM2_RST, .modid = EPWM2_MODULE },
    {  .base = EPWM2, .name = "epwm2i1", .irqn = EPWM2P0_IRQn, .rstidx = EPWM2_RST, .modid = EPWM2_MODULE },
    {  .base = EPWM2, .name = "epwm2i2", .irqn = EPWM2P1_IRQn, .rstidx = EPWM2_RST, .modid = EPWM2_MODULE },
    {  .base = EPWM2, .name = "epwm2i3", .irqn = EPWM2P1_IRQn, .rstidx = EPWM2_RST, .modid = EPWM2_MODULE },
    {  .base = EPWM2, .name = "epwm2i4", .irqn = EPWM2P2_IRQn, .rstidx = EPWM2_RST, .modid = EPWM2_MODULE },
    {  .base = EPWM2, .name = "epwm2i5", .irqn = EPWM2P2_IRQn, .rstidx = EPWM2_RST, .modid = EPWM2_MODULE },
#endif
};

static struct rt_inputcapture_ops nu_epwmcap_ops =
{
    .init   =   nu_epwmcap_init,
    .open   =   nu_epwmcap_open,
    .close  =   nu_epwmcap_close,
    .get_pulsewidth =   nu_epwmcap_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
static rt_err_t CalPulseWidth(nu_epwmcap_t psNuEpwmCap)
{
    rt_bool_t bWrapAroundFlag = RT_FALSE;

    /* Check rising/falling capture counter is overflow or not */
    if (EPWM_GetWrapAroundFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel))
    {
        EPWM_ClearWrapAroundFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel);
        bWrapAroundFlag = RT_TRUE;
    }

    /* Read the capture counter value if falling/rising edge */
    if (EPWM_GetCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel) == 1)//Rising edge
    {
        EPWM_ClearCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel, EPWM_CAPTURE_INT_RISING_LATCH);

        if (bWrapAroundFlag)
        {
            psNuEpwmCap->u32CurrentRisingCnt = 0x10000;
        }
        psNuEpwmCap->u32CurrentRisingCnt += EPWM_GET_CAPTURE_RISING_DATA(psNuEpwmCap->base, psNuEpwmCap->u8Channel);
    }
    else if (EPWM_GetCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel) == 2)//Falling edge
    {
        EPWM_ClearCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH);

        if (bWrapAroundFlag)
        {
            psNuEpwmCap->u32CurrentFallingCnt = 0x10000;
        }
        psNuEpwmCap->u32CurrentFallingCnt += EPWM_GET_CAPTURE_FALLING_DATA(psNuEpwmCap->base, psNuEpwmCap->u8Channel);
    }
    else //Rising & Falling edge
    {
        EPWM_ClearCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel, EPWM_CAPTURE_INT_RISING_LATCH);
        EPWM_ClearCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH);

        return -(RT_ERROR);
    }

    return RT_EOK;
}

static void nu_epwmcap_isr(int vector, void *param)
{
    nu_epwmcap_t psNuEpwmCap = (nu_epwmcap_t)param;

    if (EPWM_GetCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel) != 0)
    {
        /* Calculate pulse width */
        if (CalPulseWidth(psNuEpwmCap) == RT_EOK)
        {
            rt_hw_inputcapture_isr(&psNuEpwmCap->parent, psNuEpwmCap->input_data_level);
        }
    }
}

static rt_err_t nu_epwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    nu_epwmcap_t psNuEpwmCap = (nu_epwmcap_t)inputcapture;

    RT_ASSERT(psNuEpwmCap != RT_NULL);

    if (psNuEpwmCap->u32CurrentFallingCnt)
    {
        *pulsewidth_us = psNuEpwmCap->u32CurrentFallingCnt;
        psNuEpwmCap->input_data_level = RT_FALSE;
        psNuEpwmCap->u32CurrentFallingCnt = 0;
    }
    else if (psNuEpwmCap->u32CurrentRisingCnt)
    {
        *pulsewidth_us = psNuEpwmCap->u32CurrentRisingCnt;
        psNuEpwmCap->input_data_level = RT_TRUE;
        psNuEpwmCap->u32CurrentRisingCnt = 0;
    }
    else
    {
        ret = -RT_ERROR;
    }
    return -(ret);
}

static rt_err_t nu_epwmcap_init(struct rt_inputcapture_device *inputcapture)
{
    return RT_EOK;
}

static rt_err_t nu_epwmcap_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_epwmcap_t psNuEpwmCap = (nu_epwmcap_t) inputcapture;

    RT_ASSERT(psNuEpwmCap != RT_NULL);

    /* Set capture time as 1000 nanosecond */
    EPWM_ConfigCaptureChannel(psNuEpwmCap->base, psNuEpwmCap->u8Channel, 1000, 0);

    /* Enable capture rising/falling edge interrupt */
    EPWM_EnableCaptureInt(psNuEpwmCap->base, psNuEpwmCap->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH | EPWM_CAPTURE_INT_RISING_LATCH);

    /* Enable Capture Function for EPWM */
    EPWM_EnableCapture(psNuEpwmCap->base, 0x1 << psNuEpwmCap->u8Channel);

    /* Enable rising/falling capture reload */
    psNuEpwmCap->base->CAPCTL |= (0x1 << (EPWM_CAPCTL_RCRLDEN0_Pos + psNuEpwmCap->u8Channel))
                                 | (0x1 << (EPWM_CAPCTL_FCRLDEN0_Pos + psNuEpwmCap->u8Channel));

    /* Set counter type as down count */
    EPWM_SET_ALIGNED_TYPE(psNuEpwmCap->base, 0x1 << psNuEpwmCap->u8Channel, EPWM_UP_COUNTER);

    /* Enable EPWM Timer */
    EPWM_Start(psNuEpwmCap->base, 0x1 << psNuEpwmCap->u8Channel);

    /* Enable EPWMxPx interrupt. */
    rt_hw_interrupt_umask(psNuEpwmCap->irqn);

    return ret;
}

static rt_err_t nu_epwmcap_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;

    nu_epwmcap_t psNuEpwmCap = (nu_epwmcap_t) inputcapture;

    RT_ASSERT(psNuEpwmCap != RT_NULL);

    /* Disable capture rising/falling edge interrupt */
    EPWM_DisableCaptureInt(psNuEpwmCap->base, psNuEpwmCap->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH | EPWM_CAPTURE_INT_RISING_LATCH);

    /* Stop EPWM Timer */
    EPWM_ForceStop(psNuEpwmCap->base, 0x1 << psNuEpwmCap->u8Channel);

    /* Disable EPWMxPx interrupt */
    if ((psNuEpwmCap->base->CNTEN & (0x3 << (psNuEpwmCap->u8Channel / 2 * 2))) == 0u)
        rt_hw_interrupt_mask(psNuEpwmCap->irqn);

    return ret;
}

/* Init and register epwm capture */
int rt_hw_epwmcap_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (EPWM_START + 1); i < EPWM_CNT; i++)
    {
        nu_epwmcap_t psNuEpwmCap = &nu_epwmcap_arr[i];

        psNuEpwmCap->u8Channel = i % EPWM_CHANNEL_NUM;
        psNuEpwmCap->u32CurrentRisingCnt = 0;
        psNuEpwmCap->u32CurrentFallingCnt = 0;
        psNuEpwmCap->parent.ops = &nu_epwmcap_ops;

        if ((psNuEpwmCap->u8Channel % EPWM_CHANNEL_NUM) == 0)
        {
            /* Enable epwm module */
            CLK_EnableModuleClock(psNuEpwmCap->modid);
            SYS_ResetModule(psNuEpwmCap->rstidx);

            /* register isr */
            rt_hw_interrupt_install(psNuEpwmCap->irqn, nu_epwmcap_isr, psNuEpwmCap, psNuEpwmCap->name);
        }

        /* register inputcapture device */
        ret = rt_device_inputcapture_register(&psNuEpwmCap->parent, psNuEpwmCap->name, psNuEpwmCap);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_epwmcap_init);

#endif //#if defined(BSP_USING_EPWM_CAPTURE)
