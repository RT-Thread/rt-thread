/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_RIT_H_
#define _FSL_RIT_H_

#include "fsl_common.h"

/*!
 * @addtogroup rit
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_RIT_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0 */
/*@}*/

/*! @brief List of RIT status flags */
typedef enum _rit_status_flags
{
    kRIT_TimerFlag = RIT_CTRL_RITINT_MASK, /*!< Timer flag */
} rit_status_flags_t;

/*!
 * @brief RIT config structure
 *
 * This structure holds the configuration settings for the RIT peripheral. To initialize this
 * structure to reasonable defaults, call the RIT_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _rit_config
{
    bool enableRunInDebug; /*!< true: The timer is halted when the processor is halted for debugging.; false: Debug has
                              no effect on the timer operation. */
} rit_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the RIT clock, enables the RIT module, and configures the peripheral for basic operations.
 *
 * @note This API should be called at the beginning of the application using the RIT driver.
 *
 * @param base   RIT peripheral base address
 * @param config Pointer to the user's RIT config structure
 */
void RIT_Init(RIT_Type *base, const rit_config_t *config);

/*!
 * @brief Gates the RIT clock and disables the RIT module.
 *
 * @param base RIT peripheral base address
 */
void RIT_Deinit(RIT_Type *base);

/*!
 * @brief Fills in the RIT configuration structure with the default settings.
 *
 * The default values are as follows.
 * @code
 *     config->enableRunInDebug = false;
 * @endcode
 * @param config Pointer to the onfiguration structure.
 */
void RIT_GetDefaultConfig(rit_config_t *config);

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the RIT status flags.
 *
 * @param base    RIT peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::rit_status_flags_t
 */
static inline uint32_t RIT_GetStatusFlags(RIT_Type *base)
{
    return (base->CTRL);
}

/*!
 * @brief  Clears the RIT status flags.
 *
 * @param base    RIT peripheral base address
 * @param mask    The status flags to clear. This is a logical OR of members of the
 *                enumeration ::rit_status_flags_t
 */
static inline void RIT_ClearStatusFlags(RIT_Type *base, uint32_t mask)
{
    base->CTRL |= mask;
}

/*! @}*/

/*!
 * @name Read and Write the timer period
 * @{
 */

/*!
 * @brief Sets the timer period in units of count.
 *
 * Timers begin counting from the value set by this function until it XXXXXXX,
 * then it counting the value again.
 * Software must stop the counter before reloading it with a new value..
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * @param base    RIT peripheral base address
 * @param count   Timer period in units of ticks
 */
void RIT_SetTimerCompare(RIT_Type *base, uint64_t count);

/*!
 * @brief Sets the mask bit of count compare.
 *
 * Timers begin counting from the value set by this function until it XXXXXXX,
 * then it counting the value again.
 * Software must stop the counter before reloading it with a new value..
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * @param base    RIT peripheral base address
 * @param count   Timer period in units of ticks
 */
void RIT_SetMaskBit(RIT_Type *base, uint64_t count);

/*!
 * @brief Reads the current timer counting value of compare register.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    RIT peripheral base address
 *
 * @return Current timer counting value in ticks
 */
uint64_t RIT_GetCompareTimerCount(RIT_Type *base);

/*!
 * @brief Reads the current timer counting value of counter register.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    RIT peripheral base address
 *
 * @return Current timer counting value in ticks
 */
uint64_t RIT_GetCounterTimerCount(RIT_Type *base);

/*!
 * @brief Reads the current timer counting value of mask register.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @note Users can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    RIT peripheral base address
 *
 * @return Current timer counting value in ticks
 */
uint64_t RIT_GetMaskTimerCount(RIT_Type *base);

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the timer counting.
 *
 * After calling this function, timers load initial value(0U), count up to desired value or over-flow
 * then the counter will count up again. Each time a timer reaches desired value,
 * it generates a XXXXXXX and sets XXXXXXX.
 *
 * @param base    RIT peripheral base address
 */
static inline void RIT_StartTimer(RIT_Type *base)
{
    base->CTRL |= RIT_CTRL_RITEN_MASK;
}

/*!
 * @brief Stops the timer counting.
 *
 * This function stop timer counting. Timer reload their new value
 * after the next time they call the RIT_StartTimer.
 *
 * @param base    RIT peripheral base address
 * @param channel Timer channel number.
 */
static inline void RIT_StopTimer(RIT_Type *base)
{
    /* Disable RIT timers */
    base->CTRL &= ~RIT_CTRL_RITEN_MASK;
}

/*! @}*/

static inline void RIT_ClearCounter(RIT_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RIT_CTRL_RITENCLR_MASK;
    }
    else
    {
        base->CTRL &= ~RIT_CTRL_RITENCLR_MASK;
    }
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_RIT_H_ */
