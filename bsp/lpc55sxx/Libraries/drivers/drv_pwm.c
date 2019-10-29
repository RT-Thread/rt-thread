/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-28     tyustli      first version
 * 2019-07-15     Magicoe      The first version for LPC55S6x, we can also use SCT as PWM
 *
 */

#include <rtthread.h>

#ifdef RT_USING_PWM
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
    
#ifdef BSP_USING_CTIMER2
    /* get frequence */
    pwmClock = CLOCK_GetFreq(kCLOCK_CTimer2) ;
#endif
    
    get_frequence = pwmClock / (base->MR[kCTIMER_Match_3] + 1);

    if(configuration->channel == 1)
    {
        /* get dutycycle */
        get_duty = (100*(base->MR[kCTIMER_Match_3] + 1 - base->MR[kCTIMER_Match_1]))/(base->MR[kCTIMER_Match_3] + 1);
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
    
    if(configuration->channel == 1)
    {
        /* Get the PWM period match value and pulse width match value of DEFAULT_FREQ PWM signal with DEFAULT_DUTY dutycycle */
        /* Calculate PWM period match value */
        pwmPeriod = (( CLOCK_GetFreq(kCLOCK_CTimer2) / (config.prescale + 1) ) / DEFAULT_FREQ) - 1;

        /* Calculate pulse width match value */
        if (DEFAULT_DUTY == 0)
        {
            pulsePeriod = pwmPeriod + 1;
        }
        else
        {
            pulsePeriod = (pwmPeriod * (100 - DEFAULT_DUTY)) / 100;
        }
        /* Match on channel 3 will define the PWM period */
        base->MR[kCTIMER_Match_3] = pwmPeriod;
        /* This will define the PWM pulse period */
        base->MR[kCTIMER_Match_1] = pulsePeriod;

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
        return RT_EINVAL;
    }
}

int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_CTIMER2

    static struct rt_device_pwm pwm1_device;
    ctimer_config_t config;
    uint32_t pwmPeriod, pulsePeriod;
    
    /* Use 12 MHz clock for some of the Ctimers */
    CLOCK_AttachClk(kMAIN_CLK_to_CTIMER2);
    
    /* Run as a timer */
    config.mode = kCTIMER_TimerMode;
    /* This field is ignored when mode is timer */
    config.input = kCTIMER_Capture_0;
    /* Timer counter is incremented on every APB bus clock */
    config.prescale = 0;
    
    CTIMER_Init(CTIMER2, &config);

#ifdef BSP_USING_CTIMER2_MAT1
    /* Get the PWM period match value and pulse width match value of DEFAULT_FREQ PWM signal with DEFAULT_DUTY dutycycle */
    /* Calculate PWM period match value */
    pwmPeriod = (( CLOCK_GetFreq(kCLOCK_CTimer2) / (config.prescale + 1) ) / DEFAULT_FREQ) - 1;

    /* Calculate pulse width match value */
    if (DEFAULT_DUTY == 0)
    {
        pulsePeriod = pwmPeriod + 1;
    }
    else
    {
        pulsePeriod = (pwmPeriod * (100 - DEFAULT_DUTY)) / 100;
    }
    CTIMER_SetupPwmPeriod(CTIMER2, kCTIMER_Match_1 , pwmPeriod, pulsePeriod, false);
#endif

    ret = rt_device_pwm_register(&pwm1_device, "pwm1", &lpc_drv_ops, CTIMER2);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm1");
    }

#endif /* BSP_USING_CTIMER2 */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_pwm_init);


#ifdef RT_USING_FINSH
#include <finsh.h>

#ifdef FINSH_USING_MSH

rt_err_t rt_pwm_get(struct rt_device_pwm *device, int channel)
{
    rt_err_t result = RT_EOK;
    struct rt_pwm_configuration configuration = {0};

    if (!device)
    {
        return -RT_EIO;
    }

    configuration.channel = channel;
    result = rt_device_control(&device->parent, PWM_CMD_GET, &configuration);

    return result;
}

static int pwm_get(int argc, char **argv)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;

    if (argc != 3)
    {
        rt_kprintf("Usage: pwm_get pwm1 1\n");
        result = -RT_ERROR;
        goto _exit;
    }

    device = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }
    
    result = rt_pwm_get(device, atoi(argv[2]));

_exit:
    return result;
}
MSH_CMD_EXPORT(pwm_get, pwm_get pwm1 1);

#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */

#endif /* RT_USING_PWM */
