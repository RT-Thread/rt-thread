/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-30     NinoC137     add NS800 ADC driver
 */

#include "drv_adc.h"
#include <rtthread.h>

#include "interrupt.h"

#ifdef BSP_USING_ADC

#define DBG_TAG    "drv.adc"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

extern void Delay_us(uint32_t us);

#define NS800_ADC_RESOLUTION_BITS  12U
#define NS800_ADC_VREF_MV          3300U
#define NS800_ADC_SAMPLE_WINDOW    8U
#define NS800_ADC_PPB_SAMPLE_MAX   1024U
#define NS800_ADC_PPB_SHIFT_MAX    10U
#define NS800_ADC_BUSY_TIMEOUT     1000000U

#define NS800_ADC_PPB_REP_INSTANCE        ADC_REPINST1
#define NS800_ADC_PPB_REP_SOC_TRIGGER     ADC_TRIGGER_REP1_TRIG
#define NS800_ADC_PPB_REP_SOURCE_TRIGGER  ADC_TRIGGER_SW_ONLY
#define NS800_ADC_PPB_REP_SPREAD          32U
#define NS800_ADC_DEFAULT_PPB_SAMPLES     8U

enum ns800_adc_mode
{
    NS800_ADC_MODE_NORMAL = 0,
    NS800_ADC_MODE_PPB,
    NS800_ADC_MODE_IRQ,
};

struct ns800_adc_ppb_bind
{
    rt_uint32_t ppb;
    rt_uint32_t soc;
};

struct ns800_adc_ppb_config
{
    struct ns800_adc_ppb_bind bind;
    rt_uint32_t high_limit;
    rt_uint32_t low_limit;
    rt_uint32_t event_mask;
    rt_bool_t event_irq;
};

struct ns800_adc_ppb_oversampling_result
{
    rt_uint32_t count;
    rt_int32_t sum;
    rt_int32_t min;
    rt_int32_t max;
    rt_uint32_t min_index;
    rt_uint32_t max_index;
    rt_int32_t average;
    rt_int32_t trimmed_average;
    rt_int32_t value;
};

struct ns800_adc_ppb_oversampling_config
{
    struct ns800_adc_ppb_bind bind;
    rt_uint32_t adc_channel;
    rt_uint32_t sample_count;
    rt_uint32_t sample_window;
    rt_uint32_t shift;
    rt_bool_t drop_min_max;
    rt_bool_t enable_osint_irq;
};

struct ns800_adc_pin_config
{
    GPIO_TypeDef *port;
    GPIO_PinNum pin;
    GPIO_AltFunc mux;
};

struct ns800_adc_config
{
    const char *name;
    ADC_TypeDef *instance;
    ADCRESULT_TypeDef *result;
    IRQn_Type conv_irq;
    ADC_ClkPrescale clock_prescaler;
    rt_uint8_t resolution_bits;
    ADC_PulsePosMode eoc_pulse_pos;
    ADC_Trigger trigger;
    rt_bool_t continuous;
};

#if defined(RTTHREAD_VERSION) && defined(RT_VERSION_CHECK) && (RTTHREAD_VERSION < RT_VERSION_CHECK(5, 0, 0))
    typedef rt_uint32_t ns800_adc_channel_t;
#else
    typedef rt_int8_t ns800_adc_channel_t;
#endif

struct ns800_adc
{
    struct rt_adc_device device;
    const struct ns800_adc_config *config;
    const struct ns800_adc_pin_config *pins;
    rt_uint32_t pin_count;
    rt_uint32_t enabled_mask;
    enum ns800_adc_mode mode;
    rt_uint32_t active_channel;
};

struct ns800_adc_irq_entry
{
    ns800_adc_irq_callback_t callback;
    void *user_data;
};

/*
    根据实际情况来进行相关的GPIO配置
    默认使能GPIO H端口的数个IO口
*/
static const struct ns800_adc_pin_config adc_pins[] =
{
    {GPIOH, GPIO_PIN_0, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_1, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_2, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_3, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_4, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_5, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_6, ALT0_FUNCTION},
    {GPIOH, GPIO_PIN_7, ALT0_FUNCTION},
};

static const struct ns800_adc_config adc_config[] =
{
#ifdef BSP_USING_ADC
    {
        .name = "adc0",
        .instance = ADCA,
        .result = ADCARESULT,
        .conv_irq = ADCA_CONV_IRQn,
        .clock_prescaler = ADC_CLK_DIV_4,
        .resolution_bits = NS800_ADC_RESOLUTION_BITS,
        .eoc_pulse_pos = ADC_PULSE_END_OF_CONV,
        .trigger = ADC_TRIGGER_SW_ONLY,
        .continuous = RT_FALSE,
    },
#endif
};

static struct ns800_adc adc_obj =
{
    .config = &adc_config[0],
    .pins = adc_pins,
    .pin_count = sizeof(adc_pins) / sizeof(adc_pins[0]),
};

static rt_bool_t adc_inited = RT_FALSE;
static struct ns800_adc_irq_entry adc_irq_entries[NS800_ADC_INT_MAX];

static rt_err_t ns800_adc_hw_init(struct ns800_adc *adc)
{
    RT_ASSERT(adc != RT_NULL);
    RT_ASSERT(adc->config != RT_NULL);

    if (adc_inited == RT_TRUE)
    {
        return RT_EOK;
    }

    ADC_setVREF(adc->config->instance, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    ADC_setPrescaler(adc->config->instance, adc->config->clock_prescaler);
    ADC_setInterruptPulsePosMode(adc->config->instance, adc->config->eoc_pulse_pos);
    ADC_enableConverter(adc->config->instance);

    ADC_disableBurstMode(adc->config->instance);
    ADC_setSOCPriority(adc->config->instance, ADC_PRI_ALL_ROUND_ROBIN);
    if (adc->config->continuous == RT_TRUE)
    {
        ADC_enableContinuousMode(adc->config->instance, ADC_INT_NUMBER1);
    }
    else
    {
        ADC_disableContinuousMode(adc->config->instance, ADC_INT_NUMBER1);
    }
    ADC_disableInterrupt(adc->config->instance, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(adc->config->instance, ADC_INT_NUMBER1);
    ADC_clearInterruptOverflowStatus(adc->config->instance, ADC_INT_NUMBER1);

    adc_inited = RT_TRUE;
    return RT_EOK;
}

static void ns800_adc_gpio_init(const struct ns800_adc *adc)
{
    rt_uint32_t index;

    RT_ASSERT(adc != RT_NULL);

    for (index = 0U; index < adc->pin_count; index++)
    {
        GPIO_setPinConfig(adc->pins[index].port,
                          adc->pins[index].pin,
                          adc->pins[index].mux);
        GPIO_setAnalogMode(adc->pins[index].port,
                           adc->pins[index].pin,
                           GPIO_ANALOG_ENABLED);
        GPIO_setPadConfig(adc->pins[index].port,
                          adc->pins[index].pin,
                          GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(adc->pins[index].port,
                                  adc->pins[index].pin,
                                  GPIO_QUAL_ASYNC);
        GPIO_setDirectionMode(adc->pins[index].port,
                              adc->pins[index].pin,
                              GPIO_DIR_MODE_IN);
    }
}

static rt_bool_t ns800_adc_valid_soc(rt_uint32_t soc)
{
    return (soc < NS800_ADC_SOC_MAX) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t ns800_adc_valid_int(rt_uint32_t int_no)
{
    return (int_no < NS800_ADC_INT_MAX) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t ns800_adc_valid_ppb(rt_uint32_t ppb)
{
    return (ppb < NS800_ADC_PPB_MAX) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t ns800_adc_valid_channel(rt_uint32_t channel)
{
    return (channel < NS800_ADC_CHANNEL_MAX) ? RT_TRUE : RT_FALSE;
}

static void ns800_adc_clear(struct ns800_adc *adc, ADC_IntNumber int_no)
{
    ADC_clearInterruptStatus(adc->config->instance, int_no);
    if (ADC_getInterruptOverflowStatus(adc->config->instance, int_no) != 0U)
    {
        ADC_clearInterruptOverflowStatus(adc->config->instance, int_no);
        ADC_clearInterruptStatus(adc->config->instance, int_no);
    }
}

static rt_bool_t ns800_adc_get_channel(ns800_adc_channel_t channel, rt_uint32_t *adc_channel)
{
    RT_ASSERT(adc_channel != RT_NULL);

#if defined(RTTHREAD_VERSION) && defined(RT_VERSION_CHECK) && (RTTHREAD_VERSION < RT_VERSION_CHECK(5, 0, 0))
    *adc_channel = channel;
#else
    if (channel < 0)
    {
        return RT_FALSE;
    }
    *adc_channel = (rt_uint32_t)channel;
#endif

    return ns800_adc_valid_channel(*adc_channel);
}

static rt_err_t ns800_adc_wait_done(struct ns800_adc *adc)
{
    rt_tick_t timeout;
    rt_tick_t start_tick;

    timeout = rt_tick_from_millisecond(50);
    if (timeout == 0)
    {
        timeout = 1;
    }

    start_tick = rt_tick_get();
    while (ADC_getInterruptStatus(adc->config->instance, ADC_INT_NUMBER1) == 0U)
    {
        if ((rt_tick_get() - start_tick) > timeout)
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static void ns800_adc_setup_soc(struct ns800_adc *adc,
                                rt_uint32_t soc,
                                rt_uint32_t channel,
                                ADC_Trigger trigger,
                                rt_uint32_t sample_window)
{
    ADC_setupSOC(adc->config->instance,
                 (ADC_SOCNumber)soc,
                 trigger,
                 (ADC_Channel)channel,
                 sample_window);
    ADC_setInterruptSOCTrigger(adc->config->instance,
                               (ADC_SOCNumber)soc,
                               ADC_INT_SOC_TRIGGER_NONE);
}

static rt_err_t ns800_adc_config_sw_soc(struct ns800_adc *adc, rt_uint32_t channel)
{
    ADC_SOCNumber soc;

    RT_ASSERT(adc != RT_NULL);

    if (ns800_adc_valid_channel(channel) == RT_FALSE)
    {
        return -RT_EINVAL;
    }

    soc = (ADC_SOCNumber)channel;
    ns800_adc_setup_soc(adc, channel, channel, adc->config->trigger, NS800_ADC_SAMPLE_WINDOW);
    ADC_setInterruptSource(adc->config->instance, ADC_INT_NUMBER1, soc);
    if (adc->config->continuous == RT_TRUE)
    {
        ADC_enableContinuousMode(adc->config->instance, ADC_INT_NUMBER1);
    }
    else
    {
        ADC_disableContinuousMode(adc->config->instance, ADC_INT_NUMBER1);
    }
    ADC_enableInterrupt(adc->config->instance, ADC_INT_NUMBER1);

    return RT_EOK;
}

static void ns800_adc_conv_irq_handler(void)
{
    rt_uint32_t index;

    rt_interrupt_enter();
    for (index = 0U; index < NS800_ADC_INT_MAX; index++)
    {
        if (ADC_getInterruptStatus(adc_obj.config->instance, (ADC_IntNumber)index) != 0U)
        {
            ns800_adc_clear(&adc_obj, (ADC_IntNumber)index);
            if (adc_irq_entries[index].callback != RT_NULL)
            {
                adc_irq_entries[index].callback(adc_irq_entries[index].user_data);
            }
        }
    }
    rt_interrupt_leave();
}

static rt_err_t ns800_adc_irq_attach(rt_uint32_t int_no,
                                     rt_uint32_t eoc_soc,
                                     ns800_adc_irq_callback_t callback,
                                     void *user_data)
{
    if ((ns800_adc_valid_int(int_no) == RT_FALSE) ||
            (ns800_adc_valid_soc(eoc_soc) == RT_FALSE) ||
            (callback == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (ns800_adc_hw_init(&adc_obj) != RT_EOK)
    {
        return -RT_ERROR;
    }

    adc_irq_entries[int_no].callback = callback;
    adc_irq_entries[int_no].user_data = user_data;

    ADC_setInterruptSource(adc_obj.config->instance, (ADC_IntNumber)int_no, (ADC_SOCNumber)eoc_soc);
    ns800_adc_clear(&adc_obj, (ADC_IntNumber)int_no);
    if (adc_obj.config->continuous == RT_TRUE)
    {
        ADC_enableContinuousMode(adc_obj.config->instance, (ADC_IntNumber)int_no);
    }
    else
    {
        ADC_disableContinuousMode(adc_obj.config->instance, (ADC_IntNumber)int_no);
    }
    ADC_enableInterrupt(adc_obj.config->instance, (ADC_IntNumber)int_no);

    Interrupt_register(adc_obj.config->conv_irq, ns800_adc_conv_irq_handler);
    NVIC_ClearPendingIRQ(adc_obj.config->conv_irq);
    Interrupt_enable(adc_obj.config->conv_irq);

    return RT_EOK;
}

static rt_err_t ns800_adc_irq_detach(rt_uint32_t int_no)
{
    if (ns800_adc_valid_int(int_no) == RT_FALSE)
    {
        return -RT_EINVAL;
    }

    ADC_disableInterrupt(adc_obj.config->instance, (ADC_IntNumber)int_no);
    ns800_adc_clear(&adc_obj, (ADC_IntNumber)int_no);
    adc_irq_entries[int_no].callback = RT_NULL;
    adc_irq_entries[int_no].user_data = RT_NULL;
    Interrupt_disable(adc_obj.config->conv_irq);
    NVIC_ClearPendingIRQ(adc_obj.config->conv_irq);

    return RT_EOK;
}

static rt_bool_t ns800_adc_ppb_is_power_of_two(rt_uint32_t value)
{
    return ((value != 0U) && ((value & (value - 1U)) == 0U)) ? RT_TRUE : RT_FALSE;
}

static rt_uint32_t ns800_adc_ppb_log2(rt_uint32_t value)
{
    rt_uint32_t shift = 0U;

    while (value > 1U)
    {
        value >>= 1U;
        shift++;
    }

    return shift;
}

static rt_uint32_t ns800_adc_ppb_effective_shift(const struct ns800_adc_ppb_oversampling_config *config)
{
    if ((config->shift == 0U) && (ns800_adc_ppb_is_power_of_two(config->sample_count) == RT_TRUE))
    {
        return ns800_adc_ppb_log2(config->sample_count);
    }

    return config->shift;
}

static rt_err_t ns800_adc_wait_repeater_idle(void)
{
    rt_uint32_t timeout = NS800_ADC_BUSY_TIMEOUT;

    while (((adc_obj.config->instance->REP1CTL.WORDVAL & ADC_REP1CTL_MODULEBUSY_M) != 0U) && (timeout > 0U))
    {
        timeout--;
    }

    return (timeout > 0U) ? RT_EOK : -RT_ETIMEOUT;
}

static void ns800_adc_ppb_repeater_clear_overflow(void)
{
    SET_BIT(adc_obj.config->instance->REP1CTL.WORDVAL, ADC_REP1CTL_PHASEOVF_M | ADC_REP1CTL_TRIGGEROVF_M);
}

static rt_err_t ns800_adc_wait_not_busy(void)
{
    rt_uint32_t timeout = NS800_ADC_BUSY_TIMEOUT;

    while ((ADC_isBusy(adc_obj.config->instance) != 0U) && (timeout > 0U))
    {
        timeout--;
    }

    return (timeout > 0U) ? RT_EOK : -RT_ETIMEOUT;
}

static rt_err_t ns800_adc_ppb_repeater_reset(rt_uint32_t ppb)
{
    ADC_triggerRepeaterCount(adc_obj.config->instance, NS800_ADC_PPB_REP_INSTANCE, 0U);
    ADC_forceRepeaterTriggerSync(adc_obj.config->instance, NS800_ADC_PPB_REP_INSTANCE);

    if (ns800_adc_wait_repeater_idle() != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    ADC_forcePPBSync(adc_obj.config->instance, (ADC_PPBNumber)ppb);
    ns800_adc_ppb_repeater_clear_overflow();
    return RT_EOK;
}

static rt_err_t ns800_adc_ppb_configure(const struct ns800_adc_ppb_config *config)
{
    rt_uint32_t event_mask;

    if ((config == RT_NULL) ||
            (ns800_adc_valid_ppb(config->bind.ppb) == RT_FALSE) ||
            (ns800_adc_valid_soc(config->bind.soc) == RT_FALSE))
    {
        return -RT_EINVAL;
    }

    if (ns800_adc_hw_init(&adc_obj) != RT_EOK)
    {
        return -RT_ERROR;
    }

    event_mask = config->event_mask & NS800_ADC_PPB_EVT_ALL;
    ADC_setupPPB(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, (ADC_SOCNumber)config->bind.soc);
    ADC_disablePPBEvent(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, NS800_ADC_PPB_EVT_ALL);
    ADC_disablePPBEventInterrupt(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, NS800_ADC_PPB_EVT_ALL);
    ADC_setPPBCalibrationOffset(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, 0U);
    ADC_setPPBReferenceOffset(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, 0U);
    ADC_disablePPBTwosComplement(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb);
    ADC_setPPBTripLimits(adc_obj.config->instance,
                         (ADC_PPBNumber)config->bind.ppb,
                         ADC_PPB_PosSyb,
                         config->high_limit,
                         config->low_limit);
    ADC_disablePPBEventCBCClear(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb);
    ADC_clearPPBEventStatus(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, NS800_ADC_PPB_EVT_ALL);

    if (event_mask != 0U)
    {
        ADC_enablePPBEvent(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, event_mask);
        if (config->event_irq == RT_TRUE)
        {
            ADC_enablePPBEventInterrupt(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, event_mask);
        }
    }

    return RT_EOK;
}

static rt_err_t ns800_adc_ppb_oversampling_config(const struct ns800_adc_ppb_oversampling_config *config)
{
    struct ns800_adc_ppb_config ppb_config;
    ADC_RepeaterConfig rep_config;
    rt_uint32_t sample_window;
    rt_uint32_t shift;

    if ((config == RT_NULL) ||
            (ns800_adc_valid_ppb(config->bind.ppb) == RT_FALSE) ||
            (ns800_adc_valid_soc(config->bind.soc) == RT_FALSE) ||
            (ns800_adc_valid_channel(config->adc_channel) == RT_FALSE) ||
            (config->sample_count == 0U) ||
            (config->sample_count > NS800_ADC_PPB_SAMPLE_MAX) ||
            (config->shift > NS800_ADC_PPB_SHIFT_MAX))
    {
        return -RT_EINVAL;
    }

    if (ns800_adc_hw_init(&adc_obj) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (ns800_adc_ppb_repeater_reset(config->bind.ppb) != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    sample_window = (config->sample_window == 0U) ? NS800_ADC_SAMPLE_WINDOW : config->sample_window;
    ns800_adc_setup_soc(&adc_obj,
                        config->bind.soc,
                        config->adc_channel,
                        NS800_ADC_PPB_REP_SOC_TRIGGER,
                        sample_window);

    rt_memset(&ppb_config, 0, sizeof(ppb_config));
    ppb_config.bind = config->bind;
    ppb_config.high_limit = 0x0fffU;
    ppb_config.low_limit = 0U;
    ppb_config.event_mask = NS800_ADC_PPB_EVT_ALL;
    ppb_config.event_irq = config->enable_osint_irq;
    if (ns800_adc_ppb_configure(&ppb_config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    rt_memset(&rep_config, 0, sizeof(rep_config));
    rep_config.repMode = ADC_REPMODE_OVERSAMPLING;
    rep_config.repTrigger = NS800_ADC_PPB_REP_SOURCE_TRIGGER;
    rep_config.repSyncin = ADC_SYNCIN_DISABLE;
    rep_config.repCount = (uint16_t)config->sample_count;
    rep_config.repPhase = 0U;
    rep_config.repSpread = NS800_ADC_PPB_REP_SPREAD;
    ADC_configureRepeater(adc_obj.config->instance, NS800_ADC_PPB_REP_INSTANCE, &rep_config);

    ADC_setPPBCountLimit(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, (uint16_t)config->sample_count);
    ADC_selectPPBCompareSource(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, ADC_PPB_COMPSOURCE_RESULT);
    ADC_selectPPBOSINTSource(adc_obj.config->instance,
                             (ADC_PPBNumber)config->bind.ppb,
                             config->enable_osint_irq ? ADC_PPB_OS_INT_2 : ADC_PPB_OS_INT_1);

    shift = ns800_adc_ppb_effective_shift(config);
    ADC_setPPBShiftValue(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, (uint16_t)shift);
    ADC_selectPPBSyncInput(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb, ADC_SYNCIN_DISABLE);

    ADC_forceRepeaterTriggerSync(adc_obj.config->instance, NS800_ADC_PPB_REP_INSTANCE);
    if (ns800_adc_wait_repeater_idle() != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    ADC_forcePPBSync(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb);
    return RT_EOK;
}

static rt_err_t ns800_adc_ppb_oversampling_start(const struct ns800_adc_ppb_oversampling_config *config,
        struct ns800_adc_ppb_oversampling_result *result)
{
    rt_uint32_t shift;
    rt_int32_t scaled_sum;

    if ((config == RT_NULL) || (result == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (ns800_adc_ppb_oversampling_config(config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    rt_memset(result, 0, sizeof(*result));
    ns800_adc_ppb_repeater_clear_overflow();
    ADC_forceRepeaterTrigger(adc_obj.config->instance, NS800_ADC_PPB_REP_INSTANCE);
    if (ns800_adc_wait_not_busy() != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    result->count = ADC_readPPBCount(adc_obj.config->result, (ADC_PPBNumber)config->bind.ppb);
    result->sum = ADC_readPPBSum(adc_obj.config->result, (ADC_PPBNumber)config->bind.ppb);
    result->min = ADC_readPPBMin(adc_obj.config->result, (ADC_PPBNumber)config->bind.ppb);
    result->max = ADC_readPPBMax(adc_obj.config->result, (ADC_PPBNumber)config->bind.ppb);
    result->min_index = ADC_readPPBMinIndex(adc_obj.config->result, (ADC_PPBNumber)config->bind.ppb);
    result->max_index = ADC_readPPBMaxIndex(adc_obj.config->result, (ADC_PPBNumber)config->bind.ppb);

    shift = ns800_adc_ppb_effective_shift(config);
    scaled_sum = result->sum * (rt_int32_t)(1UL << shift);
    if (result->count > 0U)
    {
        if ((shift > 0U) && ((1UL << shift) == result->count))
        {
            result->average = result->sum;
        }
        else
        {
            result->average = scaled_sum / (rt_int32_t)result->count;
        }
    }

    if ((config->drop_min_max == RT_TRUE) && (shift == 0U) && (result->count > 2U))
    {
        result->trimmed_average = (scaled_sum - result->min - result->max) / (rt_int32_t)(result->count - 2U);
        result->value = result->trimmed_average;
    }
    else
    {
        result->trimmed_average = result->average;
        result->value = result->average;
    }

    ADC_forcePPBSync(adc_obj.config->instance, (ADC_PPBNumber)config->bind.ppb);
    return RT_EOK;
}

static rt_err_t ns800_adc_enabled(struct rt_adc_device *device, ns800_adc_channel_t channel, rt_bool_t enabled)
{
    struct ns800_adc *adc;
    rt_uint32_t channel_bit;
    rt_uint32_t adc_channel;

    RT_ASSERT(device != RT_NULL);

    adc = (struct ns800_adc *)device->parent.user_data;
    RT_ASSERT(adc != RT_NULL);

    if (ns800_adc_get_channel(channel, &adc_channel) == RT_FALSE)
    {
        return -RT_EINVAL;
    }

    if (ns800_adc_hw_init(adc) != RT_EOK)
    {
        return -RT_ERROR;
    }

    channel_bit = 1UL << adc_channel;
    if (enabled == RT_TRUE)
    {
        adc->enabled_mask |= channel_bit;
        adc->active_channel = adc_channel;
    }
    else
    {
        adc->enabled_mask &= ~channel_bit;
    }

    return RT_EOK;
}

static rt_err_t ns800_adc_read_normal(struct ns800_adc *adc, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(adc != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (ns800_adc_config_sw_soc(adc, channel) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    ns800_adc_clear(adc, ADC_INT_NUMBER1);
    ADC_forceMultipleSOC(adc->config->instance, 1UL << channel);
    if (ns800_adc_wait_done(adc) != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    *value = ADC_readResult(adc->config->result, (ADC_SOCNumber)channel);
    ns800_adc_clear(adc, ADC_INT_NUMBER1);

    return RT_EOK;
}

static rt_err_t ns800_adc_read_irq(struct ns800_adc *adc, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(adc != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (channel != adc->active_channel)
    {
        return -RT_EINVAL;
    }

    ns800_adc_clear(adc, ADC_INT_NUMBER1);
    ADC_forceMultipleSOC(adc->config->instance, 1UL << channel);
    if (ns800_adc_wait_not_busy() != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    *value = ADC_readResult(adc->config->result, (ADC_SOCNumber)channel);

    return RT_EOK;
}

static rt_err_t ns800_adc_read_ppb(struct ns800_adc *adc, rt_uint32_t channel, rt_uint32_t *value)
{
    struct ns800_adc_ppb_oversampling_config ppb_config;
    struct ns800_adc_ppb_oversampling_result ppb_result;

    RT_ASSERT(adc != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    rt_memset(&ppb_config, 0, sizeof(ppb_config));
    ppb_config.bind.ppb = NS800_ADC_PPB1;
    ppb_config.bind.soc = 0U;
    ppb_config.adc_channel = channel;
    ppb_config.sample_count = NS800_ADC_DEFAULT_PPB_SAMPLES;
    ppb_config.sample_window = NS800_ADC_SAMPLE_WINDOW;
    ppb_config.drop_min_max = RT_TRUE;

    if (ns800_adc_ppb_oversampling_start(&ppb_config, &ppb_result) != RT_EOK)
    {
        return -RT_ERROR;
    }

    *value = (rt_uint32_t)ppb_result.value;

    return RT_EOK;
}

static rt_err_t ns800_adc_convert(struct rt_adc_device *device, ns800_adc_channel_t channel, rt_uint32_t *value)
{
    struct ns800_adc *adc;
    rt_uint32_t adc_channel;

    RT_ASSERT(device != RT_NULL);

    adc = (struct ns800_adc *)device->parent.user_data;
    RT_ASSERT(adc != RT_NULL);

    if ((value == RT_NULL) || (ns800_adc_get_channel(channel, &adc_channel) == RT_FALSE))
    {
        return -RT_EINVAL;
    }

    if ((adc->enabled_mask & (1UL << adc_channel)) == 0U)
    {
        return -RT_ERROR;
    }

    switch (adc->mode)
    {
    case NS800_ADC_MODE_NORMAL:
        return ns800_adc_read_normal(adc, adc_channel, value);

    case NS800_ADC_MODE_IRQ:
        return ns800_adc_read_irq(adc, adc_channel, value);

    case NS800_ADC_MODE_PPB:
        return ns800_adc_read_ppb(adc, adc_channel, value);

    default:
        break;
    }

    return -RT_EINVAL;
}

static rt_uint8_t ns800_adc_get_resolution(struct rt_adc_device *device)
{
    struct ns800_adc *adc;

    RT_ASSERT(device != RT_NULL);

    adc = (struct ns800_adc *)device->parent.user_data;
    RT_ASSERT(adc != RT_NULL);

    return adc->config->resolution_bits;
}

static rt_int16_t ns800_adc_get_vref(struct rt_adc_device *device)
{
    RT_UNUSED(device);

    return NS800_ADC_VREF_MV;
}

static const struct rt_adc_ops ns800_adc_ops =
{
    ns800_adc_enabled,
    ns800_adc_convert,
    ns800_adc_get_resolution,
    ns800_adc_get_vref,
};

static rt_ssize_t ns800_adc_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_adc_device *device;
    rt_uint32_t *value;
    rt_size_t index;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    device = (struct rt_adc_device *)dev;
    value = (rt_uint32_t *)buffer;

    for (index = 0U; index < size; index++)
    {
        if (ns800_adc_convert(device, (ns800_adc_channel_t)pos, value) != RT_EOK)
        {
            return 0;
        }
        value++;
    }

    return index;
}

static rt_err_t ns800_adc_set_mode(struct ns800_adc *adc, enum ns800_adc_mode mode, void *args)
{
    struct ns800_adc_callback *callback;

    RT_ASSERT(adc != RT_NULL);

    switch (mode)
    {
    case NS800_ADC_MODE_NORMAL:
        adc->mode = NS800_ADC_MODE_NORMAL;
        return RT_EOK;

    case NS800_ADC_MODE_PPB:
        adc->mode = NS800_ADC_MODE_PPB;
        return RT_EOK;

    case NS800_ADC_MODE_IRQ:
        callback = (struct ns800_adc_callback *)args;
        if (callback != RT_NULL)
        {
            adc_irq_entries[NS800_ADC_INT1].callback = callback->callback;
            adc_irq_entries[NS800_ADC_INT1].user_data = callback->user_data;
        }

        if (ns800_adc_config_sw_soc(adc, adc->active_channel) != RT_EOK)
        {
            return -RT_EINVAL;
        }
        rt_err_t ret;

        ret = ns800_adc_irq_attach(NS800_ADC_INT1,
                                    adc->active_channel,
                                    adc_irq_entries[NS800_ADC_INT1].callback,
                                    adc_irq_entries[NS800_ADC_INT1].user_data);
        if (ret == RT_EOK)
        {
            adc->mode = NS800_ADC_MODE_IRQ;
        }

        return ret;

    default:
        break;
    }

    return -RT_EINVAL;
}

static rt_err_t ns800_adc_control(rt_device_t dev, int cmd, void *args)
{
    struct ns800_adc *adc;

    RT_ASSERT(dev != RT_NULL);

    adc = (struct ns800_adc *)dev->user_data;
    RT_ASSERT(adc != RT_NULL);

    switch (cmd)
    {
    case RT_ADC_CMD_ENABLE:
        return ns800_adc_enabled(&adc->device, (ns800_adc_channel_t)(rt_base_t)args, RT_TRUE);

    case RT_ADC_CMD_DISABLE:
        return ns800_adc_enabled(&adc->device, (ns800_adc_channel_t)(rt_base_t)args, RT_FALSE);

    case RT_ADC_CMD_GET_RESOLUTION:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *(rt_uint8_t *)args = ns800_adc_get_resolution(&adc->device);
        return RT_EOK;

    case RT_ADC_CMD_GET_VREF:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *(rt_int16_t *)args = ns800_adc_get_vref(&adc->device);
        return RT_EOK;

    case NS800_ADC_CMD_DISABLE_EXT:
        adc->mode = NS800_ADC_MODE_NORMAL;
        ns800_adc_irq_detach(NS800_ADC_INT1);
        return RT_EOK;

    case NS800_ADC_CMD_ENABLE_PPB:
        return ns800_adc_set_mode(adc, NS800_ADC_MODE_PPB, args);

    case NS800_ADC_CMD_ENABLE_IRQ:
        return ns800_adc_set_mode(adc, NS800_ADC_MODE_IRQ, args);

    case NS800_ADC_CMD_SET_CALLBACK:
    {
        struct ns800_adc_callback *callback = (struct ns800_adc_callback *)args;

        if (callback == RT_NULL)
        {
            return -RT_EINVAL;
        }

        adc_irq_entries[NS800_ADC_INT1].callback = callback->callback;
        adc_irq_entries[NS800_ADC_INT1].user_data = callback->user_data;
        return RT_EOK;
    }

    default:
        break;
    }

    return -RT_EINVAL;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops ns800_adc_device_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    ns800_adc_device_read,
    RT_NULL,
    ns800_adc_control,
};
#endif

int rt_hw_adc_init(void)
{
    rt_err_t result;

    result = ns800_adc_hw_init(&adc_obj);
    if (result != RT_EOK)
    {
        LOG_E("%s init failed", adc_obj.config->name);
        return result;
    }

    result = rt_hw_adc_register(&adc_obj.device,
                                adc_obj.config->name,
                                &ns800_adc_ops,
                                &adc_obj);
    if (result != RT_EOK)
    {
        LOG_E("%s register failed", adc_obj.config->name);
    }

    ns800_adc_gpio_init(&adc_obj);
#ifdef RT_USING_DEVICE_OPS
    adc_obj.device.parent.ops = &ns800_adc_device_ops;
#else
    adc_obj.device.parent.read = ns800_adc_device_read;
    adc_obj.device.parent.control = ns800_adc_control;
#endif

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
