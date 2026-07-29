/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-23     ox-horse     first version
 */

#include <board.h>
#include <rtthread.h>

#ifdef BSP_USING_PWM
#include "drv_config.h"
#include "drv_tim.h"
#include <drivers/dev_pwm.h>

//#define DRV_DEBUG
#define LOG_TAG "drv.pwm"
#include <drv_log.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 1
#define MIN_PULSE  1

/* All ATIM and GTIM timers on N32H7xx support 4 PWM output channels (CH1-CH4).
 * BTIM1-4 are basic timers without PWM capability.
 *
 * PWM device naming:
 *   ATIM1-4  -> pwm1-4   (advanced, with complementary output)
 *   GTIMA1-7 -> pwm5-11  (general purpose, A bus)
 *   GTIMB1-3 -> pwm12-14 (general purpose, B bus, with complementary output)
 */

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
#ifdef BSP_USING_PWM6
    PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
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

struct n32_pwm
{
    struct rt_device_pwm pwm_device;
    TIM_Module          *timer;
    rt_uint8_t           channel;     /* bitmask: bit0=CH1, bit1=CH2, bit2=CH3, bit3=CH4 */
    char                *name;
};

static struct n32_pwm n32_pwm_obj[] = {
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif

#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif

#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif

#ifdef BSP_USING_PWM4
    PWM4_CONFIG,
#endif

#ifdef BSP_USING_PWM5
    PWM5_CONFIG,
#endif

#ifdef BSP_USING_PWM6
    PWM6_CONFIG,
#endif

#ifdef BSP_USING_PWM7
    PWM7_CONFIG,
#endif

#ifdef BSP_USING_PWM8
    PWM8_CONFIG,
#endif

#ifdef BSP_USING_PWM9
    PWM9_CONFIG,
#endif

#ifdef BSP_USING_PWM10
    PWM10_CONFIG,
#endif

#ifdef BSP_USING_PWM11
    PWM11_CONFIG,
#endif

#ifdef BSP_USING_PWM12
    PWM12_CONFIG,
#endif

#ifdef BSP_USING_PWM13
    PWM13_CONFIG,
#endif

#ifdef BSP_USING_PWM14
    PWM14_CONFIG,
#endif
};

static rt_uint64_t tim_clock_get(TIM_Module *timer)
{
    rt_uint32_t       tim_div;
    RCC_ClocksTypeDef RCC_Clocks;

    n32_tim_ahbx_div_get(timer, &tim_div);
    RCC_GetClocksFreqValue(&RCC_Clocks);

    if ((timer == BTIM1) || (timer == BTIM2) || (timer == BTIM3) || (timer == BTIM4) || (timer == GTIMA4) || (timer == GTIMA5) || (timer == GTIMA6) || (timer == GTIMA7) || (timer == GTIMB1) || (timer == GTIMB2) || (timer == GTIMB3))
    {
        return (rt_uint64_t)RCC_Clocks.AHB1ClkFreq / tim_div;
    }
    else if ((timer == ATIM1) || (timer == ATIM2) || (timer == GTIMA1) || (timer == GTIMA2) || (timer == GTIMA3))
    {
        return (rt_uint64_t)RCC_Clocks.AHB2ClkFreq / tim_div;
    }
    else /* ATIM3, ATIM4 */
    {
        return (rt_uint64_t)RCC_Clocks.AHB5ClkFreq / tim_div;
    }
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops = {
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint32_t tim_ch = 0x04 * (configuration->channel - 1);

    if (!configuration->complementary)
    {
        TIM_EnableCapCmpCh(pwm->timer, tim_ch,
                           enable ? TIM_CAP_CMP_ENABLE : TIM_CAP_CMP_DISABLE);
    }
    else
    {
        TIM_EnableCapCmpChN(pwm->timer, tim_ch,
                            enable ? TIM_CAP_CMP_N_ENABLE : TIM_CAP_CMP_N_DISABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;
    rt_uint32_t period;
    rt_uint32_t psc;
    rt_uint32_t cmp = 0;

    tim_clock = tim_clock_get(pwm->timer);
    /* Convert to MHz for nanosecond calculation */
    tim_clock /= 1000000UL;

    period = TIM_GetAutoReload(pwm->timer) + 1;
    psc    = TIM_GetPrescaler(pwm->timer) + 1;

    /* period (ns) = (ARR+1) * (PSC+1) * 1000 / tim_clock_MHz */
    configuration->period = period * psc * 1000UL / tim_clock;

    switch (configuration->channel)
    {
    case 1:
        cmp = TIM_GetCap1(pwm->timer);
        break;
    case 2:
        cmp = TIM_GetCap2(pwm->timer);
        break;
    case 3:
        cmp = TIM_GetCap3(pwm->timer);
        break;
    case 4:
        cmp = TIM_GetCap4(pwm->timer);
        break;
    default:
        return -RT_EINVAL;
    }

    configuration->pulse = (cmp + 1) * psc * 1000UL / tim_clock;

    return RT_EOK;
}
uint32_t temp;
static rt_err_t drv_pwm_set(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock, psc;
    /* Converts the channel number to the channel number of standard library */
    rt_uint32_t tim_ch = 0x04 * (configuration->channel - 1);

    tim_clock = tim_clock_get(pwm->timer);
    temp      = tim_clock;
    /* Convert to MHz */
    tim_clock /= 1000000UL;

    /* Calculate period and prescaler from requested period (ns) */
    period = (rt_uint64_t)configuration->period * tim_clock / 1000ULL;
    psc    = period / MAX_PERIOD + 1;
    period = period / psc;

    /* Set prescaler */
    TIM_ConfigPrescaler(pwm->timer, (uint32_t)(psc - 1), TIM_PSC_RELOAD_MODE_UPDATE);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    TIM_SetAutoReload(pwm->timer, period - 1);

    /* Calculate pulse from requested pulse (ns) */
    pulse = (rt_uint64_t)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse >= period)
    {
        pulse = period;
    }

    /* Set compare value */
    switch (configuration->channel)
    {
    case 1:
        TIM_SetCmp1(pwm->timer, (uint16_t)pulse);
        break;
    case 2:
        TIM_SetCmp2(pwm->timer, (uint16_t)pulse);
        break;
    case 3:
        TIM_SetCmp3(pwm->timer, (uint16_t)pulse);
        break;
    case 4:
        TIM_SetCmp4(pwm->timer, (uint16_t)pulse);
        break;
    default:
        return -RT_EINVAL;
    }

    /* Generate update event to apply immediately */
    TIM_GenerateEvent(pwm->timer, TIM_EVT_SRC_UPDATE);

    return RT_EOK;
}

static rt_err_t drv_pwm_set_period(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period;
    rt_uint64_t tim_clock, psc;

    tim_clock  = tim_clock_get(pwm->timer);
    tim_clock /= 1000000UL;

    period = (rt_uint64_t)configuration->period * tim_clock / 1000ULL;
    psc    = period / MAX_PERIOD + 1;
    period = period / psc;

    TIM_ConfigPrescaler(pwm->timer, (uint32_t)(psc - 1), TIM_PSC_RELOAD_MODE_UPDATE);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    TIM_SetAutoReload(pwm->timer, period - 1);

    return RT_EOK;
}

static rt_err_t drv_pwm_set_pulse(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock;

    tim_clock  = tim_clock_get(pwm->timer);
    tim_clock /= 1000000UL;

    period = (TIM_GetAutoReload(pwm->timer) + 1) * (TIM_GetPrescaler(pwm->timer) + 1) * 1000UL / tim_clock;
    pulse  = (rt_uint64_t)configuration->pulse * (TIM_GetAutoReload(pwm->timer) + 1) / period;

    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > (rt_uint32_t)(TIM_GetAutoReload(pwm->timer) + 1))
    {
        pulse = TIM_GetAutoReload(pwm->timer) + 1;
    }

    switch (configuration->channel)
    {
    case 1:
        TIM_SetCmp1(pwm->timer, (uint16_t)(pulse - 1));
        break;
    case 2:
        TIM_SetCmp2(pwm->timer, (uint16_t)(pulse - 1));
        break;
    case 3:
        TIM_SetCmp3(pwm->timer, (uint16_t)(pulse - 1));
        break;
    case 4:
        TIM_SetCmp4(pwm->timer, (uint16_t)(pulse - 1));
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct n32_pwm              *pwm           = (struct n32_pwm *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(pwm, configuration);
    case PWM_CMD_SET_PERIOD:
        return drv_pwm_set_period(pwm, configuration);
    case PWM_CMD_SET_PULSE:
        return drv_pwm_set_pulse(pwm, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm, configuration);
    default:
        return -RT_EINVAL;
    }
}

/**
 * @brief Initialize a single PWM channel hardware.
 */
static void drv_pwm_channel_init(TIM_Module *timer, rt_uint32_t channel_idx, rt_uint32_t oc_mode)
{
    OCInitType TIM_OCInitStructure;

    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode       = oc_mode;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
    TIM_OCInitStructure.Pulse        = 0;
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_RESET;
    TIM_OCInitStructure.OCNIdleState = TIM_OCN_IDLE_STATE_RESET;

    switch (channel_idx)
    {
    case 0:
        TIM_InitOc1(timer, &TIM_OCInitStructure);
        TIM_ConfigOc1Preload(timer, TIM_OC_PRE_LOAD_ENABLE);
        break;
    case 1:
        TIM_InitOc2(timer, &TIM_OCInitStructure);
        TIM_ConfigOc2Preload(timer, TIM_OC_PRE_LOAD_ENABLE);
        break;
    case 2:
        TIM_InitOc3(timer, &TIM_OCInitStructure);
        TIM_ConfigOc3Preload(timer, TIM_OC_PRE_LOAD_ENABLE);
        break;
    case 3:
        TIM_InitOc4(timer, &TIM_OCInitStructure);
        TIM_ConfigOc4Preload(timer, TIM_OC_PRE_LOAD_ENABLE);
        break;
    default:
        break;
    }
}

/**
 * @brief Hardware initialization for one PWM device.
 */
static rt_err_t n32_hw_pwm_init(struct n32_pwm *device)
{
    rt_err_t             result = RT_EOK;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    rt_uint32_t          i;

    RT_ASSERT(device != RT_NULL);

    /* Enable timer clock (M7 + M4 dual-core clock enable) */
    n32_tim_enable_clock(device->timer);

    /* Configure time base: default 1kHz, PWM mode */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period      = 1000 - 1;
    TIM_TimeBaseStructure.Prescaler   = 0;
    TIM_TimeBaseStructure.ClkDiv      = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.RepetCnt    = 0;
    TIM_InitTimeBase(device->timer, &TIM_TimeBaseStructure);

    /* Configure PWM output channels */
    for (i = 0; i < 4; i++)
    {
        if (device->channel & (1 << i))
        {
            drv_pwm_channel_init(device->timer, i, TIM_OCMODE_PWM1);
        }
    }

    /* Enable auto-reload preload */
    TIM_ConfigArPreload(device->timer, ENABLE);

    /* Enable main output for advanced timers (ATIM1-4, GTIMB1-3) */
    if ((IS_ATIM1_4_DEVICE(device->timer)) || ((IS_GTIMB1_3_DEVICE(device->timer))))
    {
        TIM_EnableCtrlPwmOutputs(device->timer, ENABLE);
    }

    /* Enable timer counter */
    TIM_Enable(device->timer, ENABLE);

    LOG_D("%s init success", device->name);

    return result;
}

/**
 * @brief Parse BSP_USING_PWMx_CHy macros to set channel bitmask.
 */
static void n32_pwm_get_channel(void)
{
#ifdef BSP_USING_PWM1_CH1
    n32_pwm_obj[PWM1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM1_CH2
    n32_pwm_obj[PWM1_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM1_CH3
    n32_pwm_obj[PWM1_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM1_CH4
    n32_pwm_obj[PWM1_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM2_CH1
    n32_pwm_obj[PWM2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM2_CH2
    n32_pwm_obj[PWM2_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM2_CH3
    n32_pwm_obj[PWM2_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM2_CH4
    n32_pwm_obj[PWM2_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM3_CH1
    n32_pwm_obj[PWM3_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM3_CH2
    n32_pwm_obj[PWM3_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM3_CH3
    n32_pwm_obj[PWM3_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM3_CH4
    n32_pwm_obj[PWM3_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM4_CH1
    n32_pwm_obj[PWM4_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM4_CH2
    n32_pwm_obj[PWM4_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM4_CH3
    n32_pwm_obj[PWM4_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM4_CH4
    n32_pwm_obj[PWM4_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM5_CH1
    n32_pwm_obj[PWM5_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM5_CH2
    n32_pwm_obj[PWM5_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM5_CH3
    n32_pwm_obj[PWM5_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM5_CH4
    n32_pwm_obj[PWM5_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM6_CH1
    n32_pwm_obj[PWM6_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM6_CH2
    n32_pwm_obj[PWM6_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM6_CH3
    n32_pwm_obj[PWM6_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM6_CH4
    n32_pwm_obj[PWM6_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM7_CH1
    n32_pwm_obj[PWM7_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM7_CH2
    n32_pwm_obj[PWM7_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM7_CH3
    n32_pwm_obj[PWM7_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM7_CH4
    n32_pwm_obj[PWM7_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM8_CH1
    n32_pwm_obj[PWM8_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM8_CH2
    n32_pwm_obj[PWM8_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM8_CH3
    n32_pwm_obj[PWM8_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM8_CH4
    n32_pwm_obj[PWM8_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM9_CH1
    n32_pwm_obj[PWM9_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM9_CH2
    n32_pwm_obj[PWM9_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM9_CH3
    n32_pwm_obj[PWM9_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM9_CH4
    n32_pwm_obj[PWM9_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM10_CH1
    n32_pwm_obj[PWM10_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM10_CH2
    n32_pwm_obj[PWM10_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM10_CH3
    n32_pwm_obj[PWM10_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM10_CH4
    n32_pwm_obj[PWM10_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM11_CH1
    n32_pwm_obj[PWM11_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM11_CH2
    n32_pwm_obj[PWM11_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM11_CH3
    n32_pwm_obj[PWM11_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM11_CH4
    n32_pwm_obj[PWM11_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM12_CH1
    n32_pwm_obj[PWM12_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM12_CH2
    n32_pwm_obj[PWM12_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM12_CH3
    n32_pwm_obj[PWM12_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM12_CH4
    n32_pwm_obj[PWM12_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM13_CH1
    n32_pwm_obj[PWM13_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM13_CH2
    n32_pwm_obj[PWM13_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM13_CH3
    n32_pwm_obj[PWM13_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM13_CH4
    n32_pwm_obj[PWM13_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM14_CH1
    n32_pwm_obj[PWM14_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM14_CH2
    n32_pwm_obj[PWM14_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM14_CH3
    n32_pwm_obj[PWM14_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM14_CH4
    n32_pwm_obj[PWM14_INDEX].channel |= 1 << 3;
#endif
}

static int n32_pwm_init(void)
{
    int i      = 0;
    int result = RT_EOK;

    n32_pwm_get_channel();

    for (i = 0; i < sizeof(n32_pwm_obj) / sizeof(n32_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (n32_hw_pwm_init(&n32_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", n32_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            LOG_D("%s init success", n32_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&n32_pwm_obj[i].pwm_device, n32_pwm_obj[i].name, &drv_ops, &n32_pwm_obj[i]) == RT_EOK)
            {
                LOG_D("%s register success", n32_pwm_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", n32_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(n32_pwm_init);

#endif /* BSP_USING_PWM */
