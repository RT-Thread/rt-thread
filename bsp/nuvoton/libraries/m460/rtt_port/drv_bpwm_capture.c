/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-8-19       Philo            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_BPWM_CAPTURE)

#include <rtdevice.h>
#include "NuMicro.h"

/* Private typedef --------------------------------------------------------------*/
enum
{
    BPWM_START = -1,
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
    BPWM_CNT
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

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_bpwmcap_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_bpwmcap_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_bpwmcap_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_bpwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Private define ---------------------------------------------------------------*/
#define NU_DUMMY_DATA   2   /* First rising and falling edge should be ignore */

#define NU_NO_EDGE      0
#define NU_RISING_EDGE  1
#define NU_FALLING_EDGE 2

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static struct nu_bpwmcap nu_bpwmcap_arr [] =
{
#if defined(BSP_USING_BPWM0_CAPTURE)
    {  .base = BPWM0, .name = "bpwm0i0", .irqn = BPWM0_IRQn, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
    {  .base = BPWM0, .name = "bpwm0i1", .irqn = BPWM0_IRQn, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
    {  .base = BPWM0, .name = "bpwm0i2", .irqn = BPWM0_IRQn, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
    {  .base = BPWM0, .name = "bpwm0i3", .irqn = BPWM0_IRQn, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
    {  .base = BPWM0, .name = "bpwm0i4", .irqn = BPWM0_IRQn, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
    {  .base = BPWM0, .name = "bpwm0i5", .irqn = BPWM0_IRQn, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
#endif
#if defined(BSP_USING_BPWM1_CAPTURE)
    {  .base = BPWM1, .name = "bpwm1i0", .irqn = BPWM1_IRQn, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
    {  .base = BPWM1, .name = "bpwm1i1", .irqn = BPWM1_IRQn, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
    {  .base = BPWM1, .name = "bpwm1i2", .irqn = BPWM1_IRQn, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
    {  .base = BPWM1, .name = "bpwm1i3", .irqn = BPWM1_IRQn, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
    {  .base = BPWM1, .name = "bpwm1i4", .irqn = BPWM1_IRQn, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
    {  .base = BPWM1, .name = "bpwm1i5", .irqn = BPWM1_IRQn, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
#endif
#if (BPWM_CNT==0)
    0
#endif
};

static struct rt_inputcapture_ops nu_bpwmcap_ops =
{
    .init   =   nu_bpwmcap_init,
    .open   =   nu_bpwmcap_open,
    .close  =   nu_bpwmcap_close,
    .get_pulsewidth =   nu_bpwmcap_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
static void nu_bpwmcap_isr(nu_bpwmcap_t psNuBpwmCapBase)
{
    uint32_t u32Status;
    int i;

    for (i = 0; i < BPWM_CHANNEL_NUM ; i++)
    {
        nu_bpwmcap_t psNuBpwmCap = psNuBpwmCapBase + i;
        if (psNuBpwmCap->u8DummyData < NU_DUMMY_DATA)
        {
            psNuBpwmCap->u8DummyData++;
        }
        else
        {
            u32Status = BPWM_GetCaptureIntFlag(psNuBpwmCap->base, psNuBpwmCap->u8Channel);

            switch (u32Status)
            {
            case NU_NO_EDGE:
                break;

            case NU_RISING_EDGE:
                BPWM_ClearCaptureIntFlag(psNuBpwmCap->base, psNuBpwmCap->u8Channel, BPWM_CAPTURE_INT_RISING_LATCH);
                psNuBpwmCap->u32CurrentRisingCnt = BPWM_GET_CAPTURE_RISING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);
                rt_hw_inputcapture_isr(&psNuBpwmCap->parent, psNuBpwmCap->input_data_level);
                break;

            case NU_FALLING_EDGE:
                BPWM_ClearCaptureIntFlag(psNuBpwmCap->base, psNuBpwmCap->u8Channel, BPWM_CAPTURE_INT_FALLING_LATCH);
                psNuBpwmCap->u32CurrentFallingCnt = BPWM_GET_CAPTURE_FALLING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);
                rt_hw_inputcapture_isr(&psNuBpwmCap->parent, psNuBpwmCap->input_data_level);
                break;

            default:
                BPWM_ClearCaptureIntFlag(psNuBpwmCap->base, psNuBpwmCap->u8Channel, BPWM_CAPTURE_INT_RISING_LATCH | BPWM_CAPTURE_INT_FALLING_LATCH);
                BPWM_GET_CAPTURE_RISING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);
                BPWM_GET_CAPTURE_FALLING_DATA(psNuBpwmCap->base, psNuBpwmCap->u8Channel);

                break;
            }
        }
    }
}

#if defined(BSP_USING_BPWM0_CAPTURE)
void BPWM0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_bpwmcap_isr(&nu_bpwmcap_arr[BPWM0I0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //defined(BSP_USING_BPWM0_CAPTURE)

#if defined(BSP_USING_BPWM1_CAPTURE)
void BPWM1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_bpwmcap_isr(&nu_bpwmcap_arr[BPWM1I0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //defined(BSP_USING_BPWM1_CAPTURE)

static rt_err_t nu_bpwmcap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    nu_bpwmcap_t psNuBpwmCap;
    float fTempCnt;

    psNuBpwmCap = (nu_bpwmcap_t)inputcapture;

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
        ret = -RT_ERROR;
    }
    return -(ret);
}

static rt_err_t nu_bpwmcap_init(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_bpwmcap_t psNuBpwmCap;

    RT_ASSERT(inputcapture);

    psNuBpwmCap = (nu_bpwmcap_t) inputcapture;

    psNuBpwmCap->u8DummyData = 0;
    psNuBpwmCap->u32CurrentFallingCnt = 0;
    psNuBpwmCap->u32CurrentRisingCnt = 0;
    psNuBpwmCap->u32LastRisingCnt = 0;
    psNuBpwmCap->u32LastFallingCnt = 0;
    psNuBpwmCap->parent.ops = &nu_bpwmcap_ops;

    if ((psNuBpwmCap->u8Channel % BPWM_CHANNEL_NUM) == 0)
    {
        /* Enable bpwm module */
        CLK_EnableModuleClock(psNuBpwmCap->modid);
        SYS_ResetModule(psNuBpwmCap->rstidx);
    }

    return -(ret);
}

static rt_err_t nu_bpwmcap_open(struct rt_inputcapture_device *inputcapture)
{
    nu_bpwmcap_t psNuBpwmCap;

    RT_ASSERT(inputcapture);

    psNuBpwmCap = (nu_bpwmcap_t) inputcapture;

    /* Set capture time as 500 nano second */
    psNuBpwmCap->fUsPerTick = (float)BPWM_ConfigCaptureChannel(psNuBpwmCap->base, 0, 500, 0) / 1000;

    /* Set counter type as up count */
    BPWM_SET_ALIGNED_TYPE(psNuBpwmCap->base, 0, BPWM_UP_COUNTER);

    /* Enable BPWM Timer */
    BPWM_Start(psNuBpwmCap->base, 0);

    /* Enable capture rising/falling edge interrupt */
    BPWM_EnableCaptureInt(psNuBpwmCap->base, psNuBpwmCap->u8Channel, BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    /* Enable Capture Function for BPWM */
    BPWM_EnableCapture(psNuBpwmCap->base, 0x1 << psNuBpwmCap->u8Channel);

    /* Enable BPWM NVIC interrupt */
    if ((psNuBpwmCap->base->CAPCTL & ((0x1 << BPWM_CHANNEL_NUM) - 1)) != 0u)
        NVIC_EnableIRQ(psNuBpwmCap->irqn);

    return RT_EOK;
}

static rt_err_t nu_bpwmcap_close(struct rt_inputcapture_device *inputcapture)
{
    nu_bpwmcap_t psNuBpwmCap;

    RT_ASSERT(inputcapture);

    psNuBpwmCap = (nu_bpwmcap_t) inputcapture;

    /* Enable Capture Function for BPWM */
    BPWM_DisableCapture(psNuBpwmCap->base, 0x1 << psNuBpwmCap->u8Channel);

    /* Disable capture rising/falling edge interrupt */
    BPWM_DisableCaptureInt(psNuBpwmCap->base, psNuBpwmCap->u8Channel, BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    /* Disable BPWM NVIC interrupt */
    if ((psNuBpwmCap->base->CAPCTL & ((0x1 << BPWM_CHANNEL_NUM) - 1)) == 0u)
        NVIC_DisableIRQ(psNuBpwmCap->irqn);

    return RT_EOK;
}

/* Init and register bpwm capture */
static int nu_bpwm_capture_device_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (BPWM_START + 1); i < BPWM_CNT; i++)
    {
        nu_bpwmcap_t psNuBpwmCap = &nu_bpwmcap_arr[i];

        psNuBpwmCap->u8Channel = i % BPWM_CHANNEL_NUM;
        psNuBpwmCap->u8DummyData = 0;
        psNuBpwmCap->u32CurrentFallingCnt = 0;
        psNuBpwmCap->u32CurrentRisingCnt = 0;
        psNuBpwmCap->u32LastRisingCnt = 0;
        psNuBpwmCap->u32LastFallingCnt = 0;
        psNuBpwmCap->parent.ops = &nu_bpwmcap_ops;

        if ((psNuBpwmCap->u8Channel % BPWM_CHANNEL_NUM) == 0)
        {
            /* Enable bpwm module */
            CLK_EnableModuleClock(psNuBpwmCap->modid);
            SYS_ResetModule(psNuBpwmCap->rstidx);
        }

        /* register inputcapture device */
        ret = rt_device_inputcapture_register(&psNuBpwmCap->parent, psNuBpwmCap->name, psNuBpwmCap);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_bpwm_capture_device_init);
#endif //#if defined(BSP_USING_BPWM_CAPTURE)
