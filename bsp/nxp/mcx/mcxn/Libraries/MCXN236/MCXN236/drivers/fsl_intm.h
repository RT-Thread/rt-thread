/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_INTM_H_
#define FSL_INTM_H_

#include "fsl_common.h"

/*!
 * @addtogroup intm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief INTM driver version. */
#define FSL_INTM_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*! @brief Interrupt monitors. */
typedef enum _intm_monitor
{
    kINTM_Monitor1 = 0U,
    kINTM_Monitor2,
    kINTM_Monitor3,
    kINTM_Monitor4
} intm_monitor_t;

/*! @brief INTM  interrupt source configuration structure. */
typedef struct _intm_monitor_config
{
    uint32_t maxtimer;   /*!< Set the maximum timer */
    IRQn_Type irqnumber; /*!< Select the interrupt request number to monitor. */
} intm_monitor_config_t;

/*! @brief INTM configuration structure. */
typedef struct _intm_config
{
    intm_monitor_config_t intm[FSL_FEATURE_INTM_MONITOR_COUNT]; /*! Interrupt source monitor config.*/
    bool enable; /*!< enables the cycle count timer on a monitored interrupt request for comparison to the latency
                    register. */
} intm_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief  Fill in the INTM config struct with the default settings
 *
 * The default values are:
 * @code
 *     config[0].irqnumber = NotAvail_IRQn;
 *     config[0].maxtimer = 1000U;
 *     config[1].irqnumber = NotAvail_IRQn;
 *     config[1].maxtimer = 1000U;
 *     config[2].irqnumber = NotAvail_IRQn;
 *     config[2].maxtimer = 1000U;
 *     config[3].irqnumber = NotAvail_IRQn;
 *     config[3].maxtimer = 1000U;
 *     config->enable = false;
 * @endcode
 * @param config Pointer to user's INTM config structure.
 */
void INTM_GetDefaultConfig(intm_config_t *config);

/*!
 * @brief Ungates the INTM clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the INTM driver.
 *
 * @param base      INTM peripheral base address
 * @param config    Pointer to user's INTM config structure.
 */
void INTM_Init(INTM_Type *base, const intm_config_t *config);

/*!
 * @brief Disables the INTM module.
 *
 * @param base INTM peripheral base address
 */
void INTM_Deinit(INTM_Type *base);

/*!
 * @brief Enable the cycle count timer mode.
 *
 * Monitor mode enables the cycle count timer on a monitored interrupt request for comparison to the latency register.
 *
 * @param base INTM peripheral base address.
 * @param enable Enable the cycle count or not.
 */
static inline void INTM_EnableCycleCount(INTM_Type *base, bool enable)
{
    if (enable)
    {
        base->INTM_MM |= INTM_INTM_MM_MM_MASK;
    }
    else
    {
        base->INTM_MM &= ~INTM_INTM_MM_MM_MASK;
    }
}

/*!
 * @brief Interrupt Acknowledge.
 *
 * Call this function in ISR to acknowledge interrupt.
 *
 * @param base INTM peripheral base address.
 * @param irq Handle interrupt number.
 */
static inline void INTM_AckIrq(INTM_Type *base, IRQn_Type irq)
{
    assert(((uint32_t)irq) < (uint32_t)NUMBER_OF_INT_VECTORS);

    base->INTM_IACK = (uint32_t)irq;
}

/*!
 * @brief Interrupt Request Select.
 *
 * This function is used to set the interrupt request number to monitor or check.
 *
 * @param base INTM peripheral base address.
 * @param intms Programmable interrupt monitors.
 * @param irq  Interrupt request number to monitor.
 *
 * @return Select the interrupt request number to monitor.
 */
static inline void INTM_SetInterruptRequestNumber(INTM_Type *base, intm_monitor_t intms, IRQn_Type irq)
{
    assert(((uint32_t)irq) < (uint32_t)NUMBER_OF_INT_VECTORS);

    base->MON[intms].INTM_IRQSEL = INTM_MON_INTM_IRQSEL_IRQ(irq);
}

/*!
 * @brief Set the maximum count time.
 *
 * This function is to set the maximum time from interrupt generation to confirmation.
 *
 * @param base INTM peripheral base address.
 * @param intms Programmable interrupt monitors.
 * @param count Timer maximum count.
 */
static inline void INTM_SetMaxTime(INTM_Type *base, intm_monitor_t intms, uint32_t count)
{
    assert((count < 0xFFFFFDU) && (count > 0U));

    base->MON[intms].INTM_LATENCY = INTM_MON_INTM_LATENCY_LAT(count);
}

/*!
 * @brief Clear the timer period in units of count.
 *
 * This function is used to clear the INTM_TIMERa register.
 *
 * @param base INTM peripheral base address.
 * @param intms Programmable interrupt monitors.
 */
static inline void INTM_ClearTimeCount(INTM_Type *base, intm_monitor_t intms)
{
    base->MON[intms].INTM_TIMER &= ~INTM_MON_INTM_TIMER_TIMER_MASK;
}

/*!
 * @brief Gets the timer period in units of count.
 *
 * This function is used to get the number of INTM clock cycles from interrupt request to confirmation interrupt
 * processing. If this number exceeds the set maximum time, will be an error signal.
 *
 * @param base INTM peripheral base address.
 * @param intms Programmable interrupt monitors.
 */
static inline uint32_t INTM_GetTimeCount(INTM_Type *base, intm_monitor_t intms)
{
    return base->MON[intms].INTM_TIMER;
}

/*!
 * @brief Interrupt monitor status.
 *
 * This function indicates whether the INTM_TIMERa value has exceeded the INTM_LATENCYa value.
 * If any interrupt source in INTM_TIMERa exceeds the programmed delay value, the monitor state
 * can be cleared by calling the INTM_ClearTimeCount() API to clear the corresponding INTM_TIMERa register.
 *
 * @param base INTM peripheral base address.
 * @param intms Programmable interrupt monitors.
 *
 * @return Whether INTM_TIMER value has exceeded INTM_LATENCY value.
 *         false:INTM_TIMER value has not exceeded the INTM_LATENCY value;
 *         true:INTM_TIMER value has exceeded the INTM_LATENCY value.
 */
static inline bool INTM_GetStatusFlags(INTM_Type *base, intm_monitor_t intms)
{
    return ((base->MON[intms].INTM_STATUS & INTM_MON_INTM_STATUS_STATUS_MASK) != 0U);
}

/*! @} */
#endif /* FSL_INTM_H_*/
