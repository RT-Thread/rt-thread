/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-24     wdfk-prog    add STM32 ADC V2 timer trigger backend
 */

/**
 * @file drv_adc_v2_trigger.c
 * @brief STM32 ADC V2 timer trigger selector backend.
 */
#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)

#include "drv_config.h"
#include "drv_adc_v2_private.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4)

#define DRV_DEBUG
#define LOG_TAG "drv.adc"
#include <drv_log.h>

#if defined(STM32_ADC_USING_TRIGGER)
/**
 * @brief Fill software-start trigger fields.
 * @param fields Pointer to the STM32 trigger fields to fill.
 */
static void stm32_adc_trigger_fields_set_software(struct stm32_adc_trigger_fields *fields)
{
    fields->selector = ADC_SOFTWARE_START;
#if defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE)
    fields->edge = ADC_EXTERNALTRIGCONVEDGE_NONE;
#else
    fields->edge = 0U;
#endif /* defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE) */
}

#if defined(STM32_ADC_USING_TIMER_TRIGGER)
/**
 * @brief Resolve TIMx update/TRGO selector for one STM32 ADC trigger source.
 * @param tim Pointer to the STM32 HAL timer handle.
 * @param selector Pointer to the output HAL ADC selector.
 * @return Operation status.
 */
static rt_err_t stm32_adc_timer_update_selector_get(const TIM_HandleTypeDef *tim, rt_uint32_t *selector)
{
    if ((tim == RT_NULL) || (selector == RT_NULL))
    {
        return -RT_EINVAL;
    }

#if defined(TIM1) && (defined(ADC_EXTERNALTRIGCONV_T1_TRGO) || defined(ADC_EXTERNALTRIG_T1_TRGO))
    if (tim->Instance == TIM1)
    {
#if defined(ADC_EXTERNALTRIGCONV_T1_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T1_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T1_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T1_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM1) && (defined(ADC_EXTERNALTRIGCONV_T1_TRGO) || defined(ADC_EXTERNALTRIG_T1_TRGO)) */
#if defined(TIM2) && (defined(ADC_EXTERNALTRIGCONV_T2_TRGO) || defined(ADC_EXTERNALTRIG_T2_TRGO))
    if (tim->Instance == TIM2)
    {
#if defined(ADC_EXTERNALTRIGCONV_T2_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T2_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T2_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T2_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM2) && (defined(ADC_EXTERNALTRIGCONV_T2_TRGO) || defined(ADC_EXTERNALTRIG_T2_TRGO)) */
#if defined(TIM3) && (defined(ADC_EXTERNALTRIGCONV_T3_TRGO) || defined(ADC_EXTERNALTRIG_T3_TRGO))
    if (tim->Instance == TIM3)
    {
#if defined(ADC_EXTERNALTRIGCONV_T3_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T3_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T3_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T3_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM3) && (defined(ADC_EXTERNALTRIGCONV_T3_TRGO) || defined(ADC_EXTERNALTRIG_T3_TRGO)) */
#if defined(TIM4) && (defined(ADC_EXTERNALTRIGCONV_T4_TRGO) || defined(ADC_EXTERNALTRIG_T4_TRGO))
    if (tim->Instance == TIM4)
    {
#if defined(ADC_EXTERNALTRIGCONV_T4_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T4_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T4_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T4_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM4) && (defined(ADC_EXTERNALTRIGCONV_T4_TRGO) || defined(ADC_EXTERNALTRIG_T4_TRGO)) */
#if defined(TIM5) && (defined(ADC_EXTERNALTRIGCONV_T5_TRGO) || defined(ADC_EXTERNALTRIG_T5_TRGO))
    if (tim->Instance == TIM5)
    {
#if defined(ADC_EXTERNALTRIGCONV_T5_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T5_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T5_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T5_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM5) && (defined(ADC_EXTERNALTRIGCONV_T5_TRGO) || defined(ADC_EXTERNALTRIG_T5_TRGO)) */
#if defined(TIM6) && (defined(ADC_EXTERNALTRIGCONV_T6_TRGO) || defined(ADC_EXTERNALTRIG_T6_TRGO))
    if (tim->Instance == TIM6)
    {
#if defined(ADC_EXTERNALTRIGCONV_T6_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T6_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T6_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T6_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM6) && (defined(ADC_EXTERNALTRIGCONV_T6_TRGO) || defined(ADC_EXTERNALTRIG_T6_TRGO)) */
#if defined(TIM7) && (defined(ADC_EXTERNALTRIGCONV_T7_TRGO) || defined(ADC_EXTERNALTRIG_T7_TRGO))
    if (tim->Instance == TIM7)
    {
#if defined(ADC_EXTERNALTRIGCONV_T7_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T7_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T7_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T7_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM7) && (defined(ADC_EXTERNALTRIGCONV_T7_TRGO) || defined(ADC_EXTERNALTRIG_T7_TRGO)) */
#if defined(TIM8) && (defined(ADC_EXTERNALTRIGCONV_T8_TRGO) || defined(ADC_EXTERNALTRIG_T8_TRGO))
    if (tim->Instance == TIM8)
    {
#if defined(ADC_EXTERNALTRIGCONV_T8_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T8_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T8_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T8_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM8) && (defined(ADC_EXTERNALTRIGCONV_T8_TRGO) || defined(ADC_EXTERNALTRIG_T8_TRGO)) */
#if defined(TIM9) && (defined(ADC_EXTERNALTRIGCONV_T9_TRGO) || defined(ADC_EXTERNALTRIG_T9_TRGO))
    if (tim->Instance == TIM9)
    {
#if defined(ADC_EXTERNALTRIGCONV_T9_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T9_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T9_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T9_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM9) && (defined(ADC_EXTERNALTRIGCONV_T9_TRGO) || defined(ADC_EXTERNALTRIG_T9_TRGO)) */
#if defined(TIM10) && (defined(ADC_EXTERNALTRIGCONV_T10_TRGO) || defined(ADC_EXTERNALTRIG_T10_TRGO))
    if (tim->Instance == TIM10)
    {
#if defined(ADC_EXTERNALTRIGCONV_T10_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T10_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T10_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T10_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM10) && (defined(ADC_EXTERNALTRIGCONV_T10_TRGO) || defined(ADC_EXTERNALTRIG_T10_TRGO)) */
#if defined(TIM11) && (defined(ADC_EXTERNALTRIGCONV_T11_TRGO) || defined(ADC_EXTERNALTRIG_T11_TRGO))
    if (tim->Instance == TIM11)
    {
#if defined(ADC_EXTERNALTRIGCONV_T11_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T11_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T11_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T11_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM11) && (defined(ADC_EXTERNALTRIGCONV_T11_TRGO) || defined(ADC_EXTERNALTRIG_T11_TRGO)) */
#if defined(TIM12) && (defined(ADC_EXTERNALTRIGCONV_T12_TRGO) || defined(ADC_EXTERNALTRIG_T12_TRGO))
    if (tim->Instance == TIM12)
    {
#if defined(ADC_EXTERNALTRIGCONV_T12_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T12_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T12_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T12_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM12) && (defined(ADC_EXTERNALTRIGCONV_T12_TRGO) || defined(ADC_EXTERNALTRIG_T12_TRGO)) */
#if defined(TIM13) && (defined(ADC_EXTERNALTRIGCONV_T13_TRGO) || defined(ADC_EXTERNALTRIG_T13_TRGO))
    if (tim->Instance == TIM13)
    {
#if defined(ADC_EXTERNALTRIGCONV_T13_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T13_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T13_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T13_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM13) && (defined(ADC_EXTERNALTRIGCONV_T13_TRGO) || defined(ADC_EXTERNALTRIG_T13_TRGO)) */
#if defined(TIM14) && (defined(ADC_EXTERNALTRIGCONV_T14_TRGO) || defined(ADC_EXTERNALTRIG_T14_TRGO))
    if (tim->Instance == TIM14)
    {
#if defined(ADC_EXTERNALTRIGCONV_T14_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T14_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T14_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T14_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM14) && (defined(ADC_EXTERNALTRIGCONV_T14_TRGO) || defined(ADC_EXTERNALTRIG_T14_TRGO)) */
#if defined(TIM15) && (defined(ADC_EXTERNALTRIGCONV_T15_TRGO) || defined(ADC_EXTERNALTRIG_T15_TRGO))
    if (tim->Instance == TIM15)
    {
#if defined(ADC_EXTERNALTRIGCONV_T15_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T15_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T15_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T15_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM15) && (defined(ADC_EXTERNALTRIGCONV_T15_TRGO) || defined(ADC_EXTERNALTRIG_T15_TRGO)) */
#if defined(TIM16) && (defined(ADC_EXTERNALTRIGCONV_T16_TRGO) || defined(ADC_EXTERNALTRIG_T16_TRGO))
    if (tim->Instance == TIM16)
    {
#if defined(ADC_EXTERNALTRIGCONV_T16_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T16_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T16_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T16_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM16) && (defined(ADC_EXTERNALTRIGCONV_T16_TRGO) || defined(ADC_EXTERNALTRIG_T16_TRGO)) */
#if defined(TIM17) && (defined(ADC_EXTERNALTRIGCONV_T17_TRGO) || defined(ADC_EXTERNALTRIG_T17_TRGO))
    if (tim->Instance == TIM17)
    {
#if defined(ADC_EXTERNALTRIGCONV_T17_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T17_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T17_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T17_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM17) && (defined(ADC_EXTERNALTRIGCONV_T17_TRGO) || defined(ADC_EXTERNALTRIG_T17_TRGO)) */
#if defined(TIM18) && (defined(ADC_EXTERNALTRIGCONV_T18_TRGO) || defined(ADC_EXTERNALTRIG_T18_TRGO))
    if (tim->Instance == TIM18)
    {
#if defined(ADC_EXTERNALTRIGCONV_T18_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T18_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T18_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T18_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM18) && (defined(ADC_EXTERNALTRIGCONV_T18_TRGO) || defined(ADC_EXTERNALTRIG_T18_TRGO)) */
#if defined(TIM19) && (defined(ADC_EXTERNALTRIGCONV_T19_TRGO) || defined(ADC_EXTERNALTRIG_T19_TRGO))
    if (tim->Instance == TIM19)
    {
#if defined(ADC_EXTERNALTRIGCONV_T19_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T19_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T19_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T19_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM19) && (defined(ADC_EXTERNALTRIGCONV_T19_TRGO) || defined(ADC_EXTERNALTRIG_T19_TRGO)) */
#if defined(TIM20) && (defined(ADC_EXTERNALTRIGCONV_T20_TRGO) || defined(ADC_EXTERNALTRIG_T20_TRGO))
    if (tim->Instance == TIM20)
    {
#if defined(ADC_EXTERNALTRIGCONV_T20_TRGO)
        *selector = ADC_EXTERNALTRIGCONV_T20_TRGO;
#else
        *selector = ADC_EXTERNALTRIG_T20_TRGO;
#endif /* defined(ADC_EXTERNALTRIGCONV_T20_TRGO) */
        return RT_EOK;
    }
#endif /* defined(TIM20) && (defined(ADC_EXTERNALTRIGCONV_T20_TRGO) || defined(ADC_EXTERNALTRIG_T20_TRGO)) */

    return -RT_ENOSYS;
}
#endif /* defined(STM32_ADC_USING_TIMER_TRIGGER) */

/**
 * @brief Resolve STM32 ADC trigger selector fields.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the ADC trigger configuration, or RT_NULL for software start.
 * @param fields Pointer to the output STM32 trigger fields.
 * @return Operation status.
 */
rt_err_t stm32_adc_trigger_fields_get(struct stm32_adc *adc, const struct rt_adc_trigger_cfg *cfg,
                                      struct stm32_adc_trigger_fields *fields)
{
#if defined(STM32_ADC_USING_TIMER_TRIGGER)
    TIM_HandleTypeDef *tim;
#endif /* defined(STM32_ADC_USING_TIMER_TRIGGER) */
    rt_err_t result;

    if (cfg == RT_NULL)
    {
        stm32_adc_trigger_fields_set_software(fields);
        return RT_EOK;
    }

    switch (cfg->type)
    {
    case RT_ADC_TRIGGER_TIMER_UPDATE:
#if defined(STM32_ADC_USING_TIMER_TRIGGER)
        if (cfg->event.timer.timer == RT_NULL)
        {
            return -RT_EINVAL;
        }

        tim = (TIM_HandleTypeDef *)cfg->event.timer.timer->user_data;
        if (tim == RT_NULL)
        {
            return -RT_EINVAL;
        }

        result = stm32_adc_timer_update_selector_get(tim, &fields->selector);
        if (result != RT_EOK)
        {
            LOG_E("%s timer update trigger selector unsupported", adc->name);
            return result;
        }
#if defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE) && defined(ADC_EXTERNALTRIGCONVEDGE_RISING)
        fields->edge = ADC_EXTERNALTRIGCONVEDGE_RISING;
#elif defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE)
        return -RT_ENOSYS;
#else
        fields->edge = 0U;
#endif /* defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE) && defined(ADC_EXTERNALTRIGCONVEDGE_RISING) */
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(STM32_ADC_USING_TIMER_TRIGGER) */

    case RT_ADC_TRIGGER_TIMER_COMPARE:
    case RT_ADC_TRIGGER_PWM_EDGE:
    case RT_ADC_TRIGGER_EXTI_EDGE:
    case RT_ADC_TRIGGER_ANALOG_COMPARE:
    case RT_ADC_TRIGGER_BACKEND:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }
}

/**
 * @brief Preconfigure STM32 ADC trigger selector state for the next stream configuration.
 * @param device Pointer to the ADC framework device object.
 * @param cfg Pointer to the ADC trigger configuration, or RT_NULL for software start.
 * @return Operation status.
 */
rt_err_t stm32_adc_trigger_prepare(struct rt_adc_device *device, const struct rt_adc_trigger_cfg *cfg)
{
    struct stm32_adc *adc;
    struct stm32_adc_trigger_fields fields;
    rt_err_t result;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_trigger_fields_get(adc, cfg, &fields);
    if (result != RT_EOK)
    {
        adc->prepared_trigger_valid = RT_FALSE;
        return result;
    }

    adc->prepared_trigger = fields;
    adc->prepared_trigger_valid = RT_TRUE;
    return RT_EOK;
}
#endif /* defined(STM32_ADC_USING_TRIGGER) */

#endif /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4) */

#endif /* defined(RT_USING_ADC_V2) */
