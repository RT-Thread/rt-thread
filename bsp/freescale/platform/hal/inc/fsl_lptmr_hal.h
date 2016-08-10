/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#ifndef __FSL_LPTMR_HAL_H__
#define __FSL_LPTMR_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_LPTMR_COUNT

/*!
 * @addtogroup lptmr_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief LPTMR pin selection, used in pulse counter mode.*/
typedef enum _lptmr_pin_select {
    kLptmrPinSelectInput0 = 0x0U, /*!< Pulse counter input 0 is selected. @internal gui name="Input0"*/
    kLptmrPinSelectInput1 = 0x1U, /*!< Pulse counter input 1 is selected. @internal gui name="Input1"*/
    kLptmrPinSelectInput2 = 0x2U, /*!< Pulse counter input 2 is selected. @internal gui name="Input2"*/
    kLptmrPinSelectInput3 = 0x3U  /*!< Pulse counter input 3 is selected. @internal gui name="Input3"*/
} lptmr_pin_select_t;

/*! @brief LPTMR pin polarity, used in pulse counter mode.*/
typedef enum _lptmr_pin_polarity {
    kLptmrPinPolarityActiveHigh = 0x0U, /*!< Pulse Counter input source is active-high. @internal gui name="Active-high"*/
    kLptmrPinPolarityActiveLow  = 0x1U  /*!< Pulse Counter input source is active-low. @internal gui name="Active-low"*/
} lptmr_pin_polarity_t;

/*! @brief LPTMR timer mode selection.*/
typedef enum _lptmr_timer_mode {
    kLptmrTimerModeTimeCounter  = 0x0U, /*!< Time Counter mode. @internal gui name="Time Counter mode"*/
    kLptmrTimerModePulseCounter = 0x1U  /*!< Pulse Counter mode. @internal gui name="Pulse Counter mode"*/
} lptmr_timer_mode_t;

/*! @brief LPTMR prescaler value.*/
typedef enum _lptmr_prescaler_value {
    kLptmrPrescalerDivide2                      = 0x0U, /*!< Prescaler divide 2, glitch filter invalid. @internal gui name="2/invalid"*/
    kLptmrPrescalerDivide4GlitchFilter2         = 0x1U, /*!< Prescaler divide 4, glitch filter 2. @internal gui name="4/2"*/
    kLptmrPrescalerDivide8GlitchFilter4         = 0x2U, /*!< Prescaler divide 8, glitch filter 4. @internal gui name="8/4"*/
    kLptmrPrescalerDivide16GlitchFilter8        = 0x3U, /*!< Prescaler divide 16, glitch filter 8. @internal gui name="16/8"*/
    kLptmrPrescalerDivide32GlitchFilter16       = 0x4U, /*!< Prescaler divide 32, glitch filter 16. @internal gui name="32/16"*/
    kLptmrPrescalerDivide64GlitchFilter32       = 0x5U, /*!< Prescaler divide 64, glitch filter 32. @internal gui name="64/32"*/
    kLptmrPrescalerDivide128GlitchFilter64      = 0x6U, /*!< Prescaler divide 128, glitch filter 64. @internal gui name="128/64"*/
    kLptmrPrescalerDivide256GlitchFilter128     = 0x7U, /*!< Prescaler divide 256, glitch filter 128. @internal gui name="256/128"*/
    kLptmrPrescalerDivide512GlitchFilter256     = 0x8U, /*!< Prescaler divide 512, glitch filter 256. @internal gui name="512/256"*/
    kLptmrPrescalerDivide1024GlitchFilter512    = 0x9U, /*!< Prescaler divide 1024, glitch filter 512. @internal gui name="1024/512"*/
    kLptmrPrescalerDivide2048GlitchFilter1024   = 0xAU, /*!< Prescaler divide 2048 glitch filter 1024. @internal gui name="2048/1024"*/
    kLptmrPrescalerDivide4096GlitchFilter2048   = 0xBU, /*!< Prescaler divide 4096, glitch filter 2048.@internal gui name="4096/2048"*/
    kLptmrPrescalerDivide8192GlitchFilter4096   = 0xCU, /*!< Prescaler divide 8192, glitch filter 4096. @internal gui name="8192/4096"*/
    kLptmrPrescalerDivide16384GlitchFilter8192  = 0xDU, /*!< Prescaler divide 16384, glitch filter 8192. @internal gui name="16384/8192"*/
    kLptmrPrescalerDivide32768GlitchFilter16384 = 0xEU, /*!< Prescaler divide 32768, glitch filter 16384. @internal gui name="32768/16384"*/
    kLptmrPrescalerDivide65536GlitchFilter32768 = 0xFU  /*!< Prescaler divide 65536, glitch filter 32768. @internal gui name="65535/32768"*/
} lptmr_prescaler_value_t;

/*! @brief LPTMR prescaler/glitch filter clock select. */
typedef enum _lptmr_prescaler_clock_select{
    kLptmrPrescalerClock0 = 0x0U, /*!< Prescaler/glitch filter clock 0 selected. */
    kLptmrPrescalerClock1 = 0x1U, /*!< Prescaler/glitch filter clock 1 selected. */
    kLptmrPrescalerClock2 = 0x2U, /*!< Prescaler/glitch filter clock 2 selected. */
    kLptmrPrescalerClock3 = 0x3U, /*!< Prescaler/glitch filter clock 3 selected. */
} lptmr_prescaler_clock_select_t;

/*! @brief LPTMR status return codes.*/
typedef enum _lptmr_status {
    kStatus_LPTMR_Success                       = 0x0U, /*!< Succeed. */
    kStatus_LPTMR_NotInitlialized               = 0x1U, /*!< LPTMR is not initialized yet. */
    kStatus_LPTMR_NullArgument                  = 0x2U, /*!< Argument is NULL.*/
    kStatus_LPTMR_InvalidPrescalerValue         = 0x3U, /*!< Value 0 is not valid in pulse counter mode. */
    kStatus_LPTMR_InvalidInTimeCounterMode      = 0x4U, /*!< Function cannot be called in time counter mode. */
    kStatus_LPTMR_InvalidInPulseCounterMode     = 0x5U, /*!< Function cannot be called in pulse counter mode. */
    kStatus_LPTMR_TcfNotSet                     = 0x6U, /*!< If LPTMR is enabled, compare register can only altered when TCF is set. */
    kStatus_LPTMR_TimerPeriodUsTooSmall         = 0x7U, /*!< Timer period time is too small for current clock source. */
    kStatus_LPTMR_TimerPeriodUsTooLarge         = 0x8U  /*!< Timer period time is too large for current clock source. */
 } lptmr_status_t;
 
/*! @brief Define LPTMR prescaler user configure. */
typedef struct LptmrPrescalerUserConfig {
    bool prescalerBypass;                                /*!< Set this value will by pass the prescaler or glitch filter. */
    lptmr_prescaler_clock_select_t prescalerClockSelect; /*!< Selects the clock to be used by the LPTMR prescaler/glitch filter. */
    lptmr_prescaler_value_t prescalerValue;              /*!< Configures the size of the prescaler in time counter mode 
                                                              or width of the glitch filter in pulse counter mode. */
} lptmr_prescaler_user_config_t;

/*! @brief Define LPTMR working mode user configure. */
typedef struct LptmrWorkingModeUserConfig {
    lptmr_timer_mode_t timerModeSelect; /*!< Selects the LPTMR working mode: Timer or Pulse Counter. */
    bool freeRunningEnable;             /*!< Enables or disables the LPTMR free running. */
    lptmr_pin_polarity_t pinPolarity;   /*!< Specifies LPTMR pulse input pin polarity. */
    lptmr_pin_select_t pinSelect;       /*!< Specifies LPTMR pulse input pin select. */
} lptmr_working_mode_user_config_t;

/*******************************************************************************
 ** Variables
 *******************************************************************************/

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPTMR HAL.
 * @{
 */

/*!
 * @brief Enables the LPTMR module operation.
 *
 * @param base The LPTMR peripheral base address.
 */
static inline void LPTMR_HAL_Enable(LPTMR_Type * base)
{
    LPTMR_BWR_CSR_TEN(base, (uint8_t)true);
}

/*!
 * @brief Disables the LPTMR module operation.
 *
 * @param base The LPTMR peripheral base address.
 */
static inline void LPTMR_HAL_Disable(LPTMR_Type * base)
{
    LPTMR_BWR_CSR_TEN(base, (uint8_t)false);
}

/*!
 * @brief Clears the LPTMR interrupt flag if set.
 *
 * @param base The LPTMR peripheral base address.
 */
static inline void LPTMR_HAL_ClearIntFlag(LPTMR_Type * base)
{
    LPTMR_BWR_CSR_TCF(base, 1);
}

/*!
 * @brief Returns the current LPTMR interrupt flag.
 *
 * @param base The LPTMR peripheral base address
 * @return State of LPTMR interrupt flag
 * @retval true An interrupt is pending.
 * @retval false No interrupt is pending.
 */
static inline bool LPTMR_HAL_IsIntPending(LPTMR_Type * base)
{
    return ((bool)LPTMR_BRD_CSR_TCF(base));
}

/*!
 * @brief Enables or disables the LPTMR interrupt.
 *
 * @param base The LPTMR peripheral base address
 * @param enable Pass true to enable LPTMR interrupt
 */
static inline void LPTMR_HAL_SetIntCmd(LPTMR_Type * base,  bool enable)
{
    LPTMR_BWR_CSR_TIE(base, enable);
}

/*!
 * @brief Configures the LPTMR working mode.
 *
 * @param base The LPTMR peripheral base address.
 * @param timerMode Specifies LPTMR working mode configure, see #lptmr_working_mode_user_config_t
 */
void LPTMR_HAL_SetTimerWorkingMode(LPTMR_Type * base,  lptmr_working_mode_user_config_t timerMode);

/*!
 * @brief Sets the LPTMR prescaler mode.
 *
 * @param base The LPTMR peripheral base address.
 * @param prescaler_config Specifies LPTMR prescaler configure, see #lptmr_prescaler_user_config_t
 */
void LPTMR_HAL_SetPrescalerMode(LPTMR_Type * base,  lptmr_prescaler_user_config_t prescaler_config);

/*!
 * @brief Sets the LPTMR compare value.
 *
 * @param base The LPTMR peripheral base address.
 * @param compareValue Specifies LPTMR compare value, less than 0xFFFFU
 */
static inline void LPTMR_HAL_SetCompareValue(LPTMR_Type * base,  uint32_t compareValue)
{
    LPTMR_BWR_CMR_COMPARE(base, compareValue);
}

/*!
 * @brief Gets the LPTMR compare value.
 *
 * @param base The LPTMR peripheral base address.
 * @return The LPTMR compare value.
 */
static inline uint32_t LPTMR_HAL_GetCompareValue(LPTMR_Type * base)
{
    return LPTMR_BRD_CMR_COMPARE(base);
}

/*!
 * @brief Gets the LPTMR counter value.
 *
 * @param base The LPTMR peripheral base address.
 * @return Current LPTMR counter value
 */
uint32_t LPTMR_HAL_GetCounterValue(LPTMR_Type * base);

/*!
 * @brief Restores the LPTMR module to reset state.
 *
 * @param base The LPTMR peripheral base address
 */
void LPTMR_HAL_Init(LPTMR_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_LPTMR_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

