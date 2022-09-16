/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2022-3-15       Wayne            First version
*
* Note: 2 channels of a tpwm have the same output.
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_TPWM) && defined(RT_USING_PWM))

#define LOG_TAG                 "drv.tpwm"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define TPWM_CHANNEL_NUM        2
#include <rtdbg.h>

#include <rtdevice.h>
#include "NuMicro.h"

/* Private define ---------------------------------------------------------------*/
#define NU_TPWM_DEVICE(tpwm) (nu_tpwm_t)(tpwm)

enum
{
    TPWM_START = -1,
#if defined(BSP_USING_TPWM0)
    TPWM0_IDX,
#endif
#if defined(BSP_USING_TPWM1)
    TPWM1_IDX,
#endif
#if defined(BSP_USING_TPWM2)
    TPWM2_IDX,
#endif
#if defined(BSP_USING_TPWM3)
    TPWM3_IDX,
#endif
    TPWM_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_tpwm
{
    struct rt_device_pwm  tpwm_dev;
    char                 *name;
    TIMER_T              *base;
    uint32_t              rstidx;
    uint32_t              modid;
    rt_uint32_t           channel_mask; //TPWM_CH0 | TPWM_CH1
} ;

typedef struct nu_tpwm *nu_tpwm_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_tpwm_enable(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config, rt_bool_t enable);
static rt_err_t nu_tpwm_set(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config);
static rt_err_t nu_tpwm_get(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config);
static rt_err_t nu_tpwm_control(struct rt_device_pwm *tpwm_dev, int cmd, void *arg);

/* Private variables ------------------------------------------------------------*/
static struct nu_tpwm nu_tpwm_arr [] =
{
#if defined(BSP_USING_TPWM0)
    { .name = "tpwm0", .base  = TIMER0, .rstidx = TMR0_RST, .modid = TMR0_MODULE  },
#endif
#if defined(BSP_USING_TPWM1)
    { .name = "tpwm1", .base  = TIMER1, .rstidx = TMR1_RST, .modid = TMR1_MODULE  },
#endif
#if defined(BSP_USING_TPWM2)
    { .name = "tpwm2", .base  = TIMER2, .rstidx = TMR2_RST, .modid = TMR2_MODULE  },
#endif
#if defined(BSP_USING_TPWM3)
    { .name = "tpwm3", .base  = TIMER3, .rstidx = TMR3_RST, .modid = TMR3_MODULE  },
#endif
};

static struct rt_pwm_ops nu_tpwm_ops =
{
    nu_tpwm_control
};

/* Functions define ------------------------------------------------------------*/
static rt_err_t nu_tpwm_enable(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config, rt_bool_t enable)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t tpwm_channel = tpwm_config->channel;
    nu_tpwm_t psNuTPWM = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);

    if (enable == RT_TRUE)
    {
        if (psNuTPWM->channel_mask == 0)
        {
            TPWM_START_COUNTER(psNuTPWM->base);
        }
        psNuTPWM->channel_mask |= (1 << tpwm_channel);
        TPWM_ENABLE_OUTPUT(psNuTPWM->base, psNuTPWM->channel_mask);
    }
    else
    {
        psNuTPWM->channel_mask &= ~(1 << tpwm_channel);
        TPWM_ENABLE_OUTPUT(psNuTPWM->base, psNuTPWM->channel_mask);
        if (psNuTPWM->channel_mask == 0)
        {
            TPWM_STOP_COUNTER(psNuTPWM->base);
        }
    }

    return result;
}

static rt_err_t nu_tpwm_set(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config)
{
    if (tpwm_config->period <= 0)
        return -(RT_ERROR);

    rt_uint32_t tpwm_freq, tpwm_dutycycle ;
    rt_uint32_t tpwm_period = tpwm_config->period;
    rt_uint32_t tpwm_pulse = tpwm_config->pulse;
    nu_tpwm_t psNuTPWM = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);

    rt_uint32_t pre_tpwm_prescaler = TPWM_GET_PRESCALER(psNuTPWM->base);

    tpwm_freq = 1000000000 / tpwm_period;
    tpwm_dutycycle = (tpwm_pulse * 100) / tpwm_period;

    TPWM_ConfigOutputFreqAndDuty(psNuTPWM->base, tpwm_freq, tpwm_dutycycle) ;

    return RT_EOK;
}

static rt_err_t nu_tpwm_get(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config)
{
    rt_uint32_t tpwm_real_period, tpwm_real_duty, time_tick, u32TPWMClockFreq ;

    nu_tpwm_t psNuTPWM = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);
    rt_uint32_t tpwm_prescale = TPWM_GET_PRESCALER(psNuTPWM->base);
    rt_uint32_t tpwm_period = TPWM_GET_PERIOD(psNuTPWM->base);
    rt_uint32_t tpwm_pulse = TPWM_GET_CMPDAT(psNuTPWM->base);

    u32TPWMClockFreq = TIMER_GetModuleClock(psNuTPWM->base);
    time_tick = (uint64_t)1000000000000 / u32TPWMClockFreq;

    LOG_I("%s reg--> %d %d %d %d %d\n", psNuTPWM->name, tpwm_prescale, tpwm_period, tpwm_pulse, u32TPWMClockFreq, time_tick);

    tpwm_real_period = (((tpwm_prescale + 1) * (tpwm_period + 1)) * time_tick) / 1000;
    tpwm_real_duty = (((tpwm_prescale + 1) * tpwm_pulse * time_tick)) / 1000;
    tpwm_config->period = tpwm_real_period;
    tpwm_config->pulse = tpwm_real_duty;

    LOG_I("%s %d %d %d\n", psNuTPWM->name, tpwm_config->channel, tpwm_config->period, tpwm_config->pulse);

    return RT_EOK;
}

static rt_err_t nu_tpwm_control(struct rt_device_pwm *tpwm_dev, int cmd, void *arg)
{
    struct rt_pwm_configuration *tpwm_config = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(tpwm_dev != RT_NULL);
    RT_ASSERT(tpwm_config != RT_NULL);

    nu_tpwm_t psNuTPWM = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);
    RT_ASSERT(psNuTPWM != RT_NULL);
    RT_ASSERT(psNuTPWM->base != RT_NULL);

    if ((tpwm_config->channel + 1) > TPWM_CHANNEL_NUM)
        return -(RT_ERROR);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return nu_tpwm_enable(tpwm_dev, tpwm_config, RT_TRUE);
    case PWM_CMD_DISABLE:
        return nu_tpwm_enable(tpwm_dev, tpwm_config, RT_FALSE);
    case PWM_CMD_SET:
        return nu_tpwm_set(tpwm_dev, tpwm_config);
    case PWM_CMD_GET:
        return nu_tpwm_get(tpwm_dev, tpwm_config);
    default:
        break;
    }
    return -(RT_EINVAL);
}

int rt_hw_tpwm_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    for (i = (TPWM_START + 1); i < TPWM_CNT; i++)
    {
        nu_tpwm_arr[i].channel_mask = 0;

        CLK_EnableModuleClock(nu_tpwm_arr[i].modid);

        SYS_ResetModule(nu_tpwm_arr[i].rstidx);

        TPWM_ENABLE_PWM_MODE(nu_tpwm_arr[i].base);

        /* Register RT PWM device. */
        ret = rt_device_pwm_register(&nu_tpwm_arr[i].tpwm_dev, nu_tpwm_arr[i].name, &nu_tpwm_ops, &nu_tpwm_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }
    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_tpwm_init);

#endif //#if (defined(BSP_USING_TPWM) && defined(RT_USING_PWM))
