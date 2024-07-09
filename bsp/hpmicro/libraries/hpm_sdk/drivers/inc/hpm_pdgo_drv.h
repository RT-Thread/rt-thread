/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PDGO_DRV_H
#define HPM_PDGO_DRV_H

#include "hpm_common.h"
#include "hpm_pdgo_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DGO_GPR_WORD_COUNT (4U)                              /*!< DGO GPR register count */
#define DGO_WAKEUP_COUNTER_TICKS_PER_SEC   (32768UL)         /*!< DGO Wakeup Counter frequency */
#define DGO_TURNOFF_COUNTER_TICKS_PER_SEC   (24000000UL)     /*!< DGO Turn-off counter frequency */
#define DGO_WAKEUP_TICK_IN_US  (1000000UL / DGO_WAKEUP_COUNTER_TICKS_PER_SEC)
#define DGO_TURNOFF_TICKS_PER_US (DGO_TURNOFF_COUNTER_TICKS_PER_SEC / 1000000UL)

/**
*
* @brief PDGO driver APIs
* @defgroup pdgo_interface DGO driver APIs
* @ingroup pdgo_interfaces
* @{
*
*/

/**
 * @brief Set DGO turn-off counter
 * @param [in] ptr DGO base address
 * @param [in] counter Turn-off counter value. Clock source is 32K
 */
static inline void pdgo_set_turnoff_counter(PDGO_Type *ptr, uint32_t counter)
{
    ptr->DGO_TURNOFF = counter;
}

/**
 * @brief Enable Software Wake-up feature on DGO
 * @param [in] ptr DGO base address
 */
static inline void pdgo_enable_software_wakeup(PDGO_Type *ptr)
{
    ptr->DGO_CTR1 |= PDGO_DGO_CTR1_WAKEUP_EN_MASK;
}

/**
 * @brief Disable Software Wake-up feature on DGO
 * @param [in] ptr DGO base address
 */
static inline void pdgo_disable_software_wakeup(PDGO_Type *ptr)
{
    ptr->DGO_CTR1 &= ~PDGO_DGO_CTR1_WAKEUP_EN_MASK;
}

/**
 * @brief Set DGO to one-shot wakeup mode
 * @param [in] ptr DGO base address
 */
static inline void pdgo_enable_oneshot_wakeup(PDGO_Type *ptr)
{
    ptr->DGO_CTR1 &= ~PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_MASK;
}

/**
 * @brief Enable DGO register retention mode
 * @param [in] ptr DGO base address
 */
static inline void pdgo_enable_retention_mode(PDGO_Type *ptr)
{
    ptr->DGO_CTR1 |= PDGO_DGO_CTR0_RETENTION_MASK;
}

/**
 * @brief Check whether the DGO retention mode is enabled or not
 * @param [in] ptr DGO base address
 *
 * @retval true Retention mode is enabled
 * @retval false Retention mode is disabled
 */
static inline bool pdgo_is_retention_mode_enabled(PDGO_Type *ptr)
{
    return ((ptr->DGO_CTR1 & PDGO_DGO_CTR0_RETENTION_MASK) != 0U);
}

/**
 * @brief Disable DGO register retention mode
 * @param [in] ptr DGO base address
 */
static inline void pdgo_disable_retention_mode(PDGO_Type *ptr)
{
    ptr->DGO_CTR1 &= ~PDGO_DGO_CTR0_RETENTION_MASK;
}

/**
 * @brief Set DGO to automatic wakeup mode
 * @param [in] ptr DGO base address
 */
static inline void pdgo_enable_auto_wakeup(PDGO_Type *ptr)
{
    ptr->DGO_CTR1 |= PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_MASK;
}

#if defined(PDGO_SUPPORT_SYS_WAKEUP_STATUS) && (PDGO_SUPPORT_SYS_WAKEUP_STATUS == 1)
/**
 * @brief Check whether DGO is waked up by System/Software
 * @param [in] ptr DGO base address
 *
 * @retval true if DGO is waked up by System/Software
 */
static inline bool pdgo_is_system_wakeup(PDGO_Type *ptr)
{
    return ((ptr->DGO_CTR1 & PDGO_DGO_CTR1_SYS_WAKEUP_STATUS_MASK) != 0U);
}
#endif

/**
 * @brief Check whether DGO is waked up by Wake-up/Reset Pin
 * @param [in] ptr DGO base address
 *
 * @retval true if DGO is waked up by Wakeup/Reset pin
 */
static inline bool pdgo_is_pin_wakeup(PDGO_Type *ptr)
{
    return ((ptr->DGO_CTR1 & PDGO_DGO_CTR1_PIN_WAKEUP_STATUS_MASK) != 0U);
}


/**
 * @brief Check whether Auto wake-up is enabled
 * @param [in] ptr DGO base address
 *
 * @retval true - Auto wake-up is enabled
 * @retval false - Auto wake-up is disabled
 */
static inline bool pdgo_is_auto_wakeup_enabled(PDGO_Type *ptr)
{
    return ((ptr->DGO_CTR1 & PDGO_DGO_CTR1_AOTO_SYS_WAKEUP_MASK) != 0U);
}

/**
 * @brief Enable pull-up resistor for Reset Pin
 * [in] ptr DGO base address
 */
static inline void pdgo_enable_pullup_resistor_for_reset_pin(PDGO_Type *ptr)
{
    ptr->DGO_CTR2 &= ~PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_MASK;
}

/**
 * @brief Disable pull-up resistor for Reset Pin
 * [in] ptr DGO base address
 */
static inline void pdgo_disable_pullup_resistor_for_reset_pin(PDGO_Type *ptr)
{
    ptr->DGO_CTR2 |= PDGO_DGO_CTR2_RESETN_PULLUP_DISABLE_MASK;
}

/**
 * Enable pull-down resistor for Wakeup pin
 * [in] ptr DGO base address
 */
static inline void pdgo_enable_pulldown_resistor_for_wakeup_pin(PDGO_Type *ptr)
{
    ptr->DGO_CTR2 &= ~PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_MASK;
}

/**
 * Disable pull-down resistor for Wakeup pin
 * [in] ptr DGO base address
 */
static inline void pdgo_disable_pulldown_resistor_for_wakeup_pin(PDGO_Type *ptr)
{
    ptr->DGO_CTR2 |= PDGO_DGO_CTR2_WAKEUP_PULLDN_DISABLE_MASK;
}

/**
 * @brief Set DGO wakeup counter
 * @param [in] ptr DGO base address
 * @param [in] wakeup_ctr Wakeup counter value. clock source is 32K
 */
static inline void pdgo_set_wakeup_counter(PDGO_Type *ptr, uint32_t wakeup_ctr)
{
    ptr->DGO_CTR3 = wakeup_ctr;
}

/**
 * @brief Get DGO wakeup counter value
 * @param [in] ptr DGO base address
 *
 * @return DGO wakeup counter value
 */
static inline uint32_t pdgo_get_wakeup_counter(PDGO_Type *ptr)
{
    return ptr->DGO_CTR3;
}

/**
 * @brief Write data to DGO GPR register
 * @param [in] ptr DGO base address
 * @param [in] index GPR register index
 * @param [in] content Data to be written to DGO GPR register
 */
static inline void pdgo_write_gpr(PDGO_Type *ptr, uint32_t index, uint32_t content)
{
    if (index < DGO_GPR_WORD_COUNT) {
        *(volatile uint32_t *) ((uint32_t) &ptr->DGO_GPR00 + index * 4) = content;
    }
}

/**
 * @brief Read data from DGO GPR register
 * @param [in] ptr DGO base address
 * @param [in] index GPR register index
 *
 * @return DGO GPR register value
 */
static inline uint32_t pdgo_read_gpr(PDGO_Type *ptr, uint32_t index)
{
    uint32_t reg_val = 0;
    if (index < DGO_GPR_WORD_COUNT) {
        reg_val = *(volatile uint32_t *) ((uint32_t) &ptr->DGO_GPR00 + index * 4);
    }
    return reg_val;
}

/**
 * @brief Convert the microsecond to DGO Wake-up counter value
 * @param [in] us microsecond to be converted
 *
 * @return Converted DGO Wake-up counter value
 */
static inline uint32_t pdgo_get_wakeup_counter_from_us(uint32_t us)
{
    return (us + DGO_WAKEUP_TICK_IN_US - 1U) / DGO_WAKEUP_TICK_IN_US;
}

/**
 * @brief Convert the DGO Wake-up counter to microseconds
 * @param [in] counter  DGO counter
 *
 * @return Converted microseconds
 */
static inline uint32_t pdgo_get_us_from_wakeup_counter(uint32_t counter)
{
    return (counter * DGO_WAKEUP_TICK_IN_US);
}

/**
 * @brief Convert the microsecond to DGO Turn-off counter value
 * @param [in] us microsecond to be converted
 *
 * @return Converted DGO Turn-off counter value
 */
static inline uint32_t pdgo_get_turnoff_counter_from_us(uint32_t us)
{
    return (us * DGO_TURNOFF_TICKS_PER_US);
}

/**
 * @brief Convert the DGO Turn-off counter to microseconds
 * @param [in] counter  DGO Turn-off counter
 *
 * @return Converted microseconds
 */
static inline uint32_t pdgo_get_us_from_turnoff_counter(uint32_t counter)
{
    return (counter + DGO_TURNOFF_TICKS_PER_US - 1U) / DGO_TURNOFF_TICKS_PER_US;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* HPM_DGO_DRV_H */
