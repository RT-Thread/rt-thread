/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ADC12_DRV_H
#define HPM_ADC12_DRV_H

#include "hpm_common.h"
#include "hpm_adc12_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief ADC12 driver APIs
 * @defgroup adc12_interface ADC12 driver APIs
 * @ingroup adc_interfaces
 * @{
 */

/** @brief Define ADC12 validity check for the signal type */
#define ADC12_IS_SIGNAL_TYPE_INVALID(TYPE)  (TYPE > (uint32_t)adc12_sample_signal_count)

/** @brief Define ADC12 validity check for the channel number */
#define ADC12_IS_CHANNEL_INVALID(CH) (CH > ADC12_SOC_MAX_CH_NUM)

/** @brief Define ADC12 validity check for the channel sample cycle */
#define ADC12_IS_CHANNEL_SAMPLE_CYCLE_INVALID(CYC) (CYC == 0)

/** @brief Define ADC12 validity check for the trigger number */
#define ADC12_IS_TRIG_CH_INVLAID(CH) (CH > ADC_SOC_MAX_TRIG_CH_NUM)

/** @brief Define ADC12 validity check for the trigger length */
#define ADC12_IS_TRIG_LEN_INVLAID(TRIG_LEN) (TRIG_LEN > ADC_SOC_MAX_TRIG_CH_LEN)

/** @brief Define ADC12 validity check for the sequence length */
#define ADC12_IS_SEQ_LEN_INVLAID(LEN)  ((LEN == 0) || (LEN > ADC_SOC_SEQ_MAX_LEN))

/** @brief Define ADC12 validity check for the DMA buffer length in the sequence mode */
#define ADC12_IS_SEQ_DMA_BUFF_LEN_INVLAID(LEN)  ((LEN == 0) || (LEN > ADC_SOC_SEQ_MAX_DMA_BUFF_LEN_IN_4BYTES))

/** @brief Define ADC12 validity check for the DMA buffer length in the preemption mode */
#define ADC12_IS_PMT_DMA_BUFF_LEN_INVLAID(LEN)  ((LEN == 0) || (LEN > ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES))

/** @brief Define ADC12 sample signal types. */
typedef enum {
    adc12_sample_signal_single_ended = 0,
    adc12_sample_signal_differential = 1,
    adc12_sample_signal_count = 2
} adc12_sample_signal_t;

/** @brief Define ADC12 resolutions. */
typedef enum {
    adc12_res_6_bits = 0,
    adc12_res_8_bits,
    adc12_res_10_bits,
    adc12_res_12_bits
} adc12_resolution_t;

/** @brief Define ADC12 conversion modes. */
typedef enum {
    adc12_conv_mode_oneshot = 0,
    adc12_conv_mode_period,
    adc12_conv_mode_sequence,
    adc12_conv_mode_preemption
} adc12_conversion_mode_t;

/** @brief  Define ADC12 Clock Divider */
typedef enum {
    adc12_clock_divider_1 = 1,
    adc12_clock_divider_2,
    adc12_clock_divider_3,
    adc12_clock_divider_4,
    adc12_clock_divider_5,
    adc12_clock_divider_6,
    adc12_clock_divider_7,
    adc12_clock_divider_8,
    adc12_clock_divider_9,
    adc12_clock_divider_10,
    adc12_clock_divider_11,
    adc12_clock_divider_12,
    adc12_clock_divider_13,
    adc12_clock_divider_14,
    adc12_clock_divider_15,
    adc12_clock_divider_16,
} adc12_clock_divider_t;

/** @brief  Define ADC12 irq events. */
typedef enum {
    /** This mask indicates that a trigger conversion is complete. */
    adc12_event_trig_complete       = ADC12_INT_STS_TRIG_CMPT_MASK,

    /** This mask indicates that a conflict caused by software-triggered conversions. */
    adc12_event_trig_sw_conflict    = ADC12_INT_STS_TRIG_SW_CFLCT_MASK,

    /** This mask indicates that a conflict caused by hardware-triggered conversions. */
    adc12_event_trig_hw_conflict    = ADC12_INT_STS_TRIG_HW_CFLCT_MASK,

    /** This mask indicates that a conflict caused when bus reading from different channels. */
    adc12_event_read_conflict       = ADC12_INT_STS_READ_CFLCT_MASK,

    /** This mask indicates that a conflict caused by sequence-triggered conversions. */
    adc12_event_seq_sw_conflict     = ADC12_INT_STS_SEQ_SW_CFLCT_MASK,

    /** This mask indicates that a conflict caused by hardware-triggered conversions. */
    adc12_event_seq_hw_conflict     = ADC12_INT_STS_SEQ_HW_CFLCT_MASK,

    /** This mask indicates that DMA is stopped currently. */
    adc12_event_seq_dma_abort       = ADC12_INT_STS_SEQ_DMAABT_MASK,

    /** This mask indicates that all of the configured conversion(s) in a queue is(are) complete. */
    adc12_event_seq_full_complete   = ADC12_INT_STS_SEQ_CMPT_MASK,

    /** This mask indicates that one of the configured conversion(s) in a queue is complete. */
    adc12_event_seq_single_complete = ADC12_INT_STS_SEQ_CVC_MASK,

    /** This mask indicates that DMA FIFO is full currently. */
    adc12_event_dma_fifo_full       = ADC12_INT_STS_DMA_FIFO_FULL_MASK
} adc12_irq_event_t;

/** @brief ADC12 common configuration struct. */
typedef struct {
    uint8_t res;
    uint8_t conv_mode;
    uint32_t adc_clk_div;
    bool wait_dis;
    bool sel_sync_ahb;
    bool adc_ahb_en;
} adc12_config_t;

/** @brief ADC12 channel configuration struct. */
typedef struct {
   uint8_t ch;
   uint8_t diff_sel;
   uint16_t thshdh;
   uint16_t thshdl;
   bool wdog_int_en;
   uint8_t sample_cycle_shift;
   uint32_t sample_cycle;
} adc12_channel_config_t;

/** @brief ADC12 channel configuration struct. */
typedef struct {
   uint8_t ch;
   uint16_t thshdh;
   uint16_t thshdl;
} adc12_channel_threshold_t;

/** @brief ADC12 DMA configuration struct. */
typedef struct {
    uint32_t *start_addr;
    uint32_t buff_len_in_4bytes;
    uint32_t stop_pos;
    bool stop_en;
} adc12_dma_config_t;

/** @brief ADC12 DMA configuration struct for the sequence mode. */
typedef struct {
    uint32_t           :4;
    uint32_t result    :12;
    uint32_t seq_num   :4;
    uint32_t           :4;
    uint32_t adc_ch    :5;
    uint32_t           :2;
    uint32_t cycle_bit :1;
} adc12_seq_dma_data_t;

/** @brief ADC12 DMA configuration struct for the preemption mode. */
typedef struct {
    uint32_t           :4;
    uint32_t result    :12;
    uint32_t seq_num   :2;
    uint32_t           :2;
    uint32_t trig_ch   :4;
    uint32_t adc_ch    :5;
    uint32_t           :2;
    uint32_t cycle_bit :1;
} adc12_pmt_dma_data_t;

/** @brief ADC12 configuration struct for the period mode. */
typedef struct {
    uint8_t ch;
    uint8_t prescale;
    uint8_t period_count;
} adc12_prd_config_t;

/** @brief ADC12 queue configuration struct for the sequence mode. */
typedef struct {
    bool seq_int_en;
    uint8_t ch;
} adc12_seq_queue_config_t;

/** @brief ADC12 configuration struct for the sequence mode. */
typedef struct {
    adc12_seq_queue_config_t queue[ADC_SOC_SEQ_MAX_LEN];
    bool restart_en;
    bool cont_en;
    bool sw_trig_en;
    bool hw_trig_en;
    uint8_t seq_len;
} adc12_seq_config_t;

/** @brief ADC12 trigger configuration struct for the preemption mode. */
typedef struct {
    bool    inten[ADC_SOC_MAX_TRIG_CH_LEN];
    uint8_t adc_ch[ADC_SOC_MAX_TRIG_CH_LEN];
    uint8_t trig_ch;
    uint8_t trig_len;
} adc12_pmt_config_t;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @name Initialization and Deinitialization
 * @{
 */

/**
 * @brief Get a default configuration for an ADC12 instance.
 *
 * @param[out] config A pointer to the configuration struct of @ref adc12_config_t.
 */
void adc12_get_default_config(adc12_config_t *config);

/**
 * @brief Get a default configuration for an ADC12 channel.
 *
 * @param[out] config A pointer to the configuration struct of @ref adc12_channel_config_t.
 */
void adc12_get_channel_default_config(adc12_channel_config_t *config);

/**
 * @brief De-initialize an ADC12 instance.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @return A result of de-initializing an ADC12 instance.
 * @retval status_success De-initialize an ADC12 instance successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument De-initialize an ADC12 instance unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_deinit(ADC12_Type *ptr);

/**
 * @brief Initialize an ADC12 instance.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] config A pointer to the configuration struct of @ref adc12_config_t.
 * @return A result of initializing an ADC12 instance.
 * @retval status_success Initialize an ADC12 instance successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Initialize an ADC12 instance unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_init(ADC12_Type *ptr, adc12_config_t *config);

/**
 * @brief Initialize an ADC12 channel.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] config A pointer to the configuration struct of @ref adc12_channel_config_t.
 * @return A result of initializing an ADC12 channel.
 * @retval status_success Initialize an ADC12 channel successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Initialize an ADC12 channel unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_init_channel(ADC12_Type *ptr, adc12_channel_config_t *config);

/**
 * @brief Get thresholds of an ADC12 channel
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] ch An ADC12 channel number
 * @param[out] config A pointer to the structure of channel threshold
 * @return A result of getting thresholds of an ADC12 channel .
 * @retval status_success Initialize an ADC12 channel successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Initialize an ADC12 channel unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_get_channel_threshold(ADC12_Type *ptr, uint8_t ch, adc12_channel_threshold_t *config);

/**
 * @brief Configure the the period mode for an ADC12 instance.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] config A pointer to the configuration struct of @ref adc12_prd_config_t.
 * @return A result of configuring the the period mode for an ADC12 instance.
 * @retval status_success Configure the the period mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Configure the the period mode unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_set_prd_config(ADC12_Type *ptr, adc12_prd_config_t *config);

/**
 * @brief Configure the the sequence mode for an ADC12 instance.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] config A pointer to configuration struct of @ref adc12_seq_config_t.
 * @return A result of configuring the the sequence mode for an ADC12 instance.
 * @retval status_success Configure the the sequence mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Configure the the sequence mode unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_set_seq_config(ADC12_Type *ptr, adc12_seq_config_t *config);

/**
 * @brief Configure the preemption mode for an ADC12 instance.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] config A pointer to configuration struct of @ref adc12_pmt_config_t.
 * @return A result of configuring the preemption mode for an ADC12 instance.
 * @retval status_success Configure the preemption mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Configure the preemption mode unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_set_pmt_config(ADC12_Type *ptr, adc12_pmt_config_t *config);

/** @} */

/**
 * @name DMA Control
 * @{
 */

/**
 * @brief Configure the stop position offset in the specified memory of DMA write operation for the sequence mode.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] stop_pos A stop position offset.
 */
static inline void adc12_set_seq_stop_pos(ADC12_Type *ptr, uint16_t stop_pos)
{
    ptr->SEQ_DMA_CFG = (ptr->SEQ_DMA_CFG & ~ADC12_SEQ_DMA_CFG_STOP_POS_MASK)
                     | ADC12_SEQ_DMA_CFG_STOP_POS_SET(stop_pos);
}

/**
 * @brief Configure the start address of DMA write operation for the preemption mode.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] addr A start address of DMA write operation.
 */
static inline void adc12_init_pmt_dma(ADC12_Type *ptr, uint32_t addr)
{
    ptr->TRG_DMA_ADDR = addr & ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK;
}

/**
 * @brief Configure the start address of DMA write operation for the sequence mode.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] config A pointer to configuration struct of @ref adc12_dma_config_t.
 * @return An implementation result of DMA initializing for the sequence mode
 * @retval status_success ADC12 initialize in sequence mode successfully. Please refert to @ref hpm_stat_t.
 * @retval status_invalid_argument ADC12 initialize in sequence mode unsuccessfully due to passing invalid arguments. Please refert to @ref hpm_stat_t.
 */
hpm_stat_t adc12_init_seq_dma(ADC12_Type *ptr, adc12_dma_config_t *config);

/** @} */

/**
 * @name Status
 * @{
 */

/**
 * @brief Get all ADC12 status flags.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @return A mask indicating all corresponding interrupt statuses.
 * @retval A mask. Please refer to @ref adc12_irq_event_t.
 */
static inline uint32_t adc12_get_status_flags(ADC12_Type *ptr)
{
    return ptr->INT_STS;
}

/**
 * @brief Set value of the WAIT_DIS bit. The ADC does not block access to the associated peripheral bus
 * until the ADC has completed its conversion. *
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @deprecated This API will be removed from V2.0.x
 */
static inline void adc12_disable_busywait(ADC12_Type *ptr)
{
    ptr->BUF_CFG0 |= ADC12_BUF_CFG0_WAIT_DIS_SET(1);
}

/**
 * @brief Set value of the WAIT_DIS bit. ADC blocks access to the associated peripheral bus
 * until the ADC completes the conversion.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @deprecated This API will be removed from V2.0.x
 */
static inline void adc12_enable_busywait(ADC12_Type *ptr)
{
    ptr->BUF_CFG0 &= ~ADC12_BUF_CFG0_WAIT_DIS_MASK;
}

/**
 * @brief Set nonblocking read in oneshot mode.
 * @note An ADC does not block access to the associated peripheral whether it completes a conversion or not.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 */
static inline void adc12_set_nonblocking_read(ADC12_Type *ptr)
{
    ptr->BUF_CFG0 |= ADC12_BUF_CFG0_WAIT_DIS_MASK;
}

/**
 * @brief Set blocking read in oneshot mode.
 * @note An ADC blocks access to the associated peripheral bus until it completes a conversion.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 */
static inline void adc12_set_blocking_read(ADC12_Type *ptr)
{
    ptr->BUF_CFG0 &= ~ADC12_BUF_CFG0_WAIT_DIS_MASK;
}

/**
 * @brief Judge whether the current setting is none-blocking mode or not.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @return A result indicating the status of bus waiting.
 * @retval True means that nonblocking reading.
 * @retval False means that blocking reading.
 *
 */
static inline bool adc12_is_nonblocking_mode(ADC12_Type *ptr)
{
    return (ADC12_BUF_CFG0_WAIT_DIS_GET(ptr->BUF_CFG0)  ? true : false);
}

/**
 * @brief Get the status of a conversion validity.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] ch An ADC12 peripheral channel.
 * @return Status indicating the validity of the current conversion result.
 *
 * @note This function is only used when the WAIT_DIS bit in the BUF_RESULT register is 1.
 */
static inline bool adc12_get_conv_valid_status(ADC12_Type *ptr, uint8_t ch)
{
    return ADC12_BUS_RESULT_VALID_GET(ptr->BUS_RESULT[ch]);
}

/**
 * @brief Clear the status flags.
 *
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] mask A mask that means the specified flags to be cleared. Please refer to @ref adc12_irq_event_t.
 *
 * @note Only the specified flags can be cleared by writing the INT_STS register.
 */
static inline void adc12_clear_status_flags(ADC12_Type *ptr, uint32_t mask)
{
    ptr->INT_STS = mask;
}

/** @} */

/**
 * @name Interrupts
 * @{
 */

/**
 * @brief Enable interrupts.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] mask A mask indicating the specified ADC interrupt events. Please refer to @ref adc12_irq_event_t.
 */
static inline void adc12_enable_interrupts(ADC12_Type *ptr, uint32_t mask)
{
    ptr->INT_EN |= mask;
}

/**
 * @brief Disable interrupts.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] mask A mask indicating the specified interrupt events. Please refer to @ref adc12_irq_event_t.
 */
static inline void adc12_disable_interrupts(ADC12_Type *ptr, uint32_t mask)
{
    ptr->INT_EN &= ~mask;
}

/** @} */

/**
 * @name Trigger and Conversion
 * @{
 */

/**
 * @brief Trigger ADC conversions by software in sequence mode
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @return An implementation result of getting an ADC12 software trigger.
 * @retval status_success ADC12 software triggers successfully. Please refer to @ref hpm_stat_t.
 * @retval status_fail ADC12 software triggers unsuccessfully. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_trigger_seq_by_sw(ADC12_Type *ptr);

/**
 * @brief Trigger ADC conversions by software in preemption mode
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] trig_ch A trigger channel number(e.g. TRIG0A,TRIG0B,TRIG0C...).
 * @return An implementation result of getting an ADC12 software trigger.
 * @retval status_success ADC12 software triggers successfully. Please refer to @ref hpm_stat_t.
 * @retval status_fail ADC12 software triggers unsuccessfully. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_trigger_pmt_by_sw(ADC12_Type *ptr, uint8_t trig_ch);

/**
 * @brief Get the result in oneshot mode.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] ch An ADC12 peripheral channel.
 * @param[out] result A pointer to an ADC12 conversion result.
 * @return An implementation result of getting an ADC12 conversion result in oneshot mode.
 * @retval status_success Get the result of an ADC12 conversion in oneshot mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Get the result of an ADC12 conversion in oneshot mode unsuccessfully due to passing invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_get_oneshot_result(ADC12_Type *ptr, uint8_t ch, uint16_t *result);

/**
 * @brief Get the result in the period mode.
 *
 * @param[in] ptr An ADC12 peripheral base address.
 * @param[in] ch An ADC12 peripheral channel.
 * @param[out] result A pointer to a specified ADC12 conversion result
 * @return An implementation of getting an ADC12 conversion result in the period mode.
 * @retval status_success Get the result of an ADC12 conversion in the period mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Get the result of an ADC12 conversion in the period mode unsuccessfully due to passing invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc12_get_prd_result(ADC12_Type *ptr, uint8_t ch, uint16_t *result);

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* HPM_ADC12_DRV_H */
