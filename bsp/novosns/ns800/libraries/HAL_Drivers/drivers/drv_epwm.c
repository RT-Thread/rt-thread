/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-15     Eric    Initial version.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "syscon.h"
#include "drv_epwm.h"

#if defined(BSP_USING_EPWM)

#define DBG_TAG     "drv.epwm"
#define DBG_LVL     DBG_INFO
#include <rtdbg.h>

enum
{
#ifdef BSP_USING_EPWM1
    EPWM1_INDEX,
#endif
#ifdef BSP_USING_EPWM2
    EPWM2_INDEX,
#endif
#ifdef BSP_USING_EPWM3
    EPWM3_INDEX,
#endif
#ifdef BSP_USING_EPWM4
    EPWM4_INDEX,
#endif
#ifdef BSP_USING_EPWM5
    EPWM5_INDEX,
#endif
#ifdef BSP_USING_EPWM6
    EPWM6_INDEX,
#endif
#ifdef BSP_USING_EPWM7
    EPWM7_INDEX,
#endif
#ifdef BSP_USING_EPWM8
    EPWM8_INDEX,
#endif
#ifdef BSP_USING_EPWM9
    EPWM9_INDEX,
#endif
#ifdef BSP_USING_EPWM10
    EPWM10_INDEX,
#endif
#ifdef BSP_USING_EPWM11
    EPWM11_INDEX,
#endif
#ifdef BSP_USING_EPWM12
    EPWM12_INDEX,
#endif
#ifdef BSP_USING_EPWM13
    EPWM13_INDEX,
#endif
#ifdef BSP_USING_EPWM14
    EPWM14_INDEX,
#endif
#ifdef BSP_USING_EPWM15
    EPWM15_INDEX,
#endif
#ifdef BSP_USING_EPWM16
    EPWM16_INDEX,
#endif
#ifdef BSP_USING_EPWM17
    EPWM17_INDEX,
#endif
#ifdef BSP_USING_EPWM18
    EPWM18_INDEX,
#endif
};

struct ns800_epwm_pin_config
{
    GPIO_TypeDef *port_a;
    GPIO_PinNum pin_a;
    GPIO_AltFunc mux_a;
    GPIO_TypeDef *port_b;
    GPIO_PinNum pin_b;
    GPIO_AltFunc mux_b;
};

struct ns800_epwm_config
{
    const char *name;
    EPWM_TypeDef *instance;
    EPWM_TimeBaseCountMode count_mode;
    EPWM_ClockDivider clock_div;
    EPWM_HSClockDivider hs_clock_div;
};

struct ns800_signal_params
{
    float   signal_freq;        /*!< Desired Signal Frequency(in Hz) */
    float   duty_val;           /*!< Desired ePWMxA/B Signal Duty */
    float   sys_clk_freq;       /*!< SYSCLK Frequency(in Hz) */
    float   dead_band_val;
    rt_bool_t invert_signal_b;
    EPWM_TimeBaseCountMode  count_mode;
    EPWM_ClockDivider clock_div;
    EPWM_HSClockDivider hs_clock_div;
};

struct ns800_epwm
{
    struct rt_device_pwm epwm_device;
    const struct ns800_epwm_pin_config *pin_config;
    const struct ns800_epwm_config *epwm_config;
    rt_uint32_t current_period;
    rt_uint32_t current_pulse;
};

static const struct ns800_epwm_pin_config epwm_pins[] =
{
#ifdef BSP_USING_EPWM1
    [EPWM1_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_0, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_1, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM2
    [EPWM2_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_2, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_3, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM3
    [EPWM3_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_4, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_5, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM4
    [EPWM4_INDEX] = EPWM_PIN_INFO(GPIOB, GPIO_PIN_14, ALT1_FUNCTION,
                                GPIOB, GPIO_PIN_15, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM5
    [EPWM5_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_8, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_9, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM6
    [EPWM6_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_10, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_11, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM7
    [EPWM7_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_12, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_13, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM8
    [EPWM8_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_14, ALT1_FUNCTION,
                                GPIOA, GPIO_PIN_15, ALT1_FUNCTION),
#endif
#ifdef BSP_USING_EPWM9
    [EPWM9_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_16, ALT5_FUNCTION,
                                GPIOA, GPIO_PIN_17, ALT5_FUNCTION),
#endif
#ifdef BSP_USING_EPWM10
    [EPWM10_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_18, ALT5_FUNCTION,
                                GPIOA, GPIO_PIN_19, ALT5_FUNCTION),
#endif
#ifdef BSP_USING_EPWM11
    [EPWM11_INDEX] = EPWM_PIN_INFO(GPIOA, GPIO_PIN_20, ALT5_FUNCTION,
                                GPIOA, GPIO_PIN_21, ALT5_FUNCTION),
#endif
#ifdef BSP_USING_EPWM12 /*failed*/
    [EPWM12_INDEX] = EPWM_PIN_INFO(GPIOF, GPIO_PIN_12, ALT5_FUNCTION,
                                GPIOA, GPIO_PIN_23, ALT5_FUNCTION),
#endif
#ifdef BSP_USING_EPWM13
    [EPWM13_INDEX] = EPWM_PIN_INFO(GPIOF, GPIO_PIN_14, ALT13_FUNCTION,
                                GPIOF, GPIO_PIN_15, ALT13_FUNCTION),
#endif
#ifdef BSP_USING_EPWM14
    [EPWM14_INDEX] = EPWM_PIN_INFO(GPIOF, GPIO_PIN_16, ALT13_FUNCTION,
                                GPIOF, GPIO_PIN_17, ALT13_FUNCTION),
#endif
#ifdef BSP_USING_EPWM15
    [EPWM15_INDEX] = EPWM_PIN_INFO(GPIOF, GPIO_PIN_18, ALT13_FUNCTION,
                                GPIOF, GPIO_PIN_19, ALT13_FUNCTION),
#endif
#ifdef BSP_USING_EPWM16
    [EPWM16_INDEX] = EPWM_PIN_INFO(GPIOF, GPIO_PIN_20, ALT13_FUNCTION,
                                GPIOB, GPIO_PIN_23, ALT3_FUNCTION),
#endif
#ifdef BSP_USING_EPWM17
    [EPWM17_INDEX] = EPWM_PIN_INFO(GPIOB, GPIO_PIN_24, ALT3_FUNCTION,
                                GPIOB, GPIO_PIN_25, ALT3_FUNCTION),
#endif
#ifdef BSP_USING_EPWM18
    [EPWM18_INDEX] = EPWM_PIN_INFO(GPIOD, GPIO_PIN_8, ALT2_FUNCTION,
                                GPIOD, GPIO_PIN_9, ALT2_FUNCTION),
#endif
};

static const struct ns800_epwm_config epwm_conf[] =
{
#ifdef BSP_USING_EPWM1
    [EPWM1_INDEX] = EPWM_DRV_INIT(1, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM2
    [EPWM2_INDEX] = EPWM_DRV_INIT(2, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM3
    [EPWM3_INDEX] = EPWM_DRV_INIT(3, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM4
    [EPWM4_INDEX] = EPWM_DRV_INIT(4, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM5
    [EPWM5_INDEX] = EPWM_DRV_INIT(5, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM6
    [EPWM6_INDEX] = EPWM_DRV_INIT(6, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM7
    [EPWM7_INDEX] = EPWM_DRV_INIT(7, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM8
    [EPWM8_INDEX] = EPWM_DRV_INIT(8, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM9
    [EPWM9_INDEX] = EPWM_DRV_INIT(9, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM10
    [EPWM10_INDEX] = EPWM_DRV_INIT(10, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM11
    [EPWM11_INDEX] = EPWM_DRV_INIT(11, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM12
    [EPWM12_INDEX] = EPWM_DRV_INIT(12, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM13
    [EPWM13_INDEX] = EPWM_DRV_INIT(13, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM14
    [EPWM14_INDEX] = EPWM_DRV_INIT(14, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM15
    [EPWM15_INDEX] = EPWM_DRV_INIT(15, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM16
    [EPWM16_INDEX] = EPWM_DRV_INIT(16, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM17
    [EPWM17_INDEX] = EPWM_DRV_INIT(17, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
#ifdef BSP_USING_EPWM18
    [EPWM18_INDEX] = EPWM_DRV_INIT(18, EPWM_COUNTER_MODE_UP_DOWN,
                        EPWM_CLOCK_DIVIDER_2, EPWM_HSCLOCK_DIVIDER_1),
#endif
};

static struct ns800_epwm ns800_epwm_obj[sizeof(epwm_conf) / sizeof(epwm_conf[0])];

static void ns800_epwm_gpio_init(const struct ns800_epwm_pin_config *pin_config)
{
    GPIO_setAnalogMode(pin_config->port_a, pin_config->pin_a, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(pin_config->port_a, pin_config->pin_a, pin_config->mux_a);
    GPIO_setPadConfig(pin_config->port_a, pin_config->pin_a, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(pin_config->port_a, pin_config->pin_a, GPIO_QUAL_SYNC);

    GPIO_setAnalogMode(pin_config->port_b, pin_config->pin_b, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(pin_config->port_b, pin_config->pin_b, pin_config->mux_b);
    GPIO_setPadConfig(pin_config->port_b, pin_config->pin_b, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(pin_config->port_b, pin_config->pin_b, GPIO_QUAL_SYNC);
}

static rt_err_t configuration_convert(struct ns800_epwm *device,
                            struct rt_pwm_configuration *rt_conf,
                            struct ns800_signal_params *signal_params)
{
    float deadband_val = 0.0f;
    const struct ns800_epwm_config *epwm_config;

    epwm_config = device->epwm_config;

    if ((EPWMX_A != rt_conf->channel) && (EPWMX_B != rt_conf->channel))
    {
        return -RT_EINVAL;
    }

    if ((rt_conf->pulse > rt_conf->period) || (RT_FALSE == (!!rt_conf->period)))
    {
        return -RT_EINVAL;
    }

    if (epwm_config->count_mode == EPWM_COUNTER_MODE_UP_DOWN)
    {
        signal_params->signal_freq = 1.0f / ((float)rt_conf->period / 1000000.0f);
    }
    else if (epwm_config->count_mode < EPWM_COUNTER_MODE_UP_DOWN)
    {
        signal_params->signal_freq = 1.0f / ((float)rt_conf->period / 1000000.0f) / 2.0f;
    }

    signal_params->duty_val = ((float)rt_conf->pulse / (float)rt_conf->period);
    signal_params->sys_clk_freq = (float)RCC_getPclk1Frequency();
    signal_params->invert_signal_b = (rt_conf->complementary == RT_TRUE);
    signal_params->count_mode = READ_BIT(epwm_config->instance->TBCTL.WORDVAL,
                                        EPWM_TBCTL_CTRMODE_M);
    signal_params->clock_div = epwm_config->clock_div;
    signal_params->hs_clock_div = epwm_config->hs_clock_div;
    signal_params->dead_band_val = 0;

    if (signal_params->hs_clock_div <= EPWM_HSCLOCK_DIVIDER_4)
    {
        deadband_val = (float)rt_conf->dead_time / (10.0f * (float)(1U << (uint16_t)signal_params->hs_clock_div));
        signal_params->dead_band_val = deadband_val;
    }

    return RT_EOK;
}

static void ns800_epwm_hw_init(EPWM_TypeDef *epwm)
{
    EPWM_setClockPrescaler(epwm, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_2);
    EPWM_setTimeBasePeriod(epwm, 0);
    EPWM_setTimeBaseCounter(epwm, 0);
    EPWM_setTimeBaseCounterMode(epwm, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_disablePhaseShiftLoad(epwm);
    EPWM_setPhaseShift(epwm, 0);
    EPWM_setCounterCompareValue(epwm, EPWM_COUNTER_COMPARE_A, 0);
    EPWM_setCounterCompareShadowLoadMode(epwm, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(epwm, EPWM_COUNTER_COMPARE_B, 0);
    EPWM_setCounterCompareShadowLoadMode(epwm, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setRisingEdgeDelayCountShadowLoadMode(epwm, EPWM_RED_LOAD_ON_CNTR_ZERO);
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(epwm);
    EPWM_setFallingEdgeDelayCountShadowLoadMode(epwm, EPWM_FED_LOAD_ON_CNTR_ZERO);
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(epwm);
}

static void ns800_epwm_configure_signal(rt_int32_t channel, EPWM_TypeDef *epwm, const struct ns800_signal_params *signal_params)
{
    float time_base_clock = 0.0F;
    uint16_t time_base_period = 0U, cmp_val = 0U;

    EPWM_setClockPrescaler(epwm, signal_params->clock_div, signal_params->hs_clock_div);
    EPWM_setTimeBaseCounterMode(epwm, signal_params->count_mode);

    time_base_clock = ((float)signal_params->sys_clk_freq / (float)(1U << (uint16_t)signal_params->clock_div));

    if (signal_params->hs_clock_div <= EPWM_HSCLOCK_DIVIDER_4)
    {
        time_base_clock /= (float)(1U << (uint16_t)signal_params->hs_clock_div);
    }
    else
    {
        time_base_clock /= (float)(2U * (uint16_t)signal_params->hs_clock_div);
    }

    if (signal_params->count_mode == EPWM_COUNTER_MODE_UP)
    {
        time_base_period = (uint16_t)((time_base_clock / signal_params->signal_freq) - 1.0f);
        cmp_val = (uint16_t)(signal_params->duty_val * (float)(time_base_period + 1U));
    }
    else if (signal_params->count_mode == EPWM_COUNTER_MODE_DOWN)
    {
        time_base_period = (uint16_t)((time_base_clock / signal_params->signal_freq) - 1.0f);
        cmp_val = (uint16_t)((float)(time_base_period + 1U) - (signal_params->duty_val * (float)(time_base_period + 1U)));
    }
    else
    {
        time_base_period = (uint16_t)(time_base_clock / (2.0f * signal_params->signal_freq));
        cmp_val = (uint16_t)(((float)time_base_period - ((signal_params->duty_val * (float)time_base_period))) + 0.5f);
    }

    EPWM_setTimeBasePeriod(epwm, time_base_period);
    EPWM_disablePhaseShiftLoad(epwm);
    EPWM_setPhaseShift(epwm, 0U);
    EPWM_setTimeBaseCounter(epwm, 0U);

    if (channel == EPWMX_A)
    {
        EPWM_setCounterCompareShadowLoadMode(epwm, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
        EPWM_setCounterCompareValue(epwm, EPWM_COUNTER_COMPARE_A, cmp_val);
    }
    else if(channel == EPWMX_B)
    {
        EPWM_setCounterCompareShadowLoadMode(epwm, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
        EPWM_setCounterCompareValue(epwm, EPWM_COUNTER_COMPARE_B, cmp_val);
    }

    if (signal_params->count_mode == EPWM_COUNTER_MODE_UP)
    {
        if (channel == EPWMX_A)
        {
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
        }
        else if(channel == EPWMX_B)
        {
            if (signal_params->invert_signal_b == RT_TRUE)
            {
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
            }
            else
            {
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
            }
        }
    }
    else if ((signal_params->count_mode == EPWM_COUNTER_MODE_DOWN))
    {
        if (channel == EPWMX_A)
        {
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
        }
        else if(channel == EPWMX_B)
        {
            if (signal_params->invert_signal_b == RT_TRUE)
            {
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
            }
            else
            {
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
            }
        }
    }
    else // UP_DOWN 对称模式
    {
        if (channel == EPWMX_A)
        {
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
        }
        else if(channel == EPWMX_B)
        {
            if (signal_params->invert_signal_b == RT_TRUE)
            {
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
            }
            else
            {
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
                EPWM_setActionQualifierAction(epwm, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
            }
        }
    }

    EPWM_setDeadBandDelayPolarity(epwm, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayPolarity(epwm, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    EPWM_setDeadBandDelayMode(epwm, EPWM_DB_RED, RT_TRUE);
    EPWM_setRisingEdgeDelayCountShadowLoadMode(epwm, EPWM_RED_LOAD_ON_CNTR_ZERO);
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(epwm);
    EPWM_setRisingEdgeDelayCount(epwm, (uint16_t)signal_params->dead_band_val);

    EPWM_setDeadBandDelayMode(epwm, EPWM_DB_FED, RT_TRUE);
    EPWM_setFallingEdgeDelayCountShadowLoadMode(epwm, EPWM_FED_LOAD_ON_CNTR_ZERO);
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(epwm);
    EPWM_setFallingEdgeDelayCount(epwm, (uint16_t)signal_params->dead_band_val);
}

static rt_err_t ns800_epwm_drv_set(struct ns800_epwm *device, struct rt_pwm_configuration *rt_conf)
{
    rt_err_t ret;
    struct ns800_signal_params signal_params;

    RT_ASSERT(RT_NULL != device);
    RT_ASSERT(RT_NULL != device->epwm_config);
    RT_ASSERT(RT_NULL != rt_conf);

    ret = configuration_convert(device, rt_conf, &signal_params);
    if (ret != RT_EOK)
    {
        return ret;
    }

    device->current_period = rt_conf->period;
    device->current_pulse = rt_conf->pulse;

    ns800_epwm_configure_signal(rt_conf->channel, device->epwm_config->instance, &signal_params);

    return ret;
}

static rt_err_t ns800_epwm_drv_get(struct ns800_epwm *device, struct rt_pwm_configuration *rt_conf)
{
    RT_ASSERT(RT_NULL != device);
    RT_ASSERT(RT_NULL != rt_conf);

    rt_conf->period = device->current_period;
    rt_conf->pulse = device->current_pulse;

    return RT_EOK;
}

/**
 *  @brief  Configure EPWM slave sync phase offset
 *  @param  epwm_slave   EPWM device pointer to a rt_epwm_slave_phase_ext structure
 *  @param  ext          Extended slave phase config parameter
 *  @return RT_EOK for success or error number
 */
static rt_err_t ns800_epwm_set_slave_phase(struct ns800_epwm *epwm_slave,
                                struct rt_epwm_slave_phase_ext *ext)
{
    struct ns800_epwm *epwm_master = RT_NULL;
    struct rt_device_pwm *master_dev = RT_NULL;
    EPWM_TypeDef *master_base = RT_NULL;
    EPWM_TypeDef *slave_base = RT_NULL;
    rt_uint32_t period_val = 0, phase_val = 0;

    RT_ASSERT(RT_NULL != epwm_slave);
    RT_ASSERT(RT_NULL != ext);
    RT_ASSERT(RT_NULL != ext->master_dev);

    if (ext->phase_angle > 360)
    {
        return -RT_EINVAL;
    }

    master_dev = (struct rt_device_pwm *)(ext->master_dev);
    epwm_master = rt_container_of(master_dev, struct ns800_epwm, epwm_device);
    master_base = epwm_master->epwm_config->instance;
    slave_base = epwm_slave->epwm_config->instance;

    /* Read Period value to calculate value for Phase Register */
    period_val = EPWM_getTimeBasePeriod(master_base);
    /* Caluclate phase register values based on Time Base counter mode */
    if (slave_base->TBCTL.BIT.CTRMODE == EPWM_COUNTER_MODE_UP_DOWN)
    {
        phase_val = (2U * period_val * ext->phase_angle) / 360U;
    }
    else if (slave_base->TBCTL.BIT.CTRMODE < EPWM_COUNTER_MODE_UP_DOWN)
    {
        phase_val = (period_val * ext->phase_angle) / 360U;
    }

    EPWM_selectPeriodLoadEvent(slave_base, EPWM_SHADOW_LOAD_MODE_SYNC);
    EPWM_disablePhaseShiftLoad(slave_base);
    EPWM_setPhaseShift(slave_base, phase_val);
    EPWM_enablePhaseShiftLoad(slave_base);
    EPWM_setTimeBaseCounter(slave_base, phase_val);

    return RT_EOK;
}

static rt_err_t ns800_epwm_drv_enable(struct ns800_epwm *device)
{
    const struct ns800_epwm_config *epwm_config = device->epwm_config;
    EPWM_setTimeBaseCounterMode(epwm_config->instance, epwm_config->count_mode);
    return RT_EOK;
}

static rt_err_t ns800_epwm_drv_disable(struct ns800_epwm *device)
{
    const struct ns800_epwm_config *epwm_config = device->epwm_config;
    EPWM_setTimeBaseCounterMode(epwm_config->instance, EPWM_COUNTER_MODE_STOP_FREEZE);
    return RT_EOK;
}

static rt_err_t ns800_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *conf = RT_NULL;
    struct rt_epwm_slave_phase_ext *epwm_slave = RT_NULL;
    struct ns800_epwm *epwm = RT_NULL;
    rt_err_t ret = RT_EOK;

    epwm = rt_container_of(device, struct ns800_epwm, epwm_device);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        ret = ns800_epwm_drv_enable(epwm);
        break;
    case PWM_CMD_DISABLE:
        ret = ns800_epwm_drv_disable(epwm);
        break;
    case PWM_CMD_SET:
        conf = (struct rt_pwm_configuration *)arg;
        ret = ns800_epwm_drv_set(epwm, conf);
        break;
    case PWM_CMD_GET:
        conf = (struct rt_pwm_configuration *)arg;
        ret = ns800_epwm_drv_get(epwm, conf);
        break;
    case PWM_CMD_EXT_SET_SLAVE_PHASE:
        epwm_slave = (struct rt_epwm_slave_phase_ext *)arg;
        ret = ns800_epwm_set_slave_phase(epwm, epwm_slave);
        break;
    default:
        ret = -RT_EINVAL;
        break;
    }

    return ret;
}

static const struct rt_pwm_ops drv_ops =
{
    ns800_drv_pwm_control
};

int ns800_epwm_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t i;
    struct ns800_epwm *device = RT_NULL;

    SYSCON_UNLOCK;
    SYSCON_setTbClkSync(SYSCON, false);
    SYSCON_LOCK;

    for (i = 0; i < (sizeof(epwm_conf) / sizeof(epwm_conf[0])); i++)
    {
        device = &ns800_epwm_obj[i];
        device->pin_config = &epwm_pins[i];
        device->epwm_config = &epwm_conf[i];
        device->current_period = 0;
        device->current_pulse = 0;

        ns800_epwm_gpio_init(device->pin_config);
        ns800_epwm_hw_init(device->epwm_config->instance);

        result = rt_device_pwm_register(&ns800_epwm_obj[i].epwm_device,
                                        epwm_conf[i].name,
                                        &drv_ops,
                                        &ns800_epwm_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    SYSCON_UNLOCK;
    SYSCON_setTbClkSync(SYSCON, true);
    SYSCON_LOCK;

    return result;
}
INIT_DEVICE_EXPORT(ns800_epwm_init);

#endif  /* #if defined(BSP_USING_EPWM) */