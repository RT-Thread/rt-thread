/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_WAKETIMER_H_
#define FSL_WAKETIMER_H_

#include "fsl_common.h"

/*!
 * @addtogroup waketimer
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief WAKETIMER driver version. */
#define FSL_WAKETIMER_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*! @} */

/*!
 * @brief WAKETIMER status flags.
 */
enum _waketimer_status_flags
{
    kWAKETIMER_WakeFlag =
        (WAKETIMER_WAKE_TIMER_CTRL_WAKE_FLAG_MASK), /*!< Wake Timer Status Flag, sets wake timer has timed out. */
};

/*!
 * @brief Define interrupt switchers of the module.
 */
enum _waketimer_interrupt_enable
{
    kWAKETIMER_WakeInterruptEnable = WAKETIMER_WAKE_TIMER_CTRL_INTR_EN_MASK, /*!< Generate interrupt
                                                                       requests when WAKE_FLAG is asserted. */
};

/*! @brief waketimer callback function. */
typedef void (*waketimer_callback_t)(void);

/*!
 * @brief WAKETIMER configuration structure
 *
 * This structure holds the configuration settings for the WAKETIMER peripheral. To initialize this
 * structure to reasonable defaults, call the WAKETIMER_GetDefaultConfig() function and pass a
 * pointer to the configuration structure instance.
 *
 * The configuration structure can be made constant so as to reside in flash.
 */
typedef struct _waketimer_config
{
    bool enableOSCDivide;          /*!< true: Enable OSC Divide.
                                        false: Disable OSC Divide. */
    bool enableInterrupt;          /*!< true: Enable interrupt.
                                        false: Disable interrupt. */
    waketimer_callback_t callback; /*!< timer countdown callback. */
} waketimer_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes an WAKETIMER
 *
 * This function initializes the WAKETIMER.
 *
 * @param base WAKETIMER peripheral base address.
 * @param config Pointer to the user configuration structure.
 */
void WAKETIMER_Init(WAKETIMER_Type *base, const waketimer_config_t *config);

/*!
 * @brief Deinitializes a WAKETIMER instance.
 *
 * This function deinitialize the WAKETIMER.
 *
 * @param base WAKETIMER peripheral base address.
 */
void WAKETIMER_Deinit(WAKETIMER_Type *base);

/*!
 * @brief  Fills in the WAKETIMER configuration structure with the default settings.
 *
 * The default values are:
 * @code
 *  config->enableInterrupt = true;
 *  config->enableOSCDivide = true;
 *  config->callback        = NULL;
 * @endcode
 * @param config Pointer to the user configuration structure.
 */
void WAKETIMER_GetDefaultConfig(waketimer_config_t *config);

/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected WAKETIMER interrupts.
 *
 * @param base WAKETIMER peripheral base address
 * @param mask Mask value for interrupt events. See to #_waketimer_interrupt_enable
 */
void WAKETIMER_EnableInterrupts(WAKETIMER_Type *base, uint32_t mask);

/*!
 * @brief Enables the selected WAKETIMER interrupts.
 *
 * @param base WAKETIMER peripheral base address
 * @param mask Mask value for interrupt events. See to #_waketimer_interrupt_enable
 */
void WAKETIMER_DisableInterrupts(WAKETIMER_Type *base, uint32_t mask);

/*!
 * @brief Clear Status Interrupt Flag.
 *
 * This clears intrrupt status flag.
 * Currently, only match interrupt flag can be cleared.
 *
 * @param base WAKETIMER peripheral base address.
 * @param mask Mask value for flags to be cleared. See to #_waketimer_status_flags.
 * @return none
 */
void WAKETIMER_ClearStatusFlags(WAKETIMER_Type *base, uint32_t mask);

/*!
 * @brief Receive noticification when waketime countdown.
 *
 * If the interrupt for the waketime countdown is enabled, then a callback can be registered
 * which will be invoked when the event is triggered
 *
 * @param base     WAKETIMER peripheral base address
 * @param callback Function to invoke when the event is triggered
 */
void WAKETIMER_SetCallback(WAKETIMER_Type *base, waketimer_callback_t callback);

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Halt and clear timer counter.
 *
 * This halt and clear timer counter.
 *
 * @param base WAKETIMER peripheral base address.
 * @return none
 */
static inline void WAKETIMER_HaltTimer(WAKETIMER_Type *base)
{
    base->WAKE_TIMER_CTRL |= WAKETIMER_WAKE_TIMER_CTRL_CLR_WAKE_TIMER_MASK;
}

/*!
 * @brief Set timer counter.
 *
 * This set the timer counter and start the timer countdown.
 *
 * @param base WAKETIMER peripheral base address.
 * @param value countdown value.
 * @return none
 */
static inline void WAKETIMER_StartTimer(WAKETIMER_Type *base, uint32_t value)
{
    base->WAKE_TIMER_CNT = value;
}

/*!
 * @brief Get current timer count value from WAKETIMER.
 *
 * This function will get a decimal timer count value.
 * The RAW value of timer count is gray code format, will be translated to decimal data internally.
 *
 * @param base   WAKETIMER peripheral base address.
 * @return       Value of WAKETIMER which will be formated to decimal value.
 */
uint32_t WAKETIMER_GetCurrentTimerValue(WAKETIMER_Type *base);

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_WAKETIMER_H_ */
