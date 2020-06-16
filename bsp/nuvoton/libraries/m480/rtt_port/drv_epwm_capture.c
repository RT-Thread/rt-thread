/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-4        Philo            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_EPWM_CAPTURE)
#include <rtdevice.h>
#include <NuMicro.h>

#define EPWM_CH0CH1_POS    (0)
#define EPWM_CH2CH3_POS    (2)
#define EPWM_CH4CH5_POS    (4)

/* Private typedef --------------------------------------------------------------*/
typedef struct nu_capture
{
    struct rt_inputcapture_device   parent;
    EPWM_T      *epwm;
    uint8_t     u8Channel;
    IRQn_Type   irq;
    uint32_t    u32CurrentRisingCnt;
    uint32_t    u32CurrentFallingCnt;
    rt_bool_t   input_data_level;
} nu_capture_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
#if (BSP_USING_EPWM0_CAPTURE_CHMSK!=0)
static const char *nu_epwm0_device_name[EPWM_CHANNEL_NUM] = { "epwm0i0", "epwm0i1", "epwm0i2", "epwm0i3", "epwm0i4", "epwm0i5"};
static const IRQn_Type nu_epwm0_irq[EPWM_CHANNEL_NUM / 2] = { EPWM0P0_IRQn, EPWM0P1_IRQn, EPWM0P2_IRQn};
static nu_capture_t nu_epwm0_capture[EPWM_CHANNEL_NUM] = {0};
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK!=0)
static const char *nu_epwm1_device_name[EPWM_CHANNEL_NUM] = {"epwm1i0", "epwm1i1", "epwm1i2", "epwm1i3", "epwm1i4", "epwm1i5", };
static const IRQn_Type nu_epwm1_irq[EPWM_CHANNEL_NUM / 2] = {EPWM1P0_IRQn, EPWM1P1_IRQn, EPWM1P2_IRQn };
static nu_capture_t nu_epwm1_capture[EPWM_CHANNEL_NUM] = {0};
#endif

static struct rt_inputcapture_ops nu_capture_ops =
{
    .init   =   nu_capture_init,
    .open   =   nu_capture_open,
    .close  =   nu_capture_close,
    .get_pulsewidth =   nu_capture_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
static rt_err_t CalPulseWidth(nu_capture_t *nu_capture)
{
    rt_bool_t bWrapAroundFlag = RT_FALSE;

    /* Check rising/falling capture counter is overflow or not */
    if (EPWM_GetWrapAroundFlag(nu_capture->epwm, nu_capture->u8Channel))
    {
        EPWM_ClearWrapAroundFlag(nu_capture->epwm, nu_capture->u8Channel);
        bWrapAroundFlag = RT_TRUE;
    }

    /* Read the capture counter value if falling/risning edge */
    if (EPWM_GetCaptureIntFlag(nu_capture->epwm, nu_capture->u8Channel) == 1)//Rising edge
    {
        EPWM_ClearCaptureIntFlag(nu_capture->epwm, nu_capture->u8Channel, EPWM_CAPTURE_INT_RISING_LATCH);

        if (bWrapAroundFlag)
        {
            nu_capture->u32CurrentRisingCnt = 0x10000;
        }
        nu_capture->u32CurrentRisingCnt += EPWM_GET_CAPTURE_RISING_DATA(nu_capture->epwm, nu_capture->u8Channel);
    }
    else if (EPWM_GetCaptureIntFlag(nu_capture->epwm, nu_capture->u8Channel) == 2)//Falling edge
    {
        EPWM_ClearCaptureIntFlag(nu_capture->epwm, nu_capture->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH);

        if (bWrapAroundFlag)
        {
            nu_capture->u32CurrentFallingCnt = 0x10000;
        }
        nu_capture->u32CurrentFallingCnt += EPWM_GET_CAPTURE_FALLING_DATA(nu_capture->epwm, nu_capture->u8Channel);
    }
    else
    {
        EPWM_ClearCaptureIntFlag(nu_capture->epwm, nu_capture->u8Channel, EPWM_CAPTURE_INT_RISING_LATCH);
        EPWM_ClearCaptureIntFlag(nu_capture->epwm, nu_capture->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH);

        return -(RT_ERROR);
    }

    return RT_EOK;
}

#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x3<<EPWM_CH0CH1_POS))
void EPWM0P0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* Avoid excessive iteration by monitoring enabled channels */
#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x1<<EPWM_CH0CH1_POS))
    uint8_t const start = 0 + EPWM_CH0CH1_POS;
#else   /* Only channel 1 */
    uint8_t const start = 1 + EPWM_CH0CH1_POS;
#endif

#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x2<<EPWM_CH0CH1_POS))
    uint8_t const end = 2 + EPWM_CH0CH1_POS;
#else   /* Only channel 0 */
    uint8_t const end = 1 + EPWM_CH0CH1_POS;
#endif

    /* 2 channel using same irq */
    for (uint8_t i = start; i < end ; i++)
    {
        if (EPWM_GetCaptureIntFlag(nu_epwm0_capture[i].epwm, nu_epwm0_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_epwm0_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_epwm0_capture[i].parent, nu_epwm0_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x3<<EPWM_CH2CH3_POS))
void EPWM0P1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* Avoid excessive iteration by monitoring enabled channels */
#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x1<<EPWM_CH2CH3_POS))
    uint8_t const start = 0 + EPWM_CH2CH3_POS;
#else   /* Only channel 3 */
    uint8_t const start = 1 + EPWM_CH2CH3_POS;
#endif

#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x2<<EPWM_CH2CH3_POS))
    uint8_t const end = 2 + EPWM_CH2CH3_POS;
#else   /* Only channel 2 */
    uint8_t const end = 1 + EPWM_CH2CH3_POS;
#endif

    /* 2 channel using same irq */
    for (uint8_t i = start; i < end ; i++)
    {
        if (EPWM_GetCaptureIntFlag(nu_epwm0_capture[i].epwm, nu_epwm0_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_epwm0_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_epwm0_capture[i].parent, nu_epwm0_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x3<<EPWM_CH4CH5_POS))
void EPWM0P2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* Avoid excessive iteration by monitoring enabled channels */
#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x1<<EPWM_CH4CH5_POS))
    uint8_t const start = 0 + EPWM_CH4CH5_POS;
#else   /* Only channel 5 */
    uint8_t const start = 1 + EPWM_CH4CH5_POS;
#endif

#if (BSP_USING_EPWM0_CAPTURE_CHMSK&(0x2<<EPWM_CH4CH5_POS))
    uint8_t const end = 2 + EPWM_CH4CH5_POS;
#else   /* Only channel 4 */
    uint8_t const end = 1 + EPWM_CH4CH5_POS;
#endif

    /* 2 channel using same irq */
    for (uint8_t i = start; i < end ; i++)
    {
        if (EPWM_GetCaptureIntFlag(nu_epwm0_capture[i].epwm, nu_epwm0_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_epwm0_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_epwm0_capture[i].parent, nu_epwm0_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x3<<EPWM_CH0CH1_POS))
void EPWM1P0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* Avoid excessive iteration by monitoring enabled channels */
#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x1<<EPWM_CH0CH1_POS))
    uint8_t const start = 0 + EPWM_CH0CH1_POS;
#else   /* Only channel 1 */
    uint8_t const start = 1 + EPWM_CH0CH1_POS;
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x2<<EPWM_CH0CH1_POS))
    uint8_t const end = 2 + EPWM_CH0CH1_POS;
#else   /* Only channel 0 */
    uint8_t const end = 1 + EPWM_CH0CH1_POS;
#endif

    /* 2 channel using same irq */
    for (uint8_t i = start; i < end ; i++)
    {
        if (EPWM_GetCaptureIntFlag(nu_epwm1_capture[i].epwm, nu_epwm1_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_epwm1_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_epwm1_capture[i].parent, nu_epwm1_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x3<<EPWM_CH2CH3_POS))
void EPWM1P1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* Avoid excessive iteration by monitoring enabled channels */
#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x1<<EPWM_CH2CH3_POS))
    uint8_t const start = 0 + EPWM_CH2CH3_POS;
#else   /* Only channel 3 */
    uint8_t const start = 1 + EPWM_CH2CH3_POS;
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x2<<EPWM_CH2CH3_POS))
    uint8_t const end = 2 + EPWM_CH2CH3_POS;
#else   /* Only channel 2 */
    uint8_t const end = 1 + EPWM_CH2CH3_POS;
#endif

    /* 2 channel using same irq */
    for (uint8_t i = start; i < end ; i++)
    {
        if (EPWM_GetCaptureIntFlag(nu_epwm1_capture[i].epwm, nu_epwm1_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_epwm1_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_epwm1_capture[i].parent, nu_epwm1_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x3<<EPWM_CH4CH5_POS))
void EPWM1P2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter()

    /* Avoid excessive iteration by monitoring enabled channels */
#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x1<<EPWM_CH4CH5_POS))
    uint8_t const start = 0 + EPWM_CH4CH5_POS;
#else   /* Only channel 5 */
    uint8_t const start = 1 + EPWM_CH4CH5_POS;
#endif

#if (BSP_USING_EPWM1_CAPTURE_CHMSK&(0x2<<EPWM_CH4CH5_POS))
    uint8_t const end = 2 + EPWM_CH4CH5_POS;
#else   /* Only channel 4 */
    uint8_t const end = 1 + EPWM_CH4CH5_POS;
#endif

    /* 2 channel using same irq */
    for (uint8_t i = start; i < end ; i++)
    {
        if (EPWM_GetCaptureIntFlag(nu_epwm1_capture[i].epwm, nu_epwm1_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_epwm1_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_epwm1_capture[i].parent, nu_epwm1_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    nu_capture = (nu_capture_t *)inputcapture;

    if (nu_capture->u32CurrentFallingCnt)
    {
        *pulsewidth_us = nu_capture->u32CurrentFallingCnt;
        nu_capture->input_data_level = RT_FALSE;
        nu_capture->u32CurrentFallingCnt = 0;
    }
    else if (nu_capture->u32CurrentRisingCnt)
    {
        *pulsewidth_us = nu_capture->u32CurrentRisingCnt;
        nu_capture->input_data_level = RT_TRUE;
        nu_capture->u32CurrentRisingCnt = 0;
    }
    else
    {
        ret = RT_ERROR;
    }
    return -(ret);
}

static rt_err_t nu_epwm_init(nu_capture_t *nu_capture)
{
    rt_err_t ret = RT_ERROR;
    static rt_bool_t bEPWM0Inited = RT_FALSE;
    static rt_bool_t bEPWM1Inited = RT_FALSE;

    if (nu_capture->epwm == EPWM0)
    {
        if (bEPWM0Inited == RT_FALSE)
        {
            /* Enable EPWM0 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(EPWM0_MODULE);
            CLK_SetModuleClock(EPWM0_MODULE, CLK_CLKSEL2_EPWM0SEL_PLL, (uint32_t)NULL);
            SYS_LockReg();
            bEPWM0Inited = RT_TRUE;
        }
        ret = RT_EOK;
    }
    else if (nu_capture->epwm == EPWM1)
    {
        if (bEPWM1Inited == RT_FALSE)
        {
            /* Enable EPWM1 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(EPWM1_MODULE);
            CLK_SetModuleClock(EPWM1_MODULE, CLK_CLKSEL2_EPWM1SEL_PLL, (uint32_t)NULL);
            SYS_LockReg();
            bEPWM1Inited = RT_TRUE;
        }
        ret = RT_EOK;
    }

    return -(ret);
}

static rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    if (nu_epwm_init(nu_capture) != RT_EOK)
    {
        rt_kprintf("Failed to initialize EPWM%d.\n", nu_capture->epwm);
        ret = RT_ERROR;
    }

    return -(ret);
}

static rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Set capture time as 1000 nano second */
    EPWM_ConfigCaptureChannel(nu_capture->epwm, nu_capture->u8Channel, 1000, 0);

    /* Enable capture rising/falling edge interrupt */
    EPWM_EnableCaptureInt(nu_capture->epwm, nu_capture->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH | EPWM_CAPTURE_INT_RISING_LATCH);

    /* Enable EPWM NVIC interrupt */
    NVIC_EnableIRQ(nu_capture->irq);

    /* Enable Capture Function for EPWM */
    EPWM_EnableCapture(nu_capture->epwm, 0x1 << nu_capture->u8Channel);

    /* Enable rising/falling capture reload */
    nu_capture->epwm->CAPCTL |= (0x1 << (EPWM_CAPCTL_RCRLDEN0_Pos + nu_capture->u8Channel))
                                | (0x1 << (EPWM_CAPCTL_FCRLDEN0_Pos + nu_capture->u8Channel));

    /* Set counter type as down count */
    EPWM_SET_ALIGNED_TYPE(nu_capture->epwm, 0x1 << nu_capture->u8Channel, EPWM_UP_COUNTER);

    /* Enable EPWM Timer */
    EPWM_Start(nu_capture->epwm, 0x1 << nu_capture->u8Channel);

    return ret;
}

static rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;

    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Disable capture rising/falling edge interrupt */
    EPWM_DisableCaptureInt(nu_capture->epwm, nu_capture->u8Channel, EPWM_CAPTURE_INT_FALLING_LATCH | EPWM_CAPTURE_INT_RISING_LATCH);

    /* Disable EPWM NVIC interrupt */
    NVIC_DisableIRQ(nu_capture->irq);

    /* Enable EPWM Timer */
    EPWM_Stop(nu_capture->epwm, 0x1 << nu_capture->u8Channel);
    return ret;
}

/* Init and register epwm capture */
int nu_epwm_capture_device_init(void)
{
    /* Init EPWM0 6 channel and EPWM1 6 channel */
#if (BSP_USING_EPWM0_CAPTURE_CHMSK!=0)
    for (int i = 0; i < EPWM_CHANNEL_NUM; i++)
    {
        if (BSP_USING_EPWM0_CAPTURE_CHMSK & (0x1 << i))
        {
            nu_epwm0_capture[i].epwm = EPWM0;
            nu_epwm0_capture[i].u8Channel = i;
            nu_epwm0_capture[i].irq = nu_epwm0_irq[i / 2];
            nu_epwm0_capture[i].u32CurrentRisingCnt = 0;
            nu_epwm0_capture[i].u32CurrentFallingCnt = 0;
            nu_epwm0_capture[i].parent.ops = &nu_capture_ops;

            /* register inputcapture device */
            rt_device_inputcapture_register(&nu_epwm0_capture[i].parent, nu_epwm0_device_name[i], &nu_epwm0_capture[i]);

        }
    }
#endif //#if (BSP_USING_EPWM0_CAPTURE_CHMSK!=0) 
#if (BSP_USING_EPWM1_CAPTURE_CHMSK!=0)
    for (int i = 0; i < EPWM_CHANNEL_NUM; i++)
    {
        if (BSP_USING_EPWM1_CAPTURE_CHMSK & (0x1 << i))
        {
            nu_epwm1_capture[i].epwm = EPWM1;
            nu_epwm1_capture[i].u8Channel = i;
            nu_epwm1_capture[i].irq = nu_epwm1_irq[i / 2];
            nu_epwm1_capture[i].u32CurrentRisingCnt = 0;
            nu_epwm1_capture[i].u32CurrentFallingCnt = 0;
            nu_epwm1_capture[i].parent.ops = &nu_capture_ops;

            /* register inputcapture device */
            rt_device_inputcapture_register(&nu_epwm1_capture[i].parent, nu_epwm1_device_name[i], &nu_epwm1_capture[i]);
        }
    }
#endif //#if (BSP_USING_EPWM1_CAPTURE_CHMSK!=0) 
    return 0;

}
INIT_DEVICE_EXPORT(nu_epwm_capture_device_init);

#endif //#if defined(BSP_USING_EPWM_CAPTURE)
