/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ADC_H
#define HPM_ADC_H

#include "hpm_common.h"
#ifdef CONFIG_HAS_HPMSDK_ADC12
#include "hpm_adc12_drv.h"
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
#include "hpm_adc16_drv.h"
#endif
#include "hpm_soc_feature.h"
/**
 * @brief ADC HAL driver APIs
 * @defgroup hpm_adc_interface HPM ADC driver APIs
 * @ingroup hpm_adc_interfaces
 * @{
 */

/**
 * @brief An ADC peripheral base address.
 *
 */
typedef union {
#ifdef CONFIG_HAS_HPMSDK_ADC12
    ADC12_Type *adc12;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
    ADC16_Type *adc16;
#endif
} adc_base;

/**
 * @brief use adc12 or adc16.
 *
 */
#define ADCX_MODULE_ADC12 1
#define ADCX_MODULE_ADC16 2

typedef enum {
    adc_module_adc12 = ADCX_MODULE_ADC12,
    adc_module_adc16 = ADCX_MODULE_ADC16
} adc_module;

/**
 * @brief ADC common configuration struct.
 *
 */
typedef struct {
    adc_module module;
    adc_base adc_base;
    struct {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_config_t adc12;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_config_t adc16;
#endif
    } config;
} adc_config_t;

/**
 * @brief ADC channel configuration struct.
 *
 */
typedef struct {
    adc_module module;
    adc_base adc_base;
    struct {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_channel_config_t adc12_ch;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_channel_config_t adc16_ch;
#endif
    } config;
} adc_channel_config_t;

/**
 * @brief ADC DMA configuration struct.
 *
 */
typedef struct {
    adc_module module;
    adc_base adc_base;
    struct {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_dma_config_t adc12;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_dma_config_t adc16;
#endif
    } config;
} adc_dma_config_t;

/**
 * @brief ADC configuration struct for period mode.
 *
 */
typedef struct {
    adc_module module;
    adc_base adc_base;
    struct {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_prd_config_t adc12;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_prd_config_t adc16;
#endif
    } config;
} adc_prd_config_t;

/**
 * @brief ADC configuration struct for sequence mode.
 *
 */
typedef struct {
    adc_module module;
    adc_base adc_base;
    struct {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_seq_config_t adc12;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_seq_config_t adc16;
#endif
    } config;
} adc_seq_config_t;

/**
 * @brief ADC trigger configuration struct for preempt mode.
 *
 */
typedef struct {
    adc_module module;
    adc_base adc_base;
    struct {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_pmt_config_t adc12;
#endif
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_pmt_config_t adc16;
#endif
    } config;
} adc_pmt_config_t;


typedef struct {
    adc_module module;
    adc_base adc_base;
} adc_type;



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get a default configuration for an ADC instance.
 *
 * @param[out] config A pointer to the configuration struct of "adc_config_t".
 *
 */
static inline void hpm_adc_init_default_config(adc_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_get_default_config(&config->config.adc12);
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_get_default_config(&config->config.adc16);
#endif
    }
}

/**
 * @brief Get a default configuration for an ADC channel instance.
 *
 * @param[out] config A pointer to the configuration struct of "adc_channel_config_t".
 *
 */
static inline void hpm_adc_init_channel_default_config(adc_channel_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_get_channel_default_config(&config->config.adc12_ch);
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_get_channel_default_config(&config->config.adc16_ch);
#endif
    }
}

/**
 * @brief Initialize an ADC instance.
 *
 * @param[in] config A pointer to the configuration struct of "adc_config_t".
 * @retval status_success Initialize an ADC instance successfully.
 * @retval status_invalid_argument Initialize an ADC instance unsuccessfully because of passing one or more invalid arguments.
 */
static inline hpm_stat_t hpm_adc_init(adc_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_init(config->adc_base.adc12, &config->config.adc12);
#else
        return status_invalid_argument;
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_init(config->adc_base.adc16, &config->config.adc16);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Initialize an ADC channel.
 *
 * @param[in] config A pointer to the configuration struct of "adc_config_t".
 * @retval status_success Initialize an ADC instance successfully.
 * @retval status_invalid_argument Initialize an ADC instance unsuccessfully because of passing one or more invalid arguments.
 */
static inline hpm_stat_t hpm_adc_channel_init(adc_channel_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_init_channel(config->adc_base.adc12, &config->config.adc12_ch);
#else
        return status_invalid_argument;
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_init_channel(config->adc_base.adc16, &config->config.adc16_ch);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Configure the periodic mode for an ADC instance.
 *
 * @param[in] config A pointer to the configuration struct of "adc_prd_config_t".
 * @retval status_success Configure the periodic mode for an ADC instance successfully.
 * @retval status_invalid_argument Configure the periodic mode for an ADC instance unsuccessfully because of passing one or more invalid arguments.
 *
 */
static inline hpm_stat_t hpm_adc_set_period_config(adc_prd_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_set_prd_config(config->adc_base.adc12, &config->config.adc12);
#else
        return status_invalid_argument;
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_set_prd_config(config->adc_base.adc16, &config->config.adc16);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Configure the sequence mode for an ADC instance.
 *
 * @param[in] config A pointer to configuration struct of "adc_seq_config_t".
 * @retval status_success Configure the sequence mode for an ADC instance successfully.
 * @retval status_invalid_argument Configure the sequence mode for an ADC instance unsuccessfully because of passing one or more invalid arguments.
 */
static inline hpm_stat_t hpm_adc_set_sequence_config(adc_seq_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_set_seq_config(config->adc_base.adc12, &config->config.adc12);
#else
        return status_invalid_argument;
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_set_seq_config(config->adc_base.adc16, &config->config.adc16);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Configure the preemption mode for an ADC instance.
 *
 * @param[in] config a pointer to configuration struct of "adc_pmt_config_t".
 * @retval status_success Configure the preemption mode for an ADC instance successfully.
 * @retval status_invalid_argument Configure the preemption mode for an ADC instance unsuccessfully because of passing one or more invalid arguments.
 */
static inline hpm_stat_t hpm_adc_set_preempt_config(adc_pmt_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_set_pmt_config(config->adc_base.adc12, &config->config.adc12);
#else
        return status_invalid_argument;
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_set_pmt_config(config->adc_base.adc16, &config->config.adc16);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Configure the stop position offset in the specified memory for DMA write operation for sequence mode.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] stop_pos The stop position offset.
 */
static inline void hpm_adc_set_seq_stop_pos(adc_type *ptr, uint16_t stop_pos)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_set_seq_stop_pos(ptr->adc_base.adc12, stop_pos);
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_set_seq_stop_pos(ptr->adc_base.adc16, stop_pos);
#endif
    }
}

/**
 * @brief Configure the start address of DMA write operation for preemption mode.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] addr The start address of DMA write operation.
 */
static inline void hpm_adc_init_pmt_dma(adc_type *ptr, uint32_t addr)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_init_pmt_dma(ptr->adc_base.adc12, addr);
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_init_pmt_dma(ptr->adc_base.adc16, addr);
#endif
    }
}

/**
 * @brief Configure the start address of DMA write operation for preemption mode.
 *
 * @param[in] config A pointer to configuration struct of "adc_dma_config_t".
 */
static inline void hpm_adc_init_seq_dma(adc_dma_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_init_seq_dma(config->adc_base.adc12, &config->config.adc12);
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_init_seq_dma(config->adc_base.adc16, &config->config.adc16);
#endif
    }
}

/**
 * @brief Reset value of the WAIT_DIS bit. ADC blocks access to the associated peripheral bus
 * until the ADC completes the conversion.
 *
 * @param[in] config A pointer to configuration struct of "adc_dma_config_t".
 */
static inline void hpm_adc_disable_busywait(adc_dma_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_disable_busywait(config->adc_base.adc12);
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_disable_busywait(config->adc_base.adc16);
#endif
    }
}

/**
 * @brief Set value of the WAIT_DIS bit. The ADC does not block access to the associated peripheral bus
 * until the ADC has completed its conversion.
 *
 * @param[in] config A pointer to configuration struct of "adc_dma_config_t".
 */
static inline void hpm_adc_enable_busywait(adc_dma_config_t *config)
{
    if (config->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_enable_busywait(config->adc_base.adc12);
#endif
    } else if (config->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_enable_busywait(config->adc_base.adc16);
#endif
    }
}


/**
 * @brief Get ADC status flags.
 *
 * This function gets all ADC status flags.
 * @param[in] ptr An ADC peripheral base address.
 * @retval Status The ADC interrupt status flags.
 */
static inline uint32_t hpm_adc_get_status_flags(adc_type *ptr)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_get_status_flags(ptr->adc_base.adc12);
#else
        return status_invalid_argument;
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_get_status_flags(ptr->adc_base.adc16);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Get status flag of a conversion.
 *
 * This status flag is only used when wait_dis is set to disable.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] ch An ADC peripheral channel.
 * @retval Status It means  the current conversion is valid.
 */
static inline bool hpm_adc_get_conv_valid_status(adc_type *ptr, uint8_t ch)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_get_conv_valid_status(ptr->adc_base.adc12, ch);
#else
        return status_invalid_argument;
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_get_conv_valid_status(ptr->adc_base.adc16, ch);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Clear status flags.
 *
 * Only the specified flags can be cleared by writing INT_STS register.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] mask Mask value for flags to be cleared. Refer to "adc12_irq_event_t". Refer to "adc16_irq_event_t".
 */
static inline void hpm_adc_clear_status_flags(adc_type *ptr, uint32_t mask)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_clear_status_flags(ptr->adc_base.adc12, mask);
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_clear_status_flags(ptr->adc_base.adc16, mask);
#endif
    }
}

/**
 * @brief Enable interrupts.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] mask Mask value for interrupt events. Refer to "adc12_irq_event_t".Refer to "adc16_irq_event_t".
 */
static inline void hpm_adc_enable_interrupts(adc_type *ptr, uint32_t mask)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_enable_interrupts(ptr->adc_base.adc12, mask);
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_enable_interrupts(ptr->adc_base.adc16, mask);
#endif
    }
}

/**
 * @brief Disable interrupts.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] mask Mask value for interrupt events. Refer to "adc12_irq_event_t".Refer to "adc16_irq_event_t".
 */
static inline void hpm_adc_disable_interrupts(adc_type *ptr, uint32_t mask)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        adc12_disable_interrupts(ptr->adc_base.adc12, mask);
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        adc16_disable_interrupts(ptr->adc_base.adc16, mask);
#endif
    }
}

/**
 * @brief Get the result in oneshot mode.
 *
 * @param[in] ptr An ADC peripheral base address.
 * @param[in] ch An ADC peripheral channel.
 * @param[out] result The result of an ADC12 conversion.
 *
 * @retval status_success Get the result of an ADC12 conversion in oneshot mode successfully.
 * @retval status_invalid_argument Get the result of an ADC12 conversion in oneshot mode unsuccessfully because of passing invalid arguments.
 */
static inline hpm_stat_t hpm_adc_get_oneshot_result(adc_type *ptr, uint8_t ch, uint16_t *result)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_get_oneshot_result(ptr->adc_base.adc12, ch, result);
#else
        return status_invalid_argument;
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_get_oneshot_result(ptr->adc_base.adc16, ch, result);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Get the result in periodic mode.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] ch An ADC12 peripheral channel.
 * @param[out] result The result of an ADC12 conversion.
 *
 * @retval status_success Get the result of an ADC12 conversion in periodic mode successfully.
 * @retval status_invalid_argument Get the result of an ADC12 conversion in periodic mode unsuccessfully because of passing invalid arguments.
 */
static inline hpm_stat_t hpm_adc_get_prd_result(adc_type *ptr, uint8_t ch, uint16_t *result)
{
    if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_get_prd_result(ptr->adc_base.adc12, ch, result);
#else
        return status_invalid_argument;
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_get_prd_result(ptr->adc_base.adc16, ch, result);
#else
        return status_invalid_argument;
#endif
    } else {
        return status_invalid_argument;
    }
}

/**
 * @brief Do a software trigger for sequence mode.
 *
 * @param[in] ptr An adc peripheral base address.
 *
 */
static inline hpm_stat_t hpm_adc_trigger_seq_by_sw(adc_type *ptr)
{
     if (ptr->module == adc_module_adc12) {
#ifdef CONFIG_HAS_HPMSDK_ADC12
        return adc12_trigger_seq_by_sw(ptr->adc_base.adc12);
#endif
    } else if (ptr->module == adc_module_adc16) {
#ifdef CONFIG_HAS_HPMSDK_ADC16
        return adc16_trigger_seq_by_sw(ptr->adc_base.adc16);
#endif
    } else {
        return status_invalid_argument;
    }
}

#ifdef __cplusplus
}
#endif

/** @} */

#endif
