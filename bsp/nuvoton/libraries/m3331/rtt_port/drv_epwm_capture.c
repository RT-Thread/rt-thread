/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_EPWM_CAPTURE)

#include "drv_sys.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.epwmcap"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define STR(x) #x
#define XSTR(x) STR(x)
#define CONCAT3(a, b, c) a##b##c
#define XCONCAT3(a, b, c) CONCAT3(a, b, c)
#define MAKE_EPWM_CAPTURE_NAME(x, y) XSTR(XCONCAT3(epwm, x, y))

#define MAKE_EPWM_CAPTURE_INSTANCE(x, y, z) \
    { \
        .name  = MAKE_EPWM_CAPTURE_NAME(x, y), \
        .base  = EPWM##x, \
        .irqn = EPWM##x##P##z##_IRQn, \
        .rstidx = EPWM##x##_RST, \
        .modid = EPWM##x##_MODULE, \
    },

#define FOR_EACH_EPWM_CHANNEL(x) \
    MAKE_EPWM_CAPTURE_INSTANCE(x, i0, 0) \
    MAKE_EPWM_CAPTURE_INSTANCE(x, i1, 0) \
    MAKE_EPWM_CAPTURE_INSTANCE(x, i2, 1) \
    MAKE_EPWM_CAPTURE_INSTANCE(x, i3, 1) \
    MAKE_EPWM_CAPTURE_INSTANCE(x, i4, 2) \
    MAKE_EPWM_CAPTURE_INSTANCE(x, i5, 2)

#define MAKE_EPWM_ISR(x, y, z) \
    void EPWM##x##P##y##_IRQHandler(void) \
    { \
       rt_interrupt_enter(); \
       nu_epwmcap_isr(&nu_epwmcap_arr[EPWM##x##I##z##_IDX]); \
       nu_epwmcap_isr(&nu_epwmcap_arr[EPWM##x##I##z##_IDX + 1]); \
       rt_interrupt_leave(); \
    }

/* Types / Structures ---------------------------------------------------------*/
enum
{
    EPWM_IDX_START = -1,
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
    EPWM_IDX_CNT
};

struct nu_epwmcap
{
    struct rt_inputcapture_device   parent;
    EPWM_T      *base;
    char        *name;
    IRQn_Type    irqn;
    uint32_t     rstidx;
    uint64_t     modid;

    uint8_t     u8Channel;
    uint32_t    u32CurrentRisingCnt;
    uint32_t    u32CurrentFallingCnt;
    rt_bool_t   input_data_level;
};
typedef struct nu_epwmcap *nu_epwmcap_t;

/* Static Function Prototypes ------------------------------------------------*/
static rt_err_t nu_epwmcap_init(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_epwmcap_open(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_epwmcap_close(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_epwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);
static rt_err_t CalPulseWidth(nu_epwmcap_t psNuEpwmCap);
static void nu_epwmcap_isr(nu_epwmcap_t psNuEpwmCap);
static int rt_hw_epwmcap_init(void);

/* Static Variables ----------------------------------------------------------*/
static struct nu_epwmcap nu_epwmcap_arr [] =
{
#if defined(BSP_USING_EPWM0_CAPTURE)
    FOR_EACH_EPWM_CHANNEL(0)
#endif
#if defined(BSP_USING_EPWM1_CAPTURE)
    FOR_EACH_EPWM_CHANNEL(1)
#endif
};

static struct rt_inputcapture_ops nu_epwmcap_ops =
{
    .init   = nu_epwmcap_init,
    .open   = nu_epwmcap_open,
    .close  = nu_epwmcap_close,
    .get_pulsewidth = nu_epwmcap_get_pulsewidth,
};

/* Functions Implementation --------------------------------------------------*/
static void nu_epwmcap_isr(nu_epwmcap_t psNuEpwmCap)
{
    if (EPWM_GetCaptureIntFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel) != 0)
    {
        /* Calculate pulse width */
        if (CalPulseWidth(psNuEpwmCap) == RT_EOK)
        {
            rt_hw_inputcapture_isr(&psNuEpwmCap->parent, psNuEpwmCap->input_data_level);
        }
    }
}

#if defined(BSP_USING_EPWM0_CAPTURE)
    MAKE_EPWM_ISR(0, 0, 0);
    MAKE_EPWM_ISR(0, 1, 2);
    MAKE_EPWM_ISR(0, 2, 4);
#endif

#if defined(BSP_USING_EPWM1_CAPTURE)
    MAKE_EPWM_ISR(1, 0, 0);
    MAKE_EPWM_ISR(1, 1, 2);
    MAKE_EPWM_ISR(1, 2, 4);
#endif

static rt_err_t CalPulseWidth(nu_epwmcap_t psNuEpwmCap)
{
    rt_bool_t bWrapAroundFlag = RT_FALSE;

    /* Check rising/falling capture counter is overflow or not */
    if (EPWM_GetWrapAroundFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel))
    {
        EPWM_ClearWrapAroundFlag(psNuEpwmCap->base, psNuEpwmCap->u8Channel);
        bWrapAroundFlag = RT_TRUE;
    }
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
        ret = RT_ERROR;
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
    NVIC_EnableIRQ(psNuEpwmCap->irqn);

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
        NVIC_DisableIRQ(psNuEpwmCap->irqn);

    return ret;
}

static int rt_hw_epwmcap_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (EPWM_IDX_START + 1); i < EPWM_IDX_CNT; i++)
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
        }
        ret = rt_device_inputcapture_register(&psNuEpwmCap->parent, psNuEpwmCap->name, psNuEpwmCap);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_epwmcap_init);
#endif //#if defined(BSP_USING_EPWM_CAPTURE)
