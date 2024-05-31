/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TRGM_DRV_H
#define HPM_TRGM_DRV_H

#include "hpm_common.h"
#include "hpm_trgm_regs.h"
#include "hpm_trgmmux_src.h"

/**
 *
 * @brief TRGM driver APIs
 * @defgroup trgm_interface TRGM driver APIs
 * @{
 */

/**
 * @brief Filter mode
 */
typedef enum trgm_filter_mode {
    trgm_filter_mode_bypass = 0,
    trgm_filter_mode_rapid_change = 4,
    trgm_filter_mode_delay = 5,
    trgm_filter_mode_stable_high = 6,
    trgm_filter_mode_stable_low = 7,
} trgm_filter_mode_t;

/**
 * @brief Output type
 */
typedef enum trgm_output_type {
    trgm_output_same_as_input = 0,
    trgm_output_pulse_at_input_falling_edge = TRGM_TRGOCFG_FEDG2PEN_MASK,
    trgm_output_pulse_at_input_rising_edge = TRGM_TRGOCFG_REDG2PEN_MASK,
    trgm_output_pulse_at_input_both_edge = trgm_output_pulse_at_input_falling_edge
                                    | trgm_output_pulse_at_input_rising_edge,
} trgm_output_type_t;

/**
 * @brief Input filter configuration
 */
typedef struct trgm_input_filter {
    bool invert;                /**< Invert output */
    bool sync;                  /**< Sync with TRGM clock */
    uint32_t filter_length;     /**< Filter length in TRGM clock cycle */
    trgm_filter_mode_t mode;    /**< Filter working mode */
} trgm_input_filter_t;

/**
 * @brief Output configuration
 */
typedef struct trgm_output {
    bool invert;                /**< Invert output */
    trgm_output_type_t type;    /**< Output type */
    uint8_t input;              /**< Input selection */
} trgm_output_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Enable IO output
 *
 * @param[in] ptr TRGM base address
 * @param[in] mask Mask of IOs to be enabled
 */
static inline void trgm_enable_io_output(TRGM_Type *ptr, uint32_t mask)
{
    ptr->GCR |= mask;
}

/**
 * @brief   Disable IO output
 *
 * @param[in] ptr TRGM base address
 * @param[in] mask Mask of IOs to be disabled
 */
static inline void trgm_disable_io_output(TRGM_Type *ptr, uint32_t mask)
{
    ptr->GCR &= ~mask;
}

/**
 * @brief   Set filter length
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 * @param[in] length Filter length in TRGM clock cycles
 */
static inline void trgm_input_filter_set_filter_length(TRGM_Type *ptr, uint8_t input, uint32_t length)
{
#if defined(TRGM_SOC_HAS_FILTER_SHIFT) && TRGM_SOC_HAS_FILTER_SHIFT
    uint32_t len = length;
    uint8_t shift;
    for (shift = 0; shift <= (TRGM_FILTCFG_FILTLEN_SHIFT_MASK >> TRGM_FILTCFG_FILTLEN_SHIFT_SHIFT); shift++) {
        if (shift > 0) {
            len >>= 1u;
        }
        if (len <= (TRGM_FILTCFG_FILTLEN_BASE_MASK >> TRGM_FILTCFG_FILTLEN_BASE_SHIFT)) {
            break;
        }
    }
    if (len > (TRGM_FILTCFG_FILTLEN_BASE_MASK >> TRGM_FILTCFG_FILTLEN_BASE_SHIFT)) {
        len = (TRGM_FILTCFG_FILTLEN_BASE_MASK >> TRGM_FILTCFG_FILTLEN_BASE_SHIFT);
        shift = (TRGM_FILTCFG_FILTLEN_SHIFT_MASK >> TRGM_FILTCFG_FILTLEN_SHIFT_SHIFT);
    }
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & ~(TRGM_FILTCFG_FILTLEN_BASE_MASK | TRGM_FILTCFG_FILTLEN_SHIFT_MASK))
                        | TRGM_FILTCFG_FILTLEN_BASE_SET(len) | TRGM_FILTCFG_FILTLEN_SHIFT_SET(shift);
#else
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & ~TRGM_FILTCFG_FILTLEN_MASK)
                        | TRGM_FILTCFG_FILTLEN_SET(length);
#endif
}

/**
 * @brief   Set filter length
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 * @param[in] shift Filter length shift
 */
static inline void trgm_input_filter_set_filter_shift(TRGM_Type *ptr, uint8_t input, uint8_t shift)
{
#if defined(TRGM_SOC_HAS_FILTER_SHIFT) && TRGM_SOC_HAS_FILTER_SHIFT
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & ~TRGM_FILTCFG_FILTLEN_SHIFT_MASK)
                        | TRGM_FILTCFG_FILTLEN_SHIFT_SET(shift);
#else
    (void) ptr;
    (void) input;
    (void) shift;
#endif
}

/**
 * @brief   Enable sync input with TRGM clock
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 */
static inline void trgm_input_filter_enable_sync(TRGM_Type *ptr, uint8_t input)
{
    ptr->FILTCFG[input] |= TRGM_FILTCFG_SYNCEN_MASK;
}

/**
 * @brief   Disable sync input with TRGM clock
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 */
static inline void trgm_input_filter_disable_sync(TRGM_Type *ptr, uint8_t input)
{
    ptr->FILTCFG[input] &= ~TRGM_FILTCFG_SYNCEN_MASK;
}

/**
 * @brief   Set filter working mode
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 * @param[in] mode Working mode
 */
static inline void trgm_input_filter_set_mode(TRGM_Type *ptr, uint8_t input, trgm_filter_mode_t mode)
{
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & ~TRGM_FILTCFG_MODE_MASK)
                        | TRGM_FILTCFG_MODE_SET(mode);
}

/**
 * @brief   Invert filter output
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 * @param[in] invert Set true to invert output
 */
static inline void trgm_input_filter_invert(TRGM_Type *ptr, uint8_t input, bool invert)
{
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & ~TRGM_FILTCFG_OUTINV_MASK)
                        | TRGM_FILTCFG_OUTINV_SET(invert);
}

/**
 * @brief   Configure filter
 *
 * @param[in] ptr TRGM base address
 * @param[in] input Input selection
 * @param[in] filter Pointer to filter configuration
 */
static inline void trgm_input_filter_config(TRGM_Type *ptr, uint8_t input, trgm_input_filter_t *filter)
{
    ptr->FILTCFG[input] = TRGM_FILTCFG_OUTINV_SET(filter->invert)
                        | TRGM_FILTCFG_MODE_SET(filter->mode)
                        | TRGM_FILTCFG_SYNCEN_SET(filter->sync);
    trgm_input_filter_set_filter_length(ptr, input, filter->filter_length);
}

/**
 * @brief   Update source for TRGM output
 *
 * @param[in] ptr TRGM base address
 * @param[in] output Target output
 * @param[in] source Source for output
 */
static inline void trgm_output_update_source(TRGM_Type *ptr, uint8_t output, uint8_t source)
{
    ptr->TRGOCFG[output] = (ptr->TRGOCFG[output] & ~TRGM_TRGOCFG_TRIGOSEL_MASK)
                        | TRGM_TRGOCFG_TRIGOSEL_SET(source);
}

/**
 * @brief   Configure output
 *
 * @param[in] ptr TRGM base address
 * @param[in] output Target output
 * @param[in] config Pointer to output configuration
 */
static inline void trgm_output_config(TRGM_Type *ptr, uint8_t output, trgm_output_t *config)
{
    ptr->TRGOCFG[output] = TRGM_TRGOCFG_TRIGOSEL_SET(config->input)
                        | (config->type & TRGM_TRGOCFG_FEDG2PEN_MASK)
                        | (config->type & TRGM_TRGOCFG_REDG2PEN_MASK)
                        | TRGM_TRGOCFG_OUTINV_SET(config->invert);
}

/**
 * @brief   Configure DMA request
 *
 * @param[in] ptr TRGM base address
 * @param[in] dma_out Target DMA out
 * @param[in] dma_src DMA source selection
 */
static inline void trgm_dma_request_config(TRGM_Type *ptr, uint8_t dma_out, uint8_t dma_src)
{
#if defined(TRGM_SOC_HAS_DMAMUX_EN) && TRGM_SOC_HAS_DMAMUX_EN
    ptr->DMACFG[dma_out] = TRGM_DMACFG_DMASRCSEL_SET(dma_src) | TRGM_DMACFG_DMAMUX_EN_MASK;
#else
    ptr->DMACFG[dma_out] = TRGM_DMACFG_DMASRCSEL_SET(dma_src);
#endif
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_TRGM_DRV_H */


