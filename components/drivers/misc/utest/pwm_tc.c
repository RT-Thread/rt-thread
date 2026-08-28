/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-25     CYFS         add configurable PWM matrix utest
 */

/**
 * Test Case Name: PWM Frequency and Duty-cycle Matrix Test
 *
 * Test Objectives:
 * - Validate PWM set, enable, optional get, and disable operations over a
 *   configurable frequency and duty-cycle matrix.
 * - Run multiple PWM channels concurrently and multiple test groups in order.
 * - Support fixed output, one-shot sweep with final-value hold, and repeated
 *   sweep modes independently for every channel.
 *
 * Dependencies:
 * - Requires RT_UTEST_PWM and board PWM devices/pinmux matching the selected
 *   configuration header.
 * - Channels that share one hardware timer period must use compatible
 *   frequencies while they are active in the same group.
 * - Physical frequency and duty-cycle accuracy still requires an oscilloscope,
 *   logic analyzer, or external capture input.
 */

#include <limits.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_PWM

#define PWM_TC_NSEC_PER_SEC      1000000000ULL
#define PWM_TC_DUTY_SCALE        10000U
#define PWM_TC_MAX_MILLISECOND   0x7FFFFFFFU
#define PWM_TC_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#define PWM_TC_POINT(frequency, duty) \
    { (frequency), (duty) }
#define PWM_TC_POINT_PERCENT(frequency, duty_percent) \
    PWM_TC_POINT((frequency), (duty_percent) * 100U)
#define PWM_TC_CHANNEL_CONFIG(is_enabled, device, channel_number, output_mode, \
                              point_table, interval_ms, tolerance)             \
    {                                                                          \
        (is_enabled), (device), (channel_number), (output_mode),               \
        (point_table), PWM_TC_ARRAY_SIZE(point_table), (interval_ms),          \
        (tolerance)                                                            \
    }

enum pwm_tc_mode
{
    PWM_TC_MODE_FIXED = 0,
    PWM_TC_MODE_SWEEP_ONCE,
    PWM_TC_MODE_SWEEP_LOOP,
};

struct pwm_tc_point
{
    rt_uint32_t frequency_hz;
    rt_uint32_t duty_permyriad;
};

struct pwm_tc_channel
{
    rt_bool_t enabled;
    const char *device_name;
    int channel;
    enum pwm_tc_mode mode;
    const struct pwm_tc_point *points;
    rt_size_t point_count;
    rt_uint32_t step_interval_ms;
    rt_uint32_t readback_tolerance;
};

struct pwm_tc_group
{
    const char *name;
    const struct pwm_tc_channel *channels;
    rt_size_t channel_count;
    rt_uint32_t duration_ms;
};

#include RT_PWM_TC_CONFIG_FILE

#ifndef PWM_TC_GROUPS
#error "The PWM test configuration must define PWM_TC_GROUPS"
#endif

#ifndef PWM_TC_GROUP_COUNT
#error "The PWM test configuration must define PWM_TC_GROUP_COUNT"
#endif

struct pwm_tc_runtime
{
    const struct pwm_tc_channel *config;
    struct rt_device_pwm *device;
    rt_size_t point_index;
    rt_tick_t last_update_tick;
    rt_bool_t enabled;
};

static struct pwm_tc_runtime pwm_tc_runtime[RT_PWM_TC_MAX_CHANNELS];
static rt_size_t pwm_tc_active_count;
static rt_tick_t pwm_tc_test_start_tick;
static rt_tick_t pwm_tc_test_timeout_tick;
static rt_bool_t pwm_tc_test_timeout_enabled;

static rt_tick_t pwm_tc_millisecond_to_tick(rt_uint32_t millisecond)
{
    rt_tick_t tick;

    if (millisecond > PWM_TC_MAX_MILLISECOND)
    {
        return 0;
    }

    tick = rt_tick_from_millisecond((rt_int32_t)millisecond);
    if (tick == 0)
    {
        tick = 1;
    }

    return tick;
}

static rt_bool_t pwm_tc_test_get_timeout_remaining(rt_tick_t *remaining)
{
    rt_tick_t elapsed;

    if (!pwm_tc_test_timeout_enabled)
    {
        *remaining = RT_TICK_MAX;
        return RT_TRUE;
    }

    elapsed = rt_tick_get_delta(pwm_tc_test_start_tick);
    if (elapsed >= pwm_tc_test_timeout_tick)
    {
        *remaining = 0;
        return RT_FALSE;
    }

    *remaining = pwm_tc_test_timeout_tick - elapsed;
    return RT_TRUE;
}

static rt_uint32_t pwm_tc_channel_number(int channel)
{
    if (channel < 0)
    {
        return (rt_uint32_t)(-channel);
    }

    return (rt_uint32_t)channel;
}

static rt_err_t pwm_tc_point_to_output(const struct pwm_tc_point *point,
                                       rt_uint32_t *period,
                                       rt_uint32_t *pulse)
{
    rt_uint64_t calculated_period;
    rt_uint64_t calculated_pulse;

    if (point->frequency_hz == 0 || point->duty_permyriad > PWM_TC_DUTY_SCALE)
    {
        return -RT_EINVAL;
    }

    calculated_period = (PWM_TC_NSEC_PER_SEC + point->frequency_hz / 2U) /
                        point->frequency_hz;
    if (calculated_period == 0 || calculated_period > 0xFFFFFFFFULL)
    {
        return -RT_EINVAL;
    }

    calculated_pulse = (calculated_period * point->duty_permyriad +
                        PWM_TC_DUTY_SCALE / 2U) /
                       PWM_TC_DUTY_SCALE;
    if (calculated_pulse > calculated_period)
    {
        calculated_pulse = calculated_period;
    }

    *period = (rt_uint32_t)calculated_period;
    *pulse = (rt_uint32_t)calculated_pulse;

    return RT_EOK;
}

static rt_bool_t pwm_tc_value_in_tolerance(rt_uint32_t actual,
                                           rt_uint32_t expected,
                                           rt_uint32_t tolerance)
{
    rt_uint64_t difference;

    if (expected == 0)
    {
        return actual == 0;
    }

    difference = (actual > expected) ? (actual - expected) : (expected - actual);

    return difference * PWM_TC_DUTY_SCALE <=
           (rt_uint64_t)expected * tolerance;
}

static rt_err_t pwm_tc_verify_output(struct pwm_tc_runtime *runtime,
                                     rt_uint32_t period,
                                     rt_uint32_t pulse)
{
    rt_err_t result;
    struct rt_pwm_configuration configuration;
    const struct pwm_tc_channel *channel;

    channel = runtime->config;
    if (channel->readback_tolerance == 0)
    {
        return RT_EOK;
    }

    rt_memset(&configuration, 0, sizeof(configuration));
    configuration.channel = pwm_tc_channel_number(channel->channel);
    result = rt_pwm_get(runtime->device, &configuration);
    if (result != RT_EOK)
    {
        LOG_E("PWM readback failed: device=%s channel=%d result=%d",
              channel->device_name, channel->channel, result);
        return result;
    }

    if (!pwm_tc_value_in_tolerance(configuration.period, period,
                                   channel->readback_tolerance) ||
        !pwm_tc_value_in_tolerance(configuration.pulse, pulse,
                                   channel->readback_tolerance))
    {
        LOG_E("PWM readback mismatch: device=%s channel=%d expected=%u/%u ns actual=%u/%u ns",
              channel->device_name, channel->channel,
              period, pulse, configuration.period, configuration.pulse);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t pwm_tc_apply_point(struct pwm_tc_runtime *runtime,
                                   rt_size_t point_index)
{
    rt_err_t result;
    rt_uint32_t period;
    rt_uint32_t pulse;
    const struct pwm_tc_channel *channel;
    const struct pwm_tc_point *point;

    channel = runtime->config;
    point = &channel->points[point_index];
    result = pwm_tc_point_to_output(point, &period, &pulse);
    if (result != RT_EOK)
    {
        return result;
    }

    result = rt_pwm_set(runtime->device, channel->channel, period, pulse);
    if (result != RT_EOK)
    {
        LOG_E("PWM set failed: device=%s channel=%d frequency=%u Hz duty=%u.%02u%% result=%d",
              channel->device_name, channel->channel, point->frequency_hz,
              point->duty_permyriad / 100U, point->duty_permyriad % 100U,
              result);
        return result;
    }

    result = pwm_tc_verify_output(runtime, period, pulse);
    if (result != RT_EOK)
    {
        return result;
    }

    if (!runtime->enabled)
    {
        result = rt_pwm_enable(runtime->device, channel->channel);
        if (result != RT_EOK)
        {
            LOG_E("PWM enable failed: device=%s channel=%d result=%d",
                  channel->device_name, channel->channel, result);
            return result;
        }
        runtime->enabled = RT_TRUE;
    }

    runtime->point_index = point_index;
    runtime->last_update_tick = rt_tick_get();
    LOG_I("PWM output: device=%s channel=%d frequency=%u Hz duty=%u.%02u%%",
          channel->device_name, channel->channel, point->frequency_hz,
          point->duty_permyriad / 100U, point->duty_permyriad % 100U);

    return RT_EOK;
}

static rt_bool_t pwm_tc_channel_has_next(const struct pwm_tc_runtime *runtime)
{
    const struct pwm_tc_channel *channel;

    channel = runtime->config;
    if (channel->mode == PWM_TC_MODE_SWEEP_LOOP)
    {
        return channel->point_count > 1;
    }
    if (channel->mode == PWM_TC_MODE_SWEEP_ONCE)
    {
        return runtime->point_index + 1 < channel->point_count;
    }

    return RT_FALSE;
}

static rt_size_t pwm_tc_next_point_index(const struct pwm_tc_runtime *runtime)
{
    rt_size_t next;

    next = runtime->point_index + 1;
    if (next >= runtime->config->point_count)
    {
        next = 0;
    }

    return next;
}

static rt_err_t pwm_tc_stop_active_channels(void)
{
    rt_err_t result;
    rt_err_t operation_result;
    rt_size_t index;
    rt_bool_t all_stopped;

    result = RT_EOK;
    all_stopped = RT_TRUE;
    for (index = 0; index < pwm_tc_active_count; index++)
    {
        if (!pwm_tc_runtime[index].enabled)
        {
            continue;
        }

        operation_result = rt_pwm_disable(pwm_tc_runtime[index].device,
                                          pwm_tc_runtime[index].config->channel);
        if (operation_result != RT_EOK)
        {
            LOG_E("PWM disable failed: device=%s channel=%d result=%d",
                  pwm_tc_runtime[index].config->device_name,
                  pwm_tc_runtime[index].config->channel,
                  operation_result);
            if (result == RT_EOK)
            {
                result = operation_result;
            }
            all_stopped = RT_FALSE;
        }
        else
        {
            pwm_tc_runtime[index].enabled = RT_FALSE;
        }
    }
    if (all_stopped)
    {
        pwm_tc_active_count = 0;
    }

    return result;
}

static rt_err_t pwm_tc_start_group(const struct pwm_tc_group *group)
{
    rt_err_t result;
    rt_size_t index;
    rt_device_t device;
    struct pwm_tc_runtime *runtime;

    rt_memset(pwm_tc_runtime, 0, sizeof(pwm_tc_runtime));
    pwm_tc_active_count = 0;

    for (index = 0; index < group->channel_count; index++)
    {
        if (!group->channels[index].enabled)
        {
            continue;
        }

        device = rt_device_find(group->channels[index].device_name);
        runtime = &pwm_tc_runtime[pwm_tc_active_count];
        runtime->config = &group->channels[index];
        runtime->device = (struct rt_device_pwm *)device;
        pwm_tc_active_count++;

        result = pwm_tc_apply_point(runtime, 0);
        if (result != RT_EOK)
        {
            pwm_tc_stop_active_channels();
            return result;
        }
    }

    return RT_EOK;
}

static rt_err_t pwm_tc_run_group(const struct pwm_tc_group *group)
{
    rt_err_t result;
    rt_err_t stop_result;
    rt_size_t index;
    rt_tick_t duration_tick;
    rt_tick_t elapsed_tick;
    rt_tick_t interval_tick;
    rt_tick_t timeout_remaining;
    rt_tick_t since_update_tick;
    rt_tick_t sleep_tick;
    rt_tick_t start_tick;

    result = pwm_tc_start_group(group);
    if (result != RT_EOK)
    {
        return result;
    }
    LOG_I("PWM group started: name=%s enabled=%u configured=%u duration=%u ms",
          group->name, (unsigned int)pwm_tc_active_count,
          (unsigned int)group->channel_count, group->duration_ms);

    start_tick = rt_tick_get();
    duration_tick = pwm_tc_millisecond_to_tick(group->duration_ms);
    if (duration_tick == 0)
    {
        result = -RT_EINVAL;
        goto __exit;
    }

    while ((elapsed_tick = rt_tick_get_delta(start_tick)) < duration_tick)
    {
        if (!pwm_tc_test_get_timeout_remaining(&timeout_remaining))
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }

        sleep_tick = duration_tick - elapsed_tick;
        for (index = 0; index < pwm_tc_active_count; index++)
        {
            if (!pwm_tc_channel_has_next(&pwm_tc_runtime[index]))
            {
                continue;
            }

            interval_tick = pwm_tc_millisecond_to_tick(
                pwm_tc_runtime[index].config->step_interval_ms);
            if (interval_tick == 0)
            {
                result = -RT_EINVAL;
                goto __exit;
            }
            since_update_tick = rt_tick_get_delta(
                pwm_tc_runtime[index].last_update_tick);
            if (since_update_tick >= interval_tick)
            {
                result = pwm_tc_apply_point(&pwm_tc_runtime[index],
                                            pwm_tc_next_point_index(
                                                &pwm_tc_runtime[index]));
                if (result != RT_EOK)
                {
                    goto __exit;
                }
                since_update_tick = 0;
            }

            if (interval_tick - since_update_tick < sleep_tick)
            {
                sleep_tick = interval_tick - since_update_tick;
            }
        }

        if (!pwm_tc_test_get_timeout_remaining(&timeout_remaining))
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }
        if (timeout_remaining < sleep_tick)
        {
            sleep_tick = timeout_remaining;
        }

        if (sleep_tick == 0)
        {
            sleep_tick = 1;
        }
        rt_thread_delay(sleep_tick);
    }

__exit:
    stop_result = pwm_tc_stop_active_channels();
    if (result == RT_EOK)
    {
        result = stop_result;
    }
    LOG_I("PWM group finished: name=%s result=%d", group->name, result);

    return result;
}

static rt_err_t pwm_tc_validate_channel(const struct pwm_tc_channel *channel)
{
    rt_err_t result;
    rt_size_t index;
    rt_uint32_t period;
    rt_uint32_t pulse;
    rt_device_t device;

    if (channel->device_name == RT_NULL || channel->device_name[0] == '\0' ||
        channel->points == RT_NULL || channel->point_count == 0 ||
        channel->channel == INT_MIN ||
        channel->mode < PWM_TC_MODE_FIXED ||
        channel->mode > PWM_TC_MODE_SWEEP_LOOP ||
        channel->step_interval_ms > PWM_TC_MAX_MILLISECOND ||
        channel->readback_tolerance > PWM_TC_DUTY_SCALE)
    {
        return -RT_EINVAL;
    }
    if (channel->mode == PWM_TC_MODE_FIXED && channel->point_count != 1)
    {
        return -RT_EINVAL;
    }
    if (channel->mode != PWM_TC_MODE_FIXED && channel->point_count > 1 &&
        channel->step_interval_ms == 0)
    {
        return -RT_EINVAL;
    }

    device = rt_device_find(channel->device_name);
    if (device == RT_NULL)
    {
        LOG_E("PWM device not found: %s", channel->device_name);
        return -RT_ENOSYS;
    }
    if (device->type != RT_Device_Class_PWM)
    {
        LOG_E("Device is not PWM: %s type=%d", channel->device_name, device->type);
        return -RT_EINVAL;
    }

    for (index = 0; index < channel->point_count; index++)
    {
        result = pwm_tc_point_to_output(&channel->points[index], &period, &pulse);
        if (result != RT_EOK)
        {
            LOG_E("Invalid PWM point: device=%s channel=%d point=%u",
                  channel->device_name, channel->channel, (unsigned int)index);
            return result;
        }
    }

    return RT_EOK;
}

static rt_err_t pwm_tc_validate_group(const struct pwm_tc_group *group)
{
    rt_err_t result;
    rt_size_t index;
    rt_size_t peer_index;
    rt_size_t enabled_count;

    if (group->name == RT_NULL || group->name[0] == '\0' ||
        group->channels == RT_NULL || group->channel_count == 0 ||
        group->duration_ms == 0 ||
        group->duration_ms > PWM_TC_MAX_MILLISECOND)
    {
        return -RT_EINVAL;
    }

    enabled_count = 0;
    for (index = 0; index < group->channel_count; index++)
    {
        if (!group->channels[index].enabled)
        {
            continue;
        }

        enabled_count++;
        if (enabled_count > RT_PWM_TC_MAX_CHANNELS)
        {
            LOG_E("Too many enabled PWM channels in group %s: enabled=%u max=%u",
                  group->name, (unsigned int)enabled_count,
                  (unsigned int)RT_PWM_TC_MAX_CHANNELS);
            return -RT_EINVAL;
        }

        result = pwm_tc_validate_channel(&group->channels[index]);
        if (result != RT_EOK)
        {
            return result;
        }

        for (peer_index = 0; peer_index < index; peer_index++)
        {
            if (!group->channels[peer_index].enabled)
            {
                continue;
            }

            if (group->channels[index].channel ==
                    group->channels[peer_index].channel &&
                rt_strcmp(group->channels[index].device_name,
                          group->channels[peer_index].device_name) == 0)
            {
                LOG_E("Duplicate PWM channel in group %s: device=%s channel=%d",
                      group->name, group->channels[index].device_name,
                      group->channels[index].channel);
                return -RT_EINVAL;
            }
        }
    }

    if (enabled_count == 0)
    {
        LOG_E("No PWM channel enabled in group %s", group->name);
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static void pwm_tc_configuration_matrix(void)
{
    rt_err_t result;
    rt_size_t index;

    for (index = 0; index < PWM_TC_GROUP_COUNT; index++)
    {
        result = pwm_tc_run_group(&PWM_TC_GROUPS[index]);
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            return;
        }
    }
}

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;
    rt_size_t index;
    rt_uint64_t timeout_millisecond;

    result = pwm_tc_stop_active_channels();
    if (result != RT_EOK)
    {
        LOG_E("PWM cleanup before test failed: result=%d", result);
        return result;
    }
    if (pwm_tc_active_count != 0)
    {
        LOG_E("PWM cleanup left %u active channel(s)",
              (unsigned int)pwm_tc_active_count);
        return -RT_ERROR;
    }

    pwm_tc_test_timeout_enabled = RT_FALSE;
    if (PWM_TC_GROUP_COUNT == 0)
    {
        return -RT_EINVAL;
    }

    for (index = 0; index < PWM_TC_GROUP_COUNT; index++)
    {
        result = pwm_tc_validate_group(&PWM_TC_GROUPS[index]);
        if (result != RT_EOK)
        {
            LOG_E("Invalid PWM group: index=%u result=%d",
                  (unsigned int)index, result);
            return result;
        }
    }

    timeout_millisecond = (rt_uint64_t)RT_PWM_TC_TIMEOUT * 1000ULL;
    if (timeout_millisecond == 0 ||
        timeout_millisecond > PWM_TC_MAX_MILLISECOND)
    {
        return -RT_EINVAL;
    }
    pwm_tc_test_timeout_tick = pwm_tc_millisecond_to_tick(
        (rt_uint32_t)timeout_millisecond);
    if (pwm_tc_test_timeout_tick == 0)
    {
        return -RT_EINVAL;
    }
    pwm_tc_test_start_tick = rt_tick_get();
    pwm_tc_test_timeout_enabled = RT_TRUE;

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;

    result = pwm_tc_stop_active_channels();
    if (pwm_tc_active_count == 0)
    {
        pwm_tc_test_timeout_enabled = RT_FALSE;
    }

    return result;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(pwm_tc_configuration_matrix);
}

UTEST_TC_EXPORT(testcase,
                "components.drivers.pwm.configuration_matrix",
                utest_tc_init,
                utest_tc_cleanup,
                RT_PWM_TC_TIMEOUT);

#endif /* RT_UTEST_PWM */
