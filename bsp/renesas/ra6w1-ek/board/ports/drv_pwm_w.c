#include <rtthread.h>
#include <rtdevice.h>

#define LOG_TAG "drv.pwm_w"
#include <rtdbg.h>

#include "drv_config.h"
#include "hal_data.h"

#if defined(BSP_USING_PWM) && \
    (defined(BSP_USING_PWM0) || defined(BSP_USING_PWM1) || \
     defined(BSP_USING_PWM2) || defined(BSP_USING_PWM3) || \
     defined(BSP_USING_PWM4) || defined(BSP_USING_PWM5) || \
     defined(BSP_USING_PWM6) || defined(BSP_USING_PWM7))

#define RA_PWM_W_MAX_COUNT       (TIM_W_PWM_MAX + 1U)
#define RA_PWM_W_CLOCK_HZ(pwm)   (BSP_CFG_XTALM_HZ / ((rt_uint32_t) (pwm)->g_cfg->source_div + 1U))

enum
{
#ifdef BSP_USING_PWM0
    BSP_PWM0_INDEX,
#endif
#ifdef BSP_USING_PWM1
    BSP_PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    BSP_PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    BSP_PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    BSP_PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    BSP_PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM6
    BSP_PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    BSP_PWM7_INDEX,
#endif
    RA_PWM_W_COUNT
};

struct ra_pwm_w
{
    struct rt_device_pwm       pwm_device;
    tim_w_instance_ctrl_t     *g_ctrl;
    const timer_cfg_t         *g_cfg;
    const char                *name;
};

static struct ra_pwm_w ra_pwm_w_obj[RA_PWM_W_COUNT] =
{
#ifdef BSP_USING_PWM0
    [BSP_PWM0_INDEX] = { .name = "pwm0", .g_cfg = &g_timer0_cfg, .g_ctrl = &g_timer0_ctrl },
#endif
#ifdef BSP_USING_PWM1
    [BSP_PWM1_INDEX] = { .name = "pwm1", .g_cfg = &g_timer1_cfg, .g_ctrl = &g_timer1_ctrl },
#endif
#ifdef BSP_USING_PWM2
    [BSP_PWM2_INDEX] = { .name = "pwm2", .g_cfg = &g_timer2_cfg, .g_ctrl = &g_timer2_ctrl },
#endif
#ifdef BSP_USING_PWM3
    [BSP_PWM3_INDEX] = { .name = "pwm3", .g_cfg = &g_timer3_cfg, .g_ctrl = &g_timer3_ctrl },
#endif
#ifdef BSP_USING_PWM4
    [BSP_PWM4_INDEX] = { .name = "pwm4", .g_cfg = &g_timer4_cfg, .g_ctrl = &g_timer4_ctrl },
#endif
#ifdef BSP_USING_PWM5
    [BSP_PWM5_INDEX] = { .name = "pwm5", .g_cfg = &g_timer5_cfg, .g_ctrl = &g_timer5_ctrl },
#endif
#ifdef BSP_USING_PWM6
    [BSP_PWM6_INDEX] = { .name = "pwm6", .g_cfg = &g_timer6_cfg, .g_ctrl = &g_timer6_ctrl },
#endif
#ifdef BSP_USING_PWM7
    [BSP_PWM7_INDEX] = { .name = "pwm7", .g_cfg = &g_timer7_cfg, .g_ctrl = &g_timer7_ctrl },
#endif
};

static rt_uint32_t ra_pwm_w_ns_to_cycles(const struct ra_pwm_w *pwm,
                                         rt_uint32_t nanoseconds)
{
    rt_uint64_t cycles;
    rt_uint32_t clock_hz = RA_PWM_W_CLOCK_HZ(pwm);

    if (nanoseconds == 0U)
    {
        return 0U;
    }

    cycles = ((rt_uint64_t) nanoseconds * clock_hz + 999999999ULL) / 1000000000ULL;
    if (cycles == 0U)
    {
        cycles = 1U;
    }
    if (cycles > RA_PWM_W_MAX_COUNT)
    {
        cycles = RA_PWM_W_MAX_COUNT;
    }

    return (rt_uint32_t) cycles;
}

static rt_uint32_t ra_pwm_w_cycles_to_ns(const struct ra_pwm_w *pwm,
                                         rt_uint32_t cycles)
{
    return (rt_uint32_t) (((rt_uint64_t) cycles * 1000000000ULL) /
                          RA_PWM_W_CLOCK_HZ(pwm));
}

static rt_err_t ra_pwm_w_set(struct ra_pwm_w *pwm,
                             struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period_cycles;
    rt_uint32_t pulse_cycles;

    if (configuration->period == 0U)
    {
        return -RT_EINVAL;
    }

    period_cycles = ra_pwm_w_ns_to_cycles(pwm, configuration->period);
    pulse_cycles = ra_pwm_w_ns_to_cycles(pwm, configuration->pulse);
    if (pulse_cycles > period_cycles)
    {
        pulse_cycles = period_cycles;
    }

    /* TIM_W stores period as cycles - 1 and duty as the number of high cycles. */
    if (R_TIM_W_PeriodSet(pwm->g_ctrl, period_cycles - 1U) != FSP_SUCCESS)
    {
        return -RT_ERROR;
    }

    if (pulse_cycles > TIM_W_PWM_MAX)
    {
        pulse_cycles = TIM_W_PWM_MAX;
    }
    pwm->g_ctrl->p_reg->TIMER_PWM_CTRL_REG_b.TIM_PWM_DC = (uint16_t) pulse_cycles;

    configuration->channel = 0;
    configuration->period = ra_pwm_w_cycles_to_ns(pwm, period_cycles);
    configuration->pulse = ra_pwm_w_cycles_to_ns(pwm, pulse_cycles);
    return RT_EOK;
}

static rt_err_t ra_pwm_w_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct ra_pwm_w *pwm = (struct ra_pwm_w *) device->parent.user_data;
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *) arg;
    rt_uint32_t period_cycles;
    rt_uint32_t pulse_cycles;

    if ((pwm == RT_NULL) || (configuration == RT_NULL) || (configuration->channel != 0U))
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return (R_TIM_W_Start(pwm->g_ctrl) == FSP_SUCCESS) ? RT_EOK : -RT_ERROR;

    case PWM_CMD_DISABLE:
        return (R_TIM_W_Stop(pwm->g_ctrl) == FSP_SUCCESS) ? RT_EOK : -RT_ERROR;

    case PWM_CMD_SET:
        return ra_pwm_w_set(pwm, configuration);

    case PWM_CMD_GET:
        period_cycles = (rt_uint32_t) pwm->g_ctrl->p_reg->TIMER_PWM_CTRL_REG_b.TIM_PWM_FREQ + 1U;
        pulse_cycles = (rt_uint32_t) pwm->g_ctrl->p_reg->TIMER_PWM_CTRL_REG_b.TIM_PWM_DC;
        configuration->channel = 0;
        configuration->period = ra_pwm_w_cycles_to_ns(pwm, period_cycles);
        configuration->pulse = ra_pwm_w_cycles_to_ns(pwm, pulse_cycles);
        return RT_EOK;

    default:
        return -RT_EINVAL;
    }
}

static const struct rt_pwm_ops ra_pwm_w_ops =
{
    .control = ra_pwm_w_control,
};

static int rt_hw_pwm_w_init(void)
{
    int result = RT_EOK;

    for (rt_size_t i = 0; i < RA_PWM_W_COUNT; i++)
    {
        if (R_TIM_W_Open(ra_pwm_w_obj[i].g_ctrl, ra_pwm_w_obj[i].g_cfg) != FSP_SUCCESS)
        {
            LOG_E("%s open failed", ra_pwm_w_obj[i].name);
            result = -RT_ERROR;
            continue;
        }

        if (rt_device_pwm_register(&ra_pwm_w_obj[i].pwm_device,
                                   ra_pwm_w_obj[i].name,
                                   &ra_pwm_w_ops,
                                   &ra_pwm_w_obj[i]) != RT_EOK)
        {
            LOG_E("%s register failed", ra_pwm_w_obj[i].name);
            (void) R_TIM_W_Close(ra_pwm_w_obj[i].g_ctrl);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_pwm_w_init);

#endif /* BSP_USING_PWM */
