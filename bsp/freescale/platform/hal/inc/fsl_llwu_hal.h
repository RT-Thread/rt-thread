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
#if !defined(__FSL_LLWU_HAL_H__)
#define __FSL_LLWU_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_LLWU_COUNT

/*! @addtogroup llwu_hal*/
/*! @{*/

/*! @file fsl_llwu_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief External input pin control modes */
typedef enum _llwu_external_pin_modes {
    kLlwuExternalPinDisabled,          /*!< Pin disabled as wakeup input */
    kLlwuExternalPinRisingEdge,        /*!< Pin enabled with rising edge detection */
    kLlwuExternalPinFallingEdge,       /*!< Pin enabled with falling edge detection */
    kLlwuExternalPinChangeDetect       /*!< Pin enabled with any change detection */
} llwu_external_pin_modes_t;

/*! @brief Digital filter control modes */
typedef enum _llwu_filter_modes {
    kLlwuFilterDisabled,            /*!< Filter disabled  */
    kLlwuFilterPosEdgeDetect,       /*!< Filter positive edge detection */
    kLlwuFilterNegEdgeDetect,       /*!< Filter negative edge detection */
    kLlwuFilterAnyEdgeDetect        /*!< Filter any edge detection */
} llwu_filter_modes_t;

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*! @brief LLWU external wakeup pin. */
typedef enum _llwu_wakeup_pin {
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN0
    kLlwuWakeupPin0   = 0U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN1
    kLlwuWakeupPin1   = 1U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN2
    kLlwuWakeupPin2   = 2U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN3
    kLlwuWakeupPin3   = 3U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN4
    kLlwuWakeupPin4   = 4U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN5
    kLlwuWakeupPin5   = 5U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN6
    kLlwuWakeupPin6   = 6U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN7
    kLlwuWakeupPin7   = 7U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN8
    kLlwuWakeupPin8   = 8U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN9
    kLlwuWakeupPin9   = 9U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN10
    kLlwuWakeupPin10  = 10U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN11
    kLlwuWakeupPin11  = 11U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN12
    kLlwuWakeupPin12  = 12U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN13
    kLlwuWakeupPin13  = 13U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN14
    kLlwuWakeupPin14  = 14U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN15
    kLlwuWakeupPin15  = 15U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN16
    kLlwuWakeupPin16   = 16U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN17
    kLlwuWakeupPin17   = 17U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN18
    kLlwuWakeupPin18   = 18U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN19
    kLlwuWakeupPin19   = 19U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN20
    kLlwuWakeupPin20   = 20U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN21
    kLlwuWakeupPin21   = 21U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN22
    kLlwuWakeupPin22   = 22U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN23
    kLlwuWakeupPin23   = 23U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN24
    kLlwuWakeupPin24   = 24U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN25
    kLlwuWakeupPin25   = 25U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN26
    kLlwuWakeupPin26   = 26U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN27
    kLlwuWakeupPin27   = 27U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN28
    kLlwuWakeupPin28   = 28U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN29
    kLlwuWakeupPin29   = 29U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN30
    kLlwuWakeupPin30   = 30U,
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN31
    kLlwuWakeupPin31   = 31U
#endif
} llwu_wakeup_pin_t;
#endif

#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
/*! @brief LLWU wakeup module. */
typedef enum _llwu_wakeup_module {
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE0
    kLlwuWakeupModule0  = 0U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE1
    kLlwuWakeupModule1  = 1U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE2
    kLlwuWakeupModule2  = 2U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE3
    kLlwuWakeupModule3  = 3U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE4
    kLlwuWakeupModule4  = 4U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE5
    kLlwuWakeupModule5  = 5U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE6
    kLlwuWakeupModule6  = 6U,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE7
    kLlwuWakeupModule7  = 7U
#endif
} llwu_wakeup_module_t;
#endif

/*! @brief External input pin filter control structure */
typedef struct _llwu_external_pin_filter_mode {
    llwu_filter_modes_t         filterMode;         /*!< Filter mode */
    llwu_wakeup_pin_t           pinNumber;          /*!< Pin number */
} llwu_external_pin_filter_mode_t;

/*! @brief Reset pin control structure */
typedef struct _llwu_reset_pin_mode {
    bool enable;  /*!< RESET pin is enabled as low-leakage mode exit source. */
    bool filter;  /*!< Digital filter on RESET pin.                          */
} llwu_reset_pin_mode_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Low-Leakage Wakeup Unit Control APIs
 * @{
 */

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*!
 * @brief Sets the external input pin source mode.
 *
 * This function sets the external input pin source mode that is used
 * as a wake up source. 
 *
 * @param base      Register base address of LLWU
 * @param pinMode       pin configuration mode defined in llwu_external_pin_modes_t
 * @param pinNumber     pin number specified
 */
void LLWU_HAL_SetExternalInputPinMode(LLWU_Type * base,
                                      llwu_external_pin_modes_t pinMode,
                                      llwu_wakeup_pin_t pinNumber);

#endif

#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
/*!
 * @brief Enables/disables the internal module source.
 *
 * This function enables/disables the internal module source mode that is used
 * as a wake up source. 
 *
 * @param base      Register base address of LLWU
 * @param moduleNumber  module number specified
 * @param enable        enable or disable setting
 */
void LLWU_HAL_SetInternalModuleCmd(LLWU_Type * base, llwu_wakeup_module_t moduleNumber, bool enable);
#endif

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*!
 * @brief Gets the external wakeup source flag.
 *
 * This function checks the external pin flag to detect whether the MCU is
 * woke up by the specific pin.
 *
 * @param base      Register base address of LLWU
 * @param pinNumber     pin number specified
 * @return true if the specific pin is wake up source.
 */
bool LLWU_HAL_GetExternalPinWakeupFlag(LLWU_Type * base, llwu_wakeup_pin_t pinNumber);

/*!
 * @brief Clears the external wakeup source flag.
 *
 * This function clears the external wakeup source flag for a specific pin.
 *
 * @param base      Register base address of LLWU
 * @param pinNumber     pin number specified
 */
void LLWU_HAL_ClearExternalPinWakeupFlag(LLWU_Type * base, llwu_wakeup_pin_t pinNumber);
#endif

#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
/*!
 * @brief Gets the internal module wakeup source flag.
 *
 * This function checks the internal module wake up flag to detect whether the MCU is
 * woke up by the specific internal module.
 *
 * @param base      Register base address of LLWU
 * @param moduleNumber  module number specified
 * @return true if the specific module is wake up source.
 */
bool LLWU_HAL_GetInternalModuleWakeupFlag(LLWU_Type * base, llwu_wakeup_module_t moduleNumber);
#endif

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*!
 * @brief Sets the pin filter configuration.
 *
 * This function sets the pin filter configuration.
 *
 * @param base      Register base address of LLWU
 * @param filterNumber  filter number specified
 * @param pinFilterMode filter mode configuration
 */
void LLWU_HAL_SetPinFilterMode(LLWU_Type * base, uint32_t filterNumber, 
                               llwu_external_pin_filter_mode_t pinFilterMode);

/*!
 * @brief Gets the filter detection flag.
 *
 * This function checks the filter detection flag to detect whether the external
 * pin selected by the specific filter is the wake up source.
 *
 * @param base      Register base address of LLWU
 * @param filterNumber  filter number specified
 * @return true if the the pin is wakeup source
 */
bool LLWU_HAL_GetFilterDetectFlag(LLWU_Type * base, uint32_t filterNumber);

/*!
 * @brief Clears the filter detection flag.
 *
 * This function will clear the filter detection flag.
 *
 * @param base      Register base address of LLWU
 * @param filterNumber  filter number specified
 */
void LLWU_HAL_ClearFilterDetectFlag(LLWU_Type * base, uint32_t filterNumber);
#endif

#if FSL_FEATURE_LLWU_HAS_RESET_ENABLE
/*!
 * @brief Sets the reset pin mode.
 *
 * This function sets how the reset pin is used as a low leakage mode exit source.
 *
 * @param base         Register base address of LLWU
 * @param resetPinMode RESET pin mode defined in llwu_reset_pin_mode_t
 */
void LLWU_HAL_SetResetPinMode(LLWU_Type * base, llwu_reset_pin_mode_t resetPinMode);

#endif

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_LLWU_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

