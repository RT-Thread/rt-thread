/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-24     wdfk-prog    split stm32 adc v2 msh special commands
 */

/**
 * @file drv_adc_v2_msh.c
 * @brief STM32 ADC V2 FinSH/MSH special-channel commands.
 */
#include <rtconfig.h>

#include <stdlib.h>

#if defined(RT_USING_ADC_V2)

#include "drv_adc_v2_private.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4)

#define DRV_DEBUG
#define LOG_TAG "drv.adc.msh"
#include <drv_log.h>

#if defined(RT_USING_FINSH) && defined(RT_ADC_V2_USING_MSH)

/** @brief Default timeout in milliseconds for STM32 ADC MSH special reads. */
#define STM32_ADC_MSH_DEFAULT_READ_TIMEOUT_MS 1000

#if defined(STM32_ADC_HAS_LL_VREF_CALC)
#define STM32_ADC_MSH_HAS_VREF_READ 1
#endif /* defined(STM32_ADC_HAS_LL_VREF_CALC) */

#if defined(STM32_ADC_HAS_LL_TEMPERATURE_CALC) || defined(STM32_ADC_HAS_TEMPSENSOR_CALIBRATION_DATA)
#define STM32_ADC_MSH_HAS_TEMPSENSOR_READ 1
#endif /* defined(STM32_ADC_HAS_LL_TEMPERATURE_CALC) || defined(STM32_ADC_HAS_TEMPSENSOR_CALIBRATION_DATA) */

#define STM32_ADC_MSH_HAS_VBAT_READ 1

#if defined(STM32_ADC_MSH_HAS_VREF_READ) || defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ) || \
    defined(STM32_ADC_MSH_HAS_VBAT_READ)
#define STM32_ADC_MSH_HAS_SPECIAL_READ 1
#endif /* defined(STM32_ADC_MSH_HAS_VREF_READ) || defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ) || defined(STM32_ADC_MSH_HAS_VBAT_READ) */

#if defined(STM32_ADC_MSH_HAS_SPECIAL_READ)
/**
 * @brief Sample data read from one STM32 internal ADC channel.
 */
struct stm32_adc_special_sample
{
    rt_uint32_t raw_value;      /**< Raw ADC sample of the requested channel. */
    rt_uint32_t vref_mv;        /**< VDDA calculated from VREFINT, in millivolts. */
    rt_uint8_t resolution_bits; /**< ADC conversion resolution in bits. */
};
#endif /* defined(STM32_ADC_MSH_HAS_SPECIAL_READ) */

#if defined(STM32_ADC_MSH_HAS_SPECIAL_READ)
/**
 * @brief Get VDDA in millivolts for STM32 ADC special-channel conversion.
 * @param device Pointer to the ADC device object.
 * @param samples Pointer to the ADC sample buffer containing VREFINT raw data.
 * @param has_vref_sample Whether @p samples contains a valid VREFINT sample.
 * @param vref_index Index of the VREFINT sample in @p samples.
 * @param vref_mv Pointer to the output analog reference voltage in millivolts.
 * @return Operation status.
 *
 * This helper prefers the sampled VREFINT path when a VREFINT sample is
 * available. If dynamic VREF calculation is unavailable or VREFINT is not part
 * of the current session, it falls back to the framework default_vref_mv.
 */
static rt_err_t stm32_adc_msh_get_vref_mv(rt_adc_device_t device, const rt_uint32_t *samples, rt_bool_t has_vref_sample,
                                          rt_size_t vref_index, rt_uint32_t *vref_mv)
{
    if (has_vref_sample == RT_TRUE)
    {
#if defined(STM32_ADC_HAS_LL_VREF_CALC)
        rt_err_t result;
        *vref_mv = samples[vref_index];
        result = stm32_adc_calc_vref_mv(device, vref_mv);
        if (result == RT_EOK)
        {
            return RT_EOK;
        }

        if (result != -RT_ENOSYS)
        {
            return result;
        }
#else
        RT_UNUSED(samples);
        RT_UNUSED(vref_index);
#endif /* defined(STM32_ADC_HAS_LL_VREF_CALC) */
    }

    if (device->default_vref_mv != 0U)
    {
        *vref_mv = device->default_vref_mv;
        return RT_EOK;
    }

    return (has_vref_sample == RT_TRUE) ? -RT_ENOSYS : -RT_EINVAL;
}

/**
 * @brief Read one preconfigured STM32 internal ADC channel sample.
 * @param device Pointer to the ADC device object.
 * @param channel Logical ADC channel identifier.
 * @param need_vref Whether the caller needs VDDA for value conversion.
 * @param timeout_ms Per-sample timeout in milliseconds; negative means wait forever.
 * @param sample Pointer to the output special-channel sample.
 * @return Operation status.
 *
 * This helper reads using the currently configured framework session. The
 * caller must first configure an active framework session containing the
 * requested special channel. If @p need_vref is RT_TRUE, VDDA is calculated
 * from VREFINT when VREFINT is present in the session; otherwise the configured
 * default_vref_mv is used as the fallback reference voltage.
 */
static rt_err_t stm32_adc_read_special_sample(rt_adc_device_t device, rt_uint8_t channel, rt_bool_t need_vref,
                                              rt_int32_t timeout_ms, struct stm32_adc_special_sample *sample)
{
    struct stm32_adc *adc;
    struct rt_adc_sequence_cfg sequence_cfg;
    rt_uint32_t samples[STM32_ADC_MAX_CHANNELS];
    rt_uint8_t vref_channel;
    rt_bool_t has_vref_sample;
    rt_size_t sample_count;
    rt_size_t sample_index;
    rt_size_t vref_index;
    rt_size_t read_count;
    rt_err_t result;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }


    if ((device->session_ctrl.configured != RT_TRUE) || (device->session_ctrl.channel_count == 0U) ||
        ((device->session_ctrl.channels & RT_ADC_CHANNEL_MASK(channel)) == 0U))
    {
        return -RT_EINVAL;
    }

    sample_count = device->session_ctrl.channel_count;
    if (sample_count > RT_ARRAY_SIZE(samples))
    {
        return -RT_EINVAL;
    }

    result = rt_adc_session_channel_index(device->session_ctrl.channels, RT_ADC_CHANNEL_MASK(channel), &sample_index);
    if (result != RT_EOK)
    {
        return result;
    }

    vref_index = 0U;
    has_vref_sample = RT_FALSE;

    if (need_vref == RT_TRUE)
    {
        result = stm32_adc_get_vref_logical_channel(adc, &vref_channel);
        if (result == RT_EOK)
        {
            if ((device->session_ctrl.channels & RT_ADC_CHANNEL_MASK(vref_channel)) != 0U)
            {
                result = rt_adc_session_channel_index(device->session_ctrl.channels,
                                                      RT_ADC_CHANNEL_MASK(vref_channel), &vref_index);
                if (result != RT_EOK)
                {
                    return result;
                }

                has_vref_sample = RT_TRUE;
            }
            else if (device->default_vref_mv == 0U)
            {
                return -RT_EINVAL;
            }
        }
        else if (device->default_vref_mv == 0U)
        {
            return result;
        }
    }

    rt_memset(&sequence_cfg, 0, sizeof(sequence_cfg));
    rt_memset(samples, 0, sizeof(samples));
    sequence_cfg.buffer = samples;
    sequence_cfg.buffer_length = sample_count;
    sequence_cfg.timeout_ms = timeout_ms;

    result = rt_adc_read_sequence(device, device->session_ctrl.channels, &sequence_cfg, &read_count);
    if (result != RT_EOK)
    {
        return result;
    }

    if (read_count <= sample_index)
    {
        return -RT_ERROR;
    }

    sample->raw_value = samples[sample_index];
    sample->vref_mv = 0U;
    sample->resolution_bits = stm32_adc_get_resolution_bits(adc);

    if (need_vref == RT_TRUE)
    {
        if (sample->resolution_bits == 0U)
        {
            return -RT_EINVAL;
        }

        result = stm32_adc_msh_get_vref_mv(device, samples, has_vref_sample, vref_index, &sample->vref_mv);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    return RT_EOK;
}
#endif /* defined(STM32_ADC_MSH_HAS_SPECIAL_READ) */

#if defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ)
/**
 * @brief Check whether STM32 ADC MSH can provide VDDA for temperature conversion.
 * @param adc Pointer to the STM32 ADC device object.
 * @param device Pointer to the ADC device object.
 * @return RT_TRUE if temperature conversion can obtain VDDA, otherwise RT_FALSE.
 *
 * Temperature conversion requires VDDA in millivolts. Dynamic VDDA calculation
 * requires a supported VREFINT logical channel and LL VREF calculation support;
 * otherwise the framework default_vref_mv must be configured.
 */
static rt_bool_t stm32_adc_msh_has_temperature_vref_source(struct stm32_adc *adc, rt_adc_device_t device)
{
    rt_uint8_t vref_channel;

    if ((adc == RT_NULL) || (device == RT_NULL))
    {
        return RT_FALSE;
    }

    if (device->default_vref_mv != 0U)
    {
        return RT_TRUE;
    }

#if defined(STM32_ADC_HAS_LL_VREF_CALC)
    if (stm32_adc_get_vref_logical_channel(adc, &vref_channel) == RT_EOK)
    {
        return RT_TRUE;
    }
#else
    RT_UNUSED(vref_channel);
#endif /* defined(STM32_ADC_HAS_LL_VREF_CALC) */

    return RT_FALSE;
}
#endif /* defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ) */

#if defined(STM32_ADC_MSH_HAS_VREF_READ)
/**
 * @brief Read VREFINT and calculate VDDA in millivolts for STM32 ADC MSH.
 * @param device Pointer to the ADC device object.
 * @param timeout_ms Per-sample timeout in milliseconds; negative means wait forever.
 * @param vref_mv Pointer to the output analog reference voltage in millivolts.
 * @return Operation status.
 *
 * VREF read requires LL VREF calculation support. Without that support, the
 * command is reported as unsupported instead of returning default_vref_mv.
 */
static rt_err_t stm32_adc_msh_read_vref(rt_adc_device_t device, rt_int32_t timeout_ms, rt_uint32_t *vref_mv)
{
    struct stm32_adc *adc;
    struct stm32_adc_special_sample sample;
    rt_uint8_t vref_channel;
    rt_err_t result;

    if ((device == RT_NULL) || (vref_mv == RT_NULL))
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_get_vref_logical_channel(adc, &vref_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_read_special_sample(device, vref_channel, RT_FALSE, timeout_ms, &sample);
    if (result != RT_EOK)
    {
        return result;
    }

    return stm32_adc_msh_get_vref_mv(device, &sample.raw_value, RT_TRUE, 0U, vref_mv);
}
#endif /* defined(STM32_ADC_MSH_HAS_VREF_READ) */

#if defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ)
/**
 * @brief Read the STM32 internal temperature sensor for ADC MSH.
 * @param device Pointer to the ADC device object.
 * @param timeout_ms Per-sample timeout in milliseconds; negative means wait forever.
 * @param temperature_c Pointer to the output temperature in degrees Celsius.
 * @return Operation status.
 */
static rt_err_t stm32_adc_msh_read_temperature(rt_adc_device_t device, rt_int32_t timeout_ms, rt_int32_t *temperature_c)
{
    struct stm32_adc *adc;
    struct stm32_adc_special_sample sample;
    rt_uint8_t tempsensor_channel;
    rt_err_t result;

    if ((device == RT_NULL) || (temperature_c == RT_NULL))
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_get_tempsensor_logical_channel(adc, &tempsensor_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_read_special_sample(device, tempsensor_channel, RT_TRUE, timeout_ms, &sample);
    if (result != RT_EOK)
    {
        return result;
    }

    return stm32_adc_calc_temperature(device, sample.raw_value, sample.vref_mv, sample.resolution_bits, temperature_c);
}
#endif /* defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ) */

#if defined(STM32_ADC_MSH_HAS_VBAT_READ)
/**
 * @brief Read raw VBAT ADC sample for STM32 ADC MSH.
 * @param device Pointer to the ADC device object.
 * @param timeout_ms Per-sample timeout in milliseconds; negative means wait forever.
 * @param raw_value Pointer to the output raw VBAT ADC sample.
 * @return Operation status.
 */
static rt_err_t stm32_adc_msh_read_vbat(rt_adc_device_t device, rt_int32_t timeout_ms, rt_uint32_t *raw_value)
{
    struct stm32_adc *adc;
    struct stm32_adc_special_sample sample;
    rt_uint8_t vbat_channel;
    rt_err_t result;

    if ((device == RT_NULL) || (raw_value == RT_NULL))
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_get_vbat_logical_channel(adc, &vbat_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_read_special_sample(device, vbat_channel, RT_FALSE, timeout_ms, &sample);
    if (result != RT_EOK)
    {
        return result;
    }

    *raw_value = sample.raw_value;
    return RT_EOK;
}
#endif /* defined(STM32_ADC_MSH_HAS_VBAT_READ) */

/**
 * @brief Get one STM32 ADC special MSH item property.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the item name.
 * @param channel Pointer to the output logical channel.
 * @param need_vref Optional pointer to the output VREF requirement flag.
 * @param unit Optional pointer to the output display unit string.
 * @return Operation status.
 */
static rt_err_t stm32_adc_msh_get_item(rt_adc_device_t device, const char *name, rt_uint8_t *channel,
                                       rt_bool_t *need_vref, const char **unit)
{
    struct stm32_adc *adc;

    if ((device == RT_NULL) || (name == RT_NULL) || (channel == RT_NULL))
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

#if defined(STM32_ADC_MSH_HAS_VREF_READ)
    if (rt_strcmp(name, "vref") == 0)
    {
        if (need_vref != RT_NULL)
        {
            *need_vref = RT_FALSE;
        }
        if (unit != RT_NULL)
        {
            *unit = "mV";
        }
        return stm32_adc_get_vref_logical_channel(adc, channel);
    }
#endif /* defined(STM32_ADC_MSH_HAS_VREF_READ) */

#if defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ)
    if (rt_strcmp(name, "temp") == 0)
    {
        if (stm32_adc_get_tempsensor_logical_channel(adc, channel) != RT_EOK)
        {
            return -RT_ENOSYS;
        }

        if (stm32_adc_msh_has_temperature_vref_source(adc, device) != RT_TRUE)
        {
            return -RT_ENOSYS;
        }

        if (need_vref != RT_NULL)
        {
            *need_vref = RT_TRUE;
        }
        if (unit != RT_NULL)
        {
            *unit = "C";
        }
        return RT_EOK;
    }
#endif /* defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ) */

#if defined(STM32_ADC_MSH_HAS_VBAT_READ)
    if (rt_strcmp(name, "vbat") == 0)
    {
        if (stm32_adc_get_vbat_logical_channel(adc, channel) != RT_EOK)
        {
            return -RT_ENOSYS;
        }

        if (need_vref != RT_NULL)
        {
            *need_vref = RT_FALSE;
        }
        if (unit != RT_NULL)
        {
            *unit = "raw";
        }
        return RT_EOK;
    }
#endif /* defined(STM32_ADC_MSH_HAS_VBAT_READ) */

    return -RT_ENOSYS;
}

/**
 * @brief Print one supported STM32 ADC special MSH item if available.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the item name.
 * @return RT_TRUE if the item was printed, otherwise RT_FALSE.
 */
static rt_bool_t stm32_adc_msh_print_item(rt_adc_device_t device, const char *name)
{
    struct stm32_adc *adc;
    const char *unit;
    rt_bool_t need_vref;
    rt_bool_t has_vref_channel;
    rt_uint8_t channel;
    rt_uint8_t vref_channel;
    rt_err_t result;

    if (stm32_adc_msh_get_item(device, name, &channel, &need_vref, &unit) != RT_EOK)
    {
        return RT_FALSE;
    }

    has_vref_channel = RT_FALSE;
    vref_channel = 0U;

    if (need_vref == RT_TRUE)
    {
        adc = (struct stm32_adc *)device->parent.user_data;
        if (adc == RT_NULL)
        {
            return RT_FALSE;
        }

        result = stm32_adc_get_vref_logical_channel(adc, &vref_channel);
        if (result == RT_EOK)
        {
            has_vref_channel = RT_TRUE;
        }
        else if (device->default_vref_mv == 0U)
        {
            rt_kprintf("  %s: unsupported, missing vref/default_vref\n", name);
            return RT_FALSE;
        }
    }

    rt_kprintf("  %s: channel=%u unit=%s", name, (unsigned int)channel, unit);

    if (need_vref == RT_TRUE)
    {
        if (has_vref_channel == RT_TRUE)
        {
            rt_kprintf(" needs=vref channel=%u", (unsigned int)vref_channel);
        }
        else
        {
            rt_kprintf(" needs=default_vref");
        }
    }

    rt_kprintf("\n");

    return RT_TRUE;
}
/**
 * @brief Print supported STM32 ADC special MSH items for the selected device.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_msh_special_list(rt_adc_device_t device)
{
    rt_bool_t has_temp;
    rt_size_t count;

    count = 0U;
    count += (stm32_adc_msh_print_item(device, "vref") == RT_TRUE) ? 1U : 0U;
    has_temp = stm32_adc_msh_print_item(device, "temp");

    count += (has_temp == RT_TRUE) ? 1U : 0U;
    count += (stm32_adc_msh_print_item(device, "vbat") == RT_TRUE) ? 1U : 0U;

    if (count == 0U)
    {
        rt_kprintf("  no STM32 ADC special channels supported by current device\n");
    }

    return RT_EOK;
}

/**
 * @brief Print STM32 ADC special MSH command usage.
 */
static void stm32_adc_msh_special_usage(void)
{
    rt_kprintf("STM32 ADC special commands:\n");
    rt_kprintf("  adc special list\n");
    rt_kprintf("  adc special read <item-from-list> [timeout_ms]\n");
    rt_kprintf("    timeout_ms defaults to 1000; negative means wait forever\n");
    rt_kprintf("    run adc special list first, then use the printed adc config command\n");
    rt_kprintf("    temp accuracy depends on datasheet sampling time; adc special list shows item notes\n");
}

/**
 * @brief Print ADC config command for one STM32 ADC special MSH item.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the item name.
 */
static void stm32_adc_msh_print_config_hint(rt_adc_device_t device, const char *name)
{
    struct stm32_adc *adc;
    rt_bool_t need_vref;
    rt_uint8_t channel;
    rt_uint8_t vref_channel;

    if ((device == RT_NULL) || (name == RT_NULL))
    {
        return;
    }

    if (stm32_adc_msh_get_item(device, name, &channel, &need_vref, RT_NULL) != RT_EOK)
    {
        return;
    }

    if (need_vref != RT_TRUE)
    {
        rt_kprintf("configure with: adc config %u\n", (unsigned int)channel);
        return;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if ((adc != RT_NULL) && (stm32_adc_get_vref_logical_channel(adc, &vref_channel) == RT_EOK))
    {
        rt_kprintf("configure with: adc config %u %u\n", (unsigned int)channel, (unsigned int)vref_channel);
    }
    else
    {
        rt_kprintf("configure with: adc config %u\n", (unsigned int)channel);
    }
}

/**
 * @brief Parse one optional STM32 ADC special-read timeout argument.
 * @param arg Pointer to the timeout argument string.
 * @param timeout_ms Pointer to the output timeout in milliseconds.
 * @return Operation status.
 *
 * A negative timeout keeps the ADC framework convention of waiting forever.
 */
static rt_err_t stm32_adc_msh_parse_timeout(const char *arg, rt_int32_t *timeout_ms)
{
    char *endptr;
    long value;

    if ((arg == RT_NULL) || (timeout_ms == RT_NULL) || (*arg == '\0'))
    {
        return -RT_EINVAL;
    }

    endptr = RT_NULL;
    value = strtol(arg, &endptr, 0);
    if ((endptr == arg) || (endptr == RT_NULL) || (*endptr != '\0'))
    {
        return -RT_EINVAL;
    }

    if ((value > 2147483647L) || (value < (-2147483647L - 1L)))
    {
        return -RT_EINVAL;
    }

    *timeout_ms = (rt_int32_t)value;
    return RT_EOK;
}

/**
 * @brief Print and normalize one STM32 ADC special MSH command result.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the requested item name.
 * @param action Pointer to the action name.
 * @param result Operation status to normalize.
 * @return Operation status for the framework-level command dispatcher.
 */
static rt_err_t stm32_adc_msh_finish_special_result(rt_adc_device_t device, const char *name,
                                                    const char *action, rt_err_t result)
{
    if (result == RT_EOK)
    {
        return RT_EOK;
    }

    rt_kprintf("%s %s failed: %d\n", name, action, result);

    if (result == -RT_EINVAL)
    {
        rt_kprintf("run adc special list first or use the following command before reading\n");
        stm32_adc_msh_print_config_hint(device, name);
    }

    return (result == -RT_ENOSYS) ? -RT_ERROR : result;
}

/**
 * @brief Handle one STM32 ADC special MSH read command.
 * @param device Pointer to the ADC device object.
 * @param argc Argument count excluding the top-level adc command.
 * @param argv Argument vector excluding the top-level adc command.
 * @return Operation status.
 */
static rt_err_t stm32_adc_msh_special_read(rt_adc_device_t device, int argc, char **argv)
{
    const char *name;
    rt_uint8_t channel;
    rt_int32_t timeout_ms;
    rt_err_t result;

    if ((argc != 3) && (argc != 4))
    {
        stm32_adc_msh_special_usage();
        return -RT_EINVAL;
    }

    name = argv[2];
    timeout_ms = STM32_ADC_MSH_DEFAULT_READ_TIMEOUT_MS;
    if ((argc == 4) && (stm32_adc_msh_parse_timeout(argv[3], &timeout_ms) != RT_EOK))
    {
        rt_kprintf("invalid timeout_ms: %s\n", argv[3]);
        return -RT_EINVAL;
    }

    result = stm32_adc_msh_get_item(device, name, &channel, RT_NULL, RT_NULL);
    if (result != RT_EOK)
    {
        rt_kprintf("%s is not supported by current STM32 ADC device\n", name);
        return -RT_EINVAL;
    }

#if defined(STM32_ADC_MSH_HAS_VREF_READ)
    if (rt_strcmp(name, "vref") == 0)
    {
        rt_uint32_t value_mv;
        result = stm32_adc_msh_read_vref(device, timeout_ms, &value_mv);
        if (result == RT_EOK)
        {
            rt_kprintf("vref: %lu mV\n", (unsigned long)value_mv);
        }
        return stm32_adc_msh_finish_special_result(device, name, "read", result);
    }
#endif /* defined(STM32_ADC_MSH_HAS_VREF_READ) */

#if defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ)
    if (rt_strcmp(name, "temp") == 0)
    {
        rt_int32_t temperature_c;
        result = stm32_adc_msh_read_temperature(device, timeout_ms, &temperature_c);
        if (result == RT_EOK)
        {
            rt_kprintf("temp: %ld C\n", (long)temperature_c);
        }
        return stm32_adc_msh_finish_special_result(device, name, "read", result);
    }
#endif /* defined(STM32_ADC_MSH_HAS_TEMPSENSOR_READ) */

#if defined(STM32_ADC_MSH_HAS_VBAT_READ)
    if (rt_strcmp(name, "vbat") == 0)
    {
        rt_uint32_t raw_value;
        result = stm32_adc_msh_read_vbat(device, timeout_ms, &raw_value);
        if (result == RT_EOK)
        {
            rt_kprintf("vbat: %lu raw\n", (unsigned long)raw_value);
        }
        return stm32_adc_msh_finish_special_result(device, name, "read", result);
    }
#endif /* defined(STM32_ADC_MSH_HAS_VBAT_READ) */

    RT_UNUSED(channel);
    return -RT_ENOSYS;
}

/**
 * @brief Print STM32 ADC backend-specific FinSH command usage.
 */
void rt_adc_msh_special_help(void)
{
    stm32_adc_msh_special_usage();
}

/**
 * @brief Handle STM32 ADC backend-specific FinSH commands.
 * @param device Pointer to the selected ADC device object.
 * @param argc Argument count excluding the top-level adc command.
 * @param argv Argument vector excluding the top-level adc command.
 * @return Operation status.
 */
rt_err_t rt_adc_msh_special(rt_adc_device_t device, int argc, char **argv)
{
    if ((device == RT_NULL) || (argv == RT_NULL) || (argc <= 0))
    {
        return -RT_EINVAL;
    }

    if (rt_strcmp(argv[0], "special") != 0)
    {
        return -RT_ENOSYS;
    }

    if ((argc == 2) && (rt_strcmp(argv[1], "list") == 0))
    {
        return stm32_adc_msh_special_list(device);
    }

    if ((argc >= 3) && (rt_strcmp(argv[1], "read") == 0))
    {
        return stm32_adc_msh_special_read(device, argc, argv);
    }

    stm32_adc_msh_special_usage();
    return -RT_EINVAL;
}

#endif /* defined(RT_USING_FINSH) && defined(RT_ADC_V2_USING_MSH) */

#endif /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4) */

#endif /* defined(RT_USING_ADC_V2) */
