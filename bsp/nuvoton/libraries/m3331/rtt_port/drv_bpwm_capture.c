/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_BPWM_CAPTURE)

#include "NuMicro.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.bpwmcap"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* First rising and falling edge should be ignore */
#define NU_DUMMY_DATA   2

#define NU_NO_EDGE      0
#define NU_RISING_EDGE  1
#define NU_FALLING_EDGE 2
#define NU_BOTH_EDGE    3

#define STR(x) #x
#define XSTR(x) STR(x)
#define CONCAT3(a, b, c) a##b##c
#define XCONCAT3(a, b, c) CONCAT3(a, b, c)
#define MAKE_BPWM_CAPTURE_NAME(x, y) XSTR(XCONCAT3(bpwm, x, y))

#define MAKE_BPWM_CAPTURE_INSTANCE(x, y) \
    { \
        .name  = MAKE_BPWM_CAPTURE_NAME(x, y), \
        .base  = BPWM##x, \
        .irqn = BPWM##x##_IRQn, \
        .rstidx = BPWM##x##_RST, \
        .modid = BPWM##x##_MODULE, \
    },

#define FOR_EACH_BPWM_CHANNEL(x) \
    MAKE_BPWM_CAPTURE_INSTANCE(x, i0) \
    MAKE_BPWM_CAPTURE_INSTANCE(x, i1) \
    MAKE_BPWM_CAPTURE_INSTANCE(x, i2) \
    MAKE_BPWM_CAPTURE_INSTANCE(x, i3) \
    MAKE_BPWM_CAPTURE_INSTANCE(x, i4) \
    MAKE_BPWM_CAPTURE_INSTANCE(x, i5)

/* Types / Structures ---------------------------------------------------------*/
enum
{
    BPWM_IDX_START = -1,
#if defined(BSP_USING_BPWM0_CAPTURE)
    BPWM0I0_IDX,
    BPWM0I1_IDX,
    BPWM0I2_IDX,
    BPWM0I3_IDX,
    BPWM0I4_IDX,
    BPWM0I5_IDX,
#endif
#if defined(BSP_USING_BPWM1_CAPTURE)
    BPWM1I0_IDX,
    BPWM1I1_IDX,
    BPWM1I2_IDX,
    BPWM1I3_IDX,
    BPWM1I4_IDX,
    BPWM1I5_IDX,
#endif
#if defined(BSP_USING_BPWM2_CAPTURE)
    BPWM2I0_IDX,
    BPWM2I1_IDX,
    BPWM2I2_IDX,
    BPWM2I3_IDX,
    BPWM2I4_IDX,
    BPWM2I5_IDX,
#endif
#if defined(BSP_USING_BPWM3_CAPTURE)
    BPWM3I0_IDX,
    BPWM3I1_IDX,
    BPWM3I2_IDX,
    BPWM3I3_IDX,
    BPWM3I4_IDX,
    BPWM3I5_IDX,
#endif
#if defined(BSP_USING_BPWM4_CAPTURE)
    BPWM4I0_IDX,
    BPWM4I1_IDX,
    BPWM4I2_IDX,
    BPWM4I3_IDX,
    BPWM4I4_IDX,
    BPWM4I5_IDX,
#endif
#if defined(BSP_USING_BPWM5_CAPTURE)
    BPWM5I0_IDX,
    BPWM5I1_IDX,
    BPWM5I2_IDX,
    BPWM5I3_IDX,
    BPWM5I4_IDX,
    BPWM5I5_IDX,
#endif
    BPWM_IDX_CNT
};

struct nu_bpwmcap
{
    struct rt_inputcapture_device   parent;
    BPWM_T      *base;
    char        *name;
    IRQn_Type    irqn;
    uint32_t     rstidx;
    uint32_t     modid;
    float       fUsPerTick;
    uint8_t     u8Channel;
    uint8_t     u8DummyData;
    uint32_t    u32CurrentRisingCnt;
    uint32_t    u32CurrentFallingCnt;
    uint32_t    u32LastRisingCnt;
    uint32_t    u32LastFallingCnt;
    rt_bool_t   input_data_level;
};
typedef struct nu_bpwmcap *nu_bpwmcap_t;

/* Static Function Prototypes ------------------------------------------------*/
static rt_err_t nu_bpwmcap_open(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_bpwmcap_close(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_bpwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);
static void nu_bpwmcap_isr(nu_bpwmcap_t psNuBpwmCapBase);
static void nu_bpwmcap_reset(nu_bpwmcap_t psNuBpwmCap);
static int rt_hw_bpwmcap_init(void);

/* Static Variables ----------------------------------------------------------*/
static struct nu_bpwmcap nu_bpwmcap_arr [] =
{
#if defined(BSP_USING_BPWM0_CAPTURE)
    FOR_EACH_BPWM_CHANNEL(0)
#endif
#if defined(BSP_USING_BPWM1_CAPTURE)
    FOR_EACH_BPWM_CHANNEL(1)
#endif
#if defined(BSP_USING_BPWM2_CAPTURE)
    FOR_EACH_BPWM_CHANNEL(2)
#endif
#if defined(BSP_USING_BPWM3_CAPTURE)
    FOR_EACH_BPWM_CHANNEL(3)
#endif
#if defined(BSP_USING_BPWM4_CAPTURE)
    FOR_EACH_BPWM_CHANNEL(4)
#endif
#if defined(BSP_USING_BPWM5_CAPTURE)
    FOR_EACH_BPWM_CHANNEL(5)
#endif
};

static struct rt_inputcapture_ops nu_bpwmcap_ops =
{
    .init   =   NULL,
    .open   =   nu_bpwmcap_open,
    .close  =   nu_bpwmcap_close,
    .get_pulsewidth =   nu_bpwmcap_get_pulsewidth,
};

/* Functions Implementation --------------------------------------------------*/
static void nu_bpwmcap_isr(nu_bpwmcap_t psNuBpwmCapBase)
{
    int i;
    uint32_t u32Status;

    for (i = 0; i < BPWM_CHANNEL_NUM; i++)
    {
        nu_bpwmcap_t psNuBpwmCap = psNuBpwmCapBase + i;

        if ((psNuBpwmCap->base->CAPCTL & (0x1 << i)) == 0)
            continue;

        u32Status = BPWM_GetCaptureIntFlag(psNuBpwmCap->base, psNuBpwmCap->u8Channel);
        switch (u32Status)
        {
        case NU_NO_EDGE:
            break;

        case NU_RISING_EDGE:
            BPWM_ClearCaptureIntFlag(psNuBpwmCap->base,
                                     psNuBpwmCap->u8Channel,
                                     BPWM_CAPTURE_INT_RISING_LATCH);
            psNuBpwmCap->u32CurrentRisingCnt = BPWM_GET_CAPTURE_RISING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);

            rt_hw_inputcapture_isr(&psNuBpwmCap->parent, psNuBpwmCap->input_data_level);

            break;

        case NU_FALLING_EDGE:
            BPWM_ClearCaptureIntFlag(psNuBpwmCap->base,
                                     psNuBpwmCap->u8Channel,
                                     BPWM_CAPTURE_INT_FALLING_LATCH);
            psNuBpwmCap->u32CurrentFallingCnt = BPWM_GET_CAPTURE_FALLING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);

            rt_hw_inputcapture_isr(&psNuBpwmCap->parent, psNuBpwmCap->input_data_level);

            break;

        case NU_BOTH_EDGE:
            BPWM_ClearCaptureIntFlag(psNuBpwmCap->base,
                                     psNuBpwmCap->u8Channel,
                                     BPWM_CAPTURE_INT_RISING_LATCH | BPWM_CAPTURE_INT_FALLING_LATCH);
            BPWM_GET_CAPTURE_FALLING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);
            BPWM_GET_CAPTURE_RISING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);
            break;

        default:
            break;

        }

    }
}

#define MAKE_BPWM_CAPTURE_ISR(x) \
    void BPWM##x##_IRQHandler(void) \
    { \
       rt_interrupt_enter(); \
       nu_bpwmcap_isr(&nu_bpwmcap_arr[BPWM##x##I0_IDX]); \
       rt_interrupt_leave(); \
    }

#if defined(BSP_USING_BPWM0_CAPTURE)
    MAKE_BPWM_CAPTURE_ISR(0);
#endif
#if defined(BSP_USING_BPWM1_CAPTURE)
    MAKE_BPWM_CAPTURE_ISR(1);
#endif
#if defined(BSP_USING_BPWM2_CAPTURE)
    MAKE_BPWM_CAPTURE_ISR(2);
#endif
#if defined(BSP_USING_BPWM3_CAPTURE)
    MAKE_BPWM_CAPTURE_ISR(3);
#endif
#if defined(BSP_USING_BPWM4_CAPTURE)
    MAKE_BPWM_CAPTURE_ISR(4);
#endif
#if defined(BSP_USING_BPWM5_CAPTURE)
    MAKE_BPWM_CAPTURE_ISR(5);
#endif

static rt_err_t nu_bpwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    float fTempCnt;
    nu_bpwmcap_t psNuBpwmCap = (nu_bpwmcap_t)inputcapture;

    RT_ASSERT(inputcapture);

    if (psNuBpwmCap->u32CurrentFallingCnt)
    {
        if (psNuBpwmCap->u32CurrentFallingCnt > psNuBpwmCap->u32LastRisingCnt)
            fTempCnt = psNuBpwmCap->u32CurrentFallingCnt - psNuBpwmCap->u32LastRisingCnt;
        else    /* Overrun case */
            fTempCnt = psNuBpwmCap->u32CurrentFallingCnt + (0x10000 - psNuBpwmCap->u32LastRisingCnt);

        *pulsewidth_us = fTempCnt * psNuBpwmCap->fUsPerTick;
        psNuBpwmCap->input_data_level = RT_FALSE;
        psNuBpwmCap->u32LastFallingCnt = psNuBpwmCap->u32CurrentFallingCnt;
        psNuBpwmCap->u32CurrentFallingCnt = 0;
    }
    else if (psNuBpwmCap->u32CurrentRisingCnt)
    {
        if (psNuBpwmCap->u32CurrentRisingCnt > psNuBpwmCap->u32LastFallingCnt)
            fTempCnt = psNuBpwmCap->u32CurrentRisingCnt - psNuBpwmCap->u32LastFallingCnt;
        else    /* Overrun case */
            fTempCnt = psNuBpwmCap->u32CurrentRisingCnt + (0x10000 - psNuBpwmCap->u32LastFallingCnt);

        *pulsewidth_us = fTempCnt * psNuBpwmCap->fUsPerTick;
        psNuBpwmCap->input_data_level = RT_TRUE;
        psNuBpwmCap->u32LastRisingCnt = psNuBpwmCap->u32CurrentRisingCnt;
        psNuBpwmCap->u32CurrentRisingCnt = 0;
    }
    else
    {
        ret = RT_ERROR;
    }
    return -(ret);
}

static void nu_bpwmcap_reset(nu_bpwmcap_t psNuBpwmCap)
{
    psNuBpwmCap->u8DummyData = 0;
    psNuBpwmCap->u32CurrentFallingCnt = 0;
    psNuBpwmCap->u32CurrentRisingCnt = 0;
    psNuBpwmCap->u32LastRisingCnt = 0;
    psNuBpwmCap->u32LastFallingCnt = 0;
}

static rt_err_t nu_bpwmcap_open(struct rt_inputcapture_device *inputcapture)
{
    nu_bpwmcap_t psNuBpwmCap = (nu_bpwmcap_t) inputcapture;

    RT_ASSERT(inputcapture);

    nu_bpwmcap_reset(psNuBpwmCap);

    /* Set capture time as 500 nano second */
    psNuBpwmCap->fUsPerTick = (float)BPWM_ConfigCaptureChannel(psNuBpwmCap->base, psNuBpwmCap->u8Channel, 500, 0) / 1000;

    /* Set counter type as up count */
    BPWM_SET_ALIGNED_TYPE(psNuBpwmCap->base, (0x1 << psNuBpwmCap->u8Channel), BPWM_UP_COUNTER);

    /* Enable BPWM Timer */
    BPWM_Start(psNuBpwmCap->base, (0x1 << psNuBpwmCap->u8Channel));

    /* Enable capture rising/falling edge interrupt */
    BPWM_EnableCaptureInt(psNuBpwmCap->base,
                          psNuBpwmCap->u8Channel,
                          BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    /* Enable Capture Function for BPWM */
    BPWM_EnableCapture(psNuBpwmCap->base, 0x1 << psNuBpwmCap->u8Channel);

    /* Enable BPWM NVIC interrupt */
    if ((psNuBpwmCap->base->CAPCTL & ((0x1 << BPWM_CHANNEL_NUM) - 1)) != 0u)
        NVIC_EnableIRQ(psNuBpwmCap->irqn);

    return RT_EOK;
}

static rt_err_t nu_bpwmcap_close(struct rt_inputcapture_device *inputcapture)
{
    nu_bpwmcap_t psNuBpwmCap = (nu_bpwmcap_t) inputcapture;

    RT_ASSERT(inputcapture);

    /* Disable capture rising/falling edge interrupt */
    BPWM_DisableCaptureInt(psNuBpwmCap->base,
                           psNuBpwmCap->u8Channel,
                           BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    /* Enable Capture Function for BPWM */
    BPWM_DisableCapture(psNuBpwmCap->base, 0x1 << psNuBpwmCap->u8Channel);

    /* Clear Capture Interrupt flag for BPWM */
    BPWM_ClearCaptureIntFlag(psNuBpwmCap->base,
                             psNuBpwmCap->u8Channel,
                             BPWM_CAPTURE_INT_RISING_LATCH | BPWM_CAPTURE_INT_FALLING_LATCH);

    /* Disable BPWM Timer */
    BPWM_Stop(psNuBpwmCap->base, (0x1 << psNuBpwmCap->u8Channel));

    /* Disable BPWM NVIC interrupt */
    if ((psNuBpwmCap->base->CAPCTL & ((0x1 << BPWM_CHANNEL_NUM) - 1)) == 0u)
        NVIC_DisableIRQ(psNuBpwmCap->irqn);

    nu_bpwmcap_reset(psNuBpwmCap);

    return RT_EOK;
}

static int rt_hw_bpwmcap_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (BPWM_IDX_START + 1); i < BPWM_IDX_CNT; i++)
    {
        nu_bpwmcap_t psNuBpwmCap = &nu_bpwmcap_arr[i];

        psNuBpwmCap->u8Channel = i % BPWM_CHANNEL_NUM;
        psNuBpwmCap->parent.ops = &nu_bpwmcap_ops;
        nu_bpwmcap_reset(psNuBpwmCap);

        if ((psNuBpwmCap->u8Channel % BPWM_CHANNEL_NUM) == 0)
        {
            /* Enable bpwm module */
            CLK_EnableModuleClock(psNuBpwmCap->modid);
            SYS_ResetModule(psNuBpwmCap->rstidx);
        }
        ret = rt_device_inputcapture_register(&psNuBpwmCap->parent, psNuBpwmCap->name, psNuBpwmCap);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_bpwmcap_init);

#endif //#if defined(BSP_USING_BPWM_CAPTURE)
