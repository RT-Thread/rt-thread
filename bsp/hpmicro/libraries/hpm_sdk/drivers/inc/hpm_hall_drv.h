/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_HALL_DRV_H
#define HPM_HALL_DRV_H

#include "hpm_common.h"
#include "hpm_hall_regs.h"

/**
 * @brief HALL driver APIs
 * @defgroup hall_interface HALL driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

#define HALL_EVENT_WDOG_FLAG_MASK (1U << 31)    /**< wdg flag */
#define HALL_EVENT_PHUPT_FLAG_MASK (1U << 30)   /**<  phupt flag */
#define HALL_EVENT_PHPRE_FLAG_MASK (1U << 29)   /**<  phpre flag  */
#define HALL_EVENT_PHDLYEN_FLAG_MASK (1U << 28) /**<  phdly flag */
#define HALL_EVENT_U_FLAG_MASK (1U << 23)   /**<   u flag */
#define HALL_EVENT_V_FLAG_MASK (1U << 22)   /**<  v flag */
#define HALL_EVENT_W_FLAG_MASK (1U << 21)   /**<  w flag */
#define HALL_UVW_STAT_MASK (HALL_COUNT_U_USTAT_MASK | HALL_COUNT_U_VSTAT_MASK | HALL_COUNT_U_WSTAT_MASK)
#define HALL_U_STAT_MASK HALL_COUNT_U_USTAT_MASK
#define HALL_V_STAT_MASK HALL_COUNT_U_VSTAT_MASK
#define HALL_W_STAT_MASK HALL_COUNT_U_WSTAT_MASK

/**
 * @brief  select delay start time
 *
 */
typedef enum hall_count_delay_start {
    hall_count_delay_start_after_uvw_toggle = 0,    /**< start counting delay after u,v,w toggle */
    hall_count_delay_start_after_pre_trigger = 1,   /**< start counting delay after pre-trigger */
} hall_count_delay_start_t;

/**
 * @brief return value of motor movement direction
 *
 */
typedef enum hall_rotate_direction {
    hall_rotate_direction_forward = 0,      /**< direction forward */
    hall_rotate_direction_reversed = 1      /**< direction reversed */
} hall_rotate_direction_t;

/**
 * @brief counter type config
 *
 */
typedef enum hall_counter_type {
    hall_counter_type_w = 0,            /**< type w */
    hall_counter_type_v = 1,            /**< type v */
    hall_counter_type_u = 2,            /**< type u */
    hall_counter_type_timer = 3,        /**< type timer */
} hall_counter_type_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief enable the watchdog
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] timeout watch dog timeout value , unit is HALL system clock
 */
static inline void hall_wdog_enable(HALL_Type *hall_x, uint32_t timeout)
{
    hall_x->WDGCFG = HALL_WDGCFG_WDGTO_SET(timeout)
                | HALL_WDGCFG_WDGEN_SET(true);
}

/**
 * @brief disable the watchdog
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 */
static inline void hall_wdog_disable(HALL_Type *hall_x)
{
    hall_x->WDGCFG = HALL_WDGCFG_WDGEN_SET(false);
}

/**
 * @brief delay a certain number of clock cycles after receiving a trigger event
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] delay_count delay clock cycles number
 * @param[in] delay_start select the trigger moment
 */
static inline void hall_phase_config(HALL_Type *hall_x, uint32_t delay_count,
                              hall_count_delay_start_t delay_start)
{
    hall_x->PHCFG = HALL_PHCFG_DLYSEL_SET(delay_start)
                | HALL_PHCFG_DLYCNT_SET(delay_count);
}

/**
 * @brief early trigger configuration
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] counter the clock cycle number
 */
static inline void hall_pre_uvw_transition_config(HALL_Type *hall_x, uint32_t counter)
{
    hall_x->UVWCFG = HALL_UVWCFG_PRECNT_SET(counter);
}

/**
 * @brief enable trigger event mask
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] event_mask event mask to be checked
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_trigger_output_event_enable(HALL_Type *hall_x,
                                        uint32_t event_mask)
{
    hall_x->TRGOEN = (hall_x->TRGOEN & ~event_mask) | event_mask;
}

/**
 * @brief disable trigger event mask
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] event_mask event mask to bo checked
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_trigger_output_event_disable(HALL_Type *hall_x,
                                        uint32_t event_mask)
{
    hall_x->TRGOEN &= ~event_mask;
}

/**
 * @brief enable hardware read event
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] event_mask  read registers flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_load_read_trigger_event_enable(HALL_Type *hall_x,
                                        uint32_t event_mask)
{
    hall_x->READEN = (hall_x->READEN & ~event_mask) | event_mask;
}

/**
 * @brief disable hardware read event
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] event_mask read registers flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_load_read_trigger_event_disable(HALL_Type *hall_x,
                                        uint32_t event_mask)
{
    hall_x->READEN &= ~event_mask;
}

/**
 * @brief clear status register
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] mask hall event flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_clear_status(HALL_Type *hall_x, uint32_t mask)
{
    hall_x->SR = mask;
}

/**
 * @brief get status register
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval uint32_t value:
 * @retval HALL_EVENT_WDOG_FLAG_MASK if watchdog counter timeout
 * @retval HALL_EVENT_PHUPT_FLAG_MASK if U/V/W Flip any input signal
 * @retval HALL_EVENT_PHPRE_FLAG_MASK if early trigger events occur
 * @retval HALL_EVENT_PHDLYEN_FLAG_MASK if time delay events occur
 * @retval HALL_EVENT_U_FLAG_MASK if U signal flip
 * @retval HALL_EVENT_V_FLAG_MASK if V signal flip
 * @retval HALL_EVENT_W_FLAG_MASK if W signal flip
 */
static inline uint32_t hall_get_status(HALL_Type *hall_x)
{
    return hall_x->SR;
}

/**
 * @brief enable irq
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] mask hall event flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_irq_enable(HALL_Type *hall_x, uint32_t mask)
{
    hall_x->IRQEN = (hall_x->IRQEN & ~mask) | mask;
}

/**
 * @brief disable irq
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] mask hall event flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_irq_disable(HALL_Type *hall_x, uint32_t mask)
{
    hall_x->IRQEN &= ~mask;
}

/**
 * @brief enable dma request
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] mask hall event flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_dma_request_enable(HALL_Type *hall_x, uint32_t mask)
{
    hall_x->DMAEN = (hall_x->DMAEN & ~mask) | mask;
}

/**
 * @brief disable dma request
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] mask hall event flag
 *  @arg @ref HALL_EVENT_WDOG_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHUPT_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHPRE_FLAG_MASK
 *  @arg @ref HALL_EVENT_PHDLYEN_FLAG_MASK
 *  @arg @ref HALL_EVENT_U_FLAG_MASK
 *  @arg @ref HALL_EVENT_V_FLAG_MASK
 *  @arg @ref HALL_EVENT_W_FLAG_MASK
 */
static inline void hall_dma_request_disable(HALL_Type *hall_x, uint32_t mask)
{
    hall_x->DMAEN &= ~mask;
}

/**
 * @brief get rotate direction
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval hall_rotate_direction_t
 */
static inline hall_rotate_direction_t hall_get_rotate_direction(HALL_Type *hall_x)
{
    return (hall_rotate_direction_t)HALL_COUNT_U_DIR_GET(hall_x->COUNT[HALL_COUNT_CURRENT].U);
}

/**
 * @brief get three bits indicate UVW state
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval three bits UVW state
 */
static inline uint32_t hall_get_current_uvw_stat(HALL_Type *hall_x)
{
    return (hall_x->COUNT[HALL_COUNT_CURRENT].U & (HALL_UVW_STAT_MASK)) >> HALL_COUNT_U_WSTAT_SHIFT;
}

/**
 * @brief get current count U or V or W
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] type @ref hall_counter_type_t
 * @retval count value
 */
static inline uint32_t hall_get_current_count(HALL_Type *hall_x,
                                            hall_counter_type_t type)
{
    return *(&hall_x->COUNT[HALL_COUNT_CURRENT].W + type) & HALL_COUNT_U_UCNT_MASK;
}

/**
 * @brief get count when read event generated
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] type hall_counter_type_t
 * @retval count value
 */
static inline uint32_t hall_get_count_on_read_event(HALL_Type *hall_x,
                                            hall_counter_type_t type)
{
    return *(&hall_x->COUNT[HALL_COUNT_READ].W + type);
}

/**
 * @brief get count when snap0 event generated
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] type @ref hall_counter_type_t
 * @retval count value
 */
static inline uint32_t hall_get_count_on_snap0_event(HALL_Type *hall_x,
                                            hall_counter_type_t type)
{
    return *(&hall_x->COUNT[HALL_COUNT_SNAP0].W + type);
}

/**
 * @brief get count when snap1 event generated
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @param[in] type @ref hall_counter_type_t
 * @retval count value
 */
static inline uint32_t hall_get_count_on_snap1_event(HALL_Type *hall_x,
                                            hall_counter_type_t type)
{
    return *(&hall_x->COUNT[HALL_COUNT_SNAP1].W + type);
}

/**
 * @brief  get the history count of u when u signal transition from 0 to 1
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval count value
 */
static inline uint32_t hall_get_u_history0(HALL_Type *hall_x)
{
    return hall_x->HIS[0].HIS0;
}

/**
 * @brief  get the history count of u when u signal transition from 1 to 0
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval count value
 */
static inline uint32_t hall_get_u_history1(HALL_Type *hall_x)
{
    return hall_x->HIS[0].HIS1;
}

/**
 * @brief  get the history count of v when v signal transition from 0 to 1
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval count value
 */
static inline uint32_t hall_get_v_history0(HALL_Type *hall_x)
{
    return hall_x->HIS[1].HIS0;
}

/**
 * @brief  get the history count of v when v signal transition from 1 to 0
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval count value
 */
static inline uint32_t hall_get_v_history1(HALL_Type *hall_x)
{
    return hall_x->HIS[1].HIS1;
}

/**
 * @brief  get the history count of w when w signal transition from 0 to 1
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval count value
 */
static inline uint32_t hall_get_w_history0(HALL_Type *hall_x)
{
    return hall_x->HIS[2].HIS0;
}

/**
 * @brief  get the history count of w when w signal transition from 1 to 0
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 * @retval count value
 */
static inline uint32_t hall_get_w_history1(HALL_Type *hall_x)
{
    return hall_x->HIS[2].HIS1;
}

/**
 * @brief load ucnt, vcnt, wcnt and tmrcnt into their read registers.
 *   Hardware auto-clear;
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 */
static inline void hall_load_count_to_read_registers(HALL_Type *hall_x)
{
    hall_x->CR |= HALL_CR_READ_MASK;
}

/**
 * @brief enable hall snap
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 */
static inline void hall_snap_enable(HALL_Type *hall_x)
{
    hall_x->CR |= HALL_CR_SNAPEN_SET(1);
}

/**
 * @brief disable hall snap
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 */
static inline void hall_snap_disable(HALL_Type *hall_x)
{
    hall_x->CR &= ~HALL_CR_SNAPEN_MASK;
}

/**
 * @brief reset all counter and related snapshots assert
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 */
static inline void hall_counter_reset_assert(HALL_Type *hall_x)
{
    hall_x->CR |= HALL_CR_RSTCNT_MASK;
}

/**
 * @brief reset all counter and related snapshots release
 *
 * @param[in] hall_x HALL base address HPM_HALLx(x=0..n)
 */
static inline void hall_counter_reset_release(HALL_Type *hall_x)
{
    hall_x->CR &= ~HALL_CR_RSTCNT_MASK;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_HALL_DRV_H */
