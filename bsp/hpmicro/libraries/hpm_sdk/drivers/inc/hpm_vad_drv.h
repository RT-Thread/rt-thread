/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_VAD_DRV_H
#define HPM_VAD_DRV_H

#include "hpm_common.h"
#include "hpm_vad_regs.h"

/**
 * @brief VAD driver APIs
 * @defgroup vad_interface VAD driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief vad event
 */
#define VAD_EVENT_VAD                   (1U << 7)
#define VAD_EVENT_FIFO_DATA_AVAILABLE   (1U << 6)
#define VAD_EVENT_MEMBUF_EMPTY          (1U << 5)
#define VAD_EVENT_FIFO_OVERFLOW         (1U << 4)
#define VAD_EVENT_IIR_OVERLOAD          (1U << 3)
#define VAD_EVENT_IIR_OVERFLOW          (1U << 2)
#define VAD_EVENT_CIC_OVERLOAD_ERROR    (1U << 1)
#define VAD_EVENT_CIC_STA_ERROR         (1U << 0)

/**
 * @brief vad config
 */
typedef struct vad_config {
    bool enable_buffer;
    bool enable_pdm_clock_out;
    bool enable_two_channels;
    uint8_t capture_delay;
    uint8_t pdm_half_div;
    uint8_t fifo_threshold;
    uint8_t post_scale;
    bool channel_polarity_high[2];
} vad_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief set capture deplay cycle
 *
 * @param [in] ptr VAD base address
 * @param [in] delay delay cycle value
 */
static inline void vad_set_capture_delay(VAD_Type *ptr, uint8_t delay)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_CAPT_DLY_MASK)
        | VAD_CTRL_CAPT_DLY_SET(delay);
}

/**
 * @brief set pdm clock hald_divider
 *
 * @param [in] ptr VAD base address
 * @param [in] div divider value
 */
static inline void vad_set_pdm_clock_half_div(VAD_Type *ptr, uint8_t div)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_PDM_CLK_HFDIV_MASK)
        | VAD_CTRL_PDM_CLK_HFDIV_SET(div);
}

/**
 * @brief enable irq
 *
 * @param [in] ptr VAD base address
 * @param [in] irq_mask irq mask value
 */
static inline void vad_enable_irq(VAD_Type *ptr, uint32_t irq_mask)
{
    ptr->CTRL |= irq_mask;
}

/**
 * @brief disable irq
 *
 * @param [in] ptr VAD base address
 * @param [in] irq_mask irq mask value
 */
static inline void vad_disable_irq(VAD_Type *ptr, uint32_t irq_mask)
{
    ptr->CTRL &= ~irq_mask;
}

/**
 * @brief disable buffer
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_disable_buffer(VAD_Type *ptr)
{
    ptr->CTRL |= VAD_CTRL_MEMBUF_DISABLE_MASK;
}

/**
 * @brief enable buffer
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_enable_buffer(VAD_Type *ptr)
{
    ptr->CTRL &= ~VAD_CTRL_MEMBUF_DISABLE_MASK;
}

/**
 * @brief set fifo threshold
 *
 * @param [in] ptr VAD base address
 * @param [in] threshold fifo threshold value
 */
static inline void vad_set_fifo_threshold(VAD_Type *ptr, uint8_t threshold)
{
    ptr->CTRL = (ptr->CTRL & ~(VAD_CTRL_FIFO_THRSH_MASK))
        | VAD_CTRL_FIFO_THRSH_SET(threshold);
}

/**
 * @brief enable pdm clock out
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_enable_pdm_clock_out(VAD_Type *ptr)
{
    ptr->CTRL |= VAD_CTRL_PDM_CLK_OE_MASK;
}

/**
 * @brief disable pdm clock out
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_disable_pdm_clock_out(VAD_Type *ptr)
{
    ptr->CTRL &= ~VAD_CTRL_PDM_CLK_OE_MASK;
}

/**
 * @brief set pdm clock polarity
 *
 * @param [in] ptr VAD base address
 * @param [in] level clock polarity
 */
static inline void vad_set_pdm_clock_capture_level(VAD_Type *ptr, uint8_t level)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_CH_POL_MASK)
        | VAD_CTRL_CH_POL_SET(level);
}

/**
 * @brief set channel number
 *
 * @param [in] ptr VAD base address
 * @param [in] two_channels:
 *  @arg true: set two channels
 *  @arg false: set one channel
 */
static inline void vad_set_channel_number(VAD_Type *ptr, bool two_channels)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_CHNUM_MASK)
        | (two_channels ? VAD_CTRL_CHNUM_MASK : 0);
}

/**
 * @brief get status
 *
 * @param [in] ptr VAD base address
 * @retval ST register value
 */
static inline uint32_t vad_get_status(VAD_Type *ptr)
{
    return ptr->ST;
}

/**
 * @brief slear status
 *
 * @param [in] ptr VAD base address
 * @param [in] mask status mask value
 */
static inline void vad_clear_status(VAD_Type *ptr, uint32_t mask)
{
    ptr->ST |= mask;
}

/**
 * @brief get data
 *
 * @param [in] ptr VAD base address
 * @retval OFIFO register value
 */
static inline uint32_t vad_get_data(VAD_Type *ptr)
{
    return ptr->OFIFO;
}

/**
 * @brief software reset
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_software_reset(VAD_Type *ptr)
{
    ptr->RUN |= VAD_RUN_SFTRST_MASK;
    ptr->RUN &= ~VAD_RUN_SFTRST_MASK;
}

/**
 * @brief start
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_start(VAD_Type *ptr)
{
    ptr->RUN |= VAD_RUN_VAD_EN_MASK;
}

/**
 * @brief stop
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_stop(VAD_Type *ptr)
{
    ptr->RUN &= ~VAD_RUN_VAD_EN_MASK;
}

/**
 * @brief check whether vad is running
 *
 * @param [in] ptr VAD base address
 * @retval true if vad is running
 */
static inline bool vad_is_running(VAD_Type *ptr)
{
    return ptr->RUN & VAD_RUN_VAD_EN_MASK;
}

/**
 * @brief enable fifo
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_enable_fifo(VAD_Type *ptr)
{
    ptr->OFIFO_CTRL |= VAD_OFIFO_CTRL_EN_MASK;
}

/**
 * @brief disable fifo
 *
 * @param [in] ptr VAD base address
 */
static inline void vad_disable_fifo(VAD_Type *ptr)
{
    ptr->OFIFO_CTRL &= ~VAD_OFIFO_CTRL_EN_MASK;
}

/**
 * @brief get coefficient value
 *
 * @param [in] ptr VAD base address
 * @param [in] index coefficient index
 */
static inline uint32_t vad_get_coef_value(VAD_Type *ptr, uint32_t index)
{
    return ptr->COEF[index];
}

/**
 * @brief set ouptput value post scale
 *
 * @param [in] ptr VAD base address
 * @param [in] post_scale post scale value
 */
static inline void vad_set_post_scale(VAD_Type *ptr, uint8_t post_scale)
{
    ptr->CIC_CFG |= (ptr->CIC_CFG & ~VAD_CIC_CFG_POST_SCALE_MASK)
        | VAD_CIC_CFG_POST_SCALE_SET(post_scale);
}

/**
 * @brief set sampling signal amplitude limits
 *
 * @param [in] ptr VAD base address
 * @param [in] high high limit
 * @param [in] low low limit
 */
static inline void vad_set_amplify(VAD_Type *ptr, uint16_t high, uint16_t low)
{
    ptr->DEC_CTRL2 = VAD_DEC_CTRL2_AMP_HIGH_SET(high)
        | VAD_DEC_CTRL2_AMP_LOW_SET(low);
}

/**
 * @brief get default config
 *
 * @param [in] ptr VAD base address
 * @param [out] config vad_config_t
 */
void vad_get_default_config(VAD_Type *ptr, vad_config_t *config);

/**
 * @brief initialization
 *
 * @param [in] ptr VAD base address
 * @param [in] config vad_config_t
 */
void vad_init(VAD_Type *ptr, vad_config_t *config);

/**
 * @brief reset
 *
 * @param [in] ptr VAD base address
 */
void vad_reset(VAD_Type *ptr);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_VAD_DRV_H */
