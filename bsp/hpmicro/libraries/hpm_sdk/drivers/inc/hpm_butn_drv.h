/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BUTN_DRV_H
#define HPM_BUTN_DRV_H

#include "hpm_common.h"
#include "hpm_butn_regs.h"

/**
 *
 * @brief BUTN driver APIs
 * @defgroup butn_interface BUTN driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

#define BUTN_EVENT_POWER_PRESSED (BUTN_BTN_STATUS_PBTN_SET(1))
#define BUTN_EVENT_POWER_PRESSED_HOLD_0_5_S (BUTN_BTN_STATUS_PBTN_SET(2))
#define BUTN_EVENT_POWER_PRESSED_HOLD_8_S (BUTN_BTN_STATUS_PBTN_SET(4))
#define BUTN_EVENT_POWER_PRESSED_HOLD_16_S (BUTN_BTN_STATUS_PBTN_SET(8))

#define BUTN_EVENT_WAKE_PRESSED (BUTN_BTN_STATUS_WBTN_SET(1))
#define BUTN_EVENT_WAKE_PRESSED_HOLD_0_5_S (BUTN_BTN_STATUS_WBTN_SET(2))
#define BUTN_EVENT_WAKE_PRESSED_HOLD_8_S (BUTN_BTN_STATUS_WBTN_SET(4))
#define BUTN_EVENT_WAKE_PRESSED_HOLD_16_S (BUTN_BTN_STATUS_WBTN_SET(8))

#define BUTN_EVENT_WAKE_POWER_PRESSED (BUTN_BTN_STATUS_DBTN_SET(1))
#define BUTN_EVENT_WAKE_POWER_PRESSED_HOLD_0_5_S  (BUTN_BTN_STATUS_DBTN_SET(2))
#define BUTN_EVENT_WAKE_POWER_PRESSED_HOLD_8_S  (BUTN_BTN_STATUS_DBTN_SET(4))
#define BUTN_EVENT_WAKE_POWER_PRESSED_HOLD_16_S  (BUTN_BTN_STATUS_DBTN_SET(8))

#define BUTN_EVENT_POWER_CLICKED (BUTN_BTN_STATUS_PCLICK_SET(1))
#define BUTN_EVENT_POWER_CLICKED_X2 (BUTN_BTN_STATUS_PCLICK_SET(2))
#define BUTN_EVENT_POWER_CLICKED_X3 (BUTN_BTN_STATUS_PCLICK_SET(4))

#define BUTN_EVENT_POWER_CLICKED_WAKE_HELD (BUTN_BTN_STATUS_XPCLICK_SET(1))
#define BUTN_EVENT_POWER_CLICKED_X2_WAKE_HELD (BUTN_BTN_STATUS_XPCLICK_SET(2))
#define BUTN_EVENT_POWER_CLICKED_X3_WAKE_HELD (BUTN_BTN_STATUS_XPCLICK_SET(4))

#define BUTN_EVENT_WAKE_CLICKED (BUTN_BTN_STATUS_WCLICK_SET(1))
#define BUTN_EVENT_WAKE_CLICKED_X2 (BUTN_BTN_STATUS_WCLICK_SET(2))
#define BUTN_EVENT_WAKE_CLICKED_X3 (BUTN_BTN_STATUS_WCLICK_SET(4))

#define BUTN_EVENT_WAKE_CLICKED_POWER_HELD (BUTN_BTN_STATUS_XWCLICK_SET(1))
#define BUTN_EVENT_WAKE_CLICKED_X2_POWER_HELD (BUTN_BTN_STATUS_XWCLICK_SET(2))
#define BUTN_EVENT_WAKE_CLICKED_X3_POWER_HELD (BUTN_BTN_STATUS_XWCLICK_SET(4))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get status
 *
 * @param[in] ptr BUTN base address
 * @retval status mask in 32 bits, please refer to BUTN_EVENT_* macros
 */
static inline uint32_t butn_get_status(BUTN_Type *ptr)
{
    return ptr->BTN_STATUS;
}

/**
 * @brief Enable interrupt with mask
 *
 * @param[in] ptr BUTN base address
 * @param[in] mask Mask of interrupts to be enabled, please refer to BUTN_EVENT_* macros
 */
static inline void butn_enable_irq(BUTN_Type *ptr, uint32_t mask)
{
    ptr->BTN_IRQ_MASK |= mask;
}

/**
 * @brief Disable interrupt with mask
 *
 * @param[in] ptr BUTN base address
 * @param[in] mask Mask of interrupts to be disabled, please refer to BUTN_EVENT_* macros
 */
static inline void butn_disable_irq(BUTN_Type *ptr, uint32_t mask)
{
    ptr->BTN_IRQ_MASK &= ~mask;
}

/**
 * @brief Set intense of PLED and RLED/WLED
 *
 * @param[in] ptr BUTN base address
 * @param[in] intense Intense value (0~15)
 */
static inline void butn_set_intense(BUTN_Type *ptr, uint8_t intense)
{
    ptr->LED_INTENSE = BUTN_LED_INTENSE_PLED_SET(intense)
        | BUTN_LED_INTENSE_RLED_SET(intense);
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BUTN_DRV_H */
