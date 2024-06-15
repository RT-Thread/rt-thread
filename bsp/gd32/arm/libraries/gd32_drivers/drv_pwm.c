/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-05     zengjianwei           first version
 */

#include <board.h>
#include <gd32f30x.h>
#include <rtdevice.h>
#include <rtthread.h>

#ifdef RT_USING_PWM

//#define DRV_DEBUG
#define LOG_TAG "drv.pwm"
#include <rtdbg.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE 2

typedef struct
{
    rt_int8_t TimerIndex; // timer index:0~13
    rt_uint32_t Port;     // gpio port:GPIOA/GPIOB/GPIOC/...
    rt_uint32_t pin;      // gpio pin:GPIO_PIN_0~GPIO_PIN_15
    rt_uint16_t channel;  // timer channel
    char *name;
} TIMER_PORT_CHANNEL_MAP_S;

struct gd32_pwm
{
    struct rt_device_pwm pwm_device;
    TIMER_PORT_CHANNEL_MAP_S tim_handle;
};

static struct gd32_pwm gd32_pwm_obj[] = {
#ifdef RT_USING_PWM1
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm1"}},
#endif

#ifdef RT_USING_PWM2
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm2"}},
#endif

#ifdef RT_USING_PWM3
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm3"}},
#endif

#ifdef RT_USING_PWM4
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm4"}},
#endif

#ifdef RT_USING_PWM5
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm5"}},
#endif

#ifdef RT_USING_PWM6
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm6"}},
#endif

#ifdef RT_USING_PWM7
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm7"}},
#endif

#ifdef RT_USING_PWM8
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm8"}},
#endif

#ifdef RT_USING_PWM9
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm9"}},
#endif

#ifdef RT_USING_PWM10
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm10"}},
#endif

#ifdef RT_USING_PWM11
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm11"}},
#endif

#ifdef RT_USING_PWM12
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm12"}},
#endif

#ifdef RT_USING_PWM13
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm13"}},
#endif

#ifdef RT_USING_PWM14
    {.tim_handle = {3, GPIOB, GPIO_PIN_8, 2, "pwm14"}},
#endif
};

typedef struct
{
    rt_uint32_t Port[7];
    rt_int8_t TimerIndex[14];
} TIMER_PERIPH_LIST_S;

static TIMER_PERIPH_LIST_S gd32_timer_periph_list = {
    .Port = {0, 0, 0, 0, 0, 0, 0},
    .TimerIndex = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

/*
 * 将所有用到的 gpio port 和 timer 不重复地列举出来，以方便后面不重复地初始化
 */
static rt_err_t pwm_find_timer_periph(void)
{
    rt_int16_t i, j, k;

    /* find gpio port of defined table */
    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
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
            if (gd32_pwm_obj[i].tim_handle.Port == gd32_timer_periph_list.Port[k])
            {
                break;
            }
        }

        /* if can not find the same Port */
        if (k == j)
        {
            gd32_timer_periph_list.Port[j] = gd32_pwm_obj[i].tim_handle.Port;
        }
    }

    /* find timer periph of defined table */
    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
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
            if (gd32_pwm_obj[i].tim_handle.TimerIndex == gd32_timer_periph_list.TimerIndex[k])
            {
                break;
            }
        }

        /* if can not find the same TimerIndex */
        if (k == j)
        {
            gd32_timer_periph_list.TimerIndex[j] = gd32_pwm_obj[i].tim_handle.TimerIndex;
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
    case 3:
        return TIMER3;
    case 4:
        return TIMER4;
    case 5:
        return TIMER5;
    case 6:
        return TIMER6;
    case 7:
        return TIMER7;
    case 8:
        return TIMER8;
    case 9:
        return TIMER9;
    case 10:
        return TIMER10;
    case 11:
        return TIMER11;
    case 12:
        return TIMER12;
    case 13:
        return TIMER13;

    default:
        LOG_E("Unsport timer periph!\n");
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
    case 3:
        rcu_periph_clock_enable(RCU_TIMER3);
        break;
    case 4:
        rcu_periph_clock_enable(RCU_TIMER4);
        break;
    case 5:
        rcu_periph_clock_enable(RCU_TIMER5);
        break;
    case 6:
        rcu_periph_clock_enable(RCU_TIMER6);
        break;
    case 7:
        rcu_periph_clock_enable(RCU_TIMER7);
        break;
#ifndef GD32F30X_HD
    case 8:
        rcu_periph_clock_enable(RCU_TIMER8);
        break;
    case 9:
        rcu_periph_clock_enable(RCU_TIMER9);
        break;
    case 10:
        rcu_periph_clock_enable(RCU_TIMER10);
        break;
    case 11:
        rcu_periph_clock_enable(RCU_TIMER11);
        break;
    case 12:
        rcu_periph_clock_enable(RCU_TIMER12);
        break;
    case 13:
        rcu_periph_clock_enable(RCU_TIMER13);
        break;
#endif
    default:
        LOG_E("Unsport timer periph!\n");
    }
}

static void rcu_config(void)
{
    rt_int16_t i;

    for (i = 0; i < sizeof(gd32_timer_periph_list.Port) / sizeof(gd32_timer_periph_list.Port[0]); ++i)
    {
        if (0 == gd32_timer_periph_list.Port[i])
        {
            break;
        }

        /* enable GPIO clock */
        gpio_clock_enable(gd32_timer_periph_list.Port[i]);
    }

    rcu_periph_clock_enable(RCU_AF);

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

static void gpio_config(void)
{
    rt_int16_t i;

    /* config the GPIO as analog mode */
    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
    {
        gpio_init(gd32_pwm_obj[i].tim_handle.Port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, gd32_pwm_obj[i].tim_handle.pin);
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
    rt_int16_t i;
    rt_uint32_t timer_periph;

    /* config the channel config */
    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); ++i)
    {
        timer_periph = index_to_timer(gd32_pwm_obj[i].tim_handle.TimerIndex);
        timer_channel_output_config(timer_periph, gd32_pwm_obj[i].tim_handle.channel, ocpara);

        timer_channel_output_pulse_value_config(timer_periph, gd32_pwm_obj[i].tim_handle.channel, 7999);
        timer_channel_output_mode_config(timer_periph, gd32_pwm_obj[i].tim_handle.channel, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(timer_periph, gd32_pwm_obj[i].tim_handle.channel, TIMER_OC_SHADOW_DISABLE);
        /* auto-reload preload shadow reg enable */
        // timer_auto_reload_shadow_enable(timer_periph);
        timer_channel_output_state_config(timer_periph, gd32_pwm_obj[i].tim_handle.channel, TIMER_CCX_DISABLE);
    }

    /* enable timer */
    for (i = 0; i < sizeof(gd32_timer_periph_list.TimerIndex) / sizeof(gd32_timer_periph_list.TimerIndex[0]); ++i)
    {
        if (-1 != gd32_timer_periph_list.TimerIndex[i])
        {
            timer_periph = index_to_timer(gd32_timer_periph_list.TimerIndex[i]);
            timer_enable(timer_periph);
        }
    }
}

static void timer_config(void)
{
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    /* TIMER configuration */
    timer_initpara.prescaler = 119;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 15999;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init_para(&timer_initpara);

    /* CHX configuration in PWM mode */
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    channel_output_config(&timer_ocintpara);
}

static rt_err_t drv_pwm_enable(TIMER_PORT_CHANNEL_MAP_S *pstTimerMap, struct rt_pwm_configuration *configuration,
                               rt_bool_t enable)
{
    if (!enable)
    {
        timer_channel_output_state_config(index_to_timer(pstTimerMap->TimerIndex), configuration->channel,
                                          TIMER_CCX_DISABLE);
    }
    else
    {
        timer_channel_output_state_config(index_to_timer(pstTimerMap->TimerIndex), configuration->channel,
                                          TIMER_CCX_ENABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(TIMER_PORT_CHANNEL_MAP_S *pstTimerMap, struct rt_pwm_configuration *configuration)
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
    tim_clock /= 1000000UL;
    configuration->period = (TIMER_CAR(index_to_timer(pstTimerMap->TimerIndex)) + 1) * (psc + 1) * 1000UL / tim_clock;
    configuration->pulse = (chxcv + 1) * (psc + 1) * 1000UL / tim_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(TIMER_PORT_CHANNEL_MAP_S *pstTimerMap, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock, psc;

    tim_clock = rcu_clock_freq_get(CK_SYS);

    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    period = (unsigned long long)configuration->period * tim_clock / 1000ULL;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;

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

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TIMER_PORT_CHANNEL_MAP_S *pstTimerMap = (TIMER_PORT_CHANNEL_MAP_S *)device->parent.user_data;

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
        return RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops = {drv_pwm_control};

static rt_err_t gd32_hw_pwm_init(void)
{
    pwm_find_timer_periph();
    rcu_config();
    gpio_config();
    timer_config();

    return RT_EOK;
}

static int gd32_pwm_init(void)
{
    int i = 0;
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
        if (rt_device_pwm_register(&gd32_pwm_obj[i].pwm_device, gd32_pwm_obj[i].tim_handle.name, &drv_ops,
                                   &gd32_pwm_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", gd32_pwm_obj[i].tim_handle.name);
        }
        else
        {
            LOG_E("%s register failed", gd32_pwm_obj[i].tim_handle.name);
            result = -RT_ERROR;
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(gd32_pwm_init);
#endif /* RT_USING_PWM */
