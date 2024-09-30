/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SMIX_DRV_H
#define HPM_SMIX_DRV_H

#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_smix_regs.h"
#include <math.h>

/**
 * @brief SMIX driver APIs
 * @defgroup smix_interface SMIX driver APIs
 * @ingroup smix_interfaces
 * @{
 */

typedef enum {
    smix_dma_transfer_burst_1t = 0U,
    smix_dma_transfer_burst_2t = 1U,
    smix_dma_transfer_burst_4t = 2U,
    smix_dma_transfer_burst_8t = 3U,
    smix_dma_transfer_burst_16t = 4U,
    smix_dma_transfer_burst_32t = 5U,
    smix_dma_transfer_burst_64t = 6U,
    smix_dma_transfer_burst_128t = 7U,
} smix_dma_transfer_burst_t;

typedef enum {
    smix_dma_transfer_byte = 0U,
    smix_dma_transfer_half_word = 1U,
    smix_dma_transfer_word = 2U,
} smix_dma_transfer_width_t;

typedef enum {
    smix_dma_address_increment = 0U,
    smix_dma_address_decrement = 1U,
    smix_dma_address_fixed = 2U
} smix_dma_address_control_t;

typedef enum {
    smix_dma_mode_normal = 0,
    smix_dma_mode_handshake = 1,
} smix_dma_handshake_mode_t;

typedef enum {
    smix_dma_req_i2s0_rx = 6,
    smix_dma_req_i2s0_tx = 7,
    smix_dma_req_i2s1_rx = 8,
    smix_dma_req_i2s1_tx = 9,
    smix_dma_req_i2s2_rx = 10,
    smix_dma_req_i2s2_tx = 11,
    smix_dma_req_i2s3_rx = 12,
    smix_dma_req_i2s3_tx = 13,

    smix_dma_req_mixer_src_ch0 = 16,
    smix_dma_req_mixer_src_ch1 = 17,
    smix_dma_req_mixer_src_ch2 = 18,
    smix_dma_req_mixer_src_ch3 = 19,
    smix_dma_req_mixer_src_ch4 = 20,
    smix_dma_req_mixer_src_ch5 = 21,
    smix_dma_req_mixer_src_ch6 = 22,
    smix_dma_req_mixer_src_ch7 = 23,
    smix_dma_req_mixer_src_ch8 = 24,
    smix_dma_req_mixer_src_ch9 = 25,
    smix_dma_req_mixer_src_ch10 = 26,
    smix_dma_req_mixer_src_ch11 = 27,
    smix_dma_req_mixer_src_ch12 = 28,
    smix_dma_req_mixer_src_ch13 = 29,

    smix_dma_req_mixer_dst_ch0 = 30,
    smix_dma_req_mixer_dst_ch1 = 31,
} smix_dma_req_t;


typedef enum {
    smix_src_clk_i2s0_bclk = 0,
    smix_src_clk_i2s0_fclk = 1,
    smix_src_clk_i2s0_mclk = 2,
    smix_src_clk_i2s1_bclk = 3,
    smix_src_clk_i2s1_fclk = 4,
    smix_src_clk_i2s1_mclk = 5,
    smix_src_clk_i2s2_bclk = 6,
    smix_src_clk_i2s2_fclk = 7,
    smix_src_clk_i2s2_mclk = 8,
    smix_src_clk_i2s3_bclk = 9,
    smix_src_clk_i2s3_fclk = 10,
    smix_src_clk_i2s3_mclk = 11,
    smix_src_clk_none      = 15,
} smix_src_clk_source_t;


typedef struct {
    uint32_t ctrl;              /**< Control */
    uint32_t trans_size;        /**< Transfer size in source width */
    uint32_t src_addr;          /**< Source address */
    uint32_t reserved0;         /**< reserved */
    uint32_t dst_addr;          /**< Destination address */
    uint32_t reserved1;         /**< reserved */
    uint32_t linked_ptr;        /**< Linked descriptor address */
    uint32_t reserved2;         /**< resetved */
} smix_dma_linked_descriptor_t;


typedef struct {
    uint8_t priority;               /**< Channel priority */
    uint8_t src_burst_size;         /**< Source burst size */
    uint8_t src_req_sel;
    uint8_t dst_req_sel;
    uint8_t src_mode;               /**< Source work mode */
    uint8_t dst_mode;               /**< Destination work mode */
    uint8_t src_width;              /**< Source width */
    uint8_t dst_width;              /**< Destination width */
    uint8_t src_addr_ctrl;          /**< Source address control */
    uint8_t dst_addr_ctrl;          /**< Destination address control */
    bool abort_int_en;              /**< enable abort interrupt */
    bool error_int_en;              /**< enable error interrupt */
    bool complete_int_en;           /**< enable complete interrupt */
    uint32_t src_addr;              /**< Source address */
    uint32_t dst_addr;              /**< Destination address */
    uint32_t linked_ptr;            /**< Next linked descriptor */
    uint32_t trans_bytes;           /**< Total size to be transferred in byte */
} smix_dma_ch_config_t;

/* gain bit[14:0] */
/* low 12 bits is fraction */
/* high 3 bits: 1 - right shift 2; 2 - right shift 4 */
typedef enum {
    smix_mixer_gain_decrease_20db = 0x199,
    smix_mixer_gain_decrease_19db = 0x1cb,
    smix_mixer_gain_decrease_18db = 0x203,
    smix_mixer_gain_decrease_17db = 0x242,
    smix_mixer_gain_decrease_16db = 0x289,
    smix_mixer_gain_decrease_15db = 0x2d8,
    smix_mixer_gain_decrease_14db = 0x331,
    smix_mixer_gain_decrease_13db = 0x395,
    smix_mixer_gain_decrease_12db = 0x404,
    smix_mixer_gain_decrease_11db = 0x482,
    smix_mixer_gain_decrease_10db = 0x50f,
    smix_mixer_gain_decrease_9db = 0x5ad,
    smix_mixer_gain_decrease_8db = 0x65e,
    smix_mixer_gain_decrease_7db = 0x725,
    smix_mixer_gain_decrease_6db = 0x804,
    smix_mixer_gain_decrease_5db = 0x8ff,
    smix_mixer_gain_decrease_4db = 0xa18,
    smix_mixer_gain_decrease_3db = 0xb53,
    smix_mixer_gain_decrease_2db = 0xcb5,
    smix_mixer_gain_decrease_1db = 0xe42,
    smix_mixer_gain_0db = 0xfff,
    smix_mixer_gain_increase_1db = 0x147c,
    smix_mixer_gain_increase_2db = 0x1509,
    smix_mixer_gain_increase_3db = 0x15a6,
    smix_mixer_gain_increase_4db = 0x1657,
    smix_mixer_gain_increase_5db = 0x171c,
    smix_mixer_gain_increase_6db = 0x17fa,
    smix_mixer_gain_increase_7db = 0x18f4,
    smix_mixer_gain_increase_8db = 0x1a0c,
    smix_mixer_gain_increase_9db = 0x1b45,
    smix_mixer_gain_increase_10db = 0x1ca5,
    smix_mixer_gain_increase_11db = 0x1e31,
    smix_mixer_gain_increase_12db = 0x1fed,
    smix_mixer_gain_increase_13db = 0x2477,
    smix_mixer_gain_increase_14db = 0x2503,
    smix_mixer_gain_increase_15db = 0x259f,
    smix_mixer_gain_increase_16db = 0x264f,
    smix_mixer_gain_increase_17db = 0x2714,
    smix_mixer_gain_increase_18db = 0x27f1,
    smix_mixer_gain_increase_19db = 0x28e9,
    smix_mixer_gain_increase_20db = 0x2a00
} smix_mixer_gain_t;


typedef enum {
    smix_mixer_no_rate_convert,
    smix_mixer_upper_2x_sample,
    smix_mixer_upper_3x_sample,
    smix_mixer_upper_4x_sample,
    smix_mixer_upper_6x_sample,
    smix_mixer_upper_8x_sample,
    smix_mixer_upper_12x_sample,
    smix_mixer_lower_2x_sample,
} smix_mixer_rate_convert_t;

typedef struct {
    bool underflow_int_en;
    uint8_t fifo_thr;
    bool calsat_int_en;
    bool da_int_en;
    bool auto_deactivate_en;
    bool fadeout_done_int_en;
    bool deactivate_en;
    bool active_en;
    bool fadeout_now_en;
    bool fadeout_auto_en;
    bool fadein_en;
    bool channel_en;
    bool mixer_en;

    uint16_t gain;
    uint32_t length;
    uint32_t fadein_delta;
    uint32_t fadeout_delta;
    uint8_t src_ch_mask;
} smix_mixer_dst_config_t;


typedef struct {
    uint8_t fifo_thr;
    bool calsat_int_en;
    bool dn_int_en;
    bool auto_deactivate_en;
    bool fadeout_int_en;
    uint8_t convert_rate;

    uint16_t gain;
    uint32_t fadein_delta;
    uint32_t fadeout_delta;
    uint32_t length;
} smix_mixer_source_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief smix dma check transfer complete status
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch_index dma channel
 * @retval true for transfer complete
 */
static inline bool smix_dma_check_transfer_complete(SMIX_Type *ptr, uint8_t ch_index)
{
    if ((SMIX_DMAC_TC_ST_CH_GET(ptr->DMAC_TC_ST) & (1U << ch_index)) != 0) {
        ptr->DMAC_TC_ST = (1U << ch_index); /* W1C clear status*/
        return true;
    }
    return false;
}

/**
 * @brief smix dma check transfer abort status
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch_index dma channel
 * @retval true for transfer abort
 */
static inline bool smix_dma_check_transfer_abort(SMIX_Type *ptr, uint8_t ch_index)
{
    if ((SMIX_DMAC_ABRT_ST_CH_GET(ptr->DMAC_ABRT_ST) & (1U << ch_index)) != 0) {
        ptr->DMAC_ABRT_ST = (1U << ch_index); /* W1C clear status*/
        return true;
    }
    return false;
}

/**
 * @brief smix dma check transfer error status
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch_index dma channel
 * @retval true for transfer error
 */
static inline bool smix_dma_check_transfer_error(SMIX_Type *ptr, uint8_t ch_index)
{
    if ((SMIX_DMAC_ERR_ST_CH_GET(ptr->DMAC_ERR_ST) & (1U << ch_index)) != 0) {
        ptr->DMAC_ERR_ST = (1U << ch_index); /* W1C clear status*/
        return true;
    }
    return false;
}

/**
 * @brief smix mixer enable source channel for dst
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @param [in] source_ch_mask source channel mask
 */
static inline void smix_mixer_dst_enable_source_channel(SMIX_Type *ptr, uint8_t dst_ch, uint32_t source_ch_mask)
{
    ptr->DST_CH[dst_ch].SOURCE_EN |= source_ch_mask;
}

/**
 * @brief smix mixer disable source channel for dst
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @param [in] source_ch_mask source channel mask
 */
static inline void smix_mixer_dst_disable_source_channel(SMIX_Type *ptr, uint8_t dst_ch, uint32_t source_ch_mask)
{
    ptr->DST_CH[dst_ch].SOURCE_EN &= ~source_ch_mask;
}

/**
 * @brief smix mixer active source channel for dst
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @param [in] source_ch_mask source channel mask
 */
static inline void smix_mixer_dst_active_source_channel(SMIX_Type *ptr, uint8_t dst_ch, uint32_t source_ch_mask)
{
    ptr->DST_CH[dst_ch].SOURCE_ACT |= source_ch_mask;
}

/**
 * @brief smix mixer deactive source channel for dst
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @param [in] source_ch_mask source channel mask
 */
static inline void smix_mixer_dst_deactive_source_channel(SMIX_Type *ptr, uint8_t dst_ch, uint32_t source_ch_mask)
{
    ptr->DST_CH[dst_ch].SOURCE_DEACT |= source_ch_mask;
}

/**
 * @brief smix mixer fadein source channel for dst
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @param [in] source_ch_mask source channel mask
 */
static inline void smix_mixer_dst_fadein_source_channel(SMIX_Type *ptr, uint8_t dst_ch, uint32_t source_ch_mask)
{
    ptr->DST_CH[dst_ch].SOURCE_FADEIN_CTRL |= source_ch_mask;
}

/**
 * @brief smix mixer fadeout source channel for dst
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @param [in] source_ch_mask source channel mask
 */
static inline void smix_mixer_dst_fadeout_source_channel(SMIX_Type *ptr, uint8_t dst_ch, uint32_t source_ch_mask)
{
    ptr->DST_CH[dst_ch].SOURCE_MFADEOUT_CTRL |= source_ch_mask;
}

/**
 * @brief smix mixer enable dst channel
 *
 * @param [in] ptr SMIX base address
 *
 * @note two dst channel share same enable bit in DST_CH[0].CTRL.MIXER_EN, DST_CH[1].CTRL.MIXER_EN should not be set
 */
static inline void smix_mixer_dst_enable(SMIX_Type *ptr)
{
    ptr->DST_CH[0].CTRL |= SMIX_DST_CH_CTRL_DST_EN_MASK;
    ptr->DST_CH[1].CTRL &= ~SMIX_DST_CH_CTRL_DST_EN_MASK;
}

/**
 * @brief smix mixer disable dst channel
 *
 * @param [in] ptr SMIX base address
 *
 * @note two dst channel share same enable bit in DST_CH[0].CTRL.MIXER_EN, DST_CH[1].CTRL.MIXER_EN should not be set
 */
static inline void smix_mixer_dst_disable(SMIX_Type *ptr)
{
    ptr->DST_CH[0].CTRL &= ~SMIX_DST_CH_CTRL_DST_EN_MASK;
}

/**
 * @brief smix mixer get calculate saturation register value
 *
 * @param [in] ptr SMIX base address
 * @retval calculate saturation register value
 */
static inline uint32_t smix_mixer_get_calsat_status(SMIX_Type *ptr)
{
    return ptr->CALSAT_ST;
}

/**
 * @brief smix mixer check dst channel calculate saturation error
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @retval true for calculate saturation error occurred
 */
static inline bool smix_mixer_check_dst_cal_saturation_error(SMIX_Type *ptr, uint8_t dst_ch)
{
    return ((SMIX_CALSAT_ST_DST_GET(ptr->CALSAT_ST) & (1U << dst_ch)) != 0) ? true : false;
}

/**
 * @brief smix mixer check source channel calculate saturation error
 *
 * @param [in] ptr SMIX base address
 * @param [in] source_ch source channel
 * @retval true for calculate saturation error occurred
 */
static inline bool smix_mixer_check_source_cal_saturation_error(SMIX_Type *ptr, uint8_t source_ch)
{
    return ((SMIX_CALSAT_ST_SRC_GET(ptr->CALSAT_ST) & (1U << source_ch)) != 0) ? true : false;
}

/**
 * @brief smix mixer check dst channel data ubderflew
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @retval true for data underflew
 */
static inline bool smix_mixer_check_dst_data_underflew(SMIX_Type *ptr, uint8_t dst_ch)
{
    return ((SMIX_DATA_ST_DST_UNDL_GET(ptr->DATA_ST) & (1U << dst_ch)) != 0) ? true : false;
}

/**
 * @brief smix mixer check dst channel data available
 *
 * @param [in] ptr SMIX base address
 * @param [in] dst_ch dst channel
 * @retval true for data available
 */
static inline bool smix_mixer_check_dst_data_available(SMIX_Type *ptr, uint8_t dst_ch)
{
    return ((SMIX_DATA_ST_DST_DA_GET(ptr->DATA_ST) & (1U << dst_ch)) != 0) ? true : false;
}

/**
 * @brief smix mixer check source channel data available
 *
 * @param [in] ptr SMIX base address
 * @param [in] source_ch source channel
 * @retval true for source channel need new data
 */
static inline bool smix_mixer_check_source_data_needed(SMIX_Type *ptr, uint8_t source_ch)
{
    return ((SMIX_DATA_ST_SRC_DN_GET(ptr->DATA_ST) & (1U << source_ch)) != 0) ? true : false;
}

/**
 * @brief smix mixer config dst channel fadein delta
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch dst channel
 * @param [in] target_sample_rate target sample rate
 * @param [in] ms fadein consumed time in ms
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_mixer_config_dst_fadein_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms);

/**
 * @brief smix mixer config dst channel fadeout delta
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch dst channel
 * @param [in] target_sample_rate target sample rate
 * @param [in] ms fadeout consumed time in ms
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_mixer_config_dst_fadeout_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms);

/**
 * @brief smix mixer config source channel fadein delta
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch source channel
 * @param [in] target_sample_rate target sample rate
 * @param [in] ms fadein consumed time in ms
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_mixer_config_source_fadein_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms);

/**
 * @brief smix mixer config source channel fadeout delta
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch source channel
 * @param [in] target_sample_rate target sample rate
 * @param [in] ms fadeout consumed time in ms
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_mixer_config_source_fadeout_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms);

/**
 * @brief smix get dma channel default config
 *
 * @param [in] ptr SMIX base address
 * @param [in] config smix_dma_ch_config_t
 */
void smix_get_dma_default_ch_config(SMIX_Type *ptr, smix_dma_ch_config_t *config);

/**
 * @brief smix get dst channel default config
 *
 * @param [in] ptr SMIX base address
 * @param [in] config smix_mixer_dst_config_t
 */
void smix_get_mixer_dst_ch_default_config(SMIX_Type *ptr, smix_mixer_dst_config_t *config);

/**
 * @brief smix get source channel default config
 *
 * @param [in] ptr SMIX base address
 * @param [in] config smix_mixer_source_config_t
 */
void smix_get_mixer_source_ch_default_config(SMIX_Type *ptr, smix_mixer_source_config_t *config);

/**
 * @brief smix config dma channel
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch dma channel
 * @param [in] config smix_dma_ch_config_t
 * @param [in] start true for start dma
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_config_dma_channel(SMIX_Type *ptr, uint8_t ch, smix_dma_ch_config_t *config, bool start);

/**
 * @brief smix mixer config source channel
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch source channel
 * @param [in] src smix_mixer_source_config_t
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_mixer_config_source_ch(SMIX_Type *ptr, uint8_t ch, smix_mixer_source_config_t *src);

/**
 * @brief smix mixer config dst channel
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch dst channel
 * @param [in] dst smix_mixer_dst_config_t
 * @retval status_success if no error occurs
 */
hpm_stat_t smix_mixer_config_dst_ch(SMIX_Type *ptr, uint8_t ch, smix_mixer_dst_config_t *dst);

/**
 * @brief smix mixer config source channel gain
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch_index source channel
 * @param [in] gain smix_mixer_gain_t
 */
static inline void smix_set_source_gain(SMIX_Type *ptr, uint8_t ch_index, smix_mixer_gain_t gain)
{
    ptr->SOURCE_CH[ch_index].GAIN = SMIX_SOURCE_CH_GAIN_VAL_SET(gain);
}

/**
 * @brief smix mixer config dst channel gain
 *
 * @param [in] ptr SMIX base address
 * @param [in] ch_index dst channel
 * @param [in] gain smix_mixer_gain_t
 */
static inline void smix_set_dst_gain(SMIX_Type *ptr, uint8_t ch_index, smix_mixer_gain_t gain)
{
    ptr->DST_CH[ch_index].GAIN = SMIX_DST_CH_GAIN_VAL_SET(gain);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_SMIX_DRV_H */
