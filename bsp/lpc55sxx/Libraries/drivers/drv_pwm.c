/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-28     tyustli      first version
 * 2019-07-15     Magicoe      The first version for LPC55S6x, we can also use SCT as PWM
 * 2023-02-28     Z8MAN8       Update docking to the RT-Thread device frame
 */

#include <rtthread.h>

#ifdef RT_USING_PWM
#if !defined(BSP_USING_CTIMER1_MAT0) && !defined(BSP_USING_CTIMER1_MAT1) && \
    !defined(BSP_USING_CTIMER1_MAT2)
#error "Please define at least one BSP_USING_CTIMERx_MATx"
#else
    #define BSP_USING_CTIMER1
#endif
#if !defined(BSP_USING_CTIMER2_MAT0) && !defined(BSP_USING_CTIMER2_MAT1) && \
    !defined(BSP_USING_CTIMER2_MAT2)
#error "Please define at least one BSP_USING_CTIMERx_MATx"
#else
    #define BSP_USING_CTIMER2
#endif

#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#include <rtdevice.h>
#include "fsl_ctimer.h"
#include "drv_pwm.h"

#define DEFAULT_DUTY                  50
#define DEFAULT_FREQ                  1000

enum
{
#ifdef BSP_USING_CTIMER1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_CTIMER2
    PWM2_INDEX,
#endif
};

struct lpc_pwm
{
    struct rt_device_pwm pwm_device;
    CTIMER_Type *    tim;
    uint32_t channel;
    char *name;
};

static struct lpc_pwm lpc_pwm_obj[] =
{
#if defined(BSP_USING_CTIMER1_MAT0) || defined(BSP_USING_CTIMER1_MAT1) || \
        defined(BSP_USING_CTIMER1_MAT2)
    {
       .tim                     = CTIMER1,
       .name                    = "pwm1",
       .channel                 = RT_NULL
    },
#endif

#if defined(BSP_USING_CTIMER2_MAT0) || defined(BSP_USING_CTIMER2_MAT1) || \
        defined(BSP_USING_CTIMER2_MAT2)
    {
       .tim                     = CTIMER2,
       .name                    = "pwm2",
       .channel                 = RT_NULL
    },
#endif
};

static void pwm_get_channel(void)
{
#ifdef BSP_USING_CTIMER1_MAT0
    lpc_pwm_obj[PWM1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_CTIMER1_MAT1
    lpc_pwm_obj[PWM1_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_CTIMER1_MAT2
    lpc_pwm_obj[PWM1_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_CTIMER2_MAT0
    lpc_pwm_obj[PWM2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_CTIMER2_MAT1
    lpc_pwm_obj[PWM2_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_CTIMER2_MAT2
    lpc_pwm_obj[PWM2_INDEX].channel |= 1 << 2;
#endif
}

static rt_err_t lpc_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops lpc_drv_ops =
{
    .control = lpc_drv_pwm_control
};

static rt_err_t lpc_drv_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    CTIMER_Type *base;

    base = (CTIMER_Type *)device->parent.user_data;

    if (!enable)
    {
        /* Stop the timer */
        CTIMER_StopTimer(base);
    }
    else
    {
        /* Start the timer */
        CTIMER_StartTimer(base);
    }

    return RT_EOK;
}

static rt_err_t lpc_drv_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    uint8_t get_duty;
    uint32_t get_frequence;
    uint32_t pwmClock = 0;
    CTIMER_Type *base;

    base = (CTIMER_Type *)device->parent.user_data;

    /* get frequence */
    if (base == CTIMER1)
    {
        pwmClock = CLOCK_GetCTimerClkFreq(1U) ;
    }
    else if(base == CTIMER2)
    {
        pwmClock = CLOCK_GetCTimerClkFreq(2U) ;
    }
    get_frequence = pwmClock / (base->MR[kCTIMER_Match_3] + 1);

    if(configuration->channel == 0)
    {
        /* get dutycycle */
        get_duty = (100*(base->MR[kCTIMER_Match_3] + 1 - base->MR[kCTIMER_Match_0]))/(base->MR[kCTIMER_Match_3] + 1);
    }
    else if(configuration->channel == 1)
    {
        /* get dutycycle */
        get_duty = (100*(base->MR[kCTIMER_Match_3] + 1 - base->MR[kCTIMER_Match_1]))/(base->MR[kCTIMER_Match_3] + 1);
    }
    else if(configuration->channel == 2)
    {
        /* get dutycycle */
        get_duty = (100*(base->MR[kCTIMER_Match_3] + 1 - base->MR[kCTIMER_Match_2]))/(base->MR[kCTIMER_Match_3] + 1);
    }

    /* get dutycycle */
    /* conversion */
    configuration->period = 1000000000 / get_frequence;
    configuration->pulse = get_duty * configuration->period / 100;

    rt_kprintf("*** PWM period %d, pulse %d\r\n", configuration->period, configuration->pulse);

    return RT_EOK;
}

static rt_err_t lpc_drv_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    RT_ASSERT(configuration->period > 0);
    RT_ASSERT(configuration->pulse <= configuration->period);

    ctimer_config_t config;
    CTIMER_Type *base;
    base = (CTIMER_Type *)device->parent.user_data;

    uint32_t pwmPeriod, pulsePeriod;
    /* Run as a timer */
    config.mode = kCTIMER_TimerMode;
    /* This field is ignored when mode is timer */
    config.input = kCTIMER_Capture_0;
    /* Timer counter is incremented on every APB bus clock */
    config.prescale = 0;

    /* Get the PWM period match value and pulse width match value of DEFAULT_FREQ PWM signal with DEFAULT_DUTY dutycycle */
    /* Calculate PWM period match value */
    double tmp = configuration->period;
    /* Target frequence. */
    tmp = 1000000000/tmp;
    if (base == CTIMER1)
    {
        pwmPeriod = (( CLOCK_GetCTimerClkFreq(1U) / (config.prescale + 1) ) / (uint32_t)tmp) - 1;
    }
    else if (base == CTIMER2)
    {
        pwmPeriod = (( CLOCK_GetCTimerClkFreq(2U) / (config.prescale + 1) ) / (uint32_t)tmp) - 1;
    }

    /* Calculate pulse width match value */
    tmp = configuration->pulse;
    pulsePeriod = (1.0 - tmp / configuration->period) * pwmPeriod;
    /* Match on channel 3 will define the PWM period */
    base->MR[kCTIMER_Match_3] = pwmPeriod;

    /* This will define the PWM pulse period */
    if(configuration->channel == 0)
    {
        base->MR[kCTIMER_Match_0] = pulsePeriod;
    }
    else if(configuration->channel == 1)
    {
        base->MR[kCTIMER_Match_1] = pulsePeriod;
    }
    else if(configuration->channel == 2)
    {
        base->MR[kCTIMER_Match_2] = pulsePeriod;
    }

    return RT_EOK;
}

static rt_err_t lpc_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return lpc_drv_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return lpc_drv_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return lpc_drv_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return lpc_drv_pwm_get(device, configuration);
    default:
        return -RT_EINVAL;
    }
}

static rt_err_t rt_hw_pwm_init(struct lpc_pwm *device)
{
    rt_err_t ret = RT_EOK;
    CTIMER_Type *tim = RT_NULL;
    uint32_t channel = RT_NULL;

    static struct rt_device_pwm pwm_device;
    ctimer_config_t config;
    uint32_t pwmPeriod, pulsePeriod;


    tim = device->tim;
    channel = device->channel;

    if(tim == CTIMER1)
    {
        /* Use 12 MHz clock for some of the Ctimers */
        CLOCK_AttachClk(kMAIN_CLK_to_CTIMER1);

        /* Run as a timer */
        config.mode = kCTIMER_TimerMode;
        /* This field is ignored when mode is timer */
        config.input = kCTIMER_Capture_0;
        /* Timer counter is incremented on every APB bus clock */
        config.prescale = 0;

        CTIMER_Init(CTIMER1, &config);
        /* Get the PWM period match value and pulse width match value of DEFAULT_FREQ PWM signal with DEFAULT_DUTY dutycycle */
        /* Calculate PWM period match value */
        pwmPeriod = (( CLOCK_GetCTimerClkFreq(1U) / (config.prescale + 1) ) / DEFAULT_FREQ) - 1;
    }
    else if (tim == CTIMER2)
    {
        /* Use 12 MHz clock for some of the Ctimers */
        CLOCK_AttachClk(kMAIN_CLK_to_CTIMER2);

        /* Run as a timer */
        config.mode = kCTIMER_TimerMode;
        /* This field is ignored when mode is timer */
        config.input = kCTIMER_Capture_0;
        /* Timer counter is incremented on every APB bus clock */
        config.prescale = 0;

        CTIMER_Init(CTIMER2, &config);
        /* Get the PWM period match value and pulse width match value of DEFAULT_FREQ PWM signal with DEFAULT_DUTY dutycycle */
        /* Calculate PWM period match value */
        pwmPeriod = (( CLOCK_GetCTimerClkFreq(2U) / (config.prescale + 1) ) / DEFAULT_FREQ) - 1;
    }

    /* Calculate pulse width match value */
    if (DEFAULT_DUTY == 0)
    {
        pulsePeriod = pwmPeriod + 1;
    }
    else
    {
        pulsePeriod = ((pwmPeriod + 1) * (100 - DEFAULT_DUTY)) / 100;
    }

    if (channel & 0x01)
    {
        CTIMER_SetupPwmPeriod(tim, kCTIMER_Match_3 , kCTIMER_Match_0, pwmPeriod, pulsePeriod, false);
        }
    if (channel & 0x02)
    {
        CTIMER_SetupPwmPeriod(tim, kCTIMER_Match_3 , kCTIMER_Match_1, pwmPeriod, pulsePeriod, false);
    }
    if (channel & 0x04)
    {
        CTIMER_SetupPwmPeriod(tim, kCTIMER_Match_3 , kCTIMER_Match_2, pwmPeriod, pulsePeriod, false);
    }
    return ret;
}

static int lpc_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    pwm_get_channel();

    for (i = 0; i < sizeof(lpc_pwm_obj) / sizeof(lpc_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (rt_hw_pwm_init(&lpc_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", lpc_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            LOG_D("%s init success", lpc_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&lpc_pwm_obj[i].pwm_device, lpc_pwm_obj[i].name, &lpc_drv_ops, lpc_pwm_obj[i].tim) == RT_EOK)
            {
                LOG_D("%s register success", lpc_pwm_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", lpc_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(lpc_pwm_init);
#endif /* RT_USING_PWM */
