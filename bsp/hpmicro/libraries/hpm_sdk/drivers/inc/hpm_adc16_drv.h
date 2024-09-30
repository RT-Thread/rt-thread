/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ADC16_DRV_H
#define HPM_ADC16_DRV_H

#include "hpm_common.h"
#include "hpm_adc16_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief ADC16 driver APIs
 * @defgroup adc16_interface ADC16 driver APIs
 * @ingroup adc_interfaces
 * @{
 */

/** @brief Define ADC16 validity check for the channel number */
#if defined (ADC16_SOC_TEMP_CH_EN) && ADC16_SOC_TEMP_CH_EN
#define ADC16_IS_CHANNEL_INVALID(CH) (CH > ADC16_SOC_MAX_CH_NUM && CH != ADC16_SOC_TEMP_CH_NUM)
#else
#define ADC16_IS_CHANNEL_INVALID(CH) (CH > ADC16_SOC_MAX_CH_NUM)
#endif

/** @brief Define ADC16 validity check for the channel sample cycle */
#define ADC16_IS_CHANNEL_SAMPLE_CYCLE_INVALID(CYC) (CYC == 0)

/** @brief Define ADC16 validity check for the trigger number */
#define ADC16_IS_TRIG_CH_INVLAID(CH) (CH > ADC_SOC_MAX_TRIG_CH_NUM)

/** @brief Define ADC16 validity check for the trigger length */
#define ADC16_IS_TRIG_LEN_INVLAID(TRIG_LEN) (TRIG_LEN > ADC_SOC_MAX_TRIG_CH_LEN)

/** @brief Define ADC16 validity check for the sequence length */
#define ADC16_IS_SEQ_LEN_INVLAID(LEN)  ((LEN == 0) || (LEN > ADC_SOC_SEQ_MAX_LEN))

/** @brief Define ADC16 validity check for the DMA buffer length in the sequence mode */
#define ADC16_IS_SEQ_DMA_BUFF_LEN_INVLAID(LEN)  ((LEN == 0) || (LEN > ADC_SOC_SEQ_MAX_DMA_BUFF_LEN_IN_4BYTES))

/** @brief Define ADC16 validity check for the DMA buffer length in the preemption mode */
#define ADC16_IS_PMT_DMA_BUFF_LEN_INVLAID(LEN)  ((LEN == 0) || (LEN > ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES))

/** @brief Define ADC16 resolutions. */
typedef enum {
    adc16_res_8_bits = 9,
    adc16_res_10_bits = 11,
    adc16_res_12_bits = 14,
    adc16_res_16_bits = 21
} adc16_resolution_t;

/** @brief Define ADC16 conversion modes. */
typedef enum {
    adc16_conv_mode_oneshot = 0,
    adc16_conv_mode_period,
    adc16_conv_mode_sequence,
    adc16_conv_mode_preemption
} adc16_conversion_mode_t;

/** @brief  Define ADC16 Clock Divider */
typedef enum {
    adc16_clock_divider_1 = 1,
    adc16_clock_divider_2,
    adc16_clock_divider_3,
    adc16_clock_divider_4,
    adc16_clock_divider_5,
    adc16_clock_divider_6,
    adc16_clock_divider_7,
    adc16_clock_divider_8,
    adc16_clock_divider_9,
    adc16_clock_divider_10,
    adc16_clock_divider_11,
    adc16_clock_divider_12,
    adc16_clock_divider_13,
    adc16_clock_divider_14,
    adc16_clock_divider_15,
    adc16_clock_divider_16,
} adc16_clock_divider_t;

/** @brief  Define ADC16 irq events. */
typedef enum {
    /** This mask indicates that a trigger conversion is complete. */
    adc16_event_trig_complete       = ADC16_INT_STS_TRIG_CMPT_MASK,

    /** This mask indicates that a conflict caused by software-triggered conversions. */
    adc16_event_trig_sw_conflict    = ADC16_INT_STS_TRIG_SW_CFLCT_MASK,

    /** This mask indicates that a conflict caused by hardware-triggered conversions. */
    adc16_event_trig_hw_conflict    = ADC16_INT_STS_TRIG_HW_CFLCT_MASK,

    /** This mask indicates that a conflict caused when bus reading from different channels. */
    adc16_event_read_conflict       = ADC16_INT_STS_READ_CFLCT_MASK,

    /** This mask indicates that a conflict caused by sequence-triggered conversions. */
    adc16_event_seq_sw_conflict     = ADC16_INT_STS_SEQ_SW_CFLCT_MASK,

    /** This mask indicates that a conflict caused by hardware-triggered conversions. */
    adc16_event_seq_hw_conflict     = ADC16_INT_STS_SEQ_HW_CFLCT_MASK,

    /** This mask indicates that DMA is stopped currently. */
    adc16_event_seq_dma_abort       = ADC16_INT_STS_SEQ_DMAABT_MASK,

    /** This mask indicates that all of the configured conversion(s) in a queue is(are) complete. */
    adc16_event_seq_full_complete   = ADC16_INT_STS_SEQ_CMPT_MASK,

    /** This mask indicates that one of the configured conversion(s) in a queue is complete. */
    adc16_event_seq_single_complete = ADC16_INT_STS_SEQ_CVC_MASK,

    /** This mask indicates that DMA FIFO is full currently. */
    adc16_event_dma_fifo_full       = ADC16_INT_STS_DMA_FIFO_FULL_MASK
} adc16_irq_event_t;

/** @brief ADC16 common configuration struct. */
typedef struct {
    uint8_t res;
    uint8_t conv_mode;
    uint32_t adc_clk_div;
    bool port3_realtime;
    bool wait_dis;
    bool sel_sync_ahb;
    bool adc_ahb_en;
} adc16_config_t;

/** @brief ADC16 channel configuration struct. */
typedef struct {
   uint8_t ch;
   uint16_t thshdh;
   uint16_t thshdl;
   bool wdog_int_en;
   uint8_t sample_cycle_shift;
   uint32_t sample_cycle;
} adc16_channel_config_t;

/** @brief ADC16 channel configuration struct. */
typedef struct {
   uint8_t ch;
   uint16_t thshdh;
   uint16_t thshdl;
} adc16_channel_threshold_t;

/** @brief ADC16 DMA configuration struct. */
typedef struct {
    uint32_t *start_addr;
    uint32_t buff_len_in_4bytes;
    uint32_t stop_pos;
    bool stop_en;
} adc16_dma_config_t;

/** @brief ADC16 DMA configuration struct for the sequence mode. */
#if defined(ADC_SOC_IP_VERSION) && (ADC_SOC_IP_VERSION < 2)
typedef struct {
    uint32_t result    :16;
    uint32_t seq_num   :4;
    uint32_t           :4;
    uint32_t adc_ch    :5;
    uint32_t           :2;
    uint32_t cycle_bit :1;
} adc16_seq_dma_data_t;
#else
typedef struct {
    uint32_t result    :16;
    uint32_t seq_num   :4;
    uint32_t adc_ch    :5;
    uint32_t           :6;
    uint32_t cycle_bit :1;
} adc16_seq_dma_data_t;
#endif

/** @brief ADC16 DMA configuration struct for the preemption mode. */
#if defined(ADC_SOC_IP_VERSION) && (ADC_SOC_IP_VERSION < 2)
typedef struct {
    uint32_t result    :16;
    uint32_t seq_num   :2;
    uint32_t           :2;
    uint32_t trig_ch   :4;
    uint32_t adc_ch    :5;
    uint32_t           :2;
    uint32_t cycle_bit :1;
} adc16_pmt_dma_data_t;
#else
typedef struct {
    uint32_t result    :16;
    uint32_t           :4;
    uint32_t adc_ch    :5;
    uint32_t trig_ch   :4;
    uint32_t seq_num   :2;
    uint32_t cycle_bit :1;
} adc16_pmt_dma_data_t;
#endif

/** @brief ADC16 configuration struct for the period mode. */
typedef struct {
    uint8_t ch;
    uint8_t prescale;
    uint8_t period_count;
} adc16_prd_config_t;

/** @brief ADC16 queue configuration struct for the sequence mode. */
typedef struct {
    bool seq_int_en;
    uint8_t ch;
} adc16_seq_queue_config_t;

/** @brief ADC16 configuration struct for the sequence mode. */
typedef struct {
    adc16_seq_queue_config_t queue[ADC_SOC_SEQ_MAX_LEN];
    bool restart_en;
    bool cont_en;
    bool sw_trig_en;
    bool hw_trig_en;
    uint8_t seq_len;
} adc16_seq_config_t;

/** @brief ADC16 trigger configuration struct for the preemption mode. */
typedef struct {
    bool    inten[ADC_SOC_MAX_TRIG_CH_LEN];
    uint8_t adc_ch[ADC_SOC_MAX_TRIG_CH_LEN];
    uint8_t trig_ch;
    uint8_t trig_len;
} adc16_pmt_config_t;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @name Initialization and Deinitialization
 * @{
 */

/**
 * @brief Get a default configuration for an ADC16 instance.
 *
 * @param[out] config A pointer to the configuration struct of @ref adc16_config_t.
 *
 */
void adc16_get_default_config(adc16_config_t *config);

/**
 * @brief Get a default configuration for an ADC16 Channel.
 *
 * @param[out] config A pointer to the configuration struct of @ref adc16_channel_config_t.
 */
void adc16_get_channel_default_config(adc16_channel_config_t *config);

/**
 * @brief De-initialize an ADC16 instance.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @return A result of de-initializing an ADC16 instance.
 * @retval status_success De-initialize an ADC16 instance successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument De-initialize an ADC16 instance unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_deinit(ADC16_Type *ptr);

/**
 * @brief Initialize an ADC16 instance.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] config A pointer to the configuration struct of @ref adc16_config_t.
 * @return A result of initializing an ADC16 instance.
 * @retval status_success Initialize an ADC16 instance successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Initialize an ADC16 instance unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_init(ADC16_Type *ptr, adc16_config_t *config);

/**
 * @brief Initialize an ADC16 channel
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] config A pointer to the configuration struct of @ref adc16_channel_config_t.
 * @return A result of initializing an ADC16 channel.
 * @retval status_success Initialize an ADC16 channel successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Initialize an ADC16 channel unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_init_channel(ADC16_Type *ptr, adc16_channel_config_t *config);

/**
 * @brief Get thresholds of an ADC16 channel
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] ch An ADC16 channel number
 * @param[out] config A pointer to the structure of channel threshold
 * @return A result of getting thresholds of an ADC16 channel .
 * @retval status_success Initialize an ADC16 channel successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Initialize an ADC16 channel unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_get_channel_threshold(ADC16_Type *ptr, uint8_t ch, adc16_channel_threshold_t *config);

#if defined (ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT) && ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT
/**
 * @brief Enable oneshot mode (bus mode)
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
void adc16_enable_oneshot_mode(ADC16_Type *ptr);

/**
 * @brief Disable oneshot mode (bus mode)
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
void adc16_disable_oneshot_mode(ADC16_Type *ptr);
#endif

/**
 * @brief Configure the the period mode for an ADC16 instance.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] config A pointer to the configuration struct of @ref adc16_prd_config_t.
 * @return A result of configuring the the period mode for an ADC16 instance.
 * @retval status_success Configure the the period mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Configure the the period mode unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_set_prd_config(ADC16_Type *ptr, adc16_prd_config_t *config);

/**
 * @brief Configure the sequence mode for an ADC16 instance.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] config A pointer to configuration struct of @ref adc16_seq_config_t.
 * @return A result of configuring the sequence mode for an ADC16 instance.
 * @retval status_success Configure the sequence mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Configure the sequence mode unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_set_seq_config(ADC16_Type *ptr, adc16_seq_config_t *config);

/**
 * @brief Configure the preemption mode for an ADC16 instance.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] config A pointer to configuration struct of @ref adc16_pmt_config_t.
 * @return A result of configuring the preemption mode for an ADC16 instance.
 * @retval status_success Configure the preemption mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Configure the preemption mode unsuccessfully due to passing one or more invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_set_pmt_config(ADC16_Type *ptr, adc16_pmt_config_t *config);

/**
 * @brief Set the queue enable control.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] trig_ch An ADC16 peripheral trigger channel.
 * @param[in] enable Set true to enable and false to disable.
 * @return A result of setting queue enable in preemption.
 * @retval status_success Get the result of an ADC16 conversion in oneshot mode successfully.
 * @retval status_invalid_argument Get the result of an ADC16 conversion in oneshot mode unsuccessfully due to passing invalid arguments.
 */
hpm_stat_t adc16_set_pmt_queue_enable(ADC16_Type *ptr, uint8_t trig_ch, bool enable);

/** @} */

/**
 * @name Enablement Control
 * @{
 */
/**
 * @brief Enable the hw trigger control for the sequence mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 *
 */
static inline void adc16_seq_enable_hw_trigger(ADC16_Type *ptr)
{
    ptr->SEQ_CFG0 |= ADC16_SEQ_CFG0_HW_TRIG_EN_MASK;
}
/**
 * @brief Disable the hw trigger control for the sequence mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 *
 */
static inline void adc16_seq_disable_hw_trigger(ADC16_Type *ptr)
{
    ptr->SEQ_CFG0 &= ~ADC16_SEQ_CFG0_HW_TRIG_EN_MASK;
}
/** @} */

/**
 * @name DMA Control
 * @{
 */

/**
 * @brief Configure the stop position offset in the specified memory of DMA write operation for the sequence mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] stop_pos A stop position offset.
 */
static inline void adc16_set_seq_stop_pos(ADC16_Type *ptr, uint16_t stop_pos)
{
    ptr->SEQ_DMA_CFG = (ptr->SEQ_DMA_CFG & ~ADC16_SEQ_DMA_CFG_STOP_POS_MASK)
                     | ADC16_SEQ_DMA_CFG_STOP_POS_SET(stop_pos);
}

/**
 * @brief Configure the start address of DMA write operation for the preemption mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] addr A start address of DMA write operation.
 */
static inline void adc16_init_pmt_dma(ADC16_Type *ptr, uint32_t addr)
{
    ptr->TRG_DMA_ADDR = addr & ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK;
}

/**
 * @brief Configure the start address of DMA write operation for the sequence mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] config A pointer to configuration struct of @ref adc16_dma_config_t.
 * @return An implementation result of DMA initializing for the sequence mode
 * @retval status_success ADC16 initialize in sequence mode successfully. Please refert to @ref hpm_stat_t.
 * @retval status_invalid_argument ADC16 initialize in sequence mode unsuccessfully due to passing invalid arguments. Please refert to @ref hpm_stat_t.
 */
hpm_stat_t adc16_init_seq_dma(ADC16_Type *ptr, adc16_dma_config_t *config);

/** @} */

/**
 * @name Status
 * @{
 */

/**
 * @brief Get all ADC16 status flags.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @return A mask indicating all corresponding interrupt statuses.
 * @retval A mask. Please refer to @ref adc16_irq_event_t.
 */
static inline uint32_t adc16_get_status_flags(ADC16_Type *ptr)
{
    return ptr->INT_STS;
}

/**
 * @brief Set value of the WAIT_DIS bit. The ADC does not block access to the associated peripheral bus
 * until the ADC has completed its conversion.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @deprecated This API will be removed from V2.0.x
 */
static inline void adc16_disable_busywait(ADC16_Type *ptr)
{
    ptr->BUF_CFG0 |= ADC16_BUF_CFG0_WAIT_DIS_SET(1);
}

/**
 * @brief Set value of the WAIT_DIS bit. ADC blocks access to the associated peripheral bus
 * until the ADC completes the conversion.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @deprecated This API will be removed from V2.0.x
 */
static inline void adc16_enable_busywait(ADC16_Type *ptr)
{
    ptr->BUF_CFG0 &= ~ADC16_BUF_CFG0_WAIT_DIS_MASK;
}

/**
 * @brief Set nonblocking read in oneshot mode.
 * @note An ADC does not block access to the associated peripheral whether it completes a conversion or not.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
static inline void adc16_set_nonblocking_read(ADC16_Type *ptr)
{
    ptr->BUF_CFG0 |= ADC16_BUF_CFG0_WAIT_DIS_MASK;
}

/**
 * @brief Set blocking read in oneshot mode.
 * @note An ADC blocks access to the associated peripheral bus until it completes a conversion.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
static inline void adc16_set_blocking_read(ADC16_Type *ptr)
{
    ptr->BUF_CFG0 &= ~ADC16_BUF_CFG0_WAIT_DIS_MASK;
}

/**
 * @brief Judge whether the current setting is none-blocking mode or not.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @return A result indicating the status of bus waiting.
 * @retval True means that nonblocking reading.
 * @retval False means that blocking reading.
 *
 */
static inline bool adc16_is_nonblocking_mode(ADC16_Type *ptr)
{
    return (ADC16_BUF_CFG0_WAIT_DIS_GET(ptr->BUF_CFG0)  ? true : false);
}

/**
 * @brief Get the status of a conversion validity.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] ch An ADC16 peripheral channel.
 * @return Status indicating the validity of the current conversion result.
 *
 * @note This function is only used when the WAIT_DIS bit in the BUF_RESULT register is 1.
 */
static inline bool adc16_get_conv_valid_status(ADC16_Type *ptr, uint8_t ch)
{
    return ADC16_BUS_RESULT_VALID_GET(ptr->BUS_RESULT[ch]);
}

/**
 * @brief Clear the status flags.
 *
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] mask A mask that means the specified flags to be cleared. Please refer to @ref adc16_irq_event_t.
 *
 * @note Only the specified flags can be cleared by writing the INT_STS register.
 */
static inline void adc16_clear_status_flags(ADC16_Type *ptr, uint32_t mask)
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
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] mask A mask indicating the specified ADC interrupt events. Please refer to @ref adc16_irq_event_t.
 */
static inline void adc16_enable_interrupts(ADC16_Type *ptr, uint32_t mask)
{
    ptr->INT_EN |= mask;
}

/**
 * @brief Disable interrupts.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] mask A mask indicating the specified interrupt events. Please refer to @ref adc16_irq_event_t.
 */
static inline void adc16_disable_interrupts(ADC16_Type *ptr, uint32_t mask)
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
 * @param[in] ptr An ADC16 peripheral base address.
 * @return An implementation result of getting an ADC16 software trigger.
 * @retval status_success ADC16 software triggers successfully. Please refer to @ref hpm_stat_t.
 * @retval status_fail ADC16 software triggers unsuccessfully. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_trigger_seq_by_sw(ADC16_Type *ptr);

/**
 * @brief Trigger ADC conversions by software in preemption mode
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] trig_ch A trigger channel number(e.g. TRIG0A,TRIG0B,TRIG0C...).
 * @return An implementation result of getting an ADC16 software trigger.
 * @retval status_success ADC16 software triggers successfully. Please refer to @ref hpm_stat_t.
 * @retval status_fail ADC16 software triggers unsuccessfully. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_trigger_pmt_by_sw(ADC16_Type *ptr, uint8_t trig_ch);

/**
 * @brief Get the result in oneshot mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] ch An ADC16 peripheral channel.
 * @param[out] result A pointer to an ADC16 conversion result.
 * @return An implementation result of getting an ADC16 conversion result in oneshot mode.
 * @retval status_success Get the result of an ADC16 conversion in oneshot mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Get the result of an ADC16 conversion in oneshot mode unsuccessfully due to passing invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_get_oneshot_result(ADC16_Type *ptr, uint8_t ch, uint16_t *result);

/**
 * @brief Get the result in the period mode.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 * @param[in] ch An ADC16 peripheral channel.
 * @param[out] result A pointer to a specified ADC16 conversion result
 * @return An implementation of getting an ADC16 conversion result in the period mode.
 * @retval status_success Get the result of an ADC16 conversion in the period mode successfully. Please refer to @ref hpm_stat_t.
 * @retval status_invalid_argument Get the result of an ADC16 conversion in the period mode unsuccessfully due to passing invalid arguments. Please refer to @ref hpm_stat_t.
 */
hpm_stat_t adc16_get_prd_result(ADC16_Type *ptr, uint8_t ch, uint16_t *result);

#if defined(ADC16_SOC_TEMP_CH_EN) && ADC16_SOC_TEMP_CH_EN
/**
 * @brief Enable the temperature sensor
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
void adc16_enable_temp_sensor(ADC16_Type *ptr);

/**
 * @brief Disable the temperature sensor
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
void adc16_disable_temp_sensor(ADC16_Type *ptr);
#endif

/**
 * @brief enable the transmission of adc data to the motor sensor unit.
 *
 * @param[in] ptr An ADC16 peripheral base address.
 */
#if defined(HPM_IP_FEATURE_ADC16_HAS_MOT_EN) && HPM_IP_FEATURE_ADC16_HAS_MOT_EN
static inline void adc16_enable_motor(ADC16_Type *ptr)
{
    ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_MOTO_EN_MASK;
}
#endif

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* HPM_ADC16_DRV_H */
