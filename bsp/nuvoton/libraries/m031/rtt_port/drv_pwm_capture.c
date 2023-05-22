/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-02-17      klcheng          First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_PWM_CAPTURE)
#if ((BSP_USING_PWM0_CAPTURE_CHMSK+BSP_USING_PWM1_CAPTURE_CHMSK)!=0)
#include <rtdevice.h>
#include "NuMicro.h"


/* Private typedef --------------------------------------------------------------*/
typedef struct nu_capture
{
    struct rt_inputcapture_device   parent;
    PWM_T      *pwm;
    uint8_t     u8Channel;
    IRQn_Type   irq;
    uint32_t    u32CurrentRisingCnt;
    uint32_t    u32CurrentFallingCnt;
    uint32_t    u32LastRisingCnt;
    uint32_t    u32LastFallingCnt;
    rt_bool_t   input_data_level;
    rt_bool_t   pwm_init;
    struct      nu_capture *pair;
} nu_capture_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
#if (BSP_USING_PWM0_CAPTURE_CHMSK!=0)
static const char *nu_pwm0_device_name[PWM_CHANNEL_NUM] = {"pwm0i0", "pwm0i1", "pwm0i2", "pwm0i3", "pwm0i4", "pwm0i5"};
static nu_capture_t nu_pwm0_capture[PWM_CHANNEL_NUM] = {0};
#endif

#if (BSP_USING_PWM1_CAPTURE_CHMSK!=0)
static const char *nu_pwm1_device_name[PWM_CHANNEL_NUM] = {"pwm1i0", "pwm1i1", "pwm1i2", "pwm1i3", "pwm1i4", "pwm1i5"};
static nu_capture_t nu_pwm1_capture[PWM_CHANNEL_NUM] = {0};
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
    /* Read the capture counter value if falling/rising edge */
    if (PWM_GetCaptureIntFlag(nu_capture->pwm, nu_capture->u8Channel) == 1)//Rising edge
    {
        PWM_ClearCaptureIntFlag(nu_capture->pwm, nu_capture->u8Channel, PWM_CAPTURE_INT_RISING_LATCH);
        nu_capture->u32CurrentRisingCnt = PWM_GET_CAPTURE_RISING_DATA(nu_capture->pwm, nu_capture->u8Channel);
    }
    else if (PWM_GetCaptureIntFlag(nu_capture->pwm, nu_capture->u8Channel) == 2)//Falling edge
    {
        PWM_ClearCaptureIntFlag(nu_capture->pwm, nu_capture->u8Channel, PWM_CAPTURE_INT_FALLING_LATCH);
        nu_capture->u32CurrentFallingCnt += PWM_GET_CAPTURE_FALLING_DATA(nu_capture->pwm, nu_capture->u8Channel);
    }
    else
    {
        PWM_ClearCaptureIntFlag(nu_capture->pwm, nu_capture->u8Channel, PWM_CAPTURE_INT_RISING_LATCH);
        PWM_ClearCaptureIntFlag(nu_capture->pwm, nu_capture->u8Channel, PWM_CAPTURE_INT_FALLING_LATCH);

        return -(RT_ERROR);
    }

    return RT_EOK;
}

#if (BSP_USING_PWM0_CAPTURE_CHMSK!=0)
void PWM0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    for (uint8_t i = 0; i < PWM_CHANNEL_NUM ; i++)
    {
        if (PWM_GetCaptureIntFlag(nu_pwm0_capture[i].pwm, nu_pwm0_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_pwm0_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_pwm0_capture[i].parent, nu_pwm0_capture[i].input_data_level);
            }
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


#if (BSP_USING_PWM1_CAPTURE_CHMSK!=0)
void PWM1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    for (uint8_t i = 0; i < PWM_CHANNEL_NUM ; i++)
    {
        if (PWM_GetCaptureIntFlag(nu_pwm1_capture[i].pwm, nu_pwm1_capture[i].u8Channel) != 0)
        {
            /* Calculate pulse width */
            if (CalPulseWidth(&nu_pwm1_capture[i]) == RT_EOK)
            {
                rt_hw_inputcapture_isr(&nu_pwm1_capture[i].parent, nu_pwm1_capture[i].input_data_level);
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
        if (nu_capture->u32CurrentFallingCnt > nu_capture->u32LastRisingCnt)
            *pulsewidth_us = nu_capture->u32CurrentFallingCnt - nu_capture->u32LastRisingCnt;
        else    /* Overrun case */
            *pulsewidth_us = nu_capture->u32CurrentFallingCnt + (0x10000 - nu_capture->u32LastRisingCnt);

        nu_capture->input_data_level = RT_FALSE;
        nu_capture->u32LastFallingCnt = nu_capture->u32CurrentFallingCnt;
        nu_capture->u32CurrentFallingCnt = 0;
    }
    else if (nu_capture->u32CurrentRisingCnt)
    {
        if (nu_capture->u32CurrentRisingCnt > nu_capture->u32LastFallingCnt)
            *pulsewidth_us = nu_capture->u32CurrentRisingCnt - nu_capture->u32LastFallingCnt;
        else    /* Overrun case */
            *pulsewidth_us = nu_capture->u32CurrentRisingCnt + (0x10000 - nu_capture->u32LastFallingCnt);

        nu_capture->input_data_level = RT_TRUE;
        nu_capture->u32LastRisingCnt = nu_capture->u32CurrentRisingCnt;
        nu_capture->u32CurrentRisingCnt = 0;
    }
    else
    {
        ret = -RT_ERROR;
    }
    return -(ret);
}

static rt_err_t nu_pwm_init(nu_capture_t *nu_capture)
{
    rt_err_t ret = -RT_ERROR;
    static rt_bool_t bPWM0Inited = RT_FALSE;
    static rt_bool_t bPWM1Inited = RT_FALSE;

    if (nu_capture->pwm == PWM0)
    {
        if (bPWM0Inited == RT_FALSE)
        {
            /* Enable PWM0 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(PWM0_MODULE);
            CLK_SetModuleClock(PWM0_MODULE, CLK_CLKSEL2_PWM0SEL_PCLK0, 0);
            SYS_LockReg();
            bPWM0Inited = RT_TRUE;
        }
        ret = RT_EOK;
    }
    else if (nu_capture->pwm == PWM1)
    {
        if (bPWM1Inited == RT_FALSE)
        {
            /* Enable PWM1 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(PWM1_MODULE);
            CLK_SetModuleClock(PWM1_MODULE, CLK_CLKSEL2_PWM1SEL_PCLK1, 0);
            SYS_LockReg();
            bPWM1Inited = RT_TRUE;
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

    if (nu_pwm_init(nu_capture) != RT_EOK)
    {
        rt_kprintf("Failed to initialize PWM%d.\n", nu_capture->pwm);
        ret = -RT_ERROR;
    }

    return -(ret);
}

static rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Enable capture rising/falling edge interrupt */
    PWM_EnableCaptureInt(nu_capture->pwm, nu_capture->u8Channel, PWM_CAPTURE_INT_FALLING_LATCH | PWM_CAPTURE_INT_RISING_LATCH);

    /* Enable PWM NVIC interrupt */
    NVIC_EnableIRQ(nu_capture->irq);

    /* Enable Capture Function for PWM */
    PWM_EnableCapture(nu_capture->pwm, 0x1 << nu_capture->u8Channel);

    if ((nu_capture->pwm_init == RT_FALSE) && (nu_capture->pair->pwm_init == RT_FALSE))
    {
        nu_capture->pwm_init = RT_TRUE;

        /* Set capture time as 1000 nanosecond */
        PWM_ConfigCaptureChannel(nu_capture->pwm, nu_capture->u8Channel, 1000, 0);

        /* Set counter type as down count */
        PWM_SET_ALIGNED_TYPE(nu_capture->pwm, 0x1 << nu_capture->u8Channel, PWM_UP_COUNTER);

        /* Enable PWM Timer */
        PWM_Start(nu_capture->pwm, 0x1 << nu_capture->u8Channel);
    }

    return ret;
}

static rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;

    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Disable capture rising/falling edge interrupt */
    PWM_DisableCaptureInt(nu_capture->pwm, nu_capture->u8Channel, PWM_CAPTURE_INT_FALLING_LATCH | PWM_CAPTURE_INT_RISING_LATCH);

    /* Disable PWM NVIC interrupt */
    NVIC_DisableIRQ(nu_capture->irq);

    /* Enable PWM Timer */
    PWM_Stop(nu_capture->pwm, 0x1 << nu_capture->u8Channel);

    nu_capture->pwm_init = RT_FALSE;

    return ret;
}

/* Init and register pwm capture */
int nu_pwm_capture_device_init(void)
{
    /* Init PWM0 6 channel and PWM1 6 channel */
#if (BSP_USING_PWM0_CAPTURE_CHMSK!=0)
    for (int i = 0; i < PWM_CHANNEL_NUM; i++)
    {
        if (BSP_USING_PWM0_CAPTURE_CHMSK & (0x1 << i))
        {
            nu_pwm0_capture[i].pwm = PWM0;
            nu_pwm0_capture[i].u8Channel = i;
            nu_pwm0_capture[i].irq = PWM0_IRQn;
            nu_pwm0_capture[i].u32CurrentRisingCnt = 0;
            nu_pwm0_capture[i].u32CurrentFallingCnt = 0;
            nu_pwm0_capture[i].parent.ops = &nu_capture_ops;
            nu_pwm0_capture[i].pair = &nu_pwm0_capture[((i>>1) << 1) == i? i+1 : i-1];
            nu_pwm0_capture[i].pwm_init = RT_FALSE;

            /* register inputcapture device */
            rt_device_inputcapture_register(&nu_pwm0_capture[i].parent, nu_pwm0_device_name[i], &nu_pwm0_capture[i]);

        }
    }
#endif //#if (BSP_USING_PWM0_CAPTURE_CHMSK!=0)
#if (BSP_USING_PWM1_CAPTURE_CHMSK!=0)
    for (int i = 0; i < PWM_CHANNEL_NUM; i++)
    {
        if (BSP_USING_PWM1_CAPTURE_CHMSK & (0x1 << i))
        {
            nu_pwm1_capture[i].pwm = PWM1;
            nu_pwm1_capture[i].u8Channel = i;
            nu_pwm1_capture[i].irq = PWM1_IRQn;
            nu_pwm1_capture[i].u32CurrentRisingCnt = 0;
            nu_pwm1_capture[i].u32CurrentFallingCnt = 0;
            nu_pwm1_capture[i].parent.ops = &nu_capture_ops;
            nu_pwm1_capture[i].pair = &nu_pwm1_capture[((i>>1) << 1) == i? i+1 : i-1];
            nu_pwm1_capture[i].pwm_init = RT_FALSE;

            /* register inputcapture device */
            rt_device_inputcapture_register(&nu_pwm1_capture[i].parent, nu_pwm1_device_name[i], &nu_pwm1_capture[i]);
        }
    }
#endif //#if (BSP_USING_PWM1_CAPTURE_CHMSK!=0)
    return 0;

}
INIT_DEVICE_EXPORT(nu_pwm_capture_device_init);
#endif  //#if ((BSP_USING_PWM0_CAPTURE_CHMSK+BSP_USING_PWM1_CAPTURE_CHMSK)!=0)
#endif //#if defined(BSP_USING_PWM_CAPTURE)
