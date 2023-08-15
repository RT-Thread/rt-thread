/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PTPC_DRV_H
#define HPM_PTPC_DRV_H

#include "hpm_common.h"
#include "hpm_ptpc_regs.h"

/**
 * @brief PTPC driver
 * @defgroup ptpc_interface PTPC driver APIs
 * @ingroup timer_interfaces Timers
 * @{
 */

#define PTPC_EVENT_COMPARE0_MASK    PTPC_INT_STS_COMP_INT_STS0_MASK
#define PTPC_EVENT_CAPTURE0_MASK    PTPC_INT_STS_CAPTURE_INT_STS0_MASK
#define PTPC_EVENT_PPS0_MASK        PTPC_INT_STS_PPS_INT_STS0_MASK
#define PTPC_EVENT_COMPARE1_MASK    PTPC_INT_STS_COMP_INT_STS1_MASK
#define PTPC_EVENT_CAPTURE1_MASK    PTPC_INT_STS_CAPTURE_INT_STS1_MASK
#define PTPC_EVENT_PPS1_MASK        PTPC_INT_STS_PPS_INT_STS1_MASK

#define PTPC_MAX_NS_COUNTER (0x3B9ACA00UL)

/**
 * @brief Counter types
 */
typedef enum ptpc_ns_counter_rollover_type {
    ptpc_ns_counter_rollover_binary = 0, /**< binary mode, resolution ~0.466ns, overflow at 0x7FFFFFFF */
    ptpc_ns_counter_rollover_digital = 1, /**< digital mode, resolution 1ns, overflow at 0x3B9ACA00 */
} ptpc_ns_counter_rollover_type_t;

/**
 * @brief Capture trigger types
 */
typedef enum ptpc_capture_trigger_type {
    ptpc_capture_trigger_none = 0,
    ptpc_capture_trigger_on_rising_edge = PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK,
    ptpc_capture_trigger_on_failing_edge = PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK,
    ptpc_capture_trigger_on_both_edges = PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK
                                        | PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK,
} ptpc_capture_trigger_type_t;

/**
 * @brief Capture trigger types
 */
typedef enum ptpc_counting_mode {
    ptpc_counting_increment = 0,            /**< Increment the counter */
    ptpc_counting_decrement = 1,            /**< Decrement the counter */
} ptpc_counting_mode;

/**
 * @brief Timer config
 */
typedef struct {
    ptpc_capture_trigger_type_t capture_trigger;        /**< Capture trigger */
    ptpc_ns_counter_rollover_type_t ns_rollover_mode;   /**< Ns rollover mode */
    bool coarse_increment;                              /**< Set false to use fine increment */
    bool capture_keep;                                  /**< Keep captured timer counter */
    uint32_t src_frequency;                             /**< Source frequency */
} ptpc_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Configure ns counter rollover mode
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Index of target counter
 * @param[in] rollover Rollover type
 */
static inline void ptpc_set_ns_counter_rollover(PTPC_Type *ptr, uint8_t index,
                                ptpc_ns_counter_rollover_type_t rollover)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_MASK)
        | PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SET(rollover);
}

/**
 * @brief   Enable capture keep
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 */
static inline void ptpc_enable_capture_keep(PTPC_Type *ptr, uint8_t index)
{
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_MASK;
}

/**
 * @brief   Disable capture keep
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 */
static inline void ptpc_disable_capture_keep(PTPC_Type *ptr, uint8_t index)
{
    ptr->PTPC[index].CTRL0 &= ~PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_MASK;
}

/**
 * @brief   Update ns counter update type
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Index of target counter
 * @param[in] coarse_update Counter will be increment by 1 on
 */
static inline void ptpc_set_ns_counter_update_type(PTPC_Type *ptr, uint8_t index, bool coarse_update)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_FINE_COARSE_SEL_MASK)
        | PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SET(coarse_update);
}

/**
 * @brief   Set ns counter increment step
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] ns_step Increment step
 */
static inline void ptpc_set_ns_counter_step(PTPC_Type *ptr, uint8_t index, uint32_t ns_step)
{
    ptr->PTPC[index].CTRL1 = PTPC_PTPC_CTRL1_SS_INCR_SET(ns_step);
}

/**
 * @brief   Set Second portion update value
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] sec Second value
 */
static inline void ptpc_set_second_update(PTPC_Type *ptr, uint8_t index, uint32_t sec)
{
    ptr->PTPC[index].TS_UPDTH = PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SET(sec);
}

/**
 * @brief   Set ns portion update value
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] ns Ns value (31 bits, 0x3B9ACA00 max)
 * @param[in] mode Counting mode
 *
 * @return status_success if everything is okay
 */
hpm_stat_t ptpc_set_ns_update(PTPC_Type *ptr, uint8_t index, uint32_t ns, ptpc_counting_mode mode);

/**
 * @brief   Get current timestamp Second portion
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 *
 * @return Seconds value
 */
static inline uint32_t ptpc_get_timestamp_second(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_GET(ptr->PTPC[index].TIMEH);
}

/**
 * @brief   Get timestamp ns portion
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 *
 * @return ns value
 */
static inline uint32_t ptpc_get_timestamp_ns(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_TIMEL_TIMESTAMP_LOW_GET(ptr->PTPC[index].TIMEL);
}

/**
 * @brief   Config compare
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] sec Target second
 * @param[in] ns Target ns
 */
static inline void ptpc_config_compare(PTPC_Type *ptr, uint8_t index, uint32_t sec, uint32_t ns)
{
    ptr->PTPC[index].TARH = PTPC_PTPC_TARH_TARGET_TIME_HIGH_SET(sec);
    ptr->PTPC[index].TARL = PTPC_PTPC_TARL_TARGET_TIME_LOW_SET(ns);
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_COMP_EN_MASK;
}

/**
 * @brief   Update Second portion
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] sec Target second
 */
static inline void ptpc_update_timestamp_second(PTPC_Type *ptr, uint8_t index, uint32_t sec)
{
    ptr->PTPC[index].TS_UPDTH = PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SET(sec);
}

/**
 * @brief   Update Ns portion
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] ns Target ns
 * @param[in] mode Counting mode
 */
static inline void ptpc_update_timestamp_ns(PTPC_Type *ptr, uint8_t index, uint32_t ns, ptpc_counting_mode mode)
{
    ptr->PTPC[index].TS_UPDTL = PTPC_PTPC_TS_UPDTL_NS_UPDATE_SET(ns) | PTPC_PTPC_TS_UPDTL_ADD_SUB_SET(mode);
}

/**
 * @brief   Enable timer
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 */
static inline void ptpc_enable_timer(PTPC_Type *ptr, uint8_t index)
{
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_TIMER_ENABLE_MASK;
}

/**
 * @brief   Disable timer
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 */
static inline void ptpc_disable_timer(PTPC_Type *ptr, uint8_t index)
{
    ptr->PTPC[index].CTRL0 &= ~PTPC_PTPC_CTRL0_TIMER_ENABLE_MASK;
}

/**
 * @brief   Config capture trigger event
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] trigger Capture trigger type
 */
static inline void ptpc_config_capture(PTPC_Type *ptr, uint8_t index,
                                ptpc_capture_trigger_type_t trigger)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~(PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK
                | PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK)) | trigger;
}

/**
 * @brief   Get snapped ns value
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 *
 * @return ns portion on capture
 */
static inline uint32_t ptpc_get_capture_ns(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_GET(ptr->PTPC[index].CAPT_SNAPL);
}

/**
 * @brief   Get captured second
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 *
 * @return second portion on capture
 */
static inline uint32_t ptpc_get_capture_second(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_GET(ptr->PTPC[index].CAPT_SNAPH);
}

/**
 * @brief   Clear interrupt status
 *
 * @param[in] ptr PTPC base address
 * @param[in] mask Mask of interrupts to be cleared
 */
static inline void ptpc_clear_irq_status(PTPC_Type *ptr, uint32_t mask)
{
    ptr->INT_STS |= mask;
}

/**
 * @brief   Get interrupt status
 *
 * @param[in] ptr PTPC base address
 *
 * @return interrupt status mask
 */
static inline uint32_t ptpc_get_irq_status(PTPC_Type *ptr)
{
    return ptr->INT_STS;
}

/**
 * @brief   Disable interrupt with mask
 *
 * @param[in] ptr PTPC base address
 * @param[in] mask Mask of interrupts to be disabled
 */
static inline void ptpc_irq_disable(PTPC_Type *ptr, uint32_t mask)
{
    ptr->INT_EN &= ~mask;
}

/**
 * @brief   Enable interrupt with mask
 *
 * @param[in] ptr PTPC base address
 * @param[in] mask Mask of interrupts to be enabled
 */
static inline void ptpc_irq_enable(PTPC_Type *ptr, uint32_t mask)
{
    ptr->INT_EN |= mask;
}

/**
 * @brief   Initialize PTPC module
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] config Pointer to configuration struct
 *
 * @return status_success if everything is okay
 */
hpm_stat_t ptpc_init(PTPC_Type *ptr, uint8_t index, ptpc_config_t *config);

/**
 * @brief   Set PTPC output destination
 *
 * @param[in] ptr PTPC base address
 * @param[in] can_index Target CAN instance
 * @param[in] use_ptpc1 Use PTPC1 if set to true, otherwise PTPC0
 *
 * @return status_success if everything is okay
 */
hpm_stat_t ptpc_set_timer_output(PTPC_Type *ptr, uint8_t can_index, bool use_ptpc1);

/**
 * @brief   Get default config
 *
 * @param[in] ptr PTPC base address
 * @param[out] config Pointer of config struct
 */
void ptpc_get_default_config(PTPC_Type *ptr, ptpc_config_t *config);

/**
 * @brief   Initialize timer to count from 0
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 *
 */
void ptpc_init_timer(PTPC_Type *ptr, uint8_t index);

/**
 * @brief   Initialize timer with initial values
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] sec Seconds
 * @param[in] ns Ns
 * @param[in] mode Counting mode
 *
 * @return status_success if everything is okay
 */
hpm_stat_t ptpc_init_timer_with_initial(PTPC_Type *ptr, uint8_t index, uint32_t sec, uint32_t ns, ptpc_counting_mode mode);

/**
 * @brief   Update timestamp counter
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] sec Seconds
 * @param[in] ns Ns
 * @param[in] mode Counting mode
 * @return status_success if everything is okay
 */
hpm_stat_t ptpc_update_timer(PTPC_Type *ptr, uint8_t index, uint32_t sec, uint32_t ns, ptpc_counting_mode mode);

/**
 * @brief   Set period of pulse generated per second
 *
 * @param[in] ptr PTPC base address
 * @param[in] index Target index
 * @param[in] p (2^power Hz, from [0 - 15])
 *
 * @return true if requested frequency can be set
 * @return false if requested frequency can not be set
 */
hpm_stat_t ptpc_set_pps(PTPC_Type *ptr, uint8_t index, uint8_t p);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_PTPC_DRV_H */
