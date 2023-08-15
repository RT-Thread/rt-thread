/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPTMR_DRV_H
#define HPM_GPTMR_DRV_H
#include "hpm_common.h"
#include "hpm_gptmr_regs.h"

/**
 * @brief GPTMR driver APIs
 * @defgroup gptmr_interface GPTMR driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief GPTMR channel IRQ mask
 */
#define GPTMR_CH_CMP_IRQ_MASK(ch, cmp) (1 << (ch * 4 + 2 + cmp))
#define GPTMR_CH_CAP_IRQ_MASK(ch) (1 << (ch * 4 + 1))
#define GPTMR_CH_RLD_IRQ_MASK(ch) (1 << (ch * 4))

/**
 * @brief GPTMR channel status
 */
#define GPTMR_CH_CMP_STAT_MASK(ch, cmp) (1 << (ch * 4 + 2 + cmp))
#define GPTMR_CH_CAP_STAT_MASK(ch) (1 << (ch * 4 + 1))
#define GPTMR_CH_RLD_STAT_MASK(ch) (1 << (ch * 4))

/**
 * @brief GPTMR channel swsynct mask
 */
#define GPTMR_CH_GCR_SWSYNCT_MASK(ch) (1 << ch)

/**
 * @brief GPTMR one channel support output comparator count
 */
#define GPTMR_CH_CMP_COUNT (2U)

/**
 * @brief GPTMR synci valid edge
 */
typedef enum gptmr_synci_edge {
    gptmr_synci_edge_none = 0,
    gptmr_synci_edge_falling = GPTMR_CHANNEL_CR_SYNCIFEN_MASK,
    gptmr_synci_edge_rising = GPTMR_CHANNEL_CR_SYNCIREN_MASK,
    gptmr_synci_edge_both = gptmr_synci_edge_falling | gptmr_synci_edge_rising,
} gptmr_synci_edge_t;

/**
 * @brief GPTMR work mode
 */
typedef enum gptmr_work_mode {
    gptmr_work_mode_no_capture = 0,
    gptmr_work_mode_capture_at_rising_edge = 1,
    gptmr_work_mode_capture_at_falling_edge = 2,
    gptmr_work_mode_capture_at_both_edge = 3,
    gptmr_work_mode_measure_width = 4,
} gptmr_work_mode_t;

/**
 * @brief GPTMR DMA request event
 */
typedef enum gptmr_dma_request_event {
    gptmr_dma_request_on_cmp0 = 0,
    gptmr_dma_request_on_cmp1 = 1,
    gptmr_dma_request_on_input_signal_toggle = 2,
    gptmr_dma_request_on_reload = 3,
    gptmr_dma_request_disabled = 0xFF,
} gptmr_dma_request_event_t;

/**
 * @brief GPTMR counter type
 */
typedef enum gptmr_counter_type {
    gptmr_counter_type_rising_edge,
    gptmr_counter_type_falling_edge,
    gptmr_counter_type_measured_period,
    gptmr_counter_type_measured_duty_cycle,
    gptmr_counter_type_normal,
} gptmr_counter_type_t;

/**
 * @brief GPTMR channel config
 */
typedef struct gptmr_channel_config {
    gptmr_work_mode_t mode;
    gptmr_dma_request_event_t dma_request_event;
    gptmr_synci_edge_t synci_edge;
    uint32_t cmp[GPTMR_CH_CMP_COUNT];
    uint32_t reload;
    bool cmp_initial_polarity_high;
    bool enable_cmp_output;
    bool enable_sync_follow_previous_channel;
    bool enable_software_sync;
    bool debug_mode;
} gptmr_channel_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief gptmr channel enable
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] enable
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void gptmr_channel_enable(GPTMR_Type *ptr, uint8_t ch_index, bool enable)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR
         & ~(GPTMR_CHANNEL_CR_CNTRST_MASK | GPTMR_CHANNEL_CR_CMPEN_MASK))
        | GPTMR_CHANNEL_CR_CMPEN_SET(enable);
}

/**
 * @brief gptmr channel reset counter
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 */
static inline void gptmr_channel_reset_count(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CNTRST_MASK;
    ptr->CHANNEL[ch_index].CR &= ~GPTMR_CHANNEL_CR_CNTRST_MASK;
}

/**
 * @brief gptmr channel update counter
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] value updated vaue
 */
static inline void gptmr_channel_update_count(GPTMR_Type *ptr,
                                             uint8_t ch_index,
                                             uint32_t value)
{
    if (value > 0) {
        value--;
    }
    ptr->CHANNEL[ch_index].CNTUPTVAL = GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_SET(value);
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CNTUPT_MASK;
}

/**
 * @brief gptmr channel slect synci valid edge
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] edge gptmr_synci_edge_t
 */
static inline void gptmr_channel_select_synci_valid_edge(GPTMR_Type *ptr,
                                                        uint8_t ch_index,
                                                        gptmr_synci_edge_t edge)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR
            & ~(GPTMR_CHANNEL_CR_SYNCIFEN_MASK
              | GPTMR_CHANNEL_CR_SYNCIREN_MASK)) | edge;
}

/**
 * @brief gptmr channel enable dma request
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] enable
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void gptmr_channel_enable_dma_request(GPTMR_Type *ptr,
                                                   uint8_t ch_index,
                                                   bool enable)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR
            & ~(GPTMR_CHANNEL_CR_DMAEN_MASK)) | GPTMR_CHANNEL_CR_DMAEN_SET(enable);
}

/**
 * @brief gptmr channel get counter value
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] capture gptmr_counter_type_t
 */
static inline uint32_t gptmr_channel_get_counter(GPTMR_Type *ptr,
                                                     uint8_t ch_index,
                                                     gptmr_counter_type_t capture)
{
    uint32_t value;
    switch (capture) {
    case gptmr_counter_type_rising_edge:
        value = (ptr->CHANNEL[ch_index].CAPPOS & GPTMR_CHANNEL_CAPPOS_CAPPOS_MASK) >> GPTMR_CHANNEL_CAPPOS_CAPPOS_SHIFT;
        break;
    case gptmr_counter_type_falling_edge:
        value = (ptr->CHANNEL[ch_index].CAPNEG & GPTMR_CHANNEL_CAPNEG_CAPNEG_MASK) >> GPTMR_CHANNEL_CAPNEG_CAPNEG_SHIFT;
        break;
    case gptmr_counter_type_measured_period:
        value = (ptr->CHANNEL[ch_index].CAPPRD & GPTMR_CHANNEL_CAPPRD_CAPPRD_MASK) >> GPTMR_CHANNEL_CAPPRD_CAPPRD_SHIFT;
        break;
    case gptmr_counter_type_measured_duty_cycle:
        value = (ptr->CHANNEL[ch_index].CAPDTY & GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_MASK) >> GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_SHIFT;
        break;
    default:
        value = (ptr->CHANNEL[ch_index].CNT & GPTMR_CHANNEL_CNT_COUNTER_MASK) >> GPTMR_CHANNEL_CNT_COUNTER_SHIFT;
        break;
    }
    return value;
}

/**
 * @brief gptmr trigger channel software sync
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index_mask channel index mask
 */
static inline void gptmr_trigger_channel_software_sync(GPTMR_Type *ptr, uint32_t ch_index_mask)
{
    ptr->GCR = ch_index_mask;
}

/**
 * @brief gptmr enable irq
 *
 * @param [in] ptr GPTMR base address
 * @param [in] irq_mask irq mask
 */
static inline void gptmr_enable_irq(GPTMR_Type *ptr, uint32_t irq_mask)
{
    ptr->IRQEN |= irq_mask;
}

/**
 * @brief gptmr disable irq
 *
 * @param [in] ptr GPTMR base address
 * @param [in] irq_mask irq mask
 */
static inline void gptmr_disable_irq(GPTMR_Type *ptr, uint32_t irq_mask)
{
    ptr->IRQEN &= ~irq_mask;
}

/**
 * @brief gptmr check status
 *
 * @param [in] ptr GPTMR base address
 * @param [in] mask channel flag mask
 */
static inline bool gptmr_check_status(GPTMR_Type *ptr, uint32_t mask)
{
    return (ptr->SR & mask) == mask;
}

/**
 * @brief gptmr clear status
 *
 * @param [in] ptr GPTMR base address
 * @param [in] mask channel flag mask
 */
static inline void gptmr_clear_status(GPTMR_Type *ptr, uint32_t mask)
{
    ptr->SR |= mask;
}

/**
 * @brief gptmr get status
 *
 * @param [in] ptr GPTMR base address
 * @retval SR register value
 */
static inline uint32_t gptmr_get_status(GPTMR_Type *ptr)
{
    return ptr->SR;
}

/**
 * @brief gptmr channel start counter
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 */
static inline void gptmr_start_counter(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CEN_MASK;
}

/**
 * @brief gptmr channel stop counter
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 */
static inline void gptmr_stop_counter(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR &= ~GPTMR_CHANNEL_CR_CEN_MASK;
}

/**
 * @brief gptmr channel enable compare output
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 */
static inline void gptmr_enable_cmp_output(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CMPEN_MASK;
}

/**
 * @brief gptmr channel disable compare output
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 */
static inline void gptmr_disable_cmp_output(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR &= ~GPTMR_CHANNEL_CR_CMPEN_MASK;
}

/**
 * @brief gptmr channel set capmode
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 */
static inline void gptmr_channel_set_capmode(GPTMR_Type *ptr, uint8_t ch_index, gptmr_work_mode_t mode)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR & ~GPTMR_CHANNEL_CR_CAPMODE_MASK) | GPTMR_CHANNEL_CR_CAPMODE_SET(mode);
}

/**
 * @brief gptmr channel get capmode
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @retval gptmr_work_mode_t enum gptmr_work_mode_capture_at_rising_edge or gptmr_work_mode_capture_at_falling_edge
 */
static inline gptmr_work_mode_t gptmr_channel_get_capmode(GPTMR_Type *ptr, uint8_t ch_index)
{
    return GPTMR_CHANNEL_CR_CAPMODE_GET(ptr->CHANNEL[ch_index].CR);
}

/**
 * @brief gptmr channel update comparator
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] cmp_index comparator index
 * @param [in] cmp comparator value
 */
static inline void gptmr_update_cmp(GPTMR_Type *ptr, uint8_t ch_index, uint8_t cmp_index, uint32_t cmp)
{
    if (cmp > 0) {
        cmp--;
    }
    ptr->CHANNEL[ch_index].CMP[cmp_index] = GPTMR_CHANNEL_CMP_CMP_SET(cmp);
}

/**
 * @brief gptmr channel get reload
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @retval RLD register value
 */
static inline uint32_t gptmr_channel_get_reload(GPTMR_Type *ptr, uint8_t ch_index)
{
    return ptr->CHANNEL[ch_index].RLD;
}

/**
 * @brief gptmr channel update reload
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] reload reload value
 */
static inline void gptmr_channel_config_update_reload(GPTMR_Type *ptr, uint8_t ch_index, uint32_t reload)
{
    if (reload > 0) {
        reload--;
    }
    ptr->CHANNEL[ch_index].RLD = GPTMR_CHANNEL_RLD_RLD_SET(reload);
}

/**
 * @brief gptmr channel get dma request event
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @retval gptmr_dma_request_event_t gptmr_dma_request_on_cmp0 or gptmr_dma_request_on_reload
 */
static inline gptmr_dma_request_event_t gptmr_channel_get_dma_request_event(GPTMR_Type *ptr, uint8_t ch_index)
{
    return GPTMR_CHANNEL_CR_DMASEL_GET(ptr->CHANNEL[ch_index].CR);
}

/**
 * @brief gptmr channel config
 *
 * @param [in] ptr GPTMR base address
 * @param [in] ch_index channel index
 * @param [in] config gptmr_channel_config_t
 * @param [in] enable
 *  @arg true: enable
 *  @arg false: disable
 *
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t gptmr_channel_config(GPTMR_Type *ptr,
                         uint8_t ch_index,
                         gptmr_channel_config_t *config,
                         bool enable);

/**
 * @brief gptmr channel get default config
 *
 * @param [in] ptr GPTMR base address
 * @param [out] config gptmr_channel_config_t
 */
void gptmr_channel_get_default_config(GPTMR_Type *ptr, gptmr_channel_config_t *config);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_GPTMR_DRV_H */
