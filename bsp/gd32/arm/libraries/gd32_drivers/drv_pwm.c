/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-05     zengjianwei       first version
 * 2025-06-23     Yucai Liu         Support for non-complementary PWM output with
 *                                  advanced timers
 * 2025-12-26     shihongchao       Optimize the timer clock frequency acquisition
 *                                  method; optimize the gd32_pwm structure to make
 *                                  it easier to configure; optimize the RCU enable
 *                                  logic; optimize GPIO configuration to maintain
 *                                  floating input mode when channels are disabled,
 *                                  reducing power consumption.
 */

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

#ifdef BSP_USING_PWM

/* #define DRV_DEBUG */
#define LOG_TAG "drv.pwm"
#include <rtdbg.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE  2

typedef struct{
    uint32_t gpio_port;
    uint32_t gpio_af;
    uint16_t gpio_pin;
}channel_type;

struct gd32_pwm
{
    struct rt_device_pwm       pwm_device;   /* Inherit PWM device */
           char                *name;        /* Device name */
           uint32_t            timerx;       /* Hardware timer dependent on PWM */
           rcu_clock_freq_enum apb_of;       /* APB bus to which TIMER belongs */
           channel_type        channels[4];  /* PWM channels */
           channel_type        nchannels[3]; /* PWM complementary channels, only supported by advanced timers */
};

static struct gd32_pwm gd32_pwm_obj[] = {
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .timerx = TIMER0,
        .apb_of = CK_APB2,
        .channels = {
            {GPIOC, GPIO_AF_1, GPIO_PIN_0},
            {GPIOA, GPIO_AF_1, GPIO_PIN_1},
            {GPIOA, GPIO_AF_1, GPIO_PIN_2},
            {GPIOA, GPIO_AF_1, GPIO_PIN_3},
        },
        .nchannels = {
            {GPIOB, GPIO_AF_1, GPIO_PIN_13},
            {GPIOB, GPIO_AF_1, GPIO_PIN_14},
            {GPIOB, GPIO_AF_1, GPIO_PIN_15},
        }
    },
#endif

#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .timerx = TIMER1,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
            {GPIOA, GPIO_AF_1, GPIO_PIN_1},
            {GPIOA, GPIO_AF_1, GPIO_PIN_2},
            {GPIOB, GPIO_AF_1, GPIO_PIN_2},
        },
    },
#endif

#ifdef BSP_USING_PWM2
    {
        .name = "pwm2",
        .timerx = TIMER2,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_6},
            {GPIOA, GPIO_AF_1, GPIO_PIN_7},
            {GPIOB, GPIO_AF_2, GPIO_PIN_0},
            {GPIOB, GPIO_AF_2, GPIO_PIN_1},
        },
    },
#endif

#ifdef BSP_USING_PWM3
    {
        .name = "pwm3",
        .timerx = TIMER3,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
            {GPIOA, GPIO_AF_1, GPIO_PIN_1},
            {GPIOA, GPIO_AF_1, GPIO_PIN_2},
            {GPIOA, GPIO_AF_1, GPIO_PIN_3},
        },
    },
#endif

#ifdef BSP_USING_PWM4
    {
        .name = "pwm4",
        .timerx = TIMER4,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_2, GPIO_PIN_0},
            {GPIOA, GPIO_AF_2, GPIO_PIN_1},
            {GPIOA, GPIO_AF_1, GPIO_PIN_2},
            {GPIOA, GPIO_AF_1, GPIO_PIN_3},
        },
    },
#endif

#ifdef BSP_USING_PWM7
    {
        .name = "pwm7",
        .timerx = TIMER7,
        .apb_of = CK_APB2,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
            {GPIOA, GPIO_AF_1, GPIO_PIN_1},
            {GPIOC, GPIO_AF_1, GPIO_PIN_8},
            {GPIOA, GPIO_AF_1, GPIO_PIN_3},
        },
        .nchannels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_5},
            {GPIOB, GPIO_AF_1, GPIO_PIN_0},
            {GPIOB, GPIO_AF_1, GPIO_PIN_1},
        }
    },
#endif

#ifdef BSP_USING_PWM8
    {
        .name = "pwm8",
        .timerx = TIMER8,
        .apb_of = CK_APB2,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_2},
            {GPIOA, GPIO_AF_3, GPIO_PIN_3},
        }, // L1 general-purpose timer is a two-channel timer
    },
#endif

#ifdef BSP_USING_PWM9
    {
        .name = "pwm9",
        .timerx = TIMER9,
        .apb_of = CK_APB2,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
        }, // L2 general-purpose timer is a single-channel timer
    },
#endif

#ifdef BSP_USING_PWM10
    {
        .name = "pwm10",
        .timerx = TIMER10,
        .apb_of = CK_APB2,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
        }, // L2 general-purpose timer is a single-channel timer
    },
#endif

#ifdef BSP_USING_PWM11
    {
        .name = "pwm11",
        .timerx = TIMER11,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
            {GPIOA, GPIO_AF_1, GPIO_PIN_1},
        }, // L1 general-purpose timer is a two-channel timer
    },
#endif

#ifdef BSP_USING_PWM12
    {
        .name = "pwm12",
        .timerx = TIMER12,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_0},
        }, // L2 general-purpose timer is a single-channel timer
    },
#endif

#ifdef BSP_USING_PWM13
    {
        .name = "pwm13",
        .timerx = TIMER13,
        .apb_of = CK_APB1,
        .channels = {
            {GPIOA, GPIO_AF_1, GPIO_PIN_7},
        }, // L2 general-purpose timer is a single-channel timer
    },
#endif
};

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
    case GPIOD:
        rcu_periph_clock_enable(RCU_GPIOD);
        break;
    case GPIOE:
        rcu_periph_clock_enable(RCU_GPIOE);
        break;
    case GPIOF:
        rcu_periph_clock_enable(RCU_GPIOF);
        break;
    case GPIOG:
        rcu_periph_clock_enable(RCU_GPIOG);
        break;

    default:
        LOG_E("Unsport gpio port!\n");
    }
}

static void timer_clock_enable(uint32_t timer)
{
    switch (timer)
    {
    case TIMER0:
        rcu_periph_clock_enable(RCU_TIMER0);
        break;
    case TIMER1:
        rcu_periph_clock_enable(RCU_TIMER1);
        break;
    case TIMER2:
        rcu_periph_clock_enable(RCU_TIMER2);
        break;
    case TIMER3:
        rcu_periph_clock_enable(RCU_TIMER3);
        break;
    case TIMER4:
        rcu_periph_clock_enable(RCU_TIMER4);
        break;
    case TIMER5:
        rcu_periph_clock_enable(RCU_TIMER5);
        break;
    case TIMER6:
        rcu_periph_clock_enable(RCU_TIMER6);
        break;
    case TIMER7:
        rcu_periph_clock_enable(RCU_TIMER7);
        break;
    case TIMER8:
        rcu_periph_clock_enable(RCU_TIMER8);
        break;
    case TIMER9:
        rcu_periph_clock_enable(RCU_TIMER9);
        break;
    case TIMER10:
        rcu_periph_clock_enable(RCU_TIMER10);
        break;
    case TIMER11:
        rcu_periph_clock_enable(RCU_TIMER11);
        break;
    case TIMER12:
        rcu_periph_clock_enable(RCU_TIMER12);
        break;
    case TIMER13:
        rcu_periph_clock_enable(RCU_TIMER13);
        break;
    default:
        LOG_E("Unsport timer periph!\n");
    }
}

static void rcu_config(void)
{
    rt_int16_t i;

    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
    {
        /* enable GPIO clock */
        switch (gd32_pwm_obj[i].timerx)
        {
        /* Advanced timer */
        case TIMER0:
        case TIMER7:
            gpio_clock_enable(gd32_pwm_obj[i].nchannels[0].gpio_port);
            gpio_clock_enable(gd32_pwm_obj[i].nchannels[1].gpio_port);
            gpio_clock_enable(gd32_pwm_obj[i].nchannels[2].gpio_port);

        /* L0 general-purpose timer */
        case TIMER1:
        case TIMER2:
        case TIMER3:
        case TIMER4:
            gpio_clock_enable(gd32_pwm_obj[i].channels[2].gpio_port);
            gpio_clock_enable(gd32_pwm_obj[i].channels[3].gpio_port);

        /* L1 general-purpose timer */
        case TIMER8:
        case TIMER11:
            gpio_clock_enable(gd32_pwm_obj[i].channels[1].gpio_port);

        /* L2 general-purpose timer */
        case TIMER9:
        case TIMER10:
        case TIMER12:
        case TIMER13:
            gpio_clock_enable(gd32_pwm_obj[i].channels[0].gpio_port);
            break;

        default:
            LOG_E("Unsport timer periph at rcu_config!\n");
            break;
        }
    }

    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
    {
        /* enable timer clock */
        timer_clock_enable(gd32_pwm_obj[i].timerx);
        timer_deinit(gd32_pwm_obj[i].timerx);
    }
}

/**
 * @brief Configure PWM output pin to PWM output mode
 * @param pwm PWM object
 * @param configuration Configuration information passed by PWM driver framework
 */
static void gpio_config_pwmout(const struct gd32_pwm *pwm,
                               const struct rt_pwm_configuration *configuration)
{
    channel_type channel;
    uint8_t channel_num = configuration->channel;
    if(channel_num == 0)
    {
        LOG_E("PWM channel starts from 1!\n");
        return;
    }
    if(configuration->complementary)
    {
        if(channel_num > 3)
        {
            LOG_E("GD32 PWM complementary channel max 3!\n");
            return;
        };
        channel = pwm->nchannels[channel_num-1];
    }
    else
    {
        if(channel_num > 4)
        {
            LOG_E("GD32 PWM complementary channel max 4!\n");
            return;
        };
        channel = pwm->channels[channel_num-1];
    }
    gpio_mode_set(channel.gpio_port, GPIO_MODE_AF, GPIO_PUPD_NONE, channel.gpio_pin);
    gpio_output_options_set(channel.gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, channel.gpio_pin);
    gpio_af_set(channel.gpio_port, channel.gpio_af, channel.gpio_pin);
}

/**
 * @brief Configure PWM output pin to PWM floating input mode
 * @param pwm PWM object
 * @param configuration Configuration information passed by PWM driver framework
 */
static void gpio_config_input(const struct gd32_pwm *pwm,
                              const struct rt_pwm_configuration *configuration)
{
    channel_type channel = {0};
    uint8_t channel_num = configuration->channel;
    if(channel_num == 0)
    {
        return;
    }
    if(configuration->complementary)
    {
        if(channel_num > 3)
        {
            LOG_E("GD32 PWM complementary channel max 3!\n");
            return;
        };
        channel = pwm->nchannels[channel_num-1];
    }
    else
    {
        if(channel_num > 4)
        {
            LOG_E("GD32 PWM complementary channel max 4!\n");
            return;
        };
        channel = pwm->channels[channel_num-1];
    }
    gpio_mode_set(channel.gpio_port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, channel.gpio_pin);
}

static void channel_output_config(rt_uint32_t timer_periph, timer_oc_parameter_struct *ocpara)
{
    switch (timer_periph)
    {
    /* Advanced timer */
    case TIMER0:
    case TIMER7:
        timer_primary_output_config(timer_periph, ENABLE);

    /* L0 general-purpose timer */
    case TIMER1:
    case TIMER2:
    case TIMER3:
    case TIMER4:
        timer_channel_output_config(timer_periph, TIMER_CH_2, ocpara);
        timer_channel_output_pulse_value_config(timer_periph, TIMER_CH_2, 7999);
        timer_channel_output_mode_config(timer_periph, TIMER_CH_2, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(timer_periph, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);
        /* auto-reload preload shadow reg enable */
        /* timer_auto_reload_shadow_enable(timer_periph); */
        timer_channel_output_state_config(timer_periph, TIMER_CH_2, TIMER_CCX_DISABLE);
        timer_channel_complementary_output_state_config(timer_periph, TIMER_CH_2, TIMER_CCXN_DISABLE);

        timer_channel_output_config(timer_periph, TIMER_CH_3, ocpara);
        timer_channel_output_pulse_value_config(timer_periph, TIMER_CH_3, 7999);
        timer_channel_output_mode_config(timer_periph, TIMER_CH_3, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(timer_periph, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);
        /* auto-reload preload shadow reg enable */
        /* timer_auto_reload_shadow_enable(timer_periph); */
        timer_channel_output_state_config(timer_periph, TIMER_CH_3, TIMER_CCX_DISABLE);
        timer_channel_complementary_output_state_config(timer_periph, TIMER_CH_3, TIMER_CCXN_DISABLE);

    /* L1 general-purpose timer */
    case TIMER8:
    case TIMER11:
        timer_channel_output_config(timer_periph, TIMER_CH_1, ocpara);
        timer_channel_output_pulse_value_config(timer_periph, TIMER_CH_1, 7999);
        timer_channel_output_mode_config(timer_periph, TIMER_CH_1, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(timer_periph, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
        /* auto-reload preload shadow reg enable */
        /* timer_auto_reload_shadow_enable(timer_periph); */
        timer_channel_output_state_config(timer_periph, TIMER_CH_1, TIMER_CCX_DISABLE);
        timer_channel_complementary_output_state_config(timer_periph, TIMER_CH_1, TIMER_CCXN_DISABLE);

    /* L2 general-purpose timer */
    case TIMER9:
    case TIMER10:
    case TIMER12:
    case TIMER13:
        timer_channel_output_config(timer_periph, TIMER_CH_0, ocpara);
        timer_channel_output_pulse_value_config(timer_periph, TIMER_CH_0, 7999);
        timer_channel_output_mode_config(timer_periph, TIMER_CH_0, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(timer_periph, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
        /* auto-reload preload shadow reg enable */
        /* timer_auto_reload_shadow_enable(timer_periph); */
        timer_channel_output_state_config(timer_periph, TIMER_CH_0, TIMER_CCX_DISABLE);
        timer_channel_complementary_output_state_config(timer_periph, TIMER_CH_0, TIMER_CCXN_DISABLE);
        break;

    default:
        LOG_E("Unsport timer periph at channel_output_config!\n");
        break;
    }

    timer_enable(timer_periph);
}

static void timer_config(void)
{
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct    timer_initpara;

    /* TIMER configuration */
    timer_initpara.prescaler         = 199;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 15999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    for (size_t i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
    {
        timer_init(gd32_pwm_obj[i].timerx, &timer_initpara);
    }

    /* CHX configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_DISABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    /* config the channel config */
    for (size_t i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
    {
        channel_output_config(gd32_pwm_obj[i].timerx, &timer_ocintpara);
    }
}

static rt_err_t drv_pwm_enable(struct gd32_pwm *pwm, const struct rt_pwm_configuration *configuration,
                               rt_bool_t enable)
{
    if(channel_num == 0)
    {
        LOG_E("GD32 PWM channel starts from 1!\n");
        return -RT_EINVAL;
    }
    if(configuration->complementary)
    {
        if(channel_num > 3)
        {
            LOG_E("GD32 PWM complementary channel max 3!\n");
            return -RT_EINVAL;
        };
    }
    else
    {
        if(channel_num > 4)
        {
            LOG_E("GD32 PWM complementary channel max 4!\n");
            return -RT_EINVAL;
        };
    }

    if (!enable)
    {
        gpio_config_input(pwm, configuration);
        if (configuration->complementary == RT_TRUE)
        {
            timer_channel_complementary_output_state_config(pwm->timerx, configuration->channel-1,
                TIMER_CCXN_DISABLE);
        }
        else
        {
            timer_channel_output_state_config(pwm->timerx, configuration->channel-1,
                TIMER_CCX_DISABLE);
        }
    }
    else
    {
        gpio_config_pwmout(pwm, configuration);
        if (configuration->complementary == RT_TRUE)
        {
            timer_channel_complementary_output_state_config(pwm->timerx, configuration->channel-1,
                TIMER_CCXN_ENABLE);
        }
        else
        {
            timer_channel_output_state_config(pwm->timerx, configuration->channel-1,
                TIMER_CCX_ENABLE);
        }
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(const struct gd32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;
    rt_uint16_t psc;
    rt_uint32_t chxcv;

    if(configuration->channel == 0)
    {
        return -RT_EINVAL;
    }

    rt_uint8_t coef = (RCU_CFG1&RCU_CFG1_TIMERSEL)?4:2;
    tim_clock = rcu_clock_freq_get(pwm->apb_of)*coef;

    psc = timer_prescaler_read(pwm->timerx);
    if (psc == TIMER_CKDIV_DIV2)
    {
        tim_clock = tim_clock / 2;
    }
    else if (psc == TIMER_CKDIV_DIV4)
    {
        tim_clock = tim_clock / 4;
    }

    chxcv = timer_channel_capture_value_register_read(pwm->timerx, configuration->channel-1);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock             /= 1000000UL;
    configuration->period  = (TIMER_CAR(pwm->timerx) + 1) * (psc + 1) * 1000UL / tim_clock;
    configuration->pulse   = (chxcv + 1) * (psc + 1) * 1000UL / tim_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(struct gd32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock, psc;

    rt_uint8_t coef = (RCU_CFG1&RCU_CFG1_TIMERSEL)?4:2;
    tim_clock = rcu_clock_freq_get(pwm->apb_of)*coef;

    if(configuration->channel == 0)
    {
        return -RT_EINVAL;
    }

    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    period     = (unsigned long long)configuration->period * tim_clock / 1000ULL;
    psc        = period / MAX_PERIOD + 1;
    period     = period / psc;

    timer_prescaler_config(pwm->timerx, psc - 1, TIMER_PSC_RELOAD_NOW);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }

    timer_autoreload_value_config(pwm->timerx, period - 1);

    pulse = (unsigned long long)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }

    timer_channel_output_pulse_value_config(pwm->timerx, configuration->channel-1, pulse);
    timer_counter_value_config(pwm->timerx, 0);

    /* Update frequency value */
    timer_event_software_generate(pwm->timerx, TIMER_EVENT_SRC_UPG);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct gd32_pwm *pwm = rt_container_of(device, struct gd32_pwm, pwm_device);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(pwm, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops = {drv_pwm_control};

static rt_err_t gd32_hw_pwm_init(void)
{
    rcu_config();
    timer_config();

    /*
     * GPIO is not configured here. When PWM channel is enabled, it will be configured as PWM output.
     * When disabled, it will be configured as floating input.
     * GPIO defaults to floating input.
    */

    return RT_EOK;
}

static int rt_hw_pwm_init(void)
{
    int i      = 0;
    int result = RT_EOK;

    /* pwm init */
    if (gd32_hw_pwm_init() != RT_EOK)
    {
        LOG_E("PWM init failed");
        result = -RT_ERROR;
        goto __exit;
    }

    LOG_D("PWM init success");

    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); i++)
    {
        /* register pwm device */
        if (rt_device_pwm_register(&gd32_pwm_obj[i].pwm_device, gd32_pwm_obj[i].name, &drv_ops,
                                   RT_NULL)== RT_EOK )
        {
            LOG_D("%s register success", gd32_pwm_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", gd32_pwm_obj[i].name);
            result = -RT_ERROR;
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);
#endif /* BSP_USING_PWM */
