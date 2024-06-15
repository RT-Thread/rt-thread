/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GWC_DRV_H
#define HPM_GWC_DRV_H

/**
 * @brief GWC APIs
 * @defgroup gwc_interface GWC driver APIs
 * @ingroup gwc_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_gwc_regs.h"

/**
 * @brief gwc channel config
 *
 * @note area of channel do not overlap. in other words, eache pixel belongs to a single channel at most.
 */
typedef struct gwc_ch_config {
    bool freeze;  /*!< freeze the channel configuration except reference CRC32 value setting. */
    uint16_t start_col; /*!< start col is X of upper left corner. Range: 0 to 2^13-1. */
    uint16_t start_row; /*!< start row is Y of upper left corner. Range: 0 to 2^12-1. */
    uint16_t end_col; /*!< end col is X of lower right corner. Range: 0 to 2^13-1. */
    uint16_t end_row; /*!< end row is Y of lower right corner. Range: 0 to 2^12-1. */
    uint32_t ref_crc; /*!< Reference CRC32 value.*/
} gwc_ch_config_t;

/**
 * @brief gwc clk polarity
 */
typedef enum gwc_clk_pol {
    gwc_clk_pol_normal = 0,
    gwc_clk_pol_invert
} gwc_clk_pol_t;

/**
 * @brief gwc config
 */
typedef struct gwc_config {
    gwc_clk_pol_t clk_pol;
} gwc_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief init the gwc
 *
 * @param[in] cfg GWC config @ref gwc_config_t
 */
void gwc_get_default_config(gwc_config_t *cfg);

/**
 * @brief init the gwc
 *
 * @param[in] ptr GWC base address
 * @param[in] cfg GWC config @ref gwc_config_t
 *
 * @note the function is called while gwc is disable only
 */
void gwc_init(GWC_Type *ptr, gwc_config_t *cfg);

/**
 * @brief enable the gwc
 *
 * @param[in] ptr GWC base address
 */
void gwc_enable(GWC_Type *ptr);

/**
 * @brief disable the gwc
 *
 * @param[in] ptr GWC base address
 */
void gwc_disable(GWC_Type *ptr);

/**
 * @brief enable interrupts
 *
 * @param[in] ptr GWC base address
 * @param[in] mask Mask of interrupt events that would be enabled
 *             @ref GWC_IRQ_MASK_ERR_MASK_MASK
 *             @ref GWC_IRQ_MASK_FUNC_MASK_MASK
 */
static inline void gwc_enable_interrupt(GWC_Type *ptr, uint32_t mask)
{
    ptr->IRQ_MASK &= ~mask;
}

/**
 * @brief disable interrupts.
 *
 * @param[in] ptr GWC base address
 * @param[in] mask mask of interrupt events that would be enabled.
 *             @ref GWC_IRQ_MASK_ERR_MASK_MASK
 *             @ref GWC_IRQ_MASK_FUNC_MASK_MASK
 */
static inline void gwc_disable_interrupt(GWC_Type *ptr, uint32_t mask)
{
    ptr->IRQ_MASK |= mask;
}

/**
 * @brief get gwc status flag
 *
 * @param[in] ptr GWC base address
 * @return gwc status
 */
static inline uint32_t gwc_get_status(GWC_Type *ptr)
{
    return ptr->IRQ_STS;
}

/**
 * @brief clear gwc status flag
 *
 * @param[in] ptr GWC base address
 * @param[in] mask logical OR'ed of GWC_IRQ_STS_XXX_STS_MASK
 */
static inline void gwc_clear_status(GWC_Type *ptr, uint32_t mask)
{
    ptr->IRQ_STS = mask;
}

/**
 * @brief disable change of interrupt masks
 *
 * Once this function is called, the interrupt enabled status could not be changed
 * until reset.
 *
 * @param[in] ptr GWC base address
 */
void gwc_freeze_interrupt_control(GWC_Type *ptr);

/**
 * @brief init gwc channel
 *
 * @param[in] ptr GWC base address
 * @param[in] ch_index channel index ref GWC_CHANNEL_CHn
 * @param[in] cfg config of gwc channel
 *
 * @note the function is called while gwc channel is disable only
 */
void gwc_ch_init(GWC_Type *ptr, uint8_t ch_index, gwc_ch_config_t *cfg);

/**
 * @brief enable gwc channel
 *
 * @param[in] ptr GWC base address
 * @param[in] ch_index channel index ref GWC_CHANNEL_CHn
 */
static inline void gwc_ch_enable(GWC_Type *ptr, uint8_t ch_index)
{
    assert(ch_index <= GWC_CHANNEL_CH15);
    ptr->CHANNEL[ch_index].CFG0 |= GWC_CHANNEL_CFG0_ENABLE_MASK;
}

/**
 * @brief disable gwc channel
 *
 * @param[in] ptr GWC base address
 * @param[in] ch_index channel index ref GWC_CHANNEL_CHn
 */
static inline void gwc_ch_disable(GWC_Type *ptr, uint8_t ch_index)
{
    assert(ch_index <= GWC_CHANNEL_CH15);
    ptr->CHANNEL[ch_index].CFG0 &= ~GWC_CHANNEL_CFG0_ENABLE_MASK;
}

/**
 * @brief get gwc channel calc crc
 *
 * @param[in] ptr GWC base address
 * @param[in] ch_index channel index ref GWC_CHANNEL_CHn
 */
static inline uint32_t gwc_ch_get_crc(GWC_Type *ptr, uint8_t ch_index)
{
    assert(ch_index <= GWC_CHANNEL_CH15);
    return ptr->CHANNEL[ch_index].CALCRC;
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_GWC_DRV_H */
