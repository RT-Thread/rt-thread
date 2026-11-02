/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-26     Yilin Sun    Initial version.
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "fsl_ctimer.h"

#define MCX_PWM_MATCH_COUNT 4

#ifdef RT_USING_PWM

typedef struct
{
    struct rt_device_pwm pwm_device;
    CTIMER_Type *ct_instance;
    uint32_t counter_period_ps;
} mcx_pwm_obj_t;

static CTIMER_Type *mcx_pwm_instances[] = CTIMER_BASE_PTRS;

static mcx_pwm_obj_t mcx_pwm_list[ARRAY_SIZE(mcx_pwm_instances)];

static int mcx_pwm_current_period_channel(mcx_pwm_obj_t *pwm)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    uint32_t mcr = ct->MCR;

    for (uint8_t i = 0; i < 4; i++)
    {
        if (mcr & (1U << (3 * i + CTIMER_MCR_MR0R_SHIFT)))
        {
            return i;
        }
    }

    return -1;
}

static int mcx_pwm_first_free_channel(mcx_pwm_obj_t *pwm)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    int pc = mcx_pwm_current_period_channel(pwm);

    uint32_t pwmc = ct->PWMC;

    for (uint8_t i = 0; i < 4; i++)
    {
        if (pwmc & (1U << i))
        {
            /* Skip this channel if there's an active PWM output */
            continue;
        }

        if (i == pc)
        {
            /* Skip this channel if this channel is the current period channel */
            continue;
        }

        return i;
    }

    /* There are no free channels left. */
    return -1;
}

static int mcx_pwm_period_set(mcx_pwm_obj_t *pwm, uint32_t period_ns)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    int p_channel = mcx_pwm_current_period_channel(pwm);
    if (p_channel < 0)
    {
        return -EINVAL;
    }

    /* Store new values in shadow registers */
    ct->MSR[p_channel] = period_ns * 1000 / pwm->counter_period_ps;

    /* Enable period channel interrupt to check a reload event occurs.
     * Since interrupts are not configured from NVIC, so no ISR will occur.
     * Check IR[MRnINT] for reload point.
     */
    uint32_t mcr_mask = (CTIMER_MCR_MR0RL_MASK << p_channel) | (CTIMER_MCR_MR0I_MASK << (3 * p_channel));

    for (uint8_t i = 0; i < 4; i++)
    {
        if (ct->PWMC & (1U << i))
        {
            /* Channel PWM output is enabled, calculate new values and store into shadow registers */
            uint32_t new_mr = ct->MR[i] * ct->MSR[p_channel] / ct->MR[p_channel];
            ct->MSR[i] = new_mr;

            /* Update MRnRL map */
            mcr_mask |= CTIMER_MCR_MR0RL_MASK << i;
        }
    }

    /* Reload MRs on next counter reset, enable reload MR interrupt */
    ct->MCR |= mcr_mask;

    while ((ct->IR & (CTIMER_IR_MR0INT_MASK << p_channel)) == 0U)
    {
        /* -- */
    }

    /* Disable reload channel interrupt and MSR synchronization */
    ct->MCR &= ~mcr_mask;

    /* Clear interrupt flags. */
    ct->IR |= (CTIMER_IR_MR0INT_MASK << p_channel);

    return 0;
}

static int mcx_pwm_period_get(mcx_pwm_obj_t *pwm, uint32_t *period_ns)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    int p_channel = mcx_pwm_current_period_channel(pwm);
    if (p_channel < 0)
    {
        return -1;
    }

    *period_ns = ct->MR[p_channel] * pwm->counter_period_ps / 1000;

    return 0;
}

static int mcx_pwm_pulse_set(mcx_pwm_obj_t *pwm, uint8_t channel, uint32_t pulse_ns)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    int p_channel = mcx_pwm_current_period_channel(pwm);
    if (p_channel < 0)
    {
        return -1;
    }

    /* Up-counting counters, the polarity is inversed */
    ct->MSR[channel] = ct->MR[p_channel] - pulse_ns * 1000 / pwm->counter_period_ps;

    /* Reload MRn on the next cycle */
    ct->MCR |= (CTIMER_MCR_MR0RL_MASK << channel);

    /* Wait for new duty cycle loaded into the MRn */
    while (ct->MR[channel] != ct->MSR[channel])
    {
        /* -- */
    }

    /* Disable shadow register updates */
    ct->MCR &= ~(CTIMER_MCR_MR0RL_MASK << channel);

    return 0;
}

static int mcx_pwm_pulse_get(mcx_pwm_obj_t *pwm, uint8_t channel, uint32_t *pulse_ns)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    int p_channel = mcx_pwm_current_period_channel(pwm);
    if (p_channel < 0)
    {
        return -1;
    }

    /* Up-counting counters, the polarity is inversed */
    *pulse_ns = (ct->MR[p_channel] - ct->MR[channel]) * pwm->counter_period_ps / 1000;

    return 0;
}

static rt_err_t mcx_drv_pwm_get(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    if (mcx_pwm_period_get(pwm, &configuration->period) < 0)
    {
        return -RT_EFAULT;
    }

    if (mcx_pwm_pulse_get(pwm, configuration->channel, &configuration->pulse) < 0)
    {
        return -RT_EFAULT;
    }

    return RT_EOK;
}

static rt_err_t mcx_drv_pwm_set(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    CTIMER_Type *ct = pwm->ct_instance;

    uint32_t period = configuration->period * 1000 / pwm->counter_period_ps;
    uint8_t channel = configuration->channel;

    if ((ct->TCR & CTIMER_TCR_CEN_MASK) == 0U)
    {
        /* There's two conditions for a all-zero TCR: either a reset condition or timer is stopped. */
        /* In either case, we need to initialize the timer instance (AHB RST CTRL). */

        /* TODO: Do not use SDK functions */

        ctimer_config_t ct_cfg =
        {
            .mode = kCTIMER_TimerMode,
            .prescale = 1U,
        };

        /* Frequency: 150MHz max., we got 32bit counters, we can take that. */
        /* Approx. maximum period: 28.6 seconds. */

        CTIMER_Init(ct, &ct_cfg);

        /* Current timer is not running, we are the first channel being configured. */

        ct->TC = 0U;   /* Reset counter */
        ct->PC = 0U;   /* Reset prescaler counter */
        ct->PR = 0U;   /* Prescaler, divide by 1 to get best resolution */
        ct->MCR = 0U;  /* Reset interrupt and reset condition */
        ct->EMR = 0U;  /* Do nothing on match event and output 0 as default state */
        ct->PWMC = 0U; /* Disable all PWM channels, outputs will be controlled by EMn */

        /* Here, we have a favoritism of using channel 3 as period channel, unless channel 3 is used for output */
        if (channel != 3)
        {
            ct->MR[3] = period;
            ct->MCR |= CTIMER_MCR_MR3R_MASK;
        }
        else
        {
            /* Use channel 2 as period channel. */
            ct->MR[2] = period;
            ct->MCR |= CTIMER_MCR_MR2R_MASK;
        }

        /* Start counter */
        ct->TCR |= CTIMER_TCR_CEN_MASK;
    }
    else
    {
        /*
         * Due to the nature of the CTimer, one of the 4 match channels is needed for period control (frequency)
         * To find out which one is the current period channel, check the MRxR bit for each match output.
         * If we are configuring the same match being used as periodic channel, configure the next free match as period
         * then current channel can be re-used. If all 4 channels are in use then the function will fail with an errno.
         */

        /* The timer is running, check whether we need to re-locate the period channel */
        int p_channel = mcx_pwm_current_period_channel(pwm);
        if (p_channel < 0)
        {
            return -RT_EINVAL;
        }

        if (p_channel == channel)
        {
            /* We need to re-locate the period channel */

            int f_channel = mcx_pwm_first_free_channel(pwm);
            if (f_channel < 0)
            {
                /* There's no free channel, bail out. */
                return -RT_EBUSY;
            }

            /* Transfer the period channel to first free channel */

            /* Step 1: Copy current period to first free channel */
            ct->MR[f_channel] = ct->MR[p_channel];

            /* Step 2: Enable reset for new period channel */
            /* Note: it's safe doing it here since both old and new channel MRs contains same value */
            ct->MCR |= (CTIMER_MCR_MR0R_MASK << (3 * f_channel));

            /* Step 3: Disable reset for old period channel */
            ct->MCR &= ~(CTIMER_MCR_MR0R_MASK << (3 * p_channel));

            /* The old period channel is now available for PWM output */
            p_channel = f_channel;
        }

        if (mcx_pwm_period_set(pwm, configuration->period) < 0)
        {
            return -RT_EINVAL;
        }
    }

    if (mcx_pwm_pulse_set(pwm, channel, configuration->pulse) < 0)
    {
        return -RT_EINVAL;
    }

    return 0;
}

static rt_err_t mcx_drv_pwm_enable(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    ct->PWMC |= (1U << configuration->channel);

    return 0;
}

static rt_err_t mcx_drv_pwm_disable(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    CTIMER_Type *ct = (CTIMER_Type *)pwm->ct_instance;

    ct->PWMC &= ~(1U << configuration->channel);

    return 0;
}

static rt_err_t mcx_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *args)
{
    mcx_pwm_obj_t *pwm = device->parent.user_data;
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)args;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return mcx_drv_pwm_enable(pwm, configuration);

    case PWM_CMD_DISABLE:
        return mcx_drv_pwm_disable(pwm, configuration);

    case PWM_CMD_SET:
        return mcx_drv_pwm_set(pwm, configuration);

    case PWM_CMD_GET:
        return mcx_drv_pwm_get(pwm, configuration);

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_pwm_ops mcx_pwm_ops =
{
    .control = mcx_drv_pwm_control,
};

int mcx_pwm_init(void)
{
    rt_err_t ret;
    char name_buf[8];

    for (uint8_t i = 0; i < ARRAY_SIZE(mcx_pwm_instances); i++)
    {
        mcx_pwm_list[i].ct_instance = mcx_pwm_instances[i];
        mcx_pwm_list[i].counter_period_ps = 1000000000000ULL / CLOCK_GetCTimerClkFreq(i);

        rt_snprintf(name_buf, sizeof(name_buf), "pwm%d", i);

        ret = rt_device_pwm_register(&mcx_pwm_list[i].pwm_device, name_buf, &mcx_pwm_ops, &mcx_pwm_list[i]);
        if (ret != RT_EOK)
        {
            return ret;
        }
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(mcx_pwm_init);

#endif /* RT_USING_PWM */
