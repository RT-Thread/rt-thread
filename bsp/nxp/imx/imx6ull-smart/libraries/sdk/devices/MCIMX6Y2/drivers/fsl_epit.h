/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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

#ifndef _FSL_EPIT_H_
#define _FSL_EPIT_H_

#include "fsl_common.h"

/*!
 * @addtogroup epit
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_EPIT_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0 */
                                                        /*@}*/

/*!
 * @brief List of clock sources
 * @note Actual number of clock sources is SoC dependent
 */
typedef enum _epit_clock_source
{
    kEPIT_ClockSource_Off = 0U,      /*!< EPIT Clock Source Off.*/
    kEPIT_ClockSource_Periph = 1U,   /*!< EPIT Clock Source from Peripheral Clock.*/
    kEPIT_ClockSource_HighFreq = 2U, /*!< EPIT Clock Source from High Frequency Reference Clock.*/
    kEPIT_ClockSource_LowFreq = 3U,  /*!< EPIT Clock Source from Low Frequency Reference Clock.*/
} epit_clock_source_t;

/*!
 * @brief List of output compare operation mode
 */
typedef enum _epit_output_operation_mode
{
    kEPIT_OutputOperation_Disconnected = 0U, /*!< EPIT Output Operation: Disconnected from pad.*/
    kEPIT_OutputOperation_Toggle = 1U,       /*!< EPIT Output Operation: Toggle output pin.*/
    kEPIT_OutputOperation_Clear = 2U,        /*!< EPIT Output Operation: Clear output pin.*/
    kEPIT_OutputOperation_Set = 3U,          /*!< EPIT Output Operation: Set putput pin.*/
} epit_output_operation_mode_t;

/*! @brief List of EPIT interrupts */
typedef enum _epit_interrupt_enable
{
    kEPIT_OutputCompareInterruptEnable = EPIT_CR_OCIEN_MASK, /*!< Output Compare interrupt enable*/
} epit_interrupt_enable_t;

/*! @brief List of EPIT status flags */
typedef enum _epit_status_flags
{
    kEPIT_OutputCompareFlag = EPIT_SR_OCIF_MASK, /*!< Output Compare flag */
} epit_status_flags_t;

/*! @brief Structure to configure the running mode. */
typedef struct _epit_config
{
    epit_clock_source_t clockSource; /*!< clock source for EPIT module. */
    uint32_t divider;                /*!< clock divider (prescaler+1) from clock source to counter. */
    bool enableRunInStop;            /*!< EPIT enabled in stop mode. */
    bool enableRunInWait;            /*!< EPIT enabled in wait mode. */
    bool enableRunInDbg;             /*!< EPIT enabled in debug mode. */
    bool enableCounterOverwrite;     /*!< set timer period results in counter value being overwritten. */
    bool enableFreeRun;   /*!< true: free-running mode, counter will be reset to 0xFFFFFFFF when timer expires;
                               false: set-and-forget mode, counter will be reloaded from set timer periods. */
    bool enableResetMode; /*!< true: counter is reset to timer periods in set-and-forget mode or 0xFFFFFFFF in
                                     free-running mode when enabled;
                               false: counter restores the value that it was disabled when enabled. */
} epit_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Software Reset
 * @{
 */

/*!
 * @brief Software reset of EPIT module.
 *
 * @param base EPIT peripheral base address.
 */
static inline void EPIT_SoftwareReset(EPIT_Type *base)
{
    base->CR |= EPIT_CR_SWR_MASK;
    /* Wait reset finished. */
    while ((base->CR & EPIT_CR_SWR_MASK) == EPIT_CR_SWR_MASK)
    {
    }
}

/* @} */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the EPIT clock and configures the peripheral for a basic operation.
 *
 * This function issues a software reset to reset all the registers to their reset values,
 * except for the EN, ENMOD, STOPEN, WAITEN and DBGEN bits in Control register.
 *
 * @note This API should be called at the beginning of the application using the EPIT driver.
 *
 * @param base EPIT peripheral base address.
 * @param config Pointer to the user configuration structure.
 */
void EPIT_Init(EPIT_Type *base, const epit_config_t *config);

/*!
 * @brief Disables the module and gates the EPIT clock.
 *
 * @param base EPIT peripheral base address.
 */
void EPIT_Deinit(EPIT_Type *base);

/*!
 * @brief Fills in the EPIT configuration structure with default settings.
 *
 * The default values are:
 * @code
 *    config->clockSource = kEPIT_ClockSource_Periph;
 *    config->divider = 1U;
 *    config->enableRunInStop = true;
 *    config->enableRunInWait = true;
 *    config->enableRunInDbg = false;
 *    config->enableCounterOverwrite = false;
 *    config->enableFreeRun = false;
 *    config->enableResetMode = true;
 * @endcode
 * @param config Pointer to the user configuration structure.
 */
void EPIT_GetDefaultConfig(epit_config_t *config);

/*! @}*/

/*!
 * @name Clock source and frequency control
 * @{
 */

/*!
 * @brief Set clock source of EPIT.
 *
 * @param base EPIT peripheral base address.
 * @param source clock source to switch to.
 */
static inline void EPIT_SetClockSource(EPIT_Type *base, epit_clock_source_t source)
{
    base->CR = (base->CR & ~EPIT_CR_CLKSRC_MASK) | EPIT_CR_CLKSRC(source);
}

/*!
 * @brief Set clock divider inside EPIT module.
 *
 * @param base EPIT peripheral base address.
 * @param divider Clock divider in EPIT module (1-4096, divider = prescaler + 1).
 */
static inline void EPIT_SetClockDivider(EPIT_Type *base, uint32_t divider)
{
    assert((divider > 0) && (divider <= (EPIT_CR_PRESCALAR_MASK >> EPIT_CR_PRESCALAR_SHIFT) + 1));
    base->CR = (base->CR & ~EPIT_CR_PRESCALAR_MASK) | EPIT_CR_PRESCALAR(divider - 1);
}

/*!
 * @brief Get clock divider inside EPIT module.
 *
 * @param base EPIT base pointer.
 * @return clock divider in EPIT module (1-4096).
 */
static inline uint32_t EPIT_GetClockDivider(EPIT_Type *base)
{
    return ((base->CR & EPIT_CR_PRESCALAR_MASK) >> EPIT_CR_PRESCALAR_SHIFT) + 1;
}

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Start EPIT timer.
 *
 * @param base EPIT peripheral base address.
 */
static inline void EPIT_StartTimer(EPIT_Type *base)
{
    base->CR |= EPIT_CR_EN_MASK;
}

/*!
 * @brief Stop EPIT timer.
 *
 * @param base EPIT peripheral base address.
 */
static inline void EPIT_StopTimer(EPIT_Type *base)
{
    base->CR &= ~EPIT_CR_EN_MASK;
}

/*! @}*/

/*!
 * @name Read and Write the timer period
 * @{
 */

/*!
 * @brief Sets the timer period in units of count.
 *
 * Timers begin counting down from the value set by this function until it reaches 0, at which point
 * it generates an interrupt and loads this register value again.
 * When enableCounterOverwrite is false, writing a new value to this register does not restart the timer,
 * and the value is loaded after the timer expires. When enableCounterOverwrite is true, the counter
 * will be set immediately and starting counting down from that value.
 *
 * @note User can call the utility macros provided in fsl_common.h to convert to ticks.
 *
 * @param base EPIT peripheral base address.
 * @param ticks   Timer period in units of ticks.
 */
static inline void EPIT_SetTimerPeriod(EPIT_Type *base, uint32_t ticks)
{
    base->LR = ticks;
}

/*!
 * @brief Reads the current timer counting value.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @note User can call the utility macros provided in fsl_common.h to convert ticks to microseconds or milliseconds.
 *
 * @param base EPIT peripheral base address.
 *
 * @return Current timer counting value in ticks.
 */
static inline uint32_t EPIT_GetCurrentTimerCount(EPIT_Type *base)
{
    return base->CNR;
}

/*@}*/

/*!
 * @name Output Signal Control
 * @{
 */

/*!
 * @brief Set EPIT output compare operation mode.
 *
 * @param base EPIT peripheral base address.
 * @param mode EPIT output compare operation mode.
 */
static inline void EPIT_SetOutputOperationMode(EPIT_Type *base, epit_output_operation_mode_t mode)
{
    base->CR = (base->CR & ~EPIT_CR_OM_MASK) | EPIT_CR_OM(mode);
}

/*!
 * @brief Set EPIT output compare value.
 *
 * @param base EPIT peripheral base address.
 * @param value EPIT output compare value.
 */
static inline void EPIT_SetOutputCompareValue(EPIT_Type *base, uint32_t value)
{
    base->CMPR = value;
}

/*@}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected EPIT interrupts.
 *
 * @param base EPIT peripheral base address.
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::epit_interrupt_enable_t
 */
static inline void EPIT_EnableInterrupts(EPIT_Type *base, uint32_t mask)
{
    base->CR |= mask;
}

/*!
 * @brief Disables the selected EPIT interrupts.
 *
 * @param base    EPIT peripheral base address
 * @param mask    The interrupts to disable. This is a logical OR of members of the
 *                enumeration ::epit_interrupt_enable_t
 */
static inline void EPIT_DisableInterrupts(EPIT_Type *base, uint32_t mask)
{
    base->CR &= ~mask;
}

/*!
 * @brief Gets the enabled EPIT interrupts.
 *
 * @param base    EPIT peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::epit_interrupt_enable_t
 */
static inline uint32_t EPIT_GetEnabledInterrupts(EPIT_Type *base)
{
    return (base->CR & EPIT_CR_OCIEN_MASK);
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the EPIT status flags.
 *
 * @param base    EPIT peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::epit_status_flags_t
 */
static inline uint32_t EPIT_GetStatusFlags(EPIT_Type *base)
{
    return (base->SR & EPIT_SR_OCIF_MASK);
}

/*!
 * @brief  Clears the EPIT status flags.
 *
 * @param base    EPIT peripheral base address
 * @param mask    The status flags to clear. This is a logical OR of members of the
 *                enumeration ::epit_status_flags_t
 */
static inline void EPIT_ClearStatusFlags(EPIT_Type *base, uint32_t mask)
{
    base->SR = mask;
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /*_FSL_EPIT_H_*/
