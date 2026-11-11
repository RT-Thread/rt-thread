/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-20     wdfk-prog    add ADC V2 trigger declarations
 */

/**
 * @file adc_v2_trigger.h
 * @brief ADC V2 trigger framework declarations.
 */

#ifndef __ADC_V2_TRIGGER_H__
#define __ADC_V2_TRIGGER_H__

#include <rtconfig.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(RT_ADC_USING_TRIGGER)
struct rt_adc_device;
struct rt_device;

/**
 * @brief ADC hardware trigger event type.
 *
 * @note A platform backend may support only part of these trigger types.
 *       Unsupported trigger types shall be rejected by the framework or backend
 *       with an error such as -RT_ENOSYS.
 */
enum rt_adc_trigger_type
{
    RT_ADC_TRIGGER_TIMER_UPDATE = 0, /**< Use a timer update/TRGO event. */
    RT_ADC_TRIGGER_TIMER_COMPARE,    /**< Use a timer compare event. */
    RT_ADC_TRIGGER_PWM_EDGE,         /**< Use a PWM edge event. */
    RT_ADC_TRIGGER_EXTI_EDGE,        /**< Use an external interrupt edge event. */
    RT_ADC_TRIGGER_ANALOG_COMPARE,   /**< Use an analog comparator event. */
    RT_ADC_TRIGGER_BACKEND,          /**< Use a backend-specific trigger event. */
};

/**
 * @brief ADC trigger edge selector.
 */
enum rt_adc_trigger_edge
{
    RT_ADC_TRIGGER_EDGE_NONE = 0, /**< No edge selection is required. */
    RT_ADC_TRIGGER_EDGE_RISING,   /**< Use the rising edge. */
    RT_ADC_TRIGGER_EDGE_FALLING,  /**< Use the falling edge. */
    RT_ADC_TRIGGER_EDGE_BOTH,     /**< Use both rising and falling edges. */
};

/**
 * @brief Timer-based ADC trigger event.
 */
struct rt_adc_trigger_timer_event
{
    struct rt_device *timer; /**< Timer device used as trigger source. */
    rt_uint32_t freq_hz;    /**< Timer trigger output frequency in hertz. */
    rt_uint16_t channel;    /**< Timer channel, or 0 for update/TRGO event. */
    rt_uint16_t reserved;   /**< Reserved for future extension. */
};

/**
 * @brief PWM-based ADC trigger event.
 */
struct rt_adc_trigger_pwm_event
{
    struct rt_device *pwm;         /**< PWM device used as trigger source. */
    rt_uint16_t channel;           /**< PWM channel. */
    enum rt_adc_trigger_edge edge; /**< PWM edge used as trigger event. */
};

/**
 * @brief External interrupt ADC trigger event.
 */
struct rt_adc_trigger_exti_event
{
    struct rt_device *pin;         /**< Pin or GPIO controller device. */
    rt_uint16_t line;              /**< External interrupt line or pin number. */
    enum rt_adc_trigger_edge edge; /**< Interrupt edge used as trigger event. */
};

/**
 * @brief Analog comparator ADC trigger event.
 */
struct rt_adc_trigger_compare_event
{
    struct rt_device *comparator;  /**< Optional comparator device used as trigger source. */
    rt_uint16_t channel;           /**< Comparator channel or instance index. */
    enum rt_adc_trigger_edge edge; /**< Comparator output edge used as trigger event. */
};

/**
 * @brief Backend-specific ADC trigger event.
 */
struct rt_adc_trigger_backend_event
{
    rt_uint32_t selector; /**< Backend-specific trigger selector. */
    rt_uint32_t edge;    /**< Backend-specific edge selector. */
    const void *data;    /**< Optional backend-specific configuration. */
    rt_size_t data_size; /**< Size of backend-specific configuration. */
};

/**
 * @brief ADC trigger configuration.
 */
struct rt_adc_trigger_cfg
{
    enum rt_adc_trigger_type type; /**< Trigger event type. */
    rt_uint32_t flags;             /**< Common trigger flags, reserved for future extension. */

    union
    {
        struct rt_adc_trigger_timer_event timer;     /**< Timer trigger event. */
        struct rt_adc_trigger_pwm_event pwm;         /**< PWM trigger event. */
        struct rt_adc_trigger_exti_event exti;       /**< External interrupt trigger event. */
        struct rt_adc_trigger_compare_event compare; /**< Comparator trigger event. */
        struct rt_adc_trigger_backend_event backend; /**< Backend-specific trigger event. */
    } event;                                         /**< Trigger event payload. */
};

/**
 * @brief ADC trigger runtime control block.
 */
struct rt_adc_trigger_ctrl
{
    struct rt_adc_trigger_cfg cfg; /**< Cached device-level hardware trigger configuration. */
    rt_bool_t configured;          /**< Whether cfg contains a cached hardware trigger request. */
};

/**
 * @brief Set one device-level ADC hardware trigger request.
 * @param device Pointer to the ADC device object.
 * @param cfg Pointer to the ADC trigger configuration object.
 * @return Operation status.
 * @note This function only checks the framework-level trigger structure and
 *       caches the request. It does not write ADC trigger registers immediately.
 *       Backend compatibility is reported when the cached trigger is
 *       preconfigured before a conversion hardware configuration.
 */
rt_err_t rt_adc_trigger_set(struct rt_adc_device *device, const struct rt_adc_trigger_cfg *cfg);

/**
 * @brief Clear the cached device-level ADC hardware trigger request.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 * @note This function does not write ADC trigger registers immediately. The
 *       next conversion hardware configuration preconfigures the backend
 *       software/default trigger state.
 */
rt_err_t rt_adc_trigger_clear(struct rt_adc_device *device);

/**
 * @brief Check whether one ADC device has a cached hardware trigger request.
 * @param device Pointer to the ADC device object.
 * @return RT_TRUE if a hardware trigger request is set, otherwise RT_FALSE.
 */
rt_bool_t rt_adc_trigger_is_set(struct rt_adc_device *device);
#endif /* defined(RT_ADC_USING_TRIGGER) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ADC_V2_TRIGGER_H__ */
