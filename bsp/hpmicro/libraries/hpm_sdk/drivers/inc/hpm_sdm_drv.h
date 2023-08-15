/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDM_DRV_H
#define HPM_SDM_DRV_H

#include "hpm_common.h"
#include "hpm_sdm_regs.h"

/* defined channel mask macro */
#define SAMPLING_MODE_MASK (0x7U)
#define CHN_SAMPLING_MODE_SHIFT(ch) ((ch) * 3U + SDM_CTRL_CHMD_SHIFT)
#define CHN_SAMPLING_MODE_MASK(ch) (SAMPLING_MODE_MASK << CHN_SAMPLING_MODE_SHIFT(ch))

#define CH0_EN_MASK (0x1U << SDM_CTRL_CH_EN_SHIFT)
#define CHN_EN_MASK(ch) (CH0_EN_MASK << (ch))

#define CHN_ERR_MASK(ch) (SDM_INT_EN_CH0ERR_MASK << (ch))
#define CHN_DRY_MASK(ch) (SDM_INT_EN_CH0DRY_MASK << (ch))

typedef enum {
   sdm_sampling_rising_clk_edge = 0,
   sdm_sampling_every_clk_edge = 1,
   sdm_sampling_manchester_mode = 2,
   sdm_sampling_falling_clk_edge = 3,
   sdm_sampling_rising_two_clk_edge = 4,
   sdm_sampling_falling_two_clk_edge = 5
} sdm_sampling_mode_t;

typedef enum {
    sdm_filter_sinc1 = 0,
    sdm_filter_sinc2 = 1,
    sdm_filter_sinc3 = 2,
    sdm_filter_fast_sinc2 = 3
} sdm_filter_type_t;

typedef struct {
    bool clk_signal_sync;
    bool data_signal_sync;
    bool interrupt_en;
} sdm_control_t;

typedef struct {
    uint8_t sampling_mode;
    bool enable_err_interrupt;
    bool enable_data_ready_interrupt;
} sdm_channel_common_config_t;

typedef struct {
    uint16_t high_threshold;
    uint16_t zero_cross_threshold;
    uint16_t low_threshold;

    bool en_zero_cross_threshold_int;
    bool en_clock_invalid_int;
    bool en_high_threshold_int;
    bool en_low_threshold_int;
    uint8_t filter_type;                 /**< sdm_filter_type_t */
    uint8_t oversampling_rate;           /**< 1 - 32 */
    uint8_t ignore_invalid_samples;
    bool enable;
} sdm_comparator_config_t;

typedef struct {
    uint8_t fifo_threshold;
    bool en_fifo_threshold_int;
    uint8_t manchester_threshold  :8;
    uint8_t wdg_threshold         :8;
    uint8_t en_af_int             :1;
    uint8_t en_data_overflow_int  :1;
    uint8_t en_cic_data_saturation_int  :1;
    uint8_t en_data_ready_int           :1;
    uint8_t sync_source                 :6;
    uint8_t fifo_clean_on_sync          :1; /**< fifo clean by hardware when fifo interrupt occurred */
    uint8_t wtsynaclr                   :1;
    uint8_t wtsynmclr                   :1;
    uint8_t wtsyncen                    :1;
    uint8_t output_32bit                :1;
    uint8_t data_ready_flag_by_fifo     :1;
    uint8_t enable                      :1;

    uint8_t filter_type;                 /**< sdm_filter_type_t */
    bool pwm_signal_sync;
    uint8_t output_offset;               /**< 16bit mode need configure this */
    uint16_t oversampling_rate;          /**< 1-256 */
    uint8_t ignore_invalid_samples;
} sdm_filter_config_t;

typedef struct {
    uint32_t count;
    uint8_t *buff;
    uint8_t data_len_in_bytes; /* 16bit-2   32bit-4 */
    bool using_fifo;
} sdm_output_config_t;

typedef enum {
    sdm_comparator_no_event = 0,
    sdm_comparator_event_out_high_threshold = SDM_CH_SCST_CMPH_MASK,
    sdm_comparator_event_out_low_threshold = SDM_CH_SCST_CMPL_MASK,
    sdm_comparator_event_hz = SDM_CH_SCST_HZ_MASK,
    sdm_comparator_event_invalid_clk = SDM_CH_SCST_MF_MASK
} sdm_comparator_event_t;

typedef enum {
    sdm_chn0_error_mask = SDM_INT_EN_CH0ERR_MASK,
    sdm_chn1_error_mask = SDM_INT_EN_CH1ERR_MASK,
    sdm_chn2_error_mask = SDM_INT_EN_CH2ERR_MASK,
    sdm_chn3_error_mask = SDM_INT_EN_CH3ERR_MASK,
    sdm_chn0_data_ready_mask = SDM_INT_EN_CH0DRY_MASK,
    sdm_chn1_data_ready_mask = SDM_INT_EN_CH1DRY_MASK,
    sdm_chn2_data_ready_mask = SDM_INT_EN_CH2DRY_MASK,
    sdm_chn3_data_ready_mask = SDM_INT_EN_CH3DRY_MASK
} sdm_channel_int_status_mask_t;

typedef enum {
    sdm_chn0_enable_mask = 1U << SDM_CTRL_CH_EN_SHIFT,
    sdm_chn1_enable_mask = 1U << (SDM_CTRL_CH_EN_SHIFT + 1U),
    sdm_chn2_enable_mask = 1U << (SDM_CTRL_CH_EN_SHIFT + 2U),
    sdm_chn3_enable_mask = 1U << (SDM_CTRL_CH_EN_SHIFT + 3U)
} sdm_channel_enable_mask_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief sdm enable module interrupt
 *
 * @param ptr SDM base address
 * @param enable true for enable, false for disable
 */
static inline void sdm_enable_module_interrupt(SDM_Type *ptr, bool enable)
{
    if (enable) {
        ptr->CTRL |= SDM_CTRL_IE_MASK;
    } else {
        ptr->CTRL &= ~SDM_CTRL_IE_MASK;
    }
}

/**
 * @brief sdm enable channel
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param enable true for enable, false for disable
 */
static inline void sdm_enable_channel(SDM_Type *ptr, uint8_t ch_index, bool enable)
{
    if (enable) {
        ptr->CTRL |= CHN_EN_MASK(ch_index);
    } else {
        ptr->CTRL &= ~CHN_EN_MASK(ch_index);
    }
}

/**
 * @brief sdm enable channel by mask
 *
 * @note ch_mask supports bitwise or operation, this API could enable multiple channels at the same time
 *
 * @param ptr SDM base address
 * @param ch_mask sdm_channel_enable_mask_t
 */
static inline void sdm_enable_channel_by_mask(SDM_Type *ptr, uint32_t ch_mask)
{
    ptr->CTRL = (ptr->CTRL & (~SDM_CTRL_CH_EN_MASK)) | ch_mask;
}

/**
 * @brief sdm set channel sampling mode
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param mode sdm_sampling_mode_t
 */
static inline void sdm_set_channel_sampling_mode(SDM_Type *ptr, uint8_t ch_index, sdm_sampling_mode_t mode)
{
    ptr->CTRL &= ~CHN_SAMPLING_MODE_MASK(ch_index);
    ptr->CTRL |= mode << (SDM_CTRL_CHMD_SHIFT + ch_index);
}

/**
 * @brief sdm enable channel interrupt
 *
 * @param ptr SDM base address
 * @param mask sdm_channel_int_status_mask_t, support bitwise or operation
 */
static inline void sdm_enable_channel_interrupt(SDM_Type *ptr, uint32_t mask)
{
    ptr->INT_EN |= mask;
}

/**
 * @brief sdm get status register value
 *
 * @param ptr SDM base address
 * @return uint32_t sdm status register value
 */
static inline uint32_t sdm_get_status(SDM_Type *ptr)
{
    return ptr->STATUS;
}

/**
 * @brief get channel data ready status
 *
 * @param ptr SDM base address
 * @param ch channel
 * @return true data ready
 * @return false not ready
 */
static inline bool sdm_get_channel_data_ready_status(SDM_Type *ptr, uint8_t ch)
{
    return (((ptr->STATUS) & CHN_DRY_MASK(ch)) == CHN_DRY_MASK(ch));
}

/**
 * @brief get channel error status
 *
 * @param ptr SDM base address
 * @param ch channel
 * @return true error occur
 * @return false no error
 */
static inline bool sdm_get_channel_data_error_status(SDM_Type *ptr, uint8_t ch)
{
    return (((ptr->STATUS) & CHN_ERR_MASK(ch)) == CHN_ERR_MASK(ch));
}

/**
 * @brief sdm set channel's fifo threshold
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @param threshold threshold value
 */
static inline void sdm_set_ch_fifo_threshold(SDM_Type *ptr, uint8_t ch, uint8_t threshold)
{
    ptr->CH[ch].SDFIFOCTRL = SDM_CH_SDFIFOCTRL_THRSH_SET(threshold);
}

/**
 * @brief sdm get channel fifo threshold
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return uint8_t fifo threshold value
 */
static inline uint8_t sdm_get_ch_fifo_threshold(SDM_Type *ptr, uint8_t ch)
{
    return (uint8_t)(SDM_CH_SDFIFOCTRL_THRSH_GET(ptr->CH[ch].SDFIFOCTRL));
}

/**
 * @brief sdm get channel filter status
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return uint32_t channel filter status register value
 */
static inline uint32_t sdm_get_channel_filter_status(SDM_Type *ptr, uint8_t ch)
{
    return ptr->CH[ch].SDST;
}

/**
 * @brief sdm get channel data count in fifo
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return uint8_t data count
 */
static inline uint8_t sdm_get_channel_fifo_data_count(SDM_Type *ptr, uint8_t ch)
{
    return (uint8_t)(SDM_CH_SDST_FILL_GET(ptr->CH[ch].SDST));
}

/**
 * @brief sdm get channel filter output data in fifo
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return int32_t data
 */
static inline int32_t sdm_get_channel_fifo_data(SDM_Type *ptr, uint8_t ch)
{
    return ptr->CH[ch].SDFIFO;
}

/**
 * @brief sdm get channel input clock cycle count
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return uint8_t clock cycle count
 */
static inline uint8_t sdm_get_channel_clock_cycle_count(SDM_Type *ptr, uint8_t ch)
{
    return (uint8_t)(SDM_CH_SDST_PERIOD_MCLK_GET(ptr->CH[ch].SDST));
}

/**
 * @brief sdm get channel comparator data
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return uint16_t comparator data
 */
static inline uint16_t sdm_get_channel_comparator_data(SDM_Type *ptr, uint8_t ch)
{
    return (uint16_t)(ptr->CH[ch].SCAMP);
}

/**
 * @brief sdm set channel comparator high threshold
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @param value high threshold value
 */
static inline void sdm_set_channel_comparator_high_threshold(SDM_Type *ptr, uint8_t ch, uint16_t value)
{
    ptr->CH[ch].SCHTL = value;
}

/**
 * @brief sdm set channel comparator zero crossing threshold
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @param value zero crossing threshold value
 */
static inline void sdm_set_channel_comparator_zero_crossing_threshold(SDM_Type *ptr, uint8_t ch, uint16_t value)
{
    ptr->CH[ch].SCHTLZ = value;
}

/**
 * @brief sdm set channel comparator low threshold
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @param value low threshold value
 */
static inline void sdm_set_channel_comparator_low_threshold(SDM_Type *ptr, uint8_t ch, uint16_t value)
{
    ptr->CH[ch].SCLLT = value;
}

/**
 * @brief sdm get channel comparator status register value
 *
 * @param ptr SDM base address
 * @param ch channel index
 * @return uint32_t channel comparator status register value
 */
static inline uint32_t sdm_get_channel_comparator_status(SDM_Type *ptr, uint8_t ch)
{
    return ptr->CH[ch].SCST;
}

/**
 * @brief sdm get default module control
 *
 * @param ptr SDM base address
 * @param control sdm_control_t
 */
void sdm_get_default_module_control(SDM_Type *ptr, sdm_control_t *control);

/**
 * @brief sdm init module
 *
 * @param ptr SDM base address
 * @param control sdm_control_t
 */
void sdm_init_module(SDM_Type *ptr, sdm_control_t *control);

/**
 * @brief sdm get channel common setting
 *
 * @param ptr SDM base address
 * @param config sdm_channel_common_config_t
 */
void sdm_get_channel_common_setting(SDM_Type *ptr, sdm_channel_common_config_t *config);

/**
 * @brief sdm config channel's common setting
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param config sdm_channel_common_config_t
 */
void sdm_config_channel_common_setting(SDM_Type *ptr, uint8_t ch_index, sdm_channel_common_config_t *config);

/**
 * @brief sdm get channel default filter config
 *
 * @param ptr SDM base address
 * @param filter_config sdm_filter_config_t
 */
void sdm_get_channel_default_filter_config(SDM_Type *ptr, sdm_filter_config_t *filter_config);

/**
 * @brief sdm config channel filter
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param filter_config sdm_filter_config_t
 */
void sdm_config_channel_filter(SDM_Type *ptr, uint8_t ch_index, sdm_filter_config_t *filter_config);

/**
 * @brief sdm get channel default comparator config
 *
 * @param ptr SDM base address
 * @param cmp_config sdm_comparator_config_t
 */
void sdm_get_channel_default_comparator_config(SDM_Type *ptr, sdm_comparator_config_t *cmp_config);

/**
 * @brief sdm config channel comparator
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param cmp_config sdm_comparator_config_t
 */
void sdm_config_channel_comparator(SDM_Type *ptr,  uint8_t ch_index, sdm_comparator_config_t *cmp_config);

/**
 * @brief sdm receive one filter data
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param using_fifo true for getting data from fifo, false for getting data from register
 * @param data data buff
 * @param data_len_in_bytes output data len in bytes
 * @retval hpm_stat_t status_success only if it succeeds
 */
hpm_stat_t sdm_receive_one_filter_data(SDM_Type *ptr, uint8_t ch_index, bool using_fifo, int8_t *data, uint8_t data_len_in_bytes);

/**
 * @brief sdm receive filter data
 *
 * @param ptr SDM base address
 * @param ch_index channel index
 * @param using_fifo true for getting data from fifo, false for getting data from register
 * @param data data buff
 * @param count data count
 * @param data_len_in_bytes output data len in bytes
 * @retval hpm_stat_t status_success only if it succeeds
 */
hpm_stat_t sdm_receive_filter_data(SDM_Type *ptr, uint8_t ch_index, bool using_fifo, int8_t *data, uint32_t count, uint8_t data_len_in_bytes);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_SDM_DRV_H */

