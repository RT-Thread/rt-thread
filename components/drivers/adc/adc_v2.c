/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-21     wdfk-prog    add standalone adc v2 framework implementation
 */

/**
 * @file adc_v2.c
 * @brief Standalone ADC V2 framework implementation.
 */

#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)

#include <rtdevice.h>
#include <rtthread.h>

#define DBG_TAG "adc.v2"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <drivers/adc_v2.h>
#include "adc_v2_internal.h"

/**
 * @brief Get the current ADC framework state atomically.
 * @param device Pointer to the ADC device object.
 * @return Current ADC runtime state.
 */
enum rt_adc_state adc_get_state(rt_adc_device_t device)
{
    return (enum rt_adc_state)rt_atomic_load(&device->state);
}

#if DBG_LVL >= DBG_LOG
/**
 * @brief Convert one ADC framework state to a debug log string.
 * @param state ADC runtime state.
 * @return Constant state name string.
 */
static const char *adc_state_name(enum rt_adc_state state)
{
    switch (state)
    {
    case RT_ADC_STATE_IDLE:
        return "IDLE";

    case RT_ADC_STATE_LOCKED:
        return "BUSY";

    default:
        return "UNKNOWN";
    }
}

#endif /* DBG_LVL >= DBG_LOG */

/** @brief ADC control command string table offset base. */
#define RT_ADC_CMD_NAME_BASE RT_ADC_CMD_GET_RESOLUTION

/** @brief ADC control command string table entry count. */
#define RT_ADC_CMD_NAME_COUNT (RT_ADC_CMD_CLEAR_CHANNEL_CONFIG - RT_ADC_CMD_GET_RESOLUTION + 1)

/**
 * @brief ADC control command name table.
 */
static const char * const rt_adc_control_cmd_names[RT_ADC_CMD_NAME_COUNT] =
{
    [RT_ADC_CMD_GET_RESOLUTION        - RT_ADC_CMD_NAME_BASE] = "GET_RESOLUTION",
    [RT_ADC_CMD_CALIBRATE             - RT_ADC_CMD_NAME_BASE] = "CALIBRATE",
    [RT_ADC_CMD_SET_VREF              - RT_ADC_CMD_NAME_BASE] = "SET_VREF",
    [RT_ADC_CMD_CALC_VREF             - RT_ADC_CMD_NAME_BASE] = "CALC_VREF",
    [RT_ADC_CMD_GET_VREF_CHANNEL      - RT_ADC_CMD_NAME_BASE] = "GET_VREF_CHANNEL",
    [RT_ADC_CMD_SET_SESSION           - RT_ADC_CMD_NAME_BASE] = "SET_SESSION",
    [RT_ADC_CMD_SET_CONFIG            - RT_ADC_CMD_NAME_BASE] = "SET_CONFIG",
    [RT_ADC_CMD_GET_CONFIG            - RT_ADC_CMD_NAME_BASE] = "GET_CONFIG",
    [RT_ADC_CMD_CLEAR_CHANNEL_CONFIG  - RT_ADC_CMD_NAME_BASE] = "CLEAR_CHANNEL_CONFIG",
};

/**
 * @brief Get ADC control command name.
 * @param cmd ADC control command identifier.
 * @return ADC control command name string.
 */
static const char *rt_adc_control_cmd_name(int cmd)
{
    int index;

    index = cmd - RT_ADC_CMD_NAME_BASE;
    if ((index < 0) || (index >= RT_ADC_CMD_NAME_COUNT) || (rt_adc_control_cmd_names[index] == RT_NULL))
    {
        return "UNKNOWN";
    }

    return rt_adc_control_cmd_names[index];
}

/**
 * @brief Store one ADC framework state atomically.
 * @param device Pointer to the ADC device object.
 * @param state New ADC runtime state.
 */
static void adc_set_state(rt_adc_device_t device, enum rt_adc_state state)
{
    LOG_D("state set: device=%s state=%s", device->parent.parent.name, adc_state_name(state));
    rt_atomic_store(&device->state, (rt_atomic_t)state);
}

/**
 * @brief Clear the cached active ADC session configuration.
 * @param device Pointer to the ADC device object.
 */
static void adc_clear_session_ctrl(rt_adc_device_t device)
{
    if (device == RT_NULL)
    {
        return;
    }

    device->session_ctrl.channels = 0U;
    device->session_ctrl.channel_count = 0U;
    device->session_ctrl.configured = RT_FALSE;
}

/**
 * @brief Cache one ADC session while the caller owns the device BUSY state.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @return Operation status.
 */
static rt_err_t adc_cache_session_ctrl(rt_adc_device_t device, rt_uint32_t channels)
{
    rt_size_t channel_count;

    if ((device == RT_NULL) || (channels == 0U))
    {
        return -RT_EINVAL;
    }

    channel_count = rt_adc_channel_mask_count(channels);
    if (channel_count == 0U)
    {
        return -RT_EINVAL;
    }

    device->session_ctrl.channels = channels;
    device->session_ctrl.channel_count = channel_count;
    device->session_ctrl.configured = RT_TRUE;

    return RT_EOK;
}

/**
 * @brief Try to change the ADC framework state atomically.
 * @param device Pointer to the ADC device object.
 * @param expected Expected current ADC runtime state.
 * @param target Target ADC runtime state.
 * @return RT_TRUE if the state transition succeeded.
 */
static rt_bool_t adc_try_set_state(rt_adc_device_t device, enum rt_adc_state expected, enum rt_adc_state target)
{
    rt_atomic_t old_state;
    rt_bool_t matched;

    old_state = (rt_atomic_t)expected;
    matched = (rt_atomic_compare_exchange_strong(&device->state, &old_state, (rt_atomic_t)target) != 0) ? RT_TRUE : RT_FALSE;
    if (matched == RT_TRUE)
    {
        LOG_D("state transition: device=%s %s -> %s", device->parent.parent.name, adc_state_name(expected), adc_state_name(target));
    }
    else
    {
        LOG_W("state transition rejected: device=%s expected=%d actual=%d target=%d", device->parent.parent.name, (int)expected, (int)old_state, (int)target);
    }

    return matched;
}

/**
 * @brief Apply one ADC conversion session to the backend driver.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @return Operation status.
 */
static rt_err_t adc_session_config(rt_adc_device_t device, rt_uint32_t channels)
{
    rt_size_t channel_count;
    rt_err_t result;

    if ((device == RT_NULL) || (channels == 0U) ||
        (device->ops == RT_NULL) || (device->ops->core == RT_NULL) ||
        (device->ops->core->session_config == RT_NULL))
    {
        return -RT_EINVAL;
    }

    channel_count = rt_adc_channel_mask_count(channels);
    LOG_D("session config: device=%s channels=0x%08x count=%d",
          device->parent.parent.name, channels, channel_count);

    result = device->ops->core->session_config(device, channels);
    if (result != RT_EOK)
    {
        goto fail;
    }

    result = adc_cache_session_ctrl(device, channels);
    if (result != RT_EOK)
    {
        goto fail;
    }

    LOG_D("session configure done: device=%s", device->parent.parent.name);
    return RT_EOK;

fail:
    adc_clear_session_ctrl(device);
    LOG_E("session configure failed: device=%s result=%d", device->parent.parent.name, result);

    return result;
}

/**
 * @brief Get the raw sample index of one channel in a configured session.
 * @param session_channels Configured ADC session channel mask.
 * @param channel Single-channel mask to locate.
 * @param index Pointer to the output raw sample index.
 * @return Operation status.
 */
rt_err_t rt_adc_session_channel_index(rt_uint32_t session_channels, rt_uint32_t channel, rt_size_t *index)
{
    if ((index == RT_NULL) || (session_channels == 0U) || (rt_adc_channel_mask_count(channel) != 1U) || ((session_channels & channel) == 0U))
    {
        return -RT_EINVAL;
    }

    *index = rt_adc_channel_mask_count(session_channels & (channel - 1U));
    return RT_EOK;
}

/**
 * @brief Transfer ADC sequence samples after the session has been selected.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the sequence request object.
 * @param sample_total Number of samples to read.
 * @param read_count Pointer to the stored sample count.
 * @return Operation status.
 */
static rt_err_t adc_sequence_transfer_locked(rt_adc_device_t device, rt_uint32_t channels,
                                             const struct rt_adc_sequence_cfg *cfg, rt_size_t sample_total, rt_size_t *read_count)
{
    rt_err_t result;
    rt_err_t stop_result;
    rt_size_t index;

    *read_count = 0U;
    result = device->ops->sequence->start(device, channels, cfg);
    if (result != RT_EOK)
    {
        LOG_E("sequence start failed: device=%s result=%d", device->parent.parent.name, result);
        return result;
    }

    for (index = 0U; index < sample_total; index++)
    {
        result = device->ops->sequence->read(device, &cfg->buffer[index], cfg->timeout_ms);
        if (result != RT_EOK)
        {
            LOG_E("sequence read failed: device=%s index=%u result=%d",
                  device->parent.parent.name, (unsigned int)index, result);
            break;
        }

        (*read_count)++;
    }

    stop_result = device->ops->sequence->stop(device);
    if (stop_result != RT_EOK)
    {
        LOG_E("sequence stop failed: device=%s result=%d", device->parent.parent.name, stop_result);
        return (result != RT_EOK) ? result : stop_result;
    }

    return result;
}

/**
 * @brief Open the ADC device.
 * @param dev Pointer to the RT-Thread device object.
 * @param oflag Open flags.
 * @return Operation status.
 */
static rt_err_t adc_open_device(rt_device_t dev, rt_uint16_t oflag)
{
    rt_adc_device_t device;
    rt_err_t result;

    RT_UNUSED(oflag);

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    device = (rt_adc_device_t)dev;
    if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) ||
        (device->ops->core->open == RT_NULL))
    {
        return -RT_ENOSYS;
    }

    if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
    {
        return -RT_EBUSY;
    }

    LOG_D("open start: device=%s", device->parent.parent.name);
    result = device->ops->core->open(device);
    adc_set_state(device, RT_ADC_STATE_IDLE);
    if (result == RT_EOK)
    {
        LOG_I("open done: device=%s", device->parent.parent.name);
    }
    else
    {
        LOG_E("open failed: device=%s result=%d", device->parent.parent.name, result);
    }
    return result;
}

/**
 * @brief Close the ADC device.
 * @param dev Pointer to the RT-Thread device object.
 * @return Operation status.
 */
static rt_err_t adc_close_device(rt_device_t dev)
{
    rt_adc_device_t device;
    rt_err_t result;

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    device = (rt_adc_device_t)dev;
    if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) || (device->ops->core->close == RT_NULL))
    {
        return -RT_ENOSYS;
    }

    if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
    {
        return -RT_EBUSY;
    }

    LOG_D("close start: device=%s", device->parent.parent.name);
    result = device->ops->core->close(device);
    if (result == RT_EOK)
    {
        adc_clear_session_ctrl(device);
    }
    adc_set_state(device, RT_ADC_STATE_IDLE);
    if (result == RT_EOK)
    {
        LOG_I("close done: device=%s", device->parent.parent.name);
    }
    else
    {
        LOG_E("close failed: device=%s result=%d", device->parent.parent.name, result);
    }
    return result;
}

/**
 * @brief Read ADC raw samples from the configured session.
 * @param dev Pointer to the RT-Thread device object.
 * @param pos Unused read position.
 * @param buffer Pointer to the output sample buffer.
 * @param size Output sample buffer length in samples.
 * @return Number of samples read, or negative error code on failure.
 *
 * @note @p size must match the configured session channel count. The output
 *       order follows the ascending bit order of the configured channel mask.
 */
static rt_ssize_t adc_read_device(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_adc_device_t device;
    rt_uint32_t *values;
    rt_err_t result;

    RT_UNUSED(pos);

    if ((dev == RT_NULL) || (buffer == RT_NULL))
    {
        return -RT_EINVAL;
    }

    device = (rt_adc_device_t)dev;
    values = (rt_uint32_t *)buffer;

    if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
    {
        return -RT_EBUSY;
    }

    if ((device->session_ctrl.configured != RT_TRUE) || (device->session_ctrl.channel_count == 0U) ||
        (size != device->session_ctrl.channel_count))
    {
        result = -RT_EINVAL;
        goto out;
    }

    struct rt_adc_sequence_cfg sequence_cfg;
    rt_size_t read_count;

    rt_memset(&sequence_cfg, 0, sizeof(sequence_cfg));
    sequence_cfg.buffer = values;
    sequence_cfg.buffer_length = size;
    sequence_cfg.timeout_ms = -1;

    result = adc_sequence_transfer_locked(device, device->session_ctrl.channels,
                                          &sequence_cfg, size, &read_count);
    if ((result == RT_EOK) && (read_count != size))
    {
        result = -RT_ERROR;
    }

out:
    adc_set_state(device, RT_ADC_STATE_IDLE);

    return (result == RT_EOK) ? (rt_ssize_t)size : (rt_ssize_t)result;
}

/**
 * @brief Handle ADC control commands.
 * @param dev Pointer to the RT-Thread device object.
 * @param cmd Control command.
 * @param args Pointer to the control argument buffer.
 * @return Operation status.
 */
static rt_err_t adc_control_device(rt_device_t dev, int cmd, void *args)
{
    rt_adc_device_t device;
    rt_err_t result;

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    device = (rt_adc_device_t)dev;
    LOG_D("control request: device=%s cmd=%s(0x%x)", device->parent.parent.name, rt_adc_control_cmd_name(cmd), cmd);
    switch (cmd)
    {
    case RT_ADC_CMD_GET_RESOLUTION:
    case RT_ADC_CMD_GET_VREF_CHANNEL:
    case RT_ADC_CMD_CALC_VREF:
    case RT_ADC_CMD_CALIBRATE:
    case RT_ADC_CMD_SET_CONFIG:
    case RT_ADC_CMD_GET_CONFIG:
        if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) ||
            (device->ops->core->control == RT_NULL))
        {
            return -RT_ENOSYS;
        }
        if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
        {
            return -RT_EBUSY;
        }
        result = device->ops->core->control(device, cmd, args);
        adc_set_state(device, RT_ADC_STATE_IDLE);
        return result;

    case RT_ADC_CMD_CLEAR_CHANNEL_CONFIG:
        if (args != RT_NULL)
        {
            return -RT_EINVAL;
        }

        if ((dev->open_flag & RT_DEVICE_OFLAG_OPEN) == 0U)
        {
            return -RT_EIO;
        }

        if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) ||
            (device->ops->core->control == RT_NULL))
        {
            return -RT_ENOSYS;
        }

        if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
        {
            return -RT_EBUSY;
        }

        result = device->ops->core->control(device, cmd, RT_NULL);
        if (result == RT_EOK)
        {
            device->session_ctrl.channels = 0U;
            device->session_ctrl.channel_count = 0U;
            device->session_ctrl.configured = RT_FALSE;
        }

        adc_set_state(device, RT_ADC_STATE_IDLE);
        return result;

    case RT_ADC_CMD_SET_VREF:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }

        rt_uint32_t vref_mv = *((rt_uint32_t *)args);
        if (vref_mv == 0U)
        {
            return -RT_EINVAL;
        }

        if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
        {
            return -RT_EBUSY;
        }
        device->default_vref_mv = vref_mv;
        LOG_I("fallback vref updated: %lu mV", (unsigned long)device->default_vref_mv);
        adc_set_state(device, RT_ADC_STATE_IDLE);
        return RT_EOK;

    case RT_ADC_CMD_SET_SESSION:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }

        if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
        {
            return -RT_EBUSY;
        }
        result = adc_session_config(device, *((const rt_uint32_t *)args));
        adc_set_state(device, RT_ADC_STATE_IDLE);
        return result;

    default:
        if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) ||
            (device->ops->core->control == RT_NULL))
        {
            return -RT_ENOSYS;
        }
        if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
        {
            return -RT_EBUSY;
        }
        result = device->ops->core->control(device, cmd, args);
        adc_set_state(device, RT_ADC_STATE_IDLE);
        return result;
    }
}

#ifdef RT_USING_DEVICE_OPS
/**
 * @brief ADC device-framework operation table.
 */
static const struct rt_device_ops adc_device_ops = {
    RT_NULL,
    adc_open_device,
    adc_close_device,
    adc_read_device,
    RT_NULL,
    adc_control_device,
};
#endif /* RT_USING_DEVICE_OPS */

/**
 * @brief Register an ADC device.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the device name string.
 * @param ops Pointer to the ADC driver operation table.
 * @param user_data Pointer to the driver private data.
 * @return Operation status.
 */
rt_err_t rt_hw_adc_register(rt_adc_device_t device, const char *name, const struct rt_adc_ops *ops, const void *user_data)
{
    rt_err_t result;

    if ((device == RT_NULL) || (name == RT_NULL) || (ops == RT_NULL) ||
        (ops->core == RT_NULL) || (ops->core->session_config == RT_NULL) ||
        (ops->sequence == RT_NULL) || (ops->sequence->start == RT_NULL) ||
        (ops->sequence->read == RT_NULL) || (ops->sequence->stop == RT_NULL))
    {
        return -RT_EINVAL;
    }

    device->parent.type = RT_Device_Class_ADC;
    device->parent.rx_indicate = RT_NULL;
    device->parent.tx_complete = RT_NULL;
#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &adc_device_ops;
#else
    device->parent.init = RT_NULL;
    device->parent.open = adc_open_device;
    device->parent.close = adc_close_device;
    device->parent.read = adc_read_device;
    device->parent.write = RT_NULL;
    device->parent.control = adc_control_device;
#endif /* RT_USING_DEVICE_OPS */
    device->ops = ops;
    rt_atomic_store(&device->state, (rt_atomic_t)RT_ADC_STATE_IDLE);
    device->default_vref_mv = 0;
    adc_clear_session_ctrl(device);
    device->parent.user_data = (void *)user_data;

    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);
    if (result == RT_EOK)
    {
        LOG_I("device registered: %s", name);
    }
    else
    {
        LOG_E("device register failed: %s result=%d", name, result);
    }

    return result;
}

/**
 * @brief Read one validated ADC sequence while the caller owns the device state.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the validated sequence request object.
 * @param keep_state_on_success Whether to keep BUSY state after a successful read.
 * @param read_count Pointer to the stored sample count.
 * @return Operation status.
 *
 * @note A synchronous sequence request reads one scan frame only. Partial
 *       samples are reported through @p read_count when a read error or timeout
 *       happens after at least one sample is stored.
 */
static rt_err_t adc_read_sequence_locked(rt_adc_device_t device, rt_uint32_t channels,
                                         const struct rt_adc_sequence_cfg *cfg, rt_bool_t keep_state_on_success, rt_size_t *read_count)
{
    rt_err_t result;
    rt_size_t channel_count;

    *read_count = 0U;
    channel_count = rt_adc_channel_mask_count(channels);

    result = adc_session_config(device, channels);
    if (result != RT_EOK)
    {
        LOG_E("sequence config failed: device=%s result=%d", device->parent.parent.name, result);
        adc_set_state(device, RT_ADC_STATE_IDLE);
        return result;
    }

    result = adc_sequence_transfer_locked(device, channels, cfg, channel_count, read_count);

    if ((result != RT_EOK) || (keep_state_on_success != RT_TRUE))
    {
        adc_set_state(device, RT_ADC_STATE_IDLE);
    }

    return result;
}

/**
 * @brief Read one ADC sequence frame.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the sequence request object.
 * @param read_count Pointer to the stored sample count.
 * @return Operation status.
 */
rt_err_t rt_adc_read_sequence(rt_adc_device_t device, rt_uint32_t channels,
                              const struct rt_adc_sequence_cfg *cfg, rt_size_t *read_count)
{
    rt_size_t channel_count;

    if ((device == RT_NULL) || (cfg == RT_NULL) || (cfg->buffer == RT_NULL) ||
        (read_count == RT_NULL) || (channels == 0U) ||
        (device->ops == RT_NULL) || (device->ops->sequence == RT_NULL) || (device->ops->sequence->start == RT_NULL) ||
        (device->ops->sequence->read == RT_NULL) || (device->ops->sequence->stop == RT_NULL))
    {
        return -RT_EINVAL;
    }

    *read_count = 0U;
    channel_count = rt_adc_channel_mask_count(channels);
    if ((channel_count == 0U) || (cfg->buffer_length < channel_count))
    {
        return -RT_EINVAL;
    }

    if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
    {
        return -RT_EBUSY;
    }

    return adc_read_sequence_locked(device, channels, cfg, RT_FALSE, read_count);
}

/**
 * @brief Convert one ADC raw sample to millivolts.
 * @param raw_value Raw ADC sample code.
 * @param vref_mv ADC reference voltage in millivolts.
 * @param resolution_bits ADC resolution in bits.
 * @param voltage_mv Pointer to the output voltage in millivolts.
 * @return Operation status.
 *
 * ADC codes are treated as an inclusive range from 0 to
 * ``(1 << resolution_bits) - 1``. The calculation uses a 64-bit
 * intermediate value and rounds to the nearest integer millivolt.
 */
rt_err_t rt_adc_raw_to_voltage_mv(rt_uint32_t raw_value, rt_uint32_t vref_mv,
                                  rt_uint8_t resolution_bits, rt_uint32_t *voltage_mv)
{
    rt_uint64_t full_scale_code;

    if ((voltage_mv == RT_NULL) || (vref_mv == 0U) || (resolution_bits == 0U) || (resolution_bits > 32U))
    {
        return -RT_EINVAL;
    }

    full_scale_code = ((rt_uint64_t)1 << resolution_bits) - 1ULL;
    if ((rt_uint64_t)raw_value > full_scale_code)
    {
        return -RT_EINVAL;
    }

    /*
     * Convert ADC code to millivolts:
     *
     *     voltage_mv = raw * vref_mv / full_scale_code
     *     full_scale_code = (1 << resolution_bits) - 1
     *
     * ADC codes are treated as an inclusive range from 0 to full scale.
     * The multiplication is promoted to 64-bit first, then half of the
     * denominator is added to round to the nearest integer millivolt instead
     * of truncating non-exact divisions toward zero.
     */
    *voltage_mv = (rt_uint32_t)(((rt_uint64_t)raw_value * (rt_uint64_t)vref_mv + (full_scale_code / 2ULL)) / full_scale_code);

    return RT_EOK;
}

/**
 * @brief Convert one ADC raw sample to a scaled voltage in millivolts.
 * @param raw_value Raw ADC sample code.
 * @param vref_mv ADC reference voltage in millivolts.
 * @param resolution_bits ADC resolution in bits.
 * @param scale_num Voltage scaling numerator.
 * @param scale_den Voltage scaling denominator.
 * @param voltage_mv Pointer to the output scaled voltage in millivolts.
 * @return Operation status.
 *
 * The scaled voltage is calculated as:
 *
 *     raw_to_voltage_mv(raw_value) * scale_num / scale_den
 *
 * @note @p scale_num and @p scale_den may describe any positive rational
 *       scaling ratio that does not overflow the internal calculation. The
 *       final scaled millivolt value must fit in rt_uint32_t.
 *
 * @retval RT_EOK The conversion completed successfully.
 * @retval -RT_EINVAL A pointer is null, a scale argument is zero, the ADC
 *         conversion arguments are invalid, or the scaled result overflows
 *         rt_uint32_t.
 */
rt_err_t rt_adc_raw_to_scaled_voltage_mv(rt_uint32_t raw_value, rt_uint32_t vref_mv,
                                         rt_uint8_t resolution_bits, rt_uint32_t scale_num,
                                         rt_uint32_t scale_den, rt_uint32_t *voltage_mv)
{
    rt_uint32_t input_mv;
    rt_uint64_t numerator;
    rt_uint64_t rounding;
    rt_uint64_t scaled_mv;
    rt_err_t result;

    if ((voltage_mv == RT_NULL) || (scale_num == 0U) || (scale_den == 0U))
    {
        return -RT_EINVAL;
    }

    result = rt_adc_raw_to_voltage_mv(raw_value, vref_mv, resolution_bits, &input_mv);
    if (result != RT_EOK)
    {
        return result;
    }

    numerator = (rt_uint64_t)input_mv * (rt_uint64_t)scale_num;
    rounding = (rt_uint64_t)scale_den / 2ULL;

    if (numerator > (((rt_uint64_t)~0ULL) - rounding))
    {
        return -RT_EINVAL;
    }

    scaled_mv = (numerator + rounding) / (rt_uint64_t)scale_den;
    if (scaled_mv > RT_UINT32_MAX)
    {
        return -RT_EINVAL;
    }

    *voltage_mv = (rt_uint32_t)scaled_mv;
    return RT_EOK;
}

/**
 * @brief Read voltage values from the configured ADC session.
 * @param device Pointer to the ADC device object.
 * @param voltages_mv Pointer to the output voltage buffer in millivolts.
 * @param size Output voltage buffer length in samples.
 * @param timeout_ms Read timeout in milliseconds; negative means wait forever.
 * @return Operation status.
 *
 * @note @p size must match the configured session channel count. The output
 *       order follows the ascending bit order of the configured channel mask.
 *       The configured default_vref_mv is preferred for voltage conversion. If
 *       default_vref_mv is not configured, the backend VREF channel is used for
 *       VDDA calculation only when it is present in the configured session.
 */
rt_err_t rt_adc_voltage(rt_adc_device_t device, rt_uint32_t *voltages_mv, rt_size_t size, rt_int32_t timeout_ms)
{
    rt_uint32_t vref_mv;
    rt_uint32_t vref_value;
    rt_uint8_t resolution_bits;
    rt_uint8_t vref_channel;
    rt_size_t vref_index;
    rt_size_t index;
    struct rt_adc_sequence_cfg sequence_cfg;
    rt_size_t read_count;
    rt_err_t result;

    if ((device == RT_NULL) || (voltages_mv == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if ((device->ops == RT_NULL) || (device->ops->core == RT_NULL) || (device->ops->core->control == RT_NULL))
    {
        return -RT_ENOSYS;
    }

    if (adc_try_set_state(device, RT_ADC_STATE_IDLE, RT_ADC_STATE_LOCKED) != RT_TRUE)
    {
        return -RT_EBUSY;
    }

    LOG_D("voltage request: device=%s count=%u timeout=%ld", device->parent.parent.name, (unsigned int)size, (long)timeout_ms);

    if ((device->session_ctrl.configured != RT_TRUE) || (device->session_ctrl.channel_count == 0U) || (size != device->session_ctrl.channel_count))
    {
        result = -RT_EINVAL;
        goto out;
    }

    rt_memset(&sequence_cfg, 0, sizeof(sequence_cfg));
    sequence_cfg.buffer = voltages_mv;
    sequence_cfg.buffer_length = size;
    sequence_cfg.timeout_ms = timeout_ms;
    result = adc_sequence_transfer_locked(device, device->session_ctrl.channels,
                                          &sequence_cfg, size, &read_count);
    if ((result == RT_EOK) && (read_count != size))
    {
        result = -RT_ERROR;
    }
    if (result != RT_EOK)
    {
        LOG_E("voltage sample read failed: device=%s result=%d", device->parent.parent.name, result);
        goto out;
    }

    result = device->ops->core->control(device, RT_ADC_CMD_GET_RESOLUTION, &resolution_bits);
    if (result != RT_EOK)
    {
        goto out;
    }

    vref_mv = 0U;
    if (device->default_vref_mv != 0U)
    {
        vref_mv = device->default_vref_mv;
        result = RT_EOK;
    }
    else
    {
        vref_channel = 0U;
        result = device->ops->core->control(device, RT_ADC_CMD_GET_VREF_CHANNEL, &vref_channel);
        if ((result == RT_EOK) && (vref_channel < 32U) && ((device->session_ctrl.channels & RT_ADC_CHANNEL_MASK(vref_channel)) != 0U))
        {
            result = rt_adc_session_channel_index(device->session_ctrl.channels, RT_ADC_CHANNEL_MASK(vref_channel), &vref_index);
            if (result != RT_EOK)
            {
                goto out;
            }

            vref_value = voltages_mv[vref_index];
            result = device->ops->core->control(device, RT_ADC_CMD_CALC_VREF, &vref_value);
            if (result != RT_EOK)
            {
                LOG_E("vref calculate failed: device=%s raw=%lu result=%d",
                      device->parent.parent.name, (unsigned long)voltages_mv[vref_index], result);
                goto out;
            }

            if (vref_value == 0U)
            {
                result = -RT_EINVAL;
                goto out;
            }

            vref_mv = vref_value;
        }
        else
        {
            result = -RT_EINVAL;
            goto out;
        }
    }

    for (index = 0U; index < size; index++)
    {
        result = rt_adc_raw_to_voltage_mv(voltages_mv[index], vref_mv, resolution_bits, &voltages_mv[index]);
        if (result != RT_EOK)
        {
            goto out;
        }
    }

    LOG_D("voltage done: device=%s count=%u vref=%lu resolution=%u",
          device->parent.parent.name, (unsigned int)size,
          (unsigned long)vref_mv, (unsigned int)resolution_bits);
    result = RT_EOK;

out:
    adc_set_state(device, RT_ADC_STATE_IDLE);
    return result;
}

#endif /* defined(RT_USING_ADC_V2) */
