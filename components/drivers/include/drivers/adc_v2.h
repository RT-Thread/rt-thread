/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-21     wdfk-prog    add standalone adc v2 framework interface
 */

/**
 * @file adc_v2.h
 * @brief Standalone ADC V2 framework declarations.
 */

#ifndef __ADC_V2_H__
#define __ADC_V2_H__

#include <rtconfig.h>
#include "misc.h"
#if defined(RT_USING_ADC)
#error "ADC V2 uses the legacy ADC namespace; disable RT_USING_ADC before enabling ADC V2."
#endif /* defined(RT_USING_ADC) */

#include <rtatomic.h>
#include <rtdevice.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief ADC control command identifiers.
 */
enum rt_adc_control_cmd
{
    RT_ADC_CMD_GET_RESOLUTION = RT_DEVICE_CTRL_BASE(ADC) + 1, /**< Get resolution in bits. */
    RT_ADC_CMD_CALIBRATE,                                     /**< Run ADC calibration. */
    RT_ADC_CMD_SET_VREF,                                      /**< Set fallback VREF from rt_uint32_t mV. */
    RT_ADC_CMD_CALC_VREF,                                     /**< Calculate VDDA from a raw VREF sample. */
    RT_ADC_CMD_GET_VREF_CHANNEL,                              /**< Get the backend VREF sample channel as rt_uint8_t. */
    RT_ADC_CMD_SET_SESSION,                                   /**< Configure and cache conversion channels from rt_uint32_t mask. */
    RT_ADC_CMD_SET_CONFIG,                                    /**< Set backend private device configuration. */
    RT_ADC_CMD_GET_CONFIG,                                    /**< Get backend private device configuration. */
    RT_ADC_CMD_CLEAR_CHANNEL_CONFIG                           /**< Clear backend channel/rank configuration explicitly. */
};

/**
 * @brief ADC input mode request flags.
 */
enum rt_adc_input_mode
{
    RT_ADC_INPUT_MODE_SINGLE_ENDED = 0x01U, /**< Single-ended ADC input mode. */
    RT_ADC_INPUT_MODE_DIFFERENTIAL = 0x02U  /**< Differential ADC input mode. */
};

/**
 * @brief Build an ADC channel mask from one logical channel index.
 * @param _channel Logical ADC channel index.
 */
#define RT_ADC_CHANNEL_MASK(_channel) (1UL << (rt_uint32_t)(_channel))

/**
 * @brief ADC framework runtime state.
 */
enum rt_adc_state
{
    RT_ADC_STATE_IDLE = 0, /**< The ADC device is idle. */
    RT_ADC_STATE_LOCKED   /**< The ADC device is temporarily locked by a framework operation. */
};

struct rt_adc_device;
typedef struct rt_adc_device *rt_adc_device_t;

struct rt_adc_sequence_cfg;

/**
 * @brief ADC core driver operation table.
 */
struct rt_adc_core_ops
{
    /**
     * @brief Open and initialize the ADC hardware.
     * @param device Pointer to the ADC device object.
     * @return Operation status.
     */
    rt_err_t (*open)(struct rt_adc_device *device);

    /**
     * @brief Close and deinitialize the ADC hardware.
     * @param device Pointer to the ADC device object.
     * @return Operation status.
     */
    rt_err_t (*close)(struct rt_adc_device *device);


    /**
     * @brief Configure one ADC conversion session before data transfer.
     * @param device Pointer to the ADC device object.
     * @param channels ADC channel selection mask.
     * @return Operation status.
     */
    rt_err_t (*session_config)(struct rt_adc_device *device, rt_uint32_t channels);

    /**
     * @brief Handle ADC control commands.
     * @param device Pointer to the ADC device object.
     * @param cmd Control command.
     * @param args Pointer to the control argument buffer.
     * @return Operation status.
     */
    rt_err_t (*control)(struct rt_adc_device *device, int cmd, void *args);
};

/**
 * @brief ADC finite-sequence operation table.
 */
struct rt_adc_sequence_ops
{
    /**
     * @brief Start one active finite transfer session.
     * @param device Pointer to the ADC device object.
     * @param channels ADC channel selection mask.
     * @param cfg Pointer to the sequence request object.
     * @return Operation status.
     */
    rt_err_t (*start)(struct rt_adc_device *device, rt_uint32_t channels, const struct rt_adc_sequence_cfg *cfg);

    /**
     * @brief Read one converted sample from an active finite transfer session.
     * @param device Pointer to the ADC device object.
     * @param value Pointer to the output sample value.
     * @param timeout_ms Read timeout in milliseconds; negative means wait forever.
     * @return Operation status.
     */
    rt_err_t (*read)(struct rt_adc_device *device, rt_uint32_t *value, rt_int32_t timeout_ms);

    /**
     * @brief Stop one active finite transfer session.
     * @param device Pointer to the ADC device object.
     * @return Operation status.
     */
    rt_err_t (*stop)(struct rt_adc_device *device);
};


/**
 * @brief ADC driver operation table.
 */
struct rt_adc_ops
{
    const struct rt_adc_core_ops *core;         /**< Core operation table. */
    const struct rt_adc_sequence_ops *sequence; /**< Sequence-session operations. */
};

/**
 * @brief ADC synchronous one-frame sequence request.
 */
struct rt_adc_sequence_cfg
{
    rt_uint32_t *buffer;     /**< Destination sample buffer. */
    rt_size_t buffer_length; /**< Destination buffer length in samples. */
    rt_int32_t timeout_ms;   /**< Per-sample timeout; negative means wait forever. */
};

/**
 * @brief ADC active session runtime control block.
 */
struct rt_adc_session_ctrl
{
    rt_uint32_t channels;    /**< Cached active ADC channel selection mask. */
    rt_size_t channel_count; /**< Cached active session channel count. */
    rt_bool_t configured;    /**< Whether the cached session configuration is valid. */
};

/**
 * @brief ADC device object.
 */
struct rt_adc_device
{
    struct rt_device parent;                 /**< RT-Thread device object. */
    const struct rt_adc_ops *ops;            /**< ADC driver operation table. */
    rt_atomic_t state;                       /**< Atomic ADC runtime state. */
    rt_uint32_t default_vref_mv;             /**< Default reference voltage in millivolts. */
    struct rt_adc_session_ctrl session_ctrl; /**< ADC active session control block. */
};

/**
 * @brief Count selected ADC channels in one channel mask.
 * @param channels ADC channel selection mask.
 * @return Number of selected channels.
 */
rt_inline rt_size_t rt_adc_channel_mask_count(rt_uint32_t channels)
{
#if defined(__GNUC__) || defined(__clang__)
    return (rt_size_t)__builtin_popcount((unsigned int)channels);
#else
    rt_size_t count;

    count = 0U;
    while (channels != 0U)
    {
        channels &= channels - 1U;
        count++;
    }

    return count;
#endif /* defined(__GNUC__) || defined(__clang__) */
}

/**
 * @brief Take the lowest selected ADC channel from one channel mask.
 * @param channels Pointer to the ADC channel selection mask.
 * @return Selected channel index, or 0xff if the mask is empty.
 */
rt_inline rt_uint8_t rt_adc_channel_mask_take_lsb(rt_uint32_t *channels)
{
    rt_uint8_t bit;

    if ((channels == RT_NULL) || (*channels == 0U))
    {
        return 0xffU;
    }

#if defined(__GNUC__) || defined(__clang__)
    bit = (rt_uint8_t)__builtin_ctz((unsigned int)*channels);
#else
    for (bit = 0U; bit < 32U; bit++)
    {
        if ((*channels & RT_ADC_CHANNEL_MASK(bit)) != 0U)
        {
            break;
        }
    }
#endif /* defined(__GNUC__) || defined(__clang__) */

    *channels &= ~RT_ADC_CHANNEL_MASK(bit);
    return bit;
}

/**
 * @brief Register an ADC device with the RT-Thread device framework.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the ADC device name string.
 * @param ops Pointer to the ADC driver operation table.
 * @param user_data Pointer to driver private data.
 * @return Operation status.
 */
rt_err_t rt_hw_adc_register(rt_adc_device_t device, const char *name, const struct rt_adc_ops *ops, const void *user_data);

/**
 * @brief Get the raw sample index of one channel in an ADC session mask.
 * @param session_channels Configured ADC session channel mask.
 * @param channel Single-channel mask to locate.
 * @param index Pointer to the output raw sample index.
 * @return Operation status.
 */
rt_err_t rt_adc_session_channel_index(rt_uint32_t session_channels, rt_uint32_t channel, rt_size_t *index);


/**
 * @brief Read one ADC conversion sequence frame.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the ADC sequence request object.
 * @param read_count Pointer to the stored sample count.
 * @return Operation status.
 */
rt_err_t rt_adc_read_sequence(rt_adc_device_t device, rt_uint32_t channels,
                              const struct rt_adc_sequence_cfg *cfg, rt_size_t *read_count);

/**
 * @brief Convert one raw ADC sample to millivolts.
 * @param raw_value Raw ADC sample value.
 * @param vref_mv ADC reference voltage in millivolts.
 * @param resolution_bits ADC resolution in bits.
 * @param voltage_mv Pointer to the output voltage in millivolts.
 * @return Operation status.
 */
rt_err_t rt_adc_raw_to_voltage_mv(rt_uint32_t raw_value, rt_uint32_t vref_mv, rt_uint8_t resolution_bits, rt_uint32_t *voltage_mv);

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
rt_err_t rt_adc_raw_to_scaled_voltage_mv(rt_uint32_t raw_value, rt_uint32_t vref_mv, rt_uint8_t resolution_bits, rt_uint32_t scale_num, rt_uint32_t scale_den, rt_uint32_t *voltage_mv);

/**
 * @brief Read ADC samples and convert them to millivolts.
 * @param device Pointer to the ADC device object.
 * @param voltages_mv Pointer to the output voltage buffer in millivolts.
 * @param size Output voltage buffer length.
 * @param timeout_ms Per-sample timeout in milliseconds; negative means wait forever.
 * @return Operation status.
 *
 * @note This API reads the currently configured ADC session and does not modify
 *       the active channel mask. If default_vref_mv is zero, callers that need
 *       backend-calculated VDDA must include the backend VREF channel in the
 *       configured session. The VREF sample is used only as the reference for
 *       conversion and is not auto-inserted by this API.
 */
rt_err_t rt_adc_voltage(rt_adc_device_t device, rt_uint32_t *voltages_mv, rt_size_t size, rt_int32_t timeout_ms);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ADC_V2_H__ */
