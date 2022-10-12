/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add apm32F4 serie MCU support
 */

#include <board.h>

#ifdef RT_USING_PWM
#include <drivers/rt_drv_pwm.h>

#define LOG_TAG               "drv.pwm"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE  2

#ifdef APM32F10X_HD
#define _PWM_GPIO_INIT(port_num, pin_num) \
do \
{ \
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIO##port_num); \
    gpio_config->pin = GPIO_PIN_##pin_num; \
    gpio_config->mode = GPIO_MODE_AF_PP; \
    gpio_config->speed = GPIO_SPEED_50MHz; \
    GPIO_Config(GPIO##port_num, gpio_config); \
} while (0)
#elif APM32F40X
#define _PWM_GPIO_INIT(port_num, pin_num) \
do \
{ \
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIO##port_num); \
    gpio_config->pin = GPIO_PIN_##pin_num; \
    gpio_config->mode = GPIO_MODE_AF; \
    gpio_config->otype = GPIO_OTYPE_PP; \
    gpio_config->speed = GPIO_SPEED_50MHz; \
    GPIO_Config(GPIO##port_num, gpio_config); \
} while (0)
#endif

enum
{
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM8
    PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    PWM9_INDEX,
#endif
#ifdef BSP_USING_PWM10
    PWM10_INDEX,
#endif
#ifdef BSP_USING_PWM11
    PWM11_INDEX,
#endif
#ifdef BSP_USING_PWM12
    PWM12_INDEX,
#endif
#ifdef BSP_USING_PWM13
    PWM13_INDEX,
#endif
#ifdef BSP_USING_PWM14
    PWM14_INDEX,
#endif
};

struct apm32_pwm
{
    char       *name;
    TMR_T      *tmr;
    rt_uint8_t channel;
    struct rt_device_pwm pwm_device;
};

static struct apm32_pwm pwm_config[] =
{
#ifdef BSP_USING_PWM1
    {
        "pwm1",
        TMR1,
        0,
    },
#endif
#ifdef BSP_USING_PWM2
    {
        "pwm2",
        TMR2,
        0,
    },
#endif
#ifdef BSP_USING_PWM3
    {
        "pwm3",
        TMR3,
        0,
    },
#endif
#ifdef BSP_USING_PWM4
    {
        "pwm4",
        TMR4,
        0,
    },
#endif
#ifdef BSP_USING_PWM5
    {
        "pwm5",
        TMR5,
        0,
    },
#endif
#ifdef BSP_USING_PWM8
    {
        "pwm8",
        TMR8,
        0,
    },
#endif
#ifdef BSP_USING_PWM9
    {
        "pwm9",
        TMR9,
        0,
    },
#endif
#ifdef BSP_USING_PWM10
    {
        "pwm10",
        TMR10,
        0,
    },
#endif
#ifdef BSP_USING_PWM11
    {
        "pwm11",
        TMR11,
        0,
    },
#endif
#ifdef BSP_USING_PWM12
    {
        "pwm12",
        TMR12,
        0,
    },
#endif
#ifdef BSP_USING_PWM13
    {
        "pwm13",
        TMR13,
        0,
    },
#endif
#ifdef BSP_USING_PWM14
    {
        "pwm14",
        TMR14,
        0,
    },
#endif
};

static void _pwm_channel_init(GPIO_Config_T *gpio_config)
{
#ifdef BSP_USING_PWM1_CH1
    pwm_config[PWM1_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(A, 8);
#endif
#ifdef BSP_USING_PWM1_CH2
    pwm_config[PWM1_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(A, 9);
#endif
#ifdef BSP_USING_PWM1_CH3
    pwm_config[PWM1_INDEX].channel |= 1 << 2;
    _PWM_GPIO_INIT(A, 10);
#endif
#ifdef BSP_USING_PWM1_CH4
    pwm_config[PWM1_INDEX].channel |= 1 << 3;
    _PWM_GPIO_INIT(A, 11);
#endif
#ifdef BSP_USING_PWM2_CH1
    pwm_config[PWM2_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(A, 0);
#endif
#ifdef BSP_USING_PWM2_CH2
    pwm_config[PWM2_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(A, 1);
#endif
#ifdef BSP_USING_PWM2_CH3
    pwm_config[PWM2_INDEX].channel |= 1 << 2;
    _PWM_GPIO_INIT(A, 2);
#endif
#ifdef BSP_USING_PWM2_CH4
    pwm_config[PWM2_INDEX].channel |= 1 << 3;
    _PWM_GPIO_INIT(A, 3);
#endif

#ifdef APM32F10X_HD
#ifdef BSP_USING_PWM3_CH1
    pwm_config[PWM3_INDEX].channel |= 1 << 0;
    GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);
    _PWM_GPIO_INIT(C, 6);
#endif
#ifdef BSP_USING_PWM3_CH2
    pwm_config[PWM3_INDEX].channel |= 1 << 1;
    GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);
    _PWM_GPIO_INIT(C, 7);
#endif
#ifdef BSP_USING_PWM3_CH3
    pwm_config[PWM3_INDEX].channel |= 1 << 2;
    GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);
    _PWM_GPIO_INIT(C, 8);
#endif
#ifdef BSP_USING_PWM3_CH4
    pwm_config[PWM3_INDEX].channel |= 1 << 3;
    GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);
    _PWM_GPIO_INIT(C, 9);
#endif
#elif APM32F40X
#ifdef BSP_USING_PWM3_CH1
    pwm_config[PWM3_INDEX].channel |= 1 << 0;
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_6, GPIO_AF_TMR3);
    _PWM_GPIO_INIT(C, 6);
#endif
#ifdef BSP_USING_PWM3_CH2
    pwm_config[PWM3_INDEX].channel |= 1 << 1;
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_7, GPIO_AF_TMR3);
    _PWM_GPIO_INIT(C, 7);
#endif
#ifdef BSP_USING_PWM3_CH3
    pwm_config[PWM3_INDEX].channel |= 1 << 2;
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_8, GPIO_AF_TMR3);
    _PWM_GPIO_INIT(C, 8);
#endif
#ifdef BSP_USING_PWM3_CH4
    pwm_config[PWM3_INDEX].channel |= 1 << 3;
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_9, GPIO_AF_TMR3);
    _PWM_GPIO_INIT(C, 9);
#endif
#endif

#ifdef BSP_USING_PWM4_CH1
    pwm_config[PWM4_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(B, 6);
#endif
#ifdef BSP_USING_PWM4_CH2
    pwm_config[PWM4_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(B, 7);
#endif
#ifdef BSP_USING_PWM4_CH3
    pwm_config[PWM4_INDEX].channel |= 1 << 2;
    _PWM_GPIO_INIT(B, 8);
#endif
#ifdef BSP_USING_PWM4_CH4
    pwm_config[PWM4_INDEX].channel |= 1 << 3;
    _PWM_GPIO_INIT(B, 9);
#endif
#ifdef BSP_USING_PWM5_CH1
    pwm_config[PWM5_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(A, 0);
#endif
#ifdef BSP_USING_PWM5_CH2
    pwm_config[PWM5_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(A, 1);
#endif
#ifdef BSP_USING_PWM5_CH3
    pwm_config[PWM5_INDEX].channel |= 1 << 2;
    _PWM_GPIO_INIT(A, 2);
#endif
#ifdef BSP_USING_PWM5_CH4
    pwm_config[PWM5_INDEX].channel |= 1 << 3;
    _PWM_GPIO_INIT(A, 3);
#endif
#ifdef BSP_USING_PWM8_CH1
    pwm_config[PWM8_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(C, 6);
#endif
#ifdef BSP_USING_PWM8_CH2
    pwm_config[PWM8_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(C, 7);
#endif
#ifdef BSP_USING_PWM8_CH3
    pwm_config[PWM8_INDEX].channel |= 1 << 2;
    _PWM_GPIO_INIT(C, 8);
#endif
#ifdef BSP_USING_PWM8_CH4
    pwm_config[PWM8_INDEX].channel |= 1 << 3;
    _PWM_GPIO_INIT(C, 9);
#endif
#ifdef APM32F40X
#ifdef BSP_USING_PWM9_CH1
    pwm_config[PWM9_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(E, 5);
#endif
#ifdef BSP_USING_PWM9_CH2
    pwm_config[PWM9_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(E, 6);
#endif
#ifdef BSP_USING_PWM10_CH1
    pwm_config[PWM10_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(F, 6);
#endif
#ifdef BSP_USING_PWM11_CH1
    pwm_config[PWM11_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(F, 7);
#endif
#ifdef BSP_USING_PWM12_CH1
    pwm_config[PWM9_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(H, 6);
#endif
#ifdef BSP_USING_PWM12_CH2
    pwm_config[PWM9_INDEX].channel |= 1 << 1;
    _PWM_GPIO_INIT(H, 9);
#endif
#ifdef BSP_USING_PWM13_CH1
    pwm_config[PWM10_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(F, 8);
#endif
#ifdef BSP_USING_PWM14_CH1
    pwm_config[PWM11_INDEX].channel |= 1 << 0;
    _PWM_GPIO_INIT(F, 9);
#endif
#endif
}

static rt_err_t _pwm_hw_init(struct apm32_pwm *device)
{
    rt_err_t result = RT_EOK;
    TMR_T *tmr = RT_NULL;
    TMR_BaseConfig_T   base_config;
    TMR_OCConfig_T     oc_config;

    RT_ASSERT(device != RT_NULL);

    tmr = (TMR_T *)device->tmr;

    if (tmr == TMR1)
    {
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
    }
    else if (tmr == TMR8)
    {
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR8);
    }
    else if (tmr == TMR2)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR2);
    }
    else if (tmr == TMR3)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
    }
    else if (tmr == TMR4)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR4);
    }
    else if (tmr == TMR5)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR5);
    }

    /* configure the tmrer to pwm mode */
    base_config.division = 0;
    base_config.countMode = TMR_COUNTER_MODE_UP;
    base_config.period = 0;
    base_config.clockDivision = TMR_CLOCK_DIV_1;
    TMR_ConfigTimeBase(tmr, &base_config);

    TMR_SelectOutputTrigger(tmr, TMR_TRGO_SOURCE_RESET);
    TMR_DisableMasterSlaveMode(tmr);

    oc_config.mode = TMR_OC_MODE_PWM1;
    oc_config.pulse = 0;
    oc_config.polarity = TMR_OC_POLARITY_HIGH;
    oc_config.nIdleState = TMR_OC_NIDLE_STATE_RESET;
    oc_config.idleState  = TMR_OC_IDLE_STATE_RESET;
    oc_config.outputState = TMR_OC_STATE_ENABLE;

    /* config pwm channel */
    if (device->channel & 0x01)
    {
        TMR_ConfigOC1(tmr, &oc_config);
    }

    if (device->channel & 0x02)
    {
        TMR_ConfigOC2(tmr, &oc_config);
    }

    if (device->channel & 0x04)
    {
        TMR_ConfigOC3(tmr, &oc_config);
    }

    if (device->channel & 0x08)
    {
        TMR_ConfigOC4(tmr, &oc_config);
    }

    /* enable update request source */
    TMR_ConfigUpdateRequest(tmr, TMR_UPDATE_SOURCE_REGULAR);

    return result;
}

static rt_uint32_t _pwm_timer_clock_get(TMR_T *tmr)
{
    uint32_t pclk1;

    RCM_ReadPCLKFreq(&pclk1, NULL);

    return (rt_uint32_t)(pclk1 * ((RCM->CFG_B.APB1PSC != RCM_APB_DIV_1) ? 2 : 1));
}

static rt_err_t _pwm_enable(TMR_T *tmr, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint32_t channel = (configuration->channel - 1) << 2;

    if (enable)
    {
        if (configuration->complementary)
        {
            TMR_EnableCCxNChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
        else
        {
            TMR_EnableCCxChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
        if (tmr == TMR1 || tmr == TMR8)
        {
            TMR_EnablePWMOutputs(tmr);
        }
        TMR_Enable(tmr);
    }
    else
    {
        if (configuration->complementary)
        {
            TMR_DisableCCxNChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
        else
        {
            TMR_DisableCCxChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
        if (tmr == TMR1 || tmr == TMR8)
        {
            TMR_DisablePWMOutputs(tmr);
        }
        TMR_Disable(tmr);
    }

    return RT_EOK;
}

static rt_err_t _pwm_get(TMR_T *tmr, struct rt_pwm_configuration *configuration)
{
    /* Converts the channel number to the channel number of library */
    rt_uint32_t channel = (configuration->channel - 1) << 2;
    rt_uint64_t timer_clock;
    rt_uint32_t timer_reload, timer_psc;

    timer_clock = _pwm_timer_clock_get(tmr);

    if (tmr->CTRL1_B.CLKDIV == TMR_CLOCK_DIV_2)
    {
        timer_clock <<= 1;
    }
    else if (tmr->CTRL1_B.CLKDIV == TMR_CLOCK_DIV_4)
    {
        timer_clock <<= 2;
    }

    uint32_t temp;
    temp = (uint32_t)tmr;
    temp += (uint32_t)(0x34 + channel);
    /* Convert nanosecond to frequency and duty cycle.*/
    timer_clock /= 1000000UL;

    timer_reload = tmr->AUTORLD;
    timer_psc = tmr->PSC;
    configuration->period = (timer_reload + 1) * (timer_psc + 1) * 1000UL / timer_clock;
    configuration->pulse = ((*(__IO uint32_t *)temp) + 1) * (timer_psc + 1) * 1000UL / timer_clock;

    return RT_EOK;
}

static rt_err_t _pwm_set(TMR_T *tmr, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t timer_clock, psc;
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);
    uint32_t temp = (uint32_t)tmr;

    timer_clock = _pwm_timer_clock_get(tmr);

    /* Convert nanosecond to frequency and duty cycle. */
    timer_clock /= 1000000UL;
    period = (unsigned long long)configuration->period * timer_clock / 1000ULL ;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    tmr->PSC = (uint16_t)(psc - 1);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    tmr->AUTORLD = (uint16_t)(period - 1);

    pulse = (unsigned long long)configuration->pulse * timer_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }

    temp += (uint32_t)(0x34 + channel);
    *(__IO uint32_t *)temp = pulse - 1;

    tmr->CNT = 0;

    /* Update frequency value */
    TMR_GenerateEvent(tmr, TMR_EVENT_UPDATE);

    return RT_EOK;
}

static rt_err_t _pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TMR_T *tmr = (TMR_T *)device->parent.user_data;

    switch (cmd)
    {
    case PWMN_CMD_ENABLE:
        configuration->complementary = RT_TRUE;
    case PWM_CMD_ENABLE:
        return _pwm_enable(tmr, configuration, RT_TRUE);
    case PWMN_CMD_DISABLE:
        configuration->complementary = RT_FALSE;
    case PWM_CMD_DISABLE:
        return _pwm_enable(tmr, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return _pwm_set(tmr, configuration);
    case PWM_CMD_GET:
        return _pwm_get(tmr, configuration);
    default:
        return RT_EINVAL;
    }
}

static const struct rt_pwm_ops _pwm_ops =
{
    _pwm_control
};

static int rt_hw_pwm_init(void)
{
    rt_uint32_t i = 0;
    rt_err_t result = RT_EOK;
    GPIO_Config_T gpio_config;

    _pwm_channel_init(&gpio_config);

    for (i = 0; i < sizeof(pwm_config) / sizeof(pwm_config[0]); i++)
    {
        /* pwm init */
        if (_pwm_hw_init(&pwm_config[i]) != RT_EOK)
        {
            LOG_E("%s init failed", pwm_config[i].name);
            return -RT_ERROR;
        }
        else
        {
            LOG_D("%s init success", pwm_config[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&pwm_config[i].pwm_device, pwm_config[i].name, &_pwm_ops, pwm_config[i].tmr) == RT_EOK)
            {
                LOG_D("%s register success", pwm_config[i].name);
            }
            else
            {
                LOG_E("%s register failed", pwm_config[i].name);
                result = -RT_ERROR;
            }
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* RT_USING_PWM */
