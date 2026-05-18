/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-01-27     CYFS              first version
 */

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

#ifdef RT_USING_PWM

#define DBG_TAG             "drv.pwm"
#define DBG_LVL             DBG_LOG

#include <rtdbg.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE  2


typedef struct gd32_pwm_pin
{
    rt_uint32_t Port;
    rt_uint32_t pin;
    rt_uint32_t alt_func_num;
    rt_int16_t  channel;
    rt_int8_t   TimerIndex;

} gd32_pwm_pin_t;

static gd32_pwm_pin_t gd32_pwm_pin_obj[] = {
#ifdef BSP_USING_PWM0
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_9,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_1,
        .TimerIndex   = 0,
    },
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_10,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_2,
        .TimerIndex   = 0,
    },
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_11,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_3,
        .TimerIndex   = 0,
    },
#endif

#ifdef BSP_USING_PWM1
{
        .Port         = GPIOA,
        .pin          = GPIO_PIN_0,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_0,
        .TimerIndex   = 1,
    },
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_1,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_1,
        .TimerIndex   = 1,
    },
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_2,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_2,
        .TimerIndex   = 1,
    },
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_3,
        .alt_func_num = GPIO_AF_1,
        .channel      = TIMER_CH_3,
        .TimerIndex   = 1,
    },
#endif

#ifdef BSP_USING_PWM2
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_6,
        .alt_func_num = GPIO_AF_2,
        .channel      = TIMER_CH_0,
        .TimerIndex   = 2,
    },
    {
        .Port         = GPIOA,
        .pin          = GPIO_PIN_7,
        .alt_func_num = GPIO_AF_2,
        .channel      = TIMER_CH_1,
        .TimerIndex   = 2,
    },

#endif

#ifdef BSP_USING_PWM15
    {
        .Port         = GPIOB,
        .pin          = GPIO_PIN_13,
        .alt_func_num = GPIO_AF_8,
        .channel      = TIMER_CH_0,
        .TimerIndex   = 15,
    },
#endif

#ifdef BSP_USING_PWM16
    {
        .Port         = GPIOB,
        .pin          = GPIO_PIN_0,
        .alt_func_num = GPIO_AF_9,
        .channel      = TIMER_CH_0,
        .TimerIndex   = 16,
    },
#endif

};

typedef struct gd32_pwm_device
{
    struct rt_device_pwm pwm_device;
    rt_int8_t   TimerIndex;
    char *name;
} gd32_pwm_device_t;


static gd32_pwm_device_t gd32_pwm_obj[] = {
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .TimerIndex = 0,
    },
#endif
#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .TimerIndex = 1,
    },
#endif
#ifdef BSP_USING_PWM2
    {
        .name = "pwm2",
        .TimerIndex = 2,
    },
#endif
#ifdef BSP_USING_PWM15
    {
        .name = "pwm15",
        .TimerIndex = 15,
    },
#endif
#ifdef BSP_USING_PWM16
    {
        .name = "pwm16",
        .TimerIndex = 16,
    },
#endif
};

typedef struct
{
    rt_uint32_t Port[3];
    rt_int8_t   TimerIndex[5];
} TIMER_PERIPH_LIST_S;

static TIMER_PERIPH_LIST_S gd32_timer_periph_list = {
    .Port       = {0, 0, 0},
    .TimerIndex = {-1, -1, -1, -1, -1},
};

/*
 * List all used GPIO ports and timers without duplication to avoid repeated initialization later.
 */
static rt_err_t pwm_find_timer_periph(void)
{
    rt_int16_t i, j, k;

    /* find gpio port of defined table */
    for (i = 0; i < sizeof(gd32_pwm_pin_obj) / sizeof(gd32_pwm_pin_obj[0]); ++i)
    {
        /* find -1 of gd32_periph_list's member of Port */
        for (j = 0; j < sizeof(gd32_timer_periph_list.Port) / sizeof(gd32_timer_periph_list.Port[0]); ++j)
        {
            if (0 == gd32_timer_periph_list.Port[j])
            {
                break;
            }
        }

        if (j >= sizeof(gd32_timer_periph_list.Port) / sizeof(gd32_timer_periph_list.Port[0]))
        {
            LOG_E("Can not find -1 of gd32_periph_list's member of Port!\n");
            break;
        }

        /* find the different of Port */
        for (k = 0; k < j; ++k)
        {
            if (gd32_pwm_pin_obj[i].Port == gd32_timer_periph_list.Port[k])
            {
                break;
            }
        }

        /* if can not find the same Port */
        if (k == j)
        {
            gd32_timer_periph_list.Port[j] = gd32_pwm_pin_obj[i].Port;
        }
    }

    /* find timer periph of defined table */
    for (i = 0; i < sizeof(gd32_pwm_pin_obj) / sizeof(gd32_pwm_pin_obj[0]); ++i)
    {
        /* find -1 of gd32_periph_list's member of TimerIndex */
        for (j = 0; j < sizeof(gd32_timer_periph_list.TimerIndex) / sizeof(gd32_timer_periph_list.TimerIndex[0]); ++j)
        {
            if (-1 == gd32_timer_periph_list.TimerIndex[j])
            {
                break;
            }
        }

        if (j >= sizeof(gd32_timer_periph_list.TimerIndex) / sizeof(gd32_timer_periph_list.TimerIndex[0]))
        {
            LOG_E("Can not find -1 of gd32_periph_list's member of TimerIndex!\n");
            break;
        }

        /* find the different of TimerIndex */
        for (k = 0; k < j; ++k)
        {
            if (gd32_pwm_pin_obj[i].TimerIndex == gd32_timer_periph_list.TimerIndex[k])
            {
                break;
            }
        }

        /* if can not find the same TimerIndex */
        if (k == j)
        {
            gd32_timer_periph_list.TimerIndex[j] = gd32_pwm_pin_obj[i].TimerIndex;
        }
    }

    return RT_EOK;
}
static rt_uint32_t index_to_timer(rt_int8_t TimerIndex)
{
    switch (TimerIndex)
    {
    case 0:
        return TIMER0;
    case 1:
        return TIMER1;
    case 2:
        return TIMER2;
    case 15:
        return TIMER15;
    case 16:
        return TIMER16;
    default:
        LOG_E("Unsupported timer periph!\n");
    }
    return TIMER0;
}

static void gpio_clock_enable(rt_uint32_t Port)
{
    switch (Port)
    {
    case GPIOA:
        rcu_periph_clock_enable(RCU_GPIOA);
        break;
    case GPIOB:
        rcu_periph_clock_enable(RCU_GPIOB);
        break;
    case GPIOC:
        rcu_periph_clock_enable(RCU_GPIOC);
        break;
    default:
        LOG_E("Unsupported gpio port!\n");
    }
}

static void timer_clock_enable(rt_int8_t TimerIndex)
{
    switch (TimerIndex)
    {
    case 0:
        rcu_periph_clock_enable(RCU_TIMER0);
        break;
    case 1:
        rcu_periph_clock_enable(RCU_TIMER1);
        break;
    case 2:
        rcu_periph_clock_enable(RCU_TIMER2);
        break;
    case 15:
        rcu_periph_clock_enable(RCU_TIMER15);
        break;
    case 16:
        rcu_periph_clock_enable(RCU_TIMER16);
        break;
    default:
        LOG_E("Unsport timer periph!\n");
    }
}
static void gpio_config(void)
{
    rt_int16_t i;
    /* configure GPIO pins in alternate-function mode for TIMER PWM output */
    for (i = 0; i < sizeof(gd32_pwm_pin_obj) / sizeof(gd32_pwm_pin_obj[0]); ++i)
    {
        /* configure pin as alternate function for the corresponding TIMER channel */
        gpio_mode_set(gd32_pwm_pin_obj[i].Port, GPIO_MODE_AF, GPIO_PUPD_NONE, gd32_pwm_pin_obj[i].pin);
        gpio_output_options_set(gd32_pwm_pin_obj[i].Port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, gd32_pwm_pin_obj[i].pin);
        gpio_af_set(gd32_pwm_pin_obj[i].Port, gd32_pwm_pin_obj[i].alt_func_num, gd32_pwm_pin_obj[i].pin);
    }
}

static void rcu_config(void)
{
    rt_int16_t i;
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    for (i = 0; i < sizeof(gd32_timer_periph_list.Port) / sizeof(gd32_timer_periph_list.Port[0]); ++i)
    {
        if (0 == gd32_timer_periph_list.Port[i])
        {
            break;
        }

        /* enable GPIO clock */
        gpio_clock_enable(gd32_timer_periph_list.Port[i]);
    }

    for (i = 0; i < sizeof(gd32_timer_periph_list.TimerIndex) / sizeof(gd32_timer_periph_list.TimerIndex[0]); ++i)
    {
        if (-1 == gd32_timer_periph_list.TimerIndex[i])
        {
            break;
        }

        /* enable timer clock */
        timer_clock_enable(gd32_timer_periph_list.TimerIndex[i]);
        timer_deinit(index_to_timer(gd32_timer_periph_list.TimerIndex[i]));
    }
}

static void timer_init_para(timer_parameter_struct *initpara)
{
    rt_int16_t i;

    for (i = 0; i < sizeof(gd32_timer_periph_list.TimerIndex) / sizeof(gd32_timer_periph_list.TimerIndex[0]); ++i)
    {
        /* config timer */
        if (-1 != gd32_timer_periph_list.TimerIndex[i])
        {
            timer_init(index_to_timer(gd32_timer_periph_list.TimerIndex[i]), initpara);
        }
    }
}

static void channel_output_config(timer_oc_parameter_struct *ocpara)
{
    rt_int16_t  i;
    rt_uint32_t timer_periph;

    /* config the channel config */
    for (i = 0; i < sizeof(gd32_pwm_pin_obj) / sizeof(gd32_pwm_pin_obj[0]); ++i)
    {

        timer_periph = index_to_timer(gd32_pwm_pin_obj[i].TimerIndex);
        timer_channel_output_config(timer_periph, gd32_pwm_pin_obj[i].channel, ocpara);

        timer_channel_output_pulse_value_config(timer_periph, gd32_pwm_pin_obj[i].channel, 7999);
        timer_channel_output_mode_config(timer_periph, gd32_pwm_pin_obj[i].channel, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(timer_periph, gd32_pwm_pin_obj[i].channel, TIMER_OC_SHADOW_DISABLE);
        /* auto-reload preload shadow reg enable */
        /* timer_auto_reload_shadow_enable(timer_periph); */
        timer_channel_output_state_config(timer_periph, gd32_pwm_pin_obj[i].channel, TIMER_CCX_DISABLE);
        timer_channel_complementary_output_state_config(timer_periph, gd32_pwm_pin_obj[i].channel, TIMER_CCXN_DISABLE);
    }

    /* enable timer */
    for (i = 0; i < sizeof(gd32_timer_periph_list.TimerIndex) / sizeof(gd32_timer_periph_list.TimerIndex[0]); ++i)
    {
        if (-1 != gd32_timer_periph_list.TimerIndex[i])
        {
            timer_periph = index_to_timer(gd32_timer_periph_list.TimerIndex[i]);
            if (timer_periph == TIMER0)
            {
                timer_primary_output_config(timer_periph, ENABLE);
            }
            timer_enable(timer_periph);
        }
    }
}

static void timer_config(void)
{
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct    timer_initpara;

    /* TIMER configuration */
    timer_initpara.prescaler         = 119;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 15999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init_para(&timer_initpara);

    /* CHX configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    channel_output_config(&timer_ocintpara);
}

static rt_err_t gd32_hw_pwm_init(void)
{
    pwm_find_timer_periph();
    rcu_config();
    gpio_config();
    timer_config();
    return RT_EOK;
}

static rt_err_t drv_pwm_enable(gd32_pwm_device_t *pstTimerMap,
                      struct rt_pwm_configuration *configuration,
                      rt_bool_t enable)
{
    uint32_t timer_periph = index_to_timer(pstTimerMap->TimerIndex);
    uint32_t channel = configuration->channel;
    
    if ((channel != TIMER_CH_0) &&
        (channel != TIMER_CH_1) &&
        (channel != TIMER_CH_2) &&
        (channel != TIMER_CH_3))
    {
        return -RT_EINVAL;
    }

    if (enable)
    {
        timer_channel_output_state_config(timer_periph, channel, TIMER_CCX_ENABLE);
    }
    else
    {
        timer_channel_output_state_config(timer_periph, channel, TIMER_CCX_DISABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_set(gd32_pwm_device_t *pstTimerMap, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock, psc;
    tim_clock = rcu_clock_freq_get(CK_SYS);

    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    period     = (unsigned long long)configuration->period * tim_clock / 1000ULL;
    psc        = period / MAX_PERIOD + 1;
    period     = period / psc;

    timer_prescaler_config(index_to_timer(pstTimerMap->TimerIndex), psc - 1, TIMER_PSC_RELOAD_NOW);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }

    timer_autoreload_value_config(index_to_timer(pstTimerMap->TimerIndex), period - 1);

    pulse = (unsigned long long)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }

    timer_channel_output_pulse_value_config(index_to_timer(pstTimerMap->TimerIndex), configuration->channel, pulse);
    timer_counter_value_config(index_to_timer(pstTimerMap->TimerIndex), 0);

    /* Update frequency value */
    timer_event_software_generate(index_to_timer(pstTimerMap->TimerIndex), TIMER_EVENT_SRC_UPG);

    return RT_EOK;
}


static rt_err_t drv_pwm_get(gd32_pwm_device_t *pstTimerMap, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;
    rt_uint16_t psc;
    rt_uint32_t chxcv;

    tim_clock = rcu_clock_freq_get(CK_SYS);

    psc = timer_prescaler_read(index_to_timer(pstTimerMap->TimerIndex));
    if (psc == TIMER_CKDIV_DIV2)
    {
        tim_clock = tim_clock / 2;
    }
    else if (psc == TIMER_CKDIV_DIV4)
    {
        tim_clock = tim_clock / 4;
    }

    chxcv = timer_channel_capture_value_register_read(index_to_timer(pstTimerMap->TimerIndex), configuration->channel);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock             /= 1000000UL;
    configuration->period  = (TIMER_CAR(index_to_timer(pstTimerMap->TimerIndex)) + 1) * (psc + 1) * 1000UL / tim_clock;
    configuration->pulse   = (chxcv + 1) * (psc + 1) * 1000UL / tim_clock;

    return RT_EOK;
}


static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    gd32_pwm_device_t    *pstTimerMap   = (gd32_pwm_device_t *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pstTimerMap, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pstTimerMap, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(pstTimerMap, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pstTimerMap, configuration);
    default:
        return -RT_EINVAL;
}
}

static struct rt_pwm_ops drv_ops = {drv_pwm_control};

static int gd32_pwm_init(void)
{
    int i      = 0;
    int result = RT_EOK;

    /* pwm init */
    gd32_hw_pwm_init();
    LOG_D("PWM init success");

    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); i++)
    {
        if (rt_device_pwm_register(&gd32_pwm_obj[i].pwm_device, gd32_pwm_obj[i].name, &drv_ops, &gd32_pwm_obj[i]) == RT_EOK)
        {
            LOG_D("%s register success", gd32_pwm_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", gd32_pwm_obj[i].name);
            result = -RT_ERROR;
        }
    }
    return result;
}

INIT_DEVICE_EXPORT(gd32_pwm_init);

#endif /* RT_USING_PWM */