/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-21     wdfk-prog    add stm32 adc v2 driver implementation
 */

/**
 * @file drv_adc_v2.c
 * @brief STM32 ADC V2 driver implementation.
 */
#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)

#include "drv_config.h"
#include "drv_adc_v2_private.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4)

#define DRV_DEBUG
#define LOG_TAG "drv.adc"
#include <drv_log.h>

/**
 * @brief Apply the STM32 private oversampling configuration to the ADC init structure.
 * @param adc Pointer to the STM32 ADC device object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_apply_oversampling(struct stm32_adc *adc)
{
#if defined(STM32_ADC_HAS_HW_OVERSAMPLING)
    if (adc->config.oversampling_ratio == 0U)
    {
        adc->handle.Init.OversamplingMode = DISABLE;
        return RT_EOK;
    }

    adc->handle.Init.OversamplingMode = ENABLE;
    adc->handle.Init.Oversampling.Ratio = adc->config.oversampling_ratio;
    adc->handle.Init.Oversampling.RightBitShift = adc->config.oversampling_right_shift;
    adc->handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
    adc->handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
    return RT_EOK;
#else
    return (adc->config.oversampling_ratio == 0U) ? RT_EOK : -RT_ENOSYS;
#endif /* defined(STM32_ADC_HAS_HW_OVERSAMPLING) */
}

/**
 * @brief STM32 ADC object indexes.
 */
enum stm32_adc_index
{
#ifdef BSP_USING_ADC1
    ADC1_INDEX,
#endif /* BSP_USING_ADC1 */
#ifdef BSP_USING_ADC2
    ADC2_INDEX,
#endif /* BSP_USING_ADC2 */
#ifdef BSP_USING_ADC3
    ADC3_INDEX,
#endif /* BSP_USING_ADC3 */
#ifdef BSP_USING_ADC4
    ADC4_INDEX,
#endif /* BSP_USING_ADC4 */
};

/**
 * @brief STM32 ADC device table.
 */
static struct stm32_adc stm32_adc_obj[] = {
#ifdef BSP_USING_ADC1
    ADC1_V2_CONFIG,
#endif /* BSP_USING_ADC1 */
#ifdef BSP_USING_ADC2
    ADC2_V2_CONFIG,
#endif /* BSP_USING_ADC2 */
#ifdef BSP_USING_ADC3
    ADC3_V2_CONFIG,
#endif /* BSP_USING_ADC3 */
#ifdef BSP_USING_ADC4
    ADC4_V2_CONFIG,
#endif /* BSP_USING_ADC4 */
};

/**
 * @brief ADC hardware channel mapping table.
 */
static const uint32_t stm32_adc_channel_table[STM32_ADC_MAX_CHANNELS] = {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15,
#if STM32_ADC_MAX_CHANNELS > 16
    STM32_ADC_CHANNEL_16,
#endif /* STM32_ADC_MAX_CHANNELS > 16 */
#if STM32_ADC_MAX_CHANNELS > 17
    STM32_ADC_CHANNEL_17,
#endif /* STM32_ADC_MAX_CHANNELS > 17 */
#if STM32_ADC_MAX_CHANNELS > 18
    STM32_ADC_CHANNEL_18,
#endif /* STM32_ADC_MAX_CHANNELS > 18 */
#if STM32_ADC_MAX_CHANNELS > 19
    STM32_ADC_CHANNEL_19,
#endif /* STM32_ADC_MAX_CHANNELS > 19 */
#if STM32_ADC_MAX_CHANNELS > 20
    STM32_ADC_CHANNEL_20,
#endif /* STM32_ADC_MAX_CHANNELS > 20 */
#if STM32_ADC_MAX_CHANNELS > 21
    STM32_ADC_CHANNEL_21,
#endif /* STM32_ADC_MAX_CHANNELS > 21 */
#if STM32_ADC_MAX_CHANNELS > 22
    STM32_ADC_CHANNEL_22,
#endif /* STM32_ADC_MAX_CHANNELS > 22 */
#if STM32_ADC_MAX_CHANNELS > 23
    STM32_ADC_CHANNEL_23,
#endif /* STM32_ADC_MAX_CHANNELS > 23 */
#if STM32_ADC_MAX_CHANNELS > 24
    STM32_ADC_CHANNEL_24,
#endif /* STM32_ADC_MAX_CHANNELS > 24 */
#if STM32_ADC_MAX_CHANNELS > 25
    STM32_ADC_CHANNEL_25,
#endif /* STM32_ADC_MAX_CHANNELS > 25 */
#if STM32_ADC_MAX_CHANNELS > 26
    STM32_ADC_CHANNEL_26,
#endif /* STM32_ADC_MAX_CHANNELS > 26 */
#if STM32_ADC_MAX_CHANNELS > 27
    STM32_ADC_CHANNEL_27,
#endif /* STM32_ADC_MAX_CHANNELS > 27 */
#if STM32_ADC_MAX_CHANNELS > 28
    STM32_ADC_CHANNEL_28,
#endif /* STM32_ADC_MAX_CHANNELS > 28 */
#if STM32_ADC_MAX_CHANNELS > 29
    STM32_ADC_CHANNEL_29,
#endif /* STM32_ADC_MAX_CHANNELS > 29 */
#if STM32_ADC_MAX_CHANNELS > 30
    STM32_ADC_CHANNEL_30,
#endif /* STM32_ADC_MAX_CHANNELS > 30 */
#if STM32_ADC_MAX_CHANNELS > 31
    STM32_ADC_CHANNEL_31,
#endif /* STM32_ADC_MAX_CHANNELS > 31 */
};

/**
 * @brief STM32 internal ADC channel capability entry.
 */
struct stm32_adc_internal_channel
{
    int logical_channel;                    /**< RT-Thread logical channel number, or negative if unsupported. */
    uint32_t hal_channel;                   /**< Primary HAL channel identifier. */
    rt_uint32_t instance_mask;              /**< ADC instances that can use the primary HAL channel. */
    uint32_t alternate_hal_channel;         /**< Alternate HAL channel identifier for instance-specific mappings. */
    rt_uint32_t alternate_instance_mask;    /**< ADC instances that can use the alternate HAL channel. */
};

/**
 * @brief STM32 internal ADC channel capability table.
 */
static const struct stm32_adc_internal_channel stm32_adc_internal_channels[] = {
    { STM32_ADC_TEMP_CHANNEL, STM32_ADC_TEMP_HAL_CHANNEL, STM32_ADC_TEMP_INSTANCE_MASK,
      STM32_ADC_TEMP_ALT_HAL_CHANNEL, STM32_ADC_TEMP_ALT_INSTANCE_MASK },
    { STM32_ADC_VBAT_CHANNEL, STM32_ADC_VBAT_HAL_CHANNEL, STM32_ADC_VBAT_INSTANCE_MASK,
      STM32_ADC_VBAT_ALT_HAL_CHANNEL, STM32_ADC_VBAT_ALT_INSTANCE_MASK },
    { STM32_ADC_VREF_CHANNEL, STM32_ADC_VREF_HAL_CHANNEL, STM32_ADC_VREF_INSTANCE_MASK,
      STM32_ADC_VREF_ALT_HAL_CHANNEL, STM32_ADC_VREF_ALT_INSTANCE_MASK },
};

/**
 * @brief Check whether an ADC channel is a valid HAL channel identifier.
 * @param hal_channel HAL channel identifier.
 * @return RT_TRUE if valid, otherwise RT_FALSE.
 */
static rt_bool_t stm32_adc_hal_channel_valid(uint32_t hal_channel)
{
    return (hal_channel != STM32_ADC_INVALID_CHANNEL) ? RT_TRUE : RT_FALSE;
}

/**
 * @brief Check whether an ADC peripheral instance matches an instance mask.
 * @param instance ADC peripheral instance.
 * @param mask STM32_ADC_INSTANCE_MASK_x bit mask.
 * @return RT_TRUE if the instance is included, otherwise RT_FALSE.
 */
rt_bool_t stm32_adc_instance_match(ADC_TypeDef *instance, rt_uint32_t mask)
{
#ifdef ADC1
    if ((instance == ADC1) && ((mask & STM32_ADC_INSTANCE_MASK_ADC1) != 0U))
    {
        return RT_TRUE;
    }
#endif /* ADC1 */

#ifdef ADC2
    if ((instance == ADC2) && ((mask & STM32_ADC_INSTANCE_MASK_ADC2) != 0U))
    {
        return RT_TRUE;
    }
#endif /* ADC2 */

#ifdef ADC3
    if ((instance == ADC3) && ((mask & STM32_ADC_INSTANCE_MASK_ADC3) != 0U))
    {
        return RT_TRUE;
    }
#endif /* ADC3 */

#ifdef ADC4
    if ((instance == ADC4) && ((mask & STM32_ADC_INSTANCE_MASK_ADC4) != 0U))
    {
        return RT_TRUE;
    }
#endif /* ADC4 */

#ifdef ADC5
    if ((instance == ADC5) && ((mask & STM32_ADC_INSTANCE_MASK_ADC5) != 0U))
    {
        return RT_TRUE;
    }
#endif /* ADC5 */

    return RT_FALSE;
}

/**
 * @brief Check whether one internal HAL channel is supported by the current ADC instance.
 * @param adc Pointer to the STM32 ADC device object.
 * @param hal_channel HAL ADC channel identifier.
 * @param instance_mask ADC instance mask allowed to access this internal channel.
 * @return RT_TRUE if the channel is available on the current ADC instance, otherwise RT_FALSE.
 */
static rt_bool_t stm32_adc_internal_channel_supported(struct stm32_adc *adc, uint32_t hal_channel, rt_uint32_t instance_mask)
{
    if ((stm32_adc_hal_channel_valid(hal_channel) != RT_TRUE))
    {
        return RT_FALSE;
    }

    return stm32_adc_instance_match(adc->handle.Instance, instance_mask);
}

/**
 * @brief Find the internal ADC channel capability entry by logical channel.
 * @param channel RT-Thread logical ADC channel identifier.
 * @return Pointer to the internal-channel entry, or RT_NULL if the channel is not internal.
 */
static const struct stm32_adc_internal_channel *stm32_adc_find_internal_channel(rt_uint8_t channel)
{
    rt_size_t index;

    for (index = 0U; index < RT_ARRAY_SIZE(stm32_adc_internal_channels); index++)
    {
        if ((stm32_adc_internal_channels[index].logical_channel >= 0) &&
            ((rt_uint8_t)stm32_adc_internal_channels[index].logical_channel == channel))
        {
            return &stm32_adc_internal_channels[index];
        }
    }

    return RT_NULL;
}

/**
 * @brief Get an instance-aware HAL channel identifier for an ADC channel.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel RT-Thread logical ADC channel identifier.
 * @param hal_channel Pointer to the output HAL ADC channel identifier.
 * @return Operation status.
 */
static rt_err_t stm32_adc_get_channel_for_instance(struct stm32_adc *adc, rt_uint8_t channel, uint32_t *hal_channel)
{
    const struct stm32_adc_internal_channel *internal_channel;
    rt_err_t result;

    internal_channel = stm32_adc_find_internal_channel(channel);
    if (internal_channel != RT_NULL)
    {
        if (stm32_adc_internal_channel_supported(adc, internal_channel->hal_channel, internal_channel->instance_mask) == RT_TRUE)
        {
            *hal_channel = internal_channel->hal_channel;
            return RT_EOK;
        }

        if (stm32_adc_internal_channel_supported(adc, internal_channel->alternate_hal_channel,
                                                 internal_channel->alternate_instance_mask) == RT_TRUE)
        {
            *hal_channel = internal_channel->alternate_hal_channel;
            return RT_EOK;
        }

        return -RT_ENOSYS;
    }

    result = stm32_adc_get_channel(channel, hal_channel);
    if ((result == RT_EOK) && (stm32_adc_hal_channel_valid(*hal_channel) != RT_TRUE))
    {
        return -RT_EINVAL;
    }

    return result;
}

/**
 * @brief Get the HAL ADC channel identifier.
 * @param channel RT-Thread ADC channel identifier.
 * @param hal_channel Pointer to the output HAL channel identifier.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_channel(rt_uint8_t channel, uint32_t *hal_channel)
{
    if (((rt_size_t)channel >= RT_ARRAY_SIZE(stm32_adc_channel_table)) ||
        (stm32_adc_hal_channel_valid(stm32_adc_channel_table[(rt_size_t)channel]) != RT_TRUE))
    {
        return -RT_EINVAL;
    }

    *hal_channel = stm32_adc_channel_table[(rt_size_t)channel];
    return RT_EOK;
}

/**
 * @brief Get the logical channel used to sample STM32 VREF.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Pointer to the output logical VREFINT channel.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_vref_logical_channel(struct stm32_adc *adc, rt_uint8_t *channel)
{
    uint32_t hal_channel;
    rt_err_t result;

    if (STM32_ADC_VREF_CHANNEL < 0)
    {
        return -RT_ENOSYS;
    }

    result = stm32_adc_get_channel_for_instance(adc, (rt_uint8_t)STM32_ADC_VREF_CHANNEL, &hal_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    RT_UNUSED(hal_channel);
    *channel = (rt_uint8_t)STM32_ADC_VREF_CHANNEL;
    return RT_EOK;
}

/**
 * @brief Get the logical channel used to sample STM32 internal temperature sensor.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Pointer to the output logical temperature-sensor channel.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_tempsensor_logical_channel(struct stm32_adc *adc, rt_uint8_t *channel)
{
    uint32_t hal_channel;
    rt_err_t result;

    if (STM32_ADC_TEMP_CHANNEL < 0)
    {
        return -RT_ENOSYS;
    }

    result = stm32_adc_get_channel_for_instance(adc, (rt_uint8_t)STM32_ADC_TEMP_CHANNEL, &hal_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    RT_UNUSED(hal_channel);
    *channel = (rt_uint8_t)STM32_ADC_TEMP_CHANNEL;
    return RT_EOK;
}

/**
 * @brief Get the logical channel used to sample STM32 internal VBAT divider.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Pointer to the output logical VBAT channel.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_vbat_logical_channel(struct stm32_adc *adc, rt_uint8_t *channel)
{
    uint32_t hal_channel;
    rt_err_t result;

    if (STM32_ADC_VBAT_CHANNEL < 0)
    {
        return -RT_ENOSYS;
    }

    result = stm32_adc_get_channel_for_instance(adc, (rt_uint8_t)STM32_ADC_VBAT_CHANNEL, &hal_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    RT_UNUSED(hal_channel);
    *channel = (rt_uint8_t)STM32_ADC_VBAT_CHANNEL;
    return RT_EOK;
}

/**
 * @brief Get the current ADC resolution in bits.
 * @param adc Pointer to the STM32 ADC device object.
 * @return Resolution in bits, or 12 when it cannot be determined.
 */
rt_uint8_t stm32_adc_get_resolution_bits(const struct stm32_adc *adc)
{
#if defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION)
    switch (adc->handle.Init.Resolution)
    {
#ifdef ADC_RESOLUTION_16B
    case ADC_RESOLUTION_16B:
        return 16U;
#endif /* ADC_RESOLUTION_16B */
#ifdef ADC_RESOLUTION_14B
    case ADC_RESOLUTION_14B:
        return 14U;
#endif /* ADC_RESOLUTION_14B */
#ifdef ADC_RESOLUTION_12B
    case ADC_RESOLUTION_12B:
        return 12U;
#endif /* ADC_RESOLUTION_12B */
#ifdef ADC_RESOLUTION_10B
    case ADC_RESOLUTION_10B:
        return 10U;
#endif /* ADC_RESOLUTION_10B */
#ifdef ADC_RESOLUTION_8B
    case ADC_RESOLUTION_8B:
        return 8U;
#endif /* ADC_RESOLUTION_8B */
#ifdef ADC_RESOLUTION_6B
    case ADC_RESOLUTION_6B:
        return 6U;
#endif /* ADC_RESOLUTION_6B */
    default:
        return 12U;
    }
#else
    RT_UNUSED(adc);
    return 12U;
#endif /* defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION) */
}

#if defined(STM32_ADC_HAS_LL_TEMPERATURE_CALC)
/**
 * @brief Convert an ADC resolution in bits to the HAL resolution token.
 * @param resolution_bits ADC conversion resolution in bits.
 * @param hal_resolution Pointer to the output HAL resolution token.
 * @return Operation status.
 */
static rt_err_t stm32_adc_get_hal_resolution(rt_uint8_t resolution_bits, uint32_t *hal_resolution)
{
    if (hal_resolution == RT_NULL)
    {
        return -RT_EINVAL;
    }

    switch (resolution_bits)
    {
#ifdef ADC_RESOLUTION_16B
    case 16U:
        *hal_resolution = ADC_RESOLUTION_16B;
        return RT_EOK;
#endif /* ADC_RESOLUTION_16B */
#ifdef ADC_RESOLUTION_14B
    case 14U:
        *hal_resolution = ADC_RESOLUTION_14B;
        return RT_EOK;
#endif /* ADC_RESOLUTION_14B */
#ifdef ADC_RESOLUTION_12B
    case 12U:
        *hal_resolution = ADC_RESOLUTION_12B;
        return RT_EOK;
#endif /* ADC_RESOLUTION_12B */
#ifdef ADC_RESOLUTION_10B
    case 10U:
        *hal_resolution = ADC_RESOLUTION_10B;
        return RT_EOK;
#endif /* ADC_RESOLUTION_10B */
#ifdef ADC_RESOLUTION_8B
    case 8U:
        *hal_resolution = ADC_RESOLUTION_8B;
        return RT_EOK;
#endif /* ADC_RESOLUTION_8B */
#ifdef ADC_RESOLUTION_6B
    case 6U:
        *hal_resolution = ADC_RESOLUTION_6B;
        return RT_EOK;
#endif /* ADC_RESOLUTION_6B */
    default:
        return -RT_EINVAL;
    }
}
#endif /* defined(STM32_ADC_HAS_LL_TEMPERATURE_CALC) */

#if defined(STM32_ADC_HAS_TEMPSENSOR_CALIBRATION_DATA)
/**
 * @brief Normalize a raw ADC sample to the 12-bit temperature calibration scale.
 * @param raw_value Raw ADC sample value.
 * @param resolution_bits ADC conversion resolution used for @p raw_value.
 * @param raw_12b Pointer to the output sample normalized to 12-bit scale.
 * @return Operation status.
 */
rt_err_t stm32_adc_normalize_to_12b(rt_uint32_t raw_value, rt_uint8_t resolution_bits, rt_uint32_t *raw_12b)
{
    if ((raw_12b == RT_NULL) || (resolution_bits == 0U) || (resolution_bits > 16U))
    {
        return -RT_EINVAL;
    }

    if (resolution_bits > 12U)
    {
        *raw_12b = raw_value >> (resolution_bits - 12U);
    }
    else
    {
        *raw_12b = raw_value << (12U - resolution_bits);
    }

    return RT_EOK;
}
#endif /* defined(STM32_ADC_HAS_TEMPSENSOR_CALIBRATION_DATA) */

/**
 * @brief Calculate STM32 internal temperature sensor value in degrees Celsius.
 * @param device ADC device handle.
 * @param raw_value Raw ADC sample value from the temperature sensor channel.
 * @param vref_mv Current analog reference voltage in millivolts.
 * @param resolution_bits ADC conversion resolution used for @p raw_value.
 * @param temperature_c Pointer to the output temperature in degrees Celsius.
 * @return Operation status.
 */
rt_err_t stm32_adc_calc_temperature(rt_adc_device_t device, rt_uint32_t raw_value,
                                    rt_uint32_t vref_mv, rt_uint8_t resolution_bits,
                                    rt_int32_t *temperature_c)
{
#if defined(STM32_ADC_HAS_LL_TEMPERATURE_CALC)
    struct stm32_adc *adc;
    uint32_t hal_resolution;
    rt_err_t result;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_get_hal_resolution(resolution_bits, &hal_resolution);
    if (result != RT_EOK)
    {
        return result;
    }

    *temperature_c = (rt_int32_t)STM32_ADC_CALC_TEMPERATURE(adc, vref_mv, raw_value, hal_resolution);
    return RT_EOK;
#elif defined(STM32_ADC_HAS_TEMPSENSOR_CALIBRATION_DATA)
    struct stm32_adc *adc;
    rt_uint32_t raw_12b;
    rt_uint32_t raw_calibrated;
    rt_int32_t cal1;
    rt_int32_t cal2;
    rt_int32_t denominator;
    rt_int64_t numerator;
    rt_err_t result;

    if ((device == RT_NULL) || (vref_mv == 0U) || (temperature_c == RT_NULL))
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_normalize_to_12b(raw_value, resolution_bits, &raw_12b);
    if (result != RT_EOK)
    {
        return result;
    }

    raw_calibrated = (rt_uint32_t)(((rt_uint64_t)raw_12b * (rt_uint64_t)vref_mv +
                                    (TEMPSENSOR_CAL_VREFANALOG / 2U)) / TEMPSENSOR_CAL_VREFANALOG);
    cal1 = (rt_int32_t)(*TEMPSENSOR_CAL1_ADDR);
    cal2 = (rt_int32_t)(*TEMPSENSOR_CAL2_ADDR);
    denominator = cal2 - cal1;
    if (denominator == 0)
    {
        return -RT_EINVAL;
    }

    numerator = ((rt_int64_t)((rt_int32_t)raw_calibrated - cal1) *
                 (rt_int64_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP));
    if (numerator >= 0)
    {
        numerator += denominator / 2;
    }
    else
    {
        numerator -= denominator / 2;
    }

    *temperature_c = (rt_int32_t)(numerator / denominator) + TEMPSENSOR_CAL1_TEMP;
    return RT_EOK;
#else
    RT_UNUSED(device);
    RT_UNUSED(raw_value);
    RT_UNUSED(vref_mv);
    RT_UNUSED(resolution_bits);
    RT_UNUSED(temperature_c);

    return -RT_ENOSYS;
#endif /* defined(STM32_ADC_HAS_LL_TEMPERATURE_CALC) */
}

#if defined(STM32_ADC_HAS_ENUM_RANK)
/**
 * @brief STM32 ADC regular-rank mapping entry.
 */
struct stm32_adc_rank_map
{
    rt_bool_t valid;   /**< Whether this logical rank is supported by HAL. */
    uint32_t hal_rank; /**< HAL regular-rank enumeration value. */
};

/**
 * @brief HAL regular-rank values indexed by logical rank.
 */
static const struct stm32_adc_rank_map stm32_adc_rank_table[] = {
    { RT_FALSE, 0U },
#ifdef ADC_REGULAR_RANK_1
    { RT_TRUE, ADC_REGULAR_RANK_1 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_1 */
#ifdef ADC_REGULAR_RANK_2
    { RT_TRUE, ADC_REGULAR_RANK_2 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_2 */
#ifdef ADC_REGULAR_RANK_3
    { RT_TRUE, ADC_REGULAR_RANK_3 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_3 */
#ifdef ADC_REGULAR_RANK_4
    { RT_TRUE, ADC_REGULAR_RANK_4 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_4 */
#ifdef ADC_REGULAR_RANK_5
    { RT_TRUE, ADC_REGULAR_RANK_5 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_5 */
#ifdef ADC_REGULAR_RANK_6
    { RT_TRUE, ADC_REGULAR_RANK_6 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_6 */
#ifdef ADC_REGULAR_RANK_7
    { RT_TRUE, ADC_REGULAR_RANK_7 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_7 */
#ifdef ADC_REGULAR_RANK_8
    { RT_TRUE, ADC_REGULAR_RANK_8 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_8 */
#ifdef ADC_REGULAR_RANK_9
    { RT_TRUE, ADC_REGULAR_RANK_9 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_9 */
#ifdef ADC_REGULAR_RANK_10
    { RT_TRUE, ADC_REGULAR_RANK_10 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_10 */
#ifdef ADC_REGULAR_RANK_11
    { RT_TRUE, ADC_REGULAR_RANK_11 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_11 */
#ifdef ADC_REGULAR_RANK_12
    { RT_TRUE, ADC_REGULAR_RANK_12 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_12 */
#ifdef ADC_REGULAR_RANK_13
    { RT_TRUE, ADC_REGULAR_RANK_13 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_13 */
#ifdef ADC_REGULAR_RANK_14
    { RT_TRUE, ADC_REGULAR_RANK_14 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_14 */
#ifdef ADC_REGULAR_RANK_15
    { RT_TRUE, ADC_REGULAR_RANK_15 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_15 */
#ifdef ADC_REGULAR_RANK_16
    { RT_TRUE, ADC_REGULAR_RANK_16 },
#else
    { RT_FALSE, 0U },
#endif /* ADC_REGULAR_RANK_16 */
};
#endif /* defined(STM32_ADC_HAS_ENUM_RANK) */

/**
 * @brief Convert one STM32 HAL status code to an RT-Thread error code.
 * @param status STM32 HAL operation status.
 * @return RT-Thread operation status.
 */
static rt_err_t stm32_hal_status_to_rt_err(HAL_StatusTypeDef status)
{
    switch (status)
    {
    case HAL_OK:
        return RT_EOK;

    case HAL_BUSY:
        return -RT_EBUSY;

    case HAL_TIMEOUT:
        return -RT_ETIMEOUT;

    case HAL_ERROR:
    default:
        return -RT_ERROR;
    }
}

/**
 * @brief Get one HAL rank value from a logical rank index.
 * @param rank Logical rank index starting from 1.
 * @param hal_rank Pointer to the output HAL rank value.
 * @return Operation status.
 */
static rt_err_t stm32_adc_get_rank_value(rt_uint32_t rank, uint32_t *hal_rank)
{
#if defined(STM32_ADC_HAS_ENUM_RANK)
    if ((rank >= RT_ARRAY_SIZE(stm32_adc_rank_table)) || (stm32_adc_rank_table[rank].valid != RT_TRUE))
    {
        return -RT_EINVAL;
    }

    *hal_rank = stm32_adc_rank_table[rank].hal_rank;
#elif defined(STM32_ADC_HAS_CHANNEL_NUMBER_RANK)
    RT_UNUSED(rank);
    *hal_rank = ADC_RANK_CHANNEL_NUMBER;
#else
    *hal_rank = rank;
#endif /* defined(STM32_ADC_HAS_ENUM_RANK) */

    return RT_EOK;
}

/**
 * @brief Enable ADC analog support required by a specific series.
 */
static void stm32_adc_enable_analog_support(void)
{
#if defined(STM32_ADC_NEEDS_ANALOG_SUPPLY)
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWREx_EnableVddA();
#endif /* defined(STM32_ADC_NEEDS_ANALOG_SUPPLY) */
}

#if defined(STM32_ADC_HAS_CALIBRATION)
/**
 * @brief Get the input-mode mask from STM32 private configuration.
 * @param cfg Pointer to the STM32 backend private configuration.
 * @return RT_ADC_INPUT_MODE_* mask used by calibration.
 */
static rt_uint8_t stm32_adc_get_input_modes(const struct stm32_adc_private_cfg *cfg)
{
    if (cfg->input_modes == 0U)
    {
        return RT_ADC_INPUT_MODE_SINGLE_ENDED;
    }

    return cfg->input_modes;
}

/**
 * @brief Run one calibration pass for a selected ADC input mode.
 * @param adc Pointer to the STM32 ADC device object.
 * @param calibration_mode HAL calibration mode selector.
 * @param input_mode HAL single-ended or differential selector.
 * @return Operation status.
 */
static rt_err_t stm32_adc_run_calibration_pass(struct stm32_adc *adc, uint32_t calibration_mode, uint32_t input_mode)
{
    HAL_StatusTypeDef status;
#if defined(STM32_ADC_HAS_SIMPLE_CALIBRATION)
    RT_UNUSED(calibration_mode);
    status = HAL_ADCEx_Calibration_Start(&adc->handle, input_mode);
    if (status != HAL_OK)
    {
        LOG_E("%s calibration failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }
    return RT_EOK;
#elif defined(STM32_ADC_HAS_LINEAR_CALIBRATION)
    status = HAL_ADCEx_Calibration_Start(&adc->handle, calibration_mode, input_mode);
    if (status != HAL_OK)
    {
        LOG_E("%s calibration failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }
    return RT_EOK;
#else
    RT_UNUSED(status);
    RT_UNUSED(calibration_mode);
    RT_UNUSED(input_mode);
    return -RT_ENOSYS;
#endif /* calibration feature buckets */
}

/**
 * @brief Run one series-specific ADC calibration from STM32 private configuration.
 * @param adc Pointer to the STM32 ADC device object.
 * @param private_cfg Pointer to the STM32 backend private configuration.
 * @return Operation status.
 */
static rt_err_t stm32_adc_run_calibration(struct stm32_adc *adc, const struct stm32_adc_private_cfg *private_cfg)
{
    rt_err_t result;
    rt_uint8_t requested_input_modes;
#if defined(STM32_ADC_HAS_LINEAR_CALIBRATION) && defined(ADC_CALIB_OFFSET)
    rt_bool_t single_ended_calibrated;
#endif /* defined(STM32_ADC_HAS_LINEAR_CALIBRATION) && defined(ADC_CALIB_OFFSET) */

    requested_input_modes = stm32_adc_get_input_modes(private_cfg);
    LOG_D("%s calibration request: modes=0x%02x", adc->name, requested_input_modes);

#if defined(STM32_ADC_HAS_SIMPLE_CALIBRATION)
    if ((requested_input_modes & RT_ADC_INPUT_MODE_SINGLE_ENDED) != 0U)
    {
        result = stm32_adc_run_calibration_pass(adc, 0U, STM32_ADC_SINGLE_ENDED_VALUE);
        if (result != RT_EOK)
        {
            return result;
        }
        LOG_I("%s single-ended calibration done", adc->name);
    }
    if ((requested_input_modes & RT_ADC_INPUT_MODE_DIFFERENTIAL) != 0U)
    {
        result = stm32_adc_run_calibration_pass(adc, 0U, STM32_ADC_DIFFERENTIAL_VALUE);
        if (result != RT_EOK)
        {
            return result;
        }
        LOG_I("%s differential calibration done", adc->name);
    }
    return RT_EOK;
#elif defined(STM32_ADC_HAS_LINEAR_CALIBRATION)
#if defined(ADC_CALIB_OFFSET)
    single_ended_calibrated = RT_FALSE;
#endif /* defined(ADC_CALIB_OFFSET) */
    if ((requested_input_modes & RT_ADC_INPUT_MODE_SINGLE_ENDED) != 0U)
    {
        result = stm32_adc_run_calibration_pass(adc, ADC_CALIB_OFFSET_LINEARITY, STM32_ADC_SINGLE_ENDED_VALUE);
        if (result != RT_EOK)
        {
            return result;
        }
#if defined(ADC_CALIB_OFFSET)
        single_ended_calibrated = RT_TRUE;
#endif /* defined(ADC_CALIB_OFFSET) */
        LOG_I("%s single-ended calibration done", adc->name);
    }
    if ((requested_input_modes & RT_ADC_INPUT_MODE_DIFFERENTIAL) != 0U)
    {
        result = stm32_adc_run_calibration_pass(adc,
#if defined(ADC_CALIB_OFFSET)
                                                (single_ended_calibrated == RT_TRUE) ? ADC_CALIB_OFFSET : ADC_CALIB_OFFSET_LINEARITY,
#else
                                                ADC_CALIB_OFFSET_LINEARITY,
#endif /* defined(ADC_CALIB_OFFSET) */
                                                STM32_ADC_DIFFERENTIAL_VALUE);
        if (result != RT_EOK)
        {
            return result;
        }
        LOG_I("%s differential calibration done", adc->name);
    }
    return RT_EOK;
#else
    RT_UNUSED(requested_input_modes);
    return -RT_ENOSYS;
#endif /* calibration feature buckets */
}

#endif /* defined(STM32_ADC_HAS_CALIBRATION) */

/**
 * @brief Fill the HAL ADC initialization structure from the device object.
 * @param adc Pointer to the STM32 ADC device object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_fill_init(struct stm32_adc *adc)
{
    ADC_TypeDef *instance;

    LOG_D("%s fill init", adc->name);
    instance = adc->handle.Instance;
    rt_memset(&adc->handle, 0, sizeof(adc->handle));
    adc->handle.Instance = instance;
#ifdef ADC_DEFAULT_CLOCK_PRESCALER
    adc->handle.Init.ClockPrescaler = ADC_DEFAULT_CLOCK_PRESCALER;
#endif /* ADC_DEFAULT_CLOCK_PRESCALER */
#if defined(STM32_ADC_HAS_INIT_DATA_ALIGN)
    adc->handle.Init.DataAlign = (adc->config.data_align != 0U) ? adc->config.data_align : ADC_DEFAULT_DATA_ALIGN;
#endif /* defined(STM32_ADC_HAS_INIT_DATA_ALIGN) */
    adc->handle.Init.ScanConvMode = STM32_ADC_SCAN_MODE_DISABLE;
#if defined(STM32_ADC_HAS_INIT_EOC_SELECTION)
    adc->handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
#endif /* defined(STM32_ADC_HAS_INIT_EOC_SELECTION) */
    adc->handle.Init.ContinuousConvMode = DISABLE;
#if defined(STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT)
    adc->handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
#endif /* defined(STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT) */
#if defined(STM32_ADC_HAS_INIT_NBR_OF_CONVERSION)
    adc->handle.Init.NbrOfConversion = 1;
#endif /* defined(STM32_ADC_HAS_INIT_NBR_OF_CONVERSION) */
    adc->handle.Init.DiscontinuousConvMode = DISABLE;
#if defined(STM32_ADC_HAS_INIT_NBR_OF_DISC_CONVERSION)
    adc->handle.Init.NbrOfDiscConversion = 1;
#endif /* defined(STM32_ADC_HAS_INIT_NBR_OF_DISC_CONVERSION) */
    adc->handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
#if defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE)
    adc->handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
#endif /* defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE) */
#if defined(STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS)
    adc->handle.Init.DMAContinuousRequests = DISABLE;
#endif /* defined(STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS) */
#if defined(STM32_ADC_HAS_HW_OVERSAMPLING)
    adc->handle.Init.OversamplingMode = DISABLE;
    adc->handle.Init.Oversampling.Ratio = 0U;
    adc->handle.Init.Oversampling.RightBitShift = 0U;
    adc->handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
    adc->handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
#endif /* defined(STM32_ADC_HAS_HW_OVERSAMPLING) */

#if defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION)
    adc->handle.Init.Resolution = (adc->config.resolution != 0U) ? adc->config.resolution : ADC_DEFAULT_RESOLUTION;
#else
    if (adc->config.resolution != 0U)
    {
        return -RT_ENOSYS;
    }
#endif /* defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION) */

    return RT_EOK;
}

/**
 * @brief Force one ADC device back to regular polling conversion mode.
 * @param adc Pointer to the STM32 ADC device object.
 *
 * Sequence reads use HAL_ADC_Start() and HAL_ADC_PollForConversion(), so any
 * DMA request state left by board initialization must be cleared before
 * starting a polling conversion.
 */
static void stm32_adc_force_poll_mode(struct stm32_adc *adc)
{
#if defined(ADC_CR2_DMA)
    CLEAR_BIT(adc->handle.Instance->CR2, ADC_CR2_DMA);
#endif /* defined(ADC_CR2_DMA) */

#if defined(ADC_CR2_DDS)
    CLEAR_BIT(adc->handle.Instance->CR2, ADC_CR2_DDS);
#endif /* defined(ADC_CR2_DDS) */

#if defined(STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS)
    adc->handle.Init.DMAContinuousRequests = DISABLE;
#endif /* defined(STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS) */

#if defined(STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT)
    adc->handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
#endif /* defined(STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT) */
}

/**
 * @brief Open one STM32 ADC device.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_open(struct rt_adc_device *device)
{
    struct stm32_adc *adc;
    HAL_StatusTypeDef status;
    rt_err_t result;

    if (device == RT_NULL)
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s open start", adc->name);
    stm32_adc_enable_analog_support();
    result = stm32_adc_fill_init(adc);
    if (result != RT_EOK)
    {
        return result;
    }
    result = stm32_adc_apply_oversampling(adc);
    if (result != RT_EOK)
    {
        return result;
    }
    status = HAL_ADC_Init(&adc->handle);
    if (status != HAL_OK)
    {
        LOG_E("%s init failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }
#if defined(STM32_ADC_HAS_CALIBRATION)
    result = stm32_adc_run_calibration(adc, &adc->config);
    if (result != RT_EOK)
    {
        return result;
    }
#endif /* defined(STM32_ADC_HAS_CALIBRATION) */
    LOG_I("%s opened", adc->name);
    return RT_EOK;
}

/**
 * @brief Close one STM32 ADC device.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_close(struct rt_adc_device *device)
{
    struct stm32_adc *adc;
    HAL_StatusTypeDef status;

    if (device == RT_NULL)
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    status = HAL_ADC_Stop(&adc->handle);
    if (status != HAL_OK)
    {
        LOG_W("%s stop during close failed", adc->name);
    }
    status = HAL_ADC_DeInit(&adc->handle);
    if (status != HAL_OK)
    {
        LOG_W("%s deinit during close failed", adc->name);
        return -RT_ERROR;
    }
    LOG_I("%s closed", adc->name);
    return RT_EOK;
}

#if defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS)
/**
 * @brief Get the HAL single-ended/differential selector from private configuration.
 * @param cfg Pointer to the STM32 backend private configuration.
 * @param single_diff Pointer to the output HAL single-ended or differential selector.
 * @return Operation status.
 */
static rt_err_t stm32_adc_get_single_diff(const struct stm32_adc_private_cfg *cfg, uint32_t *single_diff)
{
    *single_diff = ((cfg->input_modes & RT_ADC_INPUT_MODE_DIFFERENTIAL) != 0U) ?
                   STM32_ADC_DIFFERENTIAL_VALUE : STM32_ADC_SINGLE_ENDED_VALUE;
    return RT_EOK;
}
#endif /* defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS) */

/**
 * @brief Get one HAL sampling-time value from STM32 private configuration.
 * @param cfg Pointer to the STM32 backend private configuration.
 * @param sampling_time Pointer to the output HAL sampling-time value.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_sampling_time(const struct stm32_adc_private_cfg *cfg, uint32_t *sampling_time)
{
    if ((cfg == RT_NULL) || (sampling_time == RT_NULL))
    {
        return -RT_EINVAL;
    }

    *sampling_time = (cfg->sampling_time != 0U) ? cfg->sampling_time : ADC_DEFAULT_SAMPLING_TIME;
    return RT_EOK;
}

/**
 * @brief Configure one ADC regular rank.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel RT-Thread ADC channel identifier.
 * @param rank Logical regular rank index.
 * @return Operation status.
 */
static rt_err_t stm32_adc_configure_rank(struct stm32_adc *adc, rt_uint8_t channel, rt_uint32_t rank)
{
    ADC_ChannelConfTypeDef config;
    HAL_StatusTypeDef status;
    uint32_t hal_channel;
    uint32_t hal_rank;
    uint32_t sampling_time;
    rt_err_t result;

    result = stm32_adc_get_channel_for_instance(adc, channel, &hal_channel);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_get_rank_value(rank, &hal_rank);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_get_sampling_time(&adc->config, &sampling_time);
    if (result != RT_EOK)
    {
        return result;
    }

    rt_memset(&config, 0, sizeof(config));
    config.Channel = hal_channel;
    config.Rank = hal_rank;
    config.SamplingTime = sampling_time;
#if defined(STM32_ADC_HAS_CONFIG_OFFSET)
    config.Offset = 0;
#endif /* defined(STM32_ADC_HAS_CONFIG_OFFSET) */
#if defined(STM32_ADC_HAS_CONFIG_OFFSET_NUMBER)
    config.OffsetNumber = ADC_OFFSET_NONE;
#endif /* defined(STM32_ADC_HAS_CONFIG_OFFSET_NUMBER) */
#if defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS)
    result = stm32_adc_get_single_diff(&adc->config, &config.SingleDiff);
    if ((result != RT_EOK) && (result != -RT_ENOSYS))
    {
        return result;
    }
#endif /* defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS) */

    status = HAL_ADC_ConfigChannel(&adc->handle, &config);
    if (status != HAL_OK)
    {
        LOG_E("%s configure rank failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }

    return RT_EOK;
}

/**
 * @brief Clear backend ADC channel/rank configuration explicitly.
 * @param adc Pointer to the STM32 ADC device object.
 * @return Operation status.
 *
 * This operation is intentionally not called from normal session configuration.
 * It is an explicit escape hatch for users that need to clear stale
 * channel-number rank configuration before rebuilding a conversion session.
 */
static rt_err_t stm32_adc_clear_channel_config(struct stm32_adc *adc)
{
#if defined(STM32_ADC_HAS_CHANNEL_NUMBER_RANK) && defined(ADC_RANK_NONE)
    ADC_ChannelConfTypeDef config;
    HAL_StatusTypeDef status;
    rt_uint8_t channel;
    uint32_t hal_channel;
    uint32_t sampling_time;
    rt_err_t result;

    result = stm32_adc_get_sampling_time(&adc->config, &sampling_time);
    if (result != RT_EOK)
    {
        return result;
    }

    for (channel = 0U; channel < STM32_ADC_MAX_CHANNELS; channel++)
    {
        result = stm32_adc_get_channel_for_instance(adc, channel, &hal_channel);
        if (result != RT_EOK)
        {
            continue;
        }

        rt_memset(&config, 0, sizeof(config));
        config.Channel = hal_channel;
        config.Rank = ADC_RANK_NONE;
        config.SamplingTime = sampling_time;
#if defined(STM32_ADC_HAS_CONFIG_OFFSET)
        config.Offset = 0;
#endif /* defined(STM32_ADC_HAS_CONFIG_OFFSET) */
#if defined(STM32_ADC_HAS_CONFIG_OFFSET_NUMBER)
        config.OffsetNumber = ADC_OFFSET_NONE;
#endif /* defined(STM32_ADC_HAS_CONFIG_OFFSET_NUMBER) */
#if defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS)
        result = stm32_adc_get_single_diff(&adc->config, &config.SingleDiff);
        if ((result != RT_EOK) && (result != -RT_ENOSYS))
        {
            return result;
        }
#endif /* defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS) */

        status = HAL_ADC_ConfigChannel(&adc->handle, &config);
        if (status != HAL_OK)
        {
            LOG_E("%s clear channel config failed: channel=%u", adc->name, (unsigned int)channel);
            return stm32_hal_status_to_rt_err(status);
        }
    }

    LOG_D("%s channel config cleared", adc->name);
    return RT_EOK;
#else
    RT_UNUSED(adc);
    return -RT_ENOSYS;
#endif /* defined(STM32_ADC_HAS_CHANNEL_NUMBER_RANK) && defined(ADC_RANK_NONE) */
}

/**
 * @brief Configure all regular ADC ranks for one session.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channels ADC channel selection mask.
 * @return Operation status.
 */
static rt_err_t stm32_adc_configure_session_ranks(struct stm32_adc *adc, rt_uint32_t channels)
{
    rt_uint32_t rank;
    rt_uint8_t channel;
    rt_err_t result;

    rank = 1U;
    while (channels != 0U)
    {
        if (rank > STM32_ADC_MAX_SEQUENCE)
        {
            return -RT_EINVAL;
        }

        channel = rt_adc_channel_mask_take_lsb(&channels);
        result = stm32_adc_configure_rank(adc, channel, rank);
        if (result != RT_EOK)
        {
            LOG_E("%s rank config failed: channel=%u rank=%lu result=%d",
                  adc->name, (unsigned int)channel, (unsigned long)rank, result);
            return result;
        }
        rank++;
    }

    return RT_EOK;
}

/**
 * @brief Apply one complete regular ADC configuration to STM32 HAL.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channels ADC channel selection mask.
 * @return Operation status.
 */
static rt_err_t stm32_adc_apply_regular_config(struct stm32_adc *adc, rt_uint32_t channels)
{
    HAL_StatusTypeDef status;
    rt_size_t channel_count;
    rt_err_t result;

    channel_count = rt_adc_channel_mask_count(channels);
    if ((channel_count == 0U) || (channel_count > STM32_ADC_MAX_SEQUENCE))
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_fill_init(adc);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_apply_oversampling(adc);
    if (result != RT_EOK)
    {
        return result;
    }

    adc->handle.Init.ScanConvMode = (channel_count > 1U) ? STM32_ADC_SCAN_MODE_ENABLE : STM32_ADC_SCAN_MODE_DISABLE;
#if defined(STM32_ADC_HAS_INIT_NBR_OF_CONVERSION)
    adc->handle.Init.NbrOfConversion = channel_count;
#endif /* defined(STM32_ADC_HAS_INIT_NBR_OF_CONVERSION) */

#if defined(STM32_ADC_HAS_INIT_EOC_SELECTION)
    adc->handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
#endif /* defined(STM32_ADC_HAS_INIT_EOC_SELECTION) */

    /*
     * Multi-rank polling must not let one HAL_ADC_Start() drain the whole
     * regular sequence, otherwise DR can be overwritten before the CPU reads it.
     * Discontinuous mode makes each HAL_ADC_Start() convert one rank only.
     */
    adc->handle.Init.DiscontinuousConvMode = (channel_count > 1U) ? ENABLE : DISABLE;

    stm32_adc_force_poll_mode(adc);

    status = HAL_ADC_Init(&adc->handle);
    if (status != HAL_OK)
    {
        LOG_E("%s regular init failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }
    return stm32_adc_configure_session_ranks(adc, channels);
}

#if STM32_ADC_USING_DMA_STREAM
/**
 * @brief Apply one complete regular ADC configuration for circular DMA stream mode.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channels ADC channel selection mask.
 * @return Operation status.
 */
static rt_err_t stm32_adc_apply_stream_regular_config(struct stm32_adc *adc, rt_uint32_t channels)
{
    HAL_StatusTypeDef status;
    rt_size_t channel_count;
    rt_err_t result;

    channel_count = rt_adc_channel_mask_count(channels);
    if ((channel_count == 0U) || (channel_count > STM32_ADC_MAX_SEQUENCE))
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_fill_init(adc);
    if (result != RT_EOK)
    {
        return result;
    }

    result = stm32_adc_apply_oversampling(adc);
    if (result != RT_EOK)
    {
        return result;
    }

#if defined(STM32_ADC_USING_TRIGGER)
    struct stm32_adc_trigger_fields trigger_fields;
    if (adc->prepared_trigger_valid == RT_TRUE)
    {
        trigger_fields = adc->prepared_trigger;
    }
    else
    {
        result = stm32_adc_trigger_fields_get(adc, RT_NULL, &trigger_fields);
        if (result != RT_EOK)
        {
            return result;
        }
    }
#endif /* defined(STM32_ADC_USING_TRIGGER) */

    adc->handle.Init.ScanConvMode = (channel_count > 1U) ? STM32_ADC_SCAN_MODE_ENABLE : STM32_ADC_SCAN_MODE_DISABLE;
#if defined(STM32_ADC_HAS_INIT_NBR_OF_CONVERSION)
    adc->handle.Init.NbrOfConversion = channel_count;
#endif /* defined(STM32_ADC_HAS_INIT_NBR_OF_CONVERSION) */
#if defined(STM32_ADC_HAS_INIT_EOC_SELECTION) && defined(ADC_EOC_SEQ_CONV)
    adc->handle.Init.EOCSelection = ADC_EOC_SEQ_CONV;
#elif defined(STM32_ADC_HAS_INIT_EOC_SELECTION)
    adc->handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
#endif /* defined(STM32_ADC_HAS_INIT_EOC_SELECTION) && defined(ADC_EOC_SEQ_CONV) */
#if defined(STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT)
    adc->handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
#endif /* defined(STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT) */
#if defined(STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS)
    adc->handle.Init.DMAContinuousRequests = ENABLE;
#endif /* defined(STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS) */
#if defined(STM32_ADC_USING_TRIGGER)
    adc->handle.Init.ContinuousConvMode = (trigger_fields.selector == ADC_SOFTWARE_START) ? ENABLE : DISABLE;
    adc->handle.Init.ExternalTrigConv = trigger_fields.selector;
#if defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE)
    adc->handle.Init.ExternalTrigConvEdge = trigger_fields.edge;
#endif /* defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE) */
#else
    adc->handle.Init.ContinuousConvMode = ENABLE;
#endif /* defined(STM32_ADC_USING_TRIGGER) */

    status = HAL_ADC_Init(&adc->handle);
    if (status != HAL_OK)
    {
        LOG_E("%s stream regular init failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }

    return stm32_adc_configure_session_ranks(adc, channels);
}
#endif /* STM32_ADC_USING_DMA_STREAM */

/**
 * @brief Configure one ADC conversion session on one STM32 ADC device.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @return Operation status.
 */
static rt_err_t stm32_adc_session_config(struct rt_adc_device *device, rt_uint32_t channels)
{
    struct stm32_adc *adc;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    return stm32_adc_apply_regular_config(adc, channels);
}

/**
 * @brief Start one STM32 ADC finite sequence session.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the ADC sequence request object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_sequence_start(struct rt_adc_device *device, rt_uint32_t channels,
                                           const struct rt_adc_sequence_cfg *cfg)
{
    RT_UNUSED(device);
    RT_UNUSED(channels);
    RT_UNUSED(cfg);

    return RT_EOK;
}

/**
 * @brief Read one sample from one STM32 ADC sequence session.
 * @param device Pointer to the ADC device object.
 * @param value Pointer to the output sample value.
 * @param timeout_ms Read timeout in milliseconds.
 * @return Operation status.
 */
static rt_err_t stm32_adc_sequence_read(struct rt_adc_device *device, rt_uint32_t *value, rt_int32_t timeout_ms)
{
    struct stm32_adc *adc;
    HAL_StatusTypeDef status;
    uint32_t timeout;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    status = HAL_ADC_Start(&adc->handle);
    if (status != HAL_OK)
    {
        goto fail;
    }

    timeout = (timeout_ms < 0) ? HAL_MAX_DELAY : (uint32_t)timeout_ms;
    status = HAL_ADC_PollForConversion(&adc->handle, timeout);
    if (status != HAL_OK)
    {
        goto fail;
    }

    *value = (rt_uint32_t)HAL_ADC_GetValue(&adc->handle);
    LOG_D("%s sample read: value=%lu", adc->name, (unsigned long)*value);

    return RT_EOK;

fail:
    LOG_E("%s sequence read failed: status=%d state=0x%08lx error=0x%08lx",
          adc->name, (int)status, (unsigned long)adc->handle.State, (unsigned long)adc->handle.ErrorCode);

    return stm32_hal_status_to_rt_err(status);
}
/**
 * @brief Stop one STM32 ADC sequence session.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_sequence_stop(struct rt_adc_device *device)
{
    struct stm32_adc *adc;
    HAL_StatusTypeDef status;
    rt_err_t result;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s sequence stop", adc->name);
    result = RT_EOK;

    status = HAL_ADC_Stop(&adc->handle);
    if (status != HAL_OK)
    {
        LOG_W("%s sequence stop failed", adc->name);
        return stm32_hal_status_to_rt_err(status);
    }

    return result;
}

#if STM32_ADC_USING_DMA_STREAM
#if defined(STM32_ADC_NEEDS_DMA_CACHE_MAINTENANCE)
/** @brief STM32 Cortex-M7 D-Cache line size used by DMA buffers. */
#define STM32_ADC_DMA_CACHE_LINE_SIZE 32U

/**
 * @brief Release any cache-aligned ADC stream DMA buffer owned by the driver.
 * @param adc Pointer to the STM32 ADC device object.
 */
static void stm32_adc_stream_release_cache_buffer(struct stm32_adc *adc)
{
    if ((adc != RT_NULL) && (adc->cache_dma_buffer != RT_NULL))
    {
        LOG_D("%s stream cache buffer release: buffer=%p", adc->name, adc->cache_dma_buffer);
        rt_free_align(adc->cache_dma_buffer);
        adc->cache_dma_buffer = RT_NULL;
    }
}

/**
 * @brief Select a D-Cache-safe DMA buffer for one ADC stream session.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the stream configuration object.
 * @param dma_buffer Pointer to the selected DMA buffer output.
 * @return Operation status.
 */
static rt_err_t stm32_adc_stream_prepare_cache_buffer(struct stm32_adc *adc, const struct rt_adc_stream_cfg *cfg,
                                                      rt_uint32_t **dma_buffer)
{
    rt_size_t bytes;
    rt_size_t cache_bytes;

    bytes = cfg->dma_buffer_length * sizeof(rt_uint32_t);
    cache_bytes = RT_ALIGN(bytes, STM32_ADC_DMA_CACHE_LINE_SIZE);
    stm32_adc_stream_release_cache_buffer(adc);

    if (RT_IS_ALIGN((rt_ubase_t)cfg->dma_buffer, STM32_ADC_DMA_CACHE_LINE_SIZE) &&
        RT_IS_ALIGN(bytes, STM32_ADC_DMA_CACHE_LINE_SIZE))
    {
        *dma_buffer = cfg->dma_buffer;
        LOG_D("%s stream cache buffer direct: buffer=%p bytes=%u", adc->name, *dma_buffer, (unsigned int)bytes);
    }
    else
    {
        adc->cache_dma_buffer = (rt_uint32_t *)rt_malloc_align(cache_bytes, STM32_ADC_DMA_CACHE_LINE_SIZE);
        if (adc->cache_dma_buffer == RT_NULL)
        {
            LOG_E("%s stream cache buffer alloc failed: bytes=%u aligned=%u",
                  adc->name, (unsigned int)bytes, (unsigned int)cache_bytes);
            return -RT_ENOMEM;
        }

        *dma_buffer = adc->cache_dma_buffer;
        LOG_W("%s stream cache buffer fallback: caller=%p dma=%p bytes=%u",
              adc->name, cfg->dma_buffer, *dma_buffer, (unsigned int)bytes);
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, *dma_buffer, cache_bytes);
    adc->device.stream_ctrl.dma_buffer = *dma_buffer;

    return RT_EOK;
}

/**
 * @brief Invalidate a completed ADC stream DMA RX sample range.
 * @param device Pointer to the ADC device object.
 * @param sample_buffer Pointer to the sample buffer to synchronize.
 * @param sample_count Number of samples to synchronize.
 * @return Operation status.
 */
static rt_err_t stm32_adc_stream_sync(struct rt_adc_device *device, const rt_uint32_t *sample_buffer, rt_size_t sample_count)
{
    rt_ubase_t start;
    rt_ubase_t end;
    rt_ubase_t aligned_start;
    rt_ubase_t aligned_end;

    if ((device == RT_NULL) || (sample_buffer == RT_NULL) || (sample_count == 0U))
    {
        return -RT_EINVAL;
    }

    start = (rt_ubase_t)sample_buffer;
    end = start + sample_count * sizeof(rt_uint32_t);
    aligned_start = RT_ALIGN_DOWN(start, STM32_ADC_DMA_CACHE_LINE_SIZE);
    aligned_end = RT_ALIGN(end, STM32_ADC_DMA_CACHE_LINE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)aligned_start, aligned_end - aligned_start);

    return RT_EOK;
}
#else
/**
 * @brief Release any cache-aligned ADC stream DMA buffer owned by the driver.
 * @param adc Pointer to the STM32 ADC device object.
 */
static void stm32_adc_stream_release_cache_buffer(struct stm32_adc *adc)
{
    RT_UNUSED(adc);
}

/**
 * @brief Select the caller-owned DMA buffer for one ADC stream session.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the stream configuration object.
 * @param dma_buffer Pointer to the selected DMA buffer output.
 * @return Operation status.
 */
static rt_err_t stm32_adc_stream_prepare_cache_buffer(struct stm32_adc *adc, const struct rt_adc_stream_cfg *cfg,
                                                      rt_uint32_t **dma_buffer)
{
    RT_UNUSED(adc);

    *dma_buffer = cfg->dma_buffer;
    return RT_EOK;
}

/**
 * @brief Synchronize a backend DMA sample range before CPU access.
 * @param device Pointer to the ADC device object.
 * @param sample_buffer Pointer to the DMA sample buffer.
 * @param sample_count Number of samples to synchronize.
 * @return Operation status.
 */
static rt_err_t stm32_adc_stream_sync(struct rt_adc_device *device, const rt_uint32_t *sample_buffer, rt_size_t sample_count)
{
    RT_UNUSED(device);
    RT_UNUSED(sample_buffer);
    RT_UNUSED(sample_count);

    return RT_EOK;
}
#endif /* defined(STM32_ADC_NEEDS_DMA_CACHE_MAINTENANCE) */

/**
 * @brief Configure STM32 DMA transfer event interrupts for one stream session.
 * @param dma_handle Pointer to the DMA handle linked to the ADC stream.
 * @param mode Effective ADC stream DMA event mode.
 */
static void stm32_adc_stream_configure_dma_events(DMA_HandleTypeDef *dma_handle, enum rt_adc_stream_dma_event_mode mode)
{
    if (dma_handle == RT_NULL)
    {
        return;
    }

    if (mode == RT_ADC_STREAM_DMA_EVENT_NONE)
    {
        __HAL_DMA_DISABLE_IT(dma_handle, DMA_IT_HT);
        __HAL_DMA_DISABLE_IT(dma_handle, DMA_IT_TC);
    }
    else if (mode == RT_ADC_STREAM_DMA_EVENT_FULL_ONLY)
    {
        __HAL_DMA_DISABLE_IT(dma_handle, DMA_IT_HT);
        __HAL_DMA_ENABLE_IT(dma_handle, DMA_IT_TC);
    }
    else
    {
        __HAL_DMA_ENABLE_IT(dma_handle, DMA_IT_HT);
        __HAL_DMA_ENABLE_IT(dma_handle, DMA_IT_TC);
    }
}

/**
 * @brief Start one STM32 ADC stream session using circular DMA.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the stream configuration object.
 * @return Operation status.
 */
static rt_err_t stm32_adc_stream_start(struct rt_adc_device *device, rt_uint32_t channels, const struct rt_adc_stream_cfg *cfg)
{
    struct stm32_adc *adc;
    HAL_StatusTypeDef status;
    rt_uint32_t *dma_buffer;
    rt_err_t result;

    adc = RT_NULL;
    dma_buffer = RT_NULL;
    result = RT_EOK;

    adc = (struct stm32_adc *)device->parent.user_data;
    if ((adc == RT_NULL) || (adc->dma_rx == RT_NULL))
    {
        result = -RT_ENOSYS;
        goto exit;
    }

    result = stm32_adc_apply_stream_regular_config(adc, channels);
    if (result != RT_EOK)
    {
        goto exit;
    }

    result = stm32_adc_stream_prepare_cache_buffer(adc, cfg, &dma_buffer);
    if (result != RT_EOK)
    {
        goto exit;
    }

    result = stm32_dma_setup(&adc->dma_handle, &adc->handle, &adc->handle.DMA_Handle, adc->dma_rx);
    if (result != RT_EOK)
    {
        goto exit;
    }
    status = HAL_ADC_Start_DMA(&adc->handle, dma_buffer, (uint32_t)cfg->dma_buffer_length);
    if (status != HAL_OK)
    {
        result = stm32_hal_status_to_rt_err(status);
        goto exit;
    }

    stm32_adc_stream_configure_dma_events(&adc->dma_handle, adc->device.stream_ctrl.dma_event_mode);
exit:
    if (result != RT_EOK)
    {
        LOG_E("%s stream startfailed: result=%d", adc->name, result);
    }

    return result;
}

/**
 * @brief Stop one STM32 ADC stream session and release DMA resources.
 * @param device Pointer to the ADC device object.
 * @param hardware_stopped Pointer to the hardware-stop state output.
 * @return Operation status.
 */
static rt_err_t stm32_adc_stream_stop(struct rt_adc_device *device, rt_bool_t *hardware_stopped)
{
    struct stm32_adc *adc;
    HAL_StatusTypeDef status;
    rt_bool_t hal_stopped;
    rt_bool_t dma_attached;
    rt_bool_t dma_released;
    rt_err_t result;

    *hardware_stopped = RT_FALSE;
    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = RT_EOK;
    hal_stopped = RT_FALSE;
    dma_released = RT_FALSE;
    dma_attached = (adc->handle.DMA_Handle == &adc->dma_handle) ? RT_TRUE : RT_FALSE;

    if (dma_attached != RT_TRUE)
    {
        adc->handle.DMA_Handle = RT_NULL;
        adc->dma_handle.Parent = RT_NULL;
        stm32_adc_stream_release_cache_buffer(adc);
        *hardware_stopped = RT_TRUE;
        return RT_EOK;
    }

    status = HAL_ADC_Stop_DMA(&adc->handle);
    if (status == HAL_OK)
    {
        hal_stopped = RT_TRUE;
    }
    else
    {
        result = stm32_hal_status_to_rt_err(status);
        LOG_W("%s stream DMA stop returned %d, continue cleanup", adc->name, result);
    }

    if (adc->dma_rx != RT_NULL)
    {
        rt_err_t dma_result;

        dma_result = stm32_dma_deinit(&adc->dma_handle, adc->dma_rx, (hal_stopped == RT_TRUE) ? RT_FALSE : RT_TRUE);
        if (dma_result == RT_EOK)
        {
            dma_released = RT_TRUE;
        }
        else
        {
            LOG_E("%s stream DMA cleanup failed after stop: result=%d", adc->name, dma_result);
            if (result == RT_EOK)
            {
                result = dma_result;
            }
        }
    }
    else if (hal_stopped == RT_TRUE)
    {
        dma_released = RT_TRUE;
    }

    if ((hal_stopped == RT_TRUE) || (dma_released == RT_TRUE))
    {
        adc->handle.DMA_Handle = RT_NULL;
        adc->dma_handle.Parent = RT_NULL;
        stm32_adc_stream_release_cache_buffer(adc);
        *hardware_stopped = RT_TRUE;
        return result;
    }

    return (result != RT_EOK) ? result : -RT_ERROR;
}

/**
 * @brief Check whether a HAL ADC handle belongs to an active stream DMA session.
 * @param adc Pointer to the STM32 ADC device object.
 * @param hadc Pointer to the HAL ADC handle.
 * @return RT_TRUE when the handle is attached to the stream DMA backend.
 */
static rt_bool_t stm32_adc_stream_dma_is_active(const struct stm32_adc *adc, const ADC_HandleTypeDef *hadc)
{
    if (hadc->DMA_Handle != &adc->dma_handle)
    {
        return RT_FALSE;
    }

    return (adc->device.stream_ctrl.active == RT_TRUE) ? RT_TRUE : RT_FALSE;
}

#ifdef RT_ADC_STREAM_USING_FIFO
/**
 * @brief Dispatch one ADC stream DMA completion event to the ADC framework.
 * @param hadc Pointer to the HAL ADC handle.
 * @param event DMA stream event to report.
 */
static void stm32_adc_stream_dma_callback(ADC_HandleTypeDef *hadc, enum rt_adc_stream_event event)
{
    struct stm32_adc *adc;
    struct rt_adc_stream_ctrl *ctrl;
    const rt_uint32_t *sample_buffer;
    rt_size_t half;
    rt_size_t sample_count;
    rt_err_t result;

    RT_ASSERT(hadc != RT_NULL);
    adc = (struct stm32_adc *)hadc;
    if (stm32_adc_stream_dma_is_active(adc, hadc) != RT_TRUE)
    {
        return;
    }

    ctrl = &adc->device.stream_ctrl;
    sample_buffer = RT_NULL;
    sample_count = 0U;

    if (ctrl->policy != RT_ADC_STREAM_POLICY_FIFO)
    {
        return;
    }

    if (ctrl->dma_event_mode == RT_ADC_STREAM_DMA_EVENT_FULL_ONLY)
    {
        if (event != RT_ADC_STREAM_EVENT_DMA_DONE)
        {
            return;
        }
        sample_buffer = ctrl->dma_buffer;
        sample_count = ctrl->dma_buffer_length;
    }
    else if (ctrl->dma_event_mode == RT_ADC_STREAM_DMA_EVENT_HALF_FULL)
    {
        half = ctrl->dma_buffer_length / 2U;
        if (event == RT_ADC_STREAM_EVENT_DMA_DONE)
        {
            sample_buffer = &ctrl->dma_buffer[half];
            sample_count = ctrl->dma_buffer_length - half;
        }
        else
        {
            sample_buffer = ctrl->dma_buffer;
            sample_count = half;
        }
    }

    if (sample_count == 0U)
    {
        return;
    }

    result = stm32_adc_stream_sync(&adc->device, sample_buffer, sample_count);
    if (result != RT_EOK)
    {
        rt_atomic_store(&ctrl->last_error, (rt_atomic_t)result);
        event = RT_ADC_STREAM_EVENT_ERROR;
        sample_buffer = RT_NULL;
        sample_count = 0U;
    }

    (void)rt_hw_adc_stream_isr(&adc->device, event, sample_buffer, sample_count);
}

/**
 * @brief HAL ADC DMA half-transfer callback.
 * @param hadc Pointer to the HAL ADC handle.
 */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    stm32_adc_stream_dma_callback(hadc, RT_ADC_STREAM_EVENT_DMA_HALF);
}

/**
 * @brief HAL ADC DMA transfer-complete callback.
 * @param hadc Pointer to the HAL ADC handle.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    stm32_adc_stream_dma_callback(hadc, RT_ADC_STREAM_EVENT_DMA_DONE);
}

#else
/**
 * @brief HAL ADC DMA half-transfer callback.
 * @param hadc Pointer to the HAL ADC handle.
 */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    RT_UNUSED(hadc);
}

/**
 * @brief HAL ADC DMA transfer-complete callback.
 * @param hadc Pointer to the HAL ADC handle.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    RT_UNUSED(hadc);
}
#endif /* RT_ADC_STREAM_USING_FIFO */

/**
 * @brief HAL ADC error callback.
 * @param hadc Pointer to the HAL ADC handle.
 */
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    struct stm32_adc *adc;
    struct rt_adc_stream_ctrl *ctrl;

    RT_ASSERT(hadc != RT_NULL);
    adc = (struct stm32_adc *)hadc;
    if (stm32_adc_stream_dma_is_active(adc, hadc) != RT_TRUE)
    {
        return;
    }

    ctrl = &adc->device.stream_ctrl;
    rt_atomic_store(&ctrl->last_error, (rt_atomic_t)-RT_ERROR);
    LOG_E("%s stream HAL ADC error: error_code=0x%08lx", adc->name, (unsigned long)hadc->ErrorCode);
    (void)rt_hw_adc_stream_isr(&adc->device, RT_ADC_STREAM_EVENT_ERROR, RT_NULL, 0U);
}

#if defined(BSP_USING_ADC1) && defined(BSP_ADC1_USING_DMA)
/**
 * @brief ADC1 DMA interrupt handler.
 */
void ADC1_DMA_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&stm32_adc_obj[ADC1_INDEX].dma_handle);
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_ADC1) && defined(BSP_ADC1_USING_DMA) */

#if defined(BSP_USING_ADC2) && defined(BSP_ADC2_USING_DMA)
/**
 * @brief ADC2 DMA interrupt handler.
 */
void ADC2_DMA_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&stm32_adc_obj[ADC2_INDEX].dma_handle);
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_ADC2) && defined(BSP_ADC2_USING_DMA) */

#if defined(BSP_USING_ADC3) && defined(BSP_ADC3_USING_DMA)
/**
 * @brief ADC3 DMA interrupt handler.
 */
void ADC3_DMA_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&stm32_adc_obj[ADC3_INDEX].dma_handle);
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_ADC3) && defined(BSP_ADC3_USING_DMA) */

#if defined(BSP_USING_ADC4) && defined(BSP_ADC4_USING_DMA)
/**
 * @brief ADC4 DMA interrupt handler.
 */
void ADC4_DMA_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&stm32_adc_obj[ADC4_INDEX].dma_handle);
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_ADC4) && defined(BSP_ADC4_USING_DMA) */
#endif /* STM32_ADC_USING_DMA_STREAM */

#if defined(STM32_ADC_HAS_LL_VREF_CALC)
/**
 * @brief Calculate the ADC reference voltage from a raw VREF sample.
 * @param device Pointer to the ADC device object.
 * @param vref_mv Pointer to the input raw VREF code and output VDDA in mV.
 * @return Operation status.
 */
rt_err_t stm32_adc_calc_vref_mv(struct rt_adc_device *device, rt_uint32_t *vref_mv)
{
    struct stm32_adc *adc;
    rt_uint32_t raw_value;

    if (*vref_mv == 0U)
    {
        return -RT_EINVAL;
    }

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    raw_value = *vref_mv;
    *vref_mv = (rt_uint32_t)STM32_ADC_CALC_VREF_MV(adc, raw_value);
    if (*vref_mv == 0U)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s VREF calculated: raw=%lu vref=%lu mV", adc->name, (unsigned long)raw_value, (unsigned long)*vref_mv);
    return RT_EOK;
}
#endif /* defined(STM32_ADC_HAS_LL_VREF_CALC) */

/**
 * @brief Handle control commands on one STM32 ADC device.
 * @param device Pointer to the ADC device object.
 * @param cmd Control command.
 * @param args Pointer to the control argument buffer.
 * @return Operation status.
 */
static rt_err_t stm32_adc_control(struct rt_adc_device *device, int cmd, void *args)
{
    struct stm32_adc *adc;
    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    LOG_D("%s control cmd=%d", adc->name, cmd);
    switch (cmd)
    {
    case RT_ADC_CMD_GET_RESOLUTION:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *((rt_uint8_t *)args) = stm32_adc_get_resolution_bits(adc);
        return RT_EOK;

    case RT_ADC_CMD_GET_VREF_CHANNEL:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        return stm32_adc_get_vref_logical_channel(adc, (rt_uint8_t *)args);

    case RT_ADC_CMD_CALC_VREF:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
#if defined(STM32_ADC_HAS_LL_VREF_CALC)
        return stm32_adc_calc_vref_mv(device, (rt_uint32_t *)args);
#else
        if (device->default_vref_mv == 0U)
        {
            return -RT_ENOSYS;
        }
        *((rt_uint32_t *)args) = device->default_vref_mv;
        return RT_EOK;
#endif /* defined(STM32_ADC_HAS_LL_VREF_CALC) */

    case RT_ADC_CMD_CALIBRATE:
#if defined(STM32_ADC_HAS_CALIBRATION)
        return stm32_adc_run_calibration(adc, &adc->config);
#else
        return -RT_ENOSYS;
#endif /* defined(STM32_ADC_HAS_CALIBRATION) */

    case RT_ADC_CMD_SET_CONFIG:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }

        adc->config = *((const struct stm32_adc_private_cfg *)args);
        return RT_EOK;

    case RT_ADC_CMD_GET_CONFIG:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *((struct stm32_adc_private_cfg *)args) = adc->config;
        return RT_EOK;

    case RT_ADC_CMD_CLEAR_CHANNEL_CONFIG:
        if (args != RT_NULL)
        {
            return -RT_EINVAL;
        }
        return stm32_adc_clear_channel_config(adc);

    default:
        RT_UNUSED(args);
        return -RT_ENOSYS;
    }
}

/**
 * @brief STM32 ADC core operation table.
 */
static const struct rt_adc_core_ops stm32_adc_core_ops = {
    .open = stm32_adc_open,
    .close = stm32_adc_close,
    .session_config = stm32_adc_session_config,
#if defined(STM32_ADC_USING_TRIGGER)
    .trigger_prepare = stm32_adc_trigger_prepare,
#endif /* defined(STM32_ADC_USING_TRIGGER) */
    .control = stm32_adc_control,
};

/**
 * @brief STM32 ADC sequence-session operation table.
 */
static const struct rt_adc_sequence_ops stm32_adc_sequence_ops = {
    .start = stm32_adc_sequence_start,
    .read = stm32_adc_sequence_read,
    .stop = stm32_adc_sequence_stop,
};

#if STM32_ADC_USING_DMA_STREAM
/**
 * @brief STM32 ADC stream-session operation table.
 */
static const struct rt_adc_stream_ops stm32_adc_stream_ops = {
    .start = stm32_adc_stream_start,
    .sync = stm32_adc_stream_sync,
    .stop = stm32_adc_stream_stop,
};
#endif /* STM32_ADC_USING_DMA_STREAM */

/**
 * @brief STM32 ADC operation table.
 */
static const struct rt_adc_ops stm32_adc_ops = {
    .core = &stm32_adc_core_ops,
    .sequence = &stm32_adc_sequence_ops,
#if STM32_ADC_USING_DMA_STREAM
    .stream = &stm32_adc_stream_ops,
#endif /* STM32_ADC_USING_DMA_STREAM */
};

/**
 * @brief Initialize and register STM32 ADC devices.
 * @return Operation status.
 */
int stm32_adc_init(void)
{
    rt_size_t index;
    int result;

    result = RT_EOK;
    for (index = 0; index < RT_ARRAY_SIZE(stm32_adc_obj); index++)
    {
        rt_atomic_store(&stm32_adc_obj[index].device.state, RT_ADC_STATE_IDLE);
        stm32_adc_obj[index].device.default_vref_mv = 0;
        if (rt_hw_adc_register(&stm32_adc_obj[index].device, stm32_adc_obj[index].name,
                               &stm32_adc_ops, &stm32_adc_obj[index]) != RT_EOK)
        {
            result = -RT_ERROR;
            continue;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(stm32_adc_init);
#endif /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4) */

#endif /* defined(RT_USING_ADC_V2) */
