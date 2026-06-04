/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-20     wdfk-prog    add ADC V2 timer trigger framework implementation
 */

/**
 * @file adc_v2_trigger.c
 * @brief ADC V2 trigger framework implementation.
 */

#include <rtconfig.h>

#if defined(RT_USING_ADC_V2) && defined(RT_ADC_USING_TRIGGER)

#include <rtdevice.h>
#include <rtthread.h>
#if defined(RT_ADC_TRIGGER_USING_TIMER) && defined(RT_USING_CLOCK_TIMER_TRIGGER)
#include <drivers/clock_time.h>
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) && defined(RT_USING_CLOCK_TIMER_TRIGGER) */

#define DBG_TAG "adc.v2.trigger"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "adc_v2_internal.h"

/**
 * @brief Validate an ADC hardware trigger configuration at framework level.
 * @param cfg Pointer to the trigger configuration object.
 * @return Operation status.
 */
static rt_err_t adc_validate_trigger_cfg_common(const struct rt_adc_trigger_cfg *cfg)
{
    switch (cfg->type)
    {
    case RT_ADC_TRIGGER_TIMER_UPDATE:
#if defined(RT_ADC_TRIGGER_USING_TIMER)
        if ((cfg->event.timer.timer == RT_NULL) || (cfg->event.timer.timer->type != RT_Device_Class_Timer) ||
            (cfg->event.timer.freq_hz == 0U))
        {
            return -RT_EINVAL;
        }
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */

    case RT_ADC_TRIGGER_TIMER_COMPARE:
#if defined(RT_ADC_TRIGGER_USING_TIMER)
        if ((cfg->event.timer.timer == RT_NULL) || (cfg->event.timer.timer->type != RT_Device_Class_Timer) ||
            (cfg->event.timer.channel == 0U) || (cfg->event.timer.freq_hz == 0U))
        {
            return -RT_EINVAL;
        }
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */

    case RT_ADC_TRIGGER_ANALOG_COMPARE:
#if defined(RT_ADC_TRIGGER_USING_COMPARE)
        if ((cfg->event.compare.channel == 0U) || (cfg->event.compare.edge == RT_ADC_TRIGGER_EDGE_NONE))
        {
            return -RT_EINVAL;
        }
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(RT_ADC_TRIGGER_USING_COMPARE) */

    case RT_ADC_TRIGGER_PWM_EDGE:
    case RT_ADC_TRIGGER_EXTI_EDGE:
    case RT_ADC_TRIGGER_BACKEND:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }
}

/**
 * @brief Initialize the ADC trigger control state to software-started mode.
 * @param device Pointer to the ADC device object.
 */
void adc_trigger_init(rt_adc_device_t device)
{
    rt_memset(&device->trigger_ctrl, 0, sizeof(device->trigger_ctrl));
}

/**
 * @brief Get the active device-level ADC trigger configuration.
 * @param device Pointer to the ADC device object.
 * @return Pointer to the cached trigger configuration, or RT_NULL when no hardware trigger is configured.
 */
const struct rt_adc_trigger_cfg *adc_trigger_active_get(rt_adc_device_t device)
{
    if (device->trigger_ctrl.configured != RT_TRUE)
    {
        return RT_NULL;
    }

    return &device->trigger_ctrl.cfg;
}

#if defined(RT_ADC_TRIGGER_USING_TIMER)
/**
 * @brief Configure and start a timer-based ADC trigger source.
 * @param cfg Pointer to the active ADC trigger configuration object.
 * @return Operation status.
 */
static rt_err_t adc_trigger_timer_source_start(const struct rt_adc_trigger_cfg *cfg)
{
#if defined(RT_USING_CLOCK_TIMER_TRIGGER)
    struct rt_clock_timer_trigger_cfg timer_cfg = {0};
    rt_err_t result;

    timer_cfg.freq_hz = cfg->event.timer.freq_hz;
    timer_cfg.channel = cfg->event.timer.channel;

    switch (cfg->type)
    {
    case RT_ADC_TRIGGER_TIMER_UPDATE:
        timer_cfg.event = CLOCK_TIMER_TRIGGER_EVENT_UPDATE;
        timer_cfg.channel = 0U;
        break;

    case RT_ADC_TRIGGER_TIMER_COMPARE:
        timer_cfg.event = CLOCK_TIMER_TRIGGER_EVENT_COMPARE;
        break;

    default:
        return -RT_ENOSYS;
    }

    result = rt_device_control(cfg->event.timer.timer, CLOCK_TIMER_CTRL_TRIGGER_CONFIG, &timer_cfg);
    if (result != RT_EOK)
    {
        return result;
    }

    result = rt_device_control(cfg->event.timer.timer, CLOCK_TIMER_CTRL_TRIGGER_START, RT_NULL);
    if (result != RT_EOK)
    {
        (void)rt_device_control(cfg->event.timer.timer, CLOCK_TIMER_CTRL_TRIGGER_RELEASE, RT_NULL);
        return result;
    }

    return RT_EOK;
#else
    RT_UNUSED(cfg);
    return -RT_ENOSYS;
#endif /* defined(RT_USING_CLOCK_TIMER_TRIGGER) */
}

/**
 * @brief Stop and release a timer-based ADC trigger source.
 * @param cfg Pointer to the active ADC trigger configuration object.
 * @return Operation status.
 */
static rt_err_t adc_trigger_timer_source_stop(const struct rt_adc_trigger_cfg *cfg)
{
#if defined(RT_USING_CLOCK_TIMER_TRIGGER)
    rt_err_t stop_result;
    rt_err_t release_result;

    if ((cfg->type != RT_ADC_TRIGGER_TIMER_UPDATE) && (cfg->type != RT_ADC_TRIGGER_TIMER_COMPARE))
    {
        return -RT_ENOSYS;
    }

    stop_result = rt_device_control(cfg->event.timer.timer, CLOCK_TIMER_CTRL_TRIGGER_STOP, RT_NULL);
    release_result = rt_device_control(cfg->event.timer.timer, CLOCK_TIMER_CTRL_TRIGGER_RELEASE, RT_NULL);

    return (release_result != RT_EOK) ? release_result : stop_result;
#else
    RT_UNUSED(cfg);
    return -RT_ENOSYS;
#endif /* defined(RT_USING_CLOCK_TIMER_TRIGGER) */
}
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */

/**
 * @brief Start the active trigger source after the ADC conversion path is armed.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
static rt_err_t adc_trigger_source_start(rt_adc_device_t device)
{
    const struct rt_adc_trigger_cfg *cfg;

    cfg = adc_trigger_active_get(device);
    if (cfg == RT_NULL)
    {
        return RT_EOK;
    }

    switch (cfg->type)
    {
#if defined(RT_ADC_TRIGGER_USING_TIMER)
    case RT_ADC_TRIGGER_TIMER_UPDATE:
    case RT_ADC_TRIGGER_TIMER_COMPARE:
        return adc_trigger_timer_source_start(cfg);
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */

    default:
        return RT_EOK;
    }
}

/**
 * @brief Stop the active trigger source before the ADC conversion path is disarmed.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
static rt_err_t adc_trigger_source_stop(rt_adc_device_t device)
{
    const struct rt_adc_trigger_cfg *cfg;

    cfg = adc_trigger_active_get(device);
    if (cfg == RT_NULL)
    {
        return RT_EOK;
    }

    switch (cfg->type)
    {
#if defined(RT_ADC_TRIGGER_USING_TIMER)
    case RT_ADC_TRIGGER_TIMER_UPDATE:
    case RT_ADC_TRIGGER_TIMER_COMPARE:
        return adc_trigger_timer_source_stop(cfg);
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */

    default:
        return RT_EOK;
    }
}

/**
 * @brief Control the active trigger source around an armed ADC conversion path.
 * @param device Pointer to the ADC device object.
 * @param action Trigger-source lifecycle action.
 * @param started Pointer to the trigger-start state.
 * @param current_result Transfer result before trigger stop, ignored for start.
 * @return For start, trigger-source start result; for stop, @p current_result unless trigger stop is the first
 *         observed failure.
 */
rt_err_t adc_trigger_source_control(rt_adc_device_t device, enum adc_trigger_source_action action,
                                    rt_bool_t *started, rt_err_t current_result)
{
    rt_err_t stop_result;
    rt_err_t result;

    switch (action)
    {
    case ADC_TRIGGER_SOURCE_START:
        *started = RT_FALSE;
        if (adc_trigger_active_get(device) == RT_NULL)
        {
            return RT_EOK;
        }

        result = adc_trigger_source_start(device);
        if (result != RT_EOK)
        {
            LOG_E("trigger source start failed: device=%s result=%d", device->parent.parent.name, result);
            return result;
        }

        *started = RT_TRUE;
        return RT_EOK;

    case ADC_TRIGGER_SOURCE_STOP:
        if (*started != RT_TRUE)
        {
            return current_result;
        }

        stop_result = adc_trigger_source_stop(device);
        if (stop_result != RT_EOK)
        {
            LOG_E("trigger source stop failed: device=%s result=%d", device->parent.parent.name, stop_result);
            if (current_result == RT_EOK)
            {
                current_result = stop_result;
            }
        }

        *started = RT_FALSE;
        return current_result;

    default:
        return (current_result != RT_EOK) ? current_result : -RT_EINVAL;
    }
}

/**
 * @brief Preconfigure the active device-level ADC trigger before hardware configuration.
 * @param device Pointer to the ADC device object.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 *
 * @note A null active trigger still has to be passed to the backend when the
 *       backend provides trigger_prepare(), because some backends cache the
 *       previously prepared hardware trigger selector. Passing RT_NULL asks the
 *       backend to prepare the software-start/default trigger path.
 */
rt_err_t adc_trigger_preconfig(rt_adc_device_t device)
{
    const struct rt_adc_trigger_cfg *cfg;

    cfg = adc_trigger_active_get(device);

    if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) || (device->ops->core->trigger_prepare == RT_NULL))
    {
        return (cfg == RT_NULL) ? RT_EOK : -RT_ENOSYS;
    }

    return device->ops->core->trigger_prepare(device, cfg);
}

/**
 * @brief Set one device-level ADC hardware trigger request.
 * @param device Pointer to the ADC device object.
 * @param cfg Pointer to the ADC trigger configuration object.
 * @return Operation status.
 * @note This function only checks the framework-level trigger structure and
 *       caches the request. It does not write ADC trigger registers immediately.
 *       Backend compatibility is reported when the cached trigger is
 *       preconfigured before a stream hardware configuration.
 */
rt_err_t rt_adc_trigger_set(rt_adc_device_t device, const struct rt_adc_trigger_cfg *cfg)
{
    struct rt_adc_trigger_cfg trigger_cfg;
    rt_err_t result;
    rt_atomic_t old_state;

    if ((device == RT_NULL) || (cfg == RT_NULL))
    {
        return -RT_EINVAL;
    }

    trigger_cfg = *cfg;
    old_state = (rt_atomic_t)RT_ADC_STATE_IDLE;
    if (rt_atomic_compare_exchange_strong(&device->state, &old_state, (rt_atomic_t)RT_ADC_STATE_LOCKED) == 0)
    {
        return -RT_EBUSY;
    }

    result = adc_validate_trigger_cfg_common(&trigger_cfg);
    if (result == RT_EOK)
    {
        device->trigger_ctrl.cfg = trigger_cfg;
        device->trigger_ctrl.configured = RT_TRUE;
    }

    rt_atomic_store(&device->state, (rt_atomic_t)RT_ADC_STATE_IDLE);
    if (result != RT_EOK)
    {
        LOG_E("trigger set cache failed: device=%s result=%d", device->parent.parent.name, result);
    }
    return result;
}

/**
 * @brief Clear the cached ADC trigger configuration.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 * @note The ADC device must be idle so the cached trigger cannot be cleared while an active conversion is using it.
 */
rt_err_t rt_adc_trigger_clear(rt_adc_device_t device)
{
    rt_atomic_t old_state;

    if (device == RT_NULL)
    {
        return -RT_EINVAL;
    }

    old_state = (rt_atomic_t)RT_ADC_STATE_IDLE;
    if (rt_atomic_compare_exchange_strong(&device->state, &old_state, (rt_atomic_t)RT_ADC_STATE_LOCKED) == 0)
    {
        return -RT_EBUSY;
    }

    rt_memset(&device->trigger_ctrl, 0, sizeof(device->trigger_ctrl));
    rt_atomic_store(&device->state, (rt_atomic_t)RT_ADC_STATE_IDLE);

    LOG_D("trigger cleared: device=%s", device->parent.parent.name);
    return RT_EOK;
}

/**
 * @brief Check whether one ADC device has a cached hardware trigger request.
 * @param device Pointer to the ADC device object.
 * @return RT_TRUE if a hardware trigger request is set, otherwise RT_FALSE.
 */
rt_bool_t rt_adc_trigger_is_set(rt_adc_device_t device)
{
    if (device == RT_NULL)
    {
        return RT_FALSE;
    }

    return device->trigger_ctrl.configured;
}

#endif /* defined(RT_USING_ADC_V2) && defined(RT_ADC_USING_TRIGGER) */
