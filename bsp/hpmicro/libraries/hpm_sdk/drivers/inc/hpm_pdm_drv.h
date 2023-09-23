/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PDM_DRV_H
#define HPM_PDM_DRV_H

#include "hpm_common.h"
#include "hpm_pdm_regs.h"

/**
 * @brief PDM driver APIs
 * @defgroup pdm_interface PDM driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief PDM event
 */
#define PDM_EVENT_FILT_CRX_ERROR (PDM_ST_FILT_CRX_ERR_MASK)
#define PDM_EVENT_OFIFO_OVERFLOW_ERROR (PDM_ST_OFIFO_OVFL_ERR_MASK)
#define PDM_EVENT_CIC_OVERLOAD_ERROR (PDM_ST_CIC_OVLD_ERR_MASK)
#define PDM_EVENT_CIC_SAT_ERROR (PDM_ST_CIC_SAT_ERR_MASK)

/**
 * @brief PDM CIC sidma-delta filter order
 */
#define PDM_CIC_SIGMA_DELTA_ORDER_5 (2U)
#define PDM_CIC_SIGMA_DELTA_ORDER_6 (1U)
#define PDM_CIC_SIGMA_DELTA_ORDER_7 (0U)

/**
 * @brief PDM config
 */
typedef struct pdm_config {
    bool sof_at_ref_clk_falling_edge;
    bool bypass_pdm_clk_div;
    bool enable_pdm_clk_out;
    bool enable_hpf;
    uint8_t pdm_clk_div;
    uint8_t capture_delay;
    uint8_t dec_after_cic;
    uint8_t post_scale;
    uint8_t sigma_delta_order;
    uint8_t cic_dec_ratio;
} pdm_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief config high pass filter
 *
 * @param [in] ptr PDM base address
 * @param [in] hpf_coef_ma high pass filter a coefficient's complement
 * @param [in] hpf_coef_b high pass filter b coefficient
 */
static inline void pdm_config_hpf(PDM_Type *ptr,
                                     uint32_t hpf_coef_ma,
                                     uint32_t hpf_coef_b)
{
    ptr->HPF_MA = PDM_HPF_MA_COEF_SET(hpf_coef_ma);
    ptr->HPF_B = PDM_HPF_B_COEF_SET(hpf_coef_b);
}

/**
 * @brief enable high pass filter
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_enable_hpf(PDM_Type *ptr)
{
    ptr->CTRL |= PDM_CTRL_HPF_EN_MASK;
}

/**
 * @brief disable high pass filter
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_disable_hpf(PDM_Type *ptr)
{
    ptr->CTRL &= ~PDM_CTRL_HPF_EN_MASK;
}

/**
 * @brief check whether PDM is running
 *
 * @param [in] ptr PDM base address
 * @retval true in PDM is running
 */
static inline bool pdm_is_running(PDM_Type *ptr)
{
    return ptr->RUN & PDM_RUN_PDM_EN_MASK;
}

/**
 * @brief stop pdm
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_stop(PDM_Type *ptr)
{
    ptr->RUN &= ~PDM_RUN_PDM_EN_MASK;
}

/**
 * @brief start pdm
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_start(PDM_Type *ptr)
{
    ptr->RUN |= PDM_RUN_PDM_EN_MASK;
}

/**
 * @brief disable channel
 *
 * @param [in] ptr PDM base address
 * @param [in] channel_disable_mask channel mask
 */
static inline void pdm_disable_channel(PDM_Type *ptr,
                                         uint16_t channel_disable_mask)
{
    ptr->CH_CTRL &= ~PDM_CH_CTRL_CH_EN_SET(channel_disable_mask);
}

/**
 * @brief enable channel
 *
 * @param [in] ptr PDM base address
 * @param [in] capture_high_level_mask capture when PDM_CLK is high
 * @param [in] channel_enable_mask channel mask
 */
static inline void pdm_enable_channel(PDM_Type *ptr,
                                         uint16_t capture_high_level_mask,
                                         uint16_t channel_enable_mask)
{
    ptr->CH_CTRL |= PDM_CH_CTRL_CH_POL_SET(capture_high_level_mask)
        | PDM_CH_CTRL_CH_EN_SET(channel_enable_mask);
}

/**
 * @brief disable pdm clock out
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_disable_pdm_clock_out(PDM_Type *ptr)
{
    ptr->CTRL &= ~PDM_CTRL_PDM_CLK_OE_MASK;
}

/**
 * @brief enable pdm clock out
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_enable_pdm_clock_out(PDM_Type *ptr)
{
    ptr->CTRL |= PDM_CTRL_PDM_CLK_OE_MASK;
}

/**
 * @brief pdm config cic
 *
 * @param [in] ptr PDM base address
 * @param [in] sigma_delta_order sidma-delta filter order
 * @param [in] div Rate of down sampling
 * @param [in] post_scale output value post scale
 */
static inline void pdm_config_cic(PDM_Type *ptr,
                                     uint8_t sigma_delta_order,
                                     uint8_t div,
                                     uint8_t post_scale)
{
    ptr->CIC_CFG = PDM_CIC_CFG_POST_SCALE_SET(post_scale)
        | PDM_CIC_CFG_SGD_SET(sigma_delta_order)
        | PDM_CIC_CFG_CIC_DEC_RATIO_SET(div);
}

/**
 * @brief pdm software reset
 *
 * @param [in] ptr PDM base address
 */
static inline void pdm_software_reset(PDM_Type *ptr)
{
    ptr->CTRL |= PDM_CTRL_SFTRST_MASK;
    ptr->CTRL &= ~PDM_CTRL_SFTRST_MASK;
}

/**
 * @brief pdm enable irq
 *
 * @param [in] ptr PDM base address
 * @param [in] mask pdm irq mask in ST register
 */
static inline void pdm_enable_irq(PDM_Type *ptr, uint8_t mask)
{
    ptr->CTRL |= mask << (PDM_CTRL_CIC_SAT_ERR_IE_SHIFT - PDM_ST_CIC_SAT_ERR_SHIFT);
}

/**
 * @brief pdm disable irq
 *
 * @param [in] ptr PDM base address
 * @param [in] mask pdm irq mask in ST register
 */
static inline void pdm_disable_irq(PDM_Type *ptr, uint8_t mask)
{
    ptr->CTRL &= ~(mask << (PDM_CTRL_CIC_SAT_ERR_IE_SHIFT - PDM_ST_CIC_SAT_ERR_SHIFT));
}

/**
 * @brief pdm initialization
 *
 * @param [in] ptr PDM base address
 * @param [in] config pdm_config_t
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t pdm_init(PDM_Type *ptr, pdm_config_t *config);

/**
 * @brief pdm get default config
 *
 * @param [in] ptr PDM base address
 * @param [out] config pdm_config_t
 */
void pdm_get_default_config(PDM_Type *ptr, pdm_config_t *config);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_PDM_DRV_H */

