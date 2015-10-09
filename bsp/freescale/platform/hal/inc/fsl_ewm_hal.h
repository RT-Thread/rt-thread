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
#ifndef __FSL_EWM_HAL_H__
#define __FSL_EWM_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_EWM_COUNT

/*! 
 * @addtogroup ewm_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! 
 * @brief Data structure for EWM initialize
 *
 * This structure is used when initializing the EWM.
 * @internal gui name="Basic configuration" id="ewmCfg"
 */
typedef struct _ewm_config
{
    bool ewmEnable;   	       /*!< Enable EWM module @internal gui name="Enable EWM module" id="EnableModule" */
    bool ewmInEnable;  	       /*!< Enable EWM_in input enable @internal gui name="EWM_in input" id="Input" */
    bool ewmInAssertLogic;     /*!< Set EWM_in signal assertion state @internal gui name="EWM_in signal assertion" id="Assertion" */
    bool intEnable;   	       /*!< Enable EWM interrupt enable @internal gui name="EWM interrupt" id="Interrupt" */
#if FSL_FEATURE_EWM_HAS_PRESCALER
    uint8_t ewmPrescalerValue; /*!< Set EWM prescaler value @internal gui name="Prescaler" id="Prescaler" */
#endif    
    uint8_t ewmCmpLowValue;    /*!< Set EWM compare low register value @internal gui name="Compare low register value" id="LowValue" default="0" */
    uint8_t ewmCmpHighValue;   /*!< Set EWM compare high register value, the maximum value should be 0xfe otherwise the counter will never expire @internal gui name="Compare high register value" id="HighValue" default="254" */
}ewm_config_t;

/*! @brief ewm status return codes.*/
typedef enum _ewm_status {
    kStatus_EWM_Success         = 0x0U, /*!< EWM operation Succeed      */
    kStatus_EWM_Fail            = 0x01, /*!< EWM operation Failed       */
    kStatus_EWM_NotInitlialized = 0x2U, /*!< EWM is not initialized yet */
    kStatus_EWM_NullArgument    = 0x3U, /*!< Argument is NULL           */
}ewm_status_t;

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
 * @brief Enable the EWM.
 * 
 * This function enables the EWM.
 *
 * @param base The EWM peripheral base address
 */
static inline void EWM_HAL_Enable(EWM_Type * base)
{
    EWM_BWR_CTRL_EWMEN(base, 1U);
}

/*!
 * @brief Disable the EWM.
 * 
 * This function disables the EWM.
 *
 * @param base The EWM peripheral base address
 */
static inline void EWM_HAL_Disable(EWM_Type * base)
{
    EWM_BWR_CTRL_EWMEN(base, 0U);
}

/*!
 * @brief Checks whether the EWM is enabled.
 * 
 * This function checks whether the EWM is enabled.
 *
 * @param base The EWM peripheral base address
 * @return State of the module
 * @retval false means EWM is disabled
 * @retval true means WODG is enabled
 */
static inline bool EWM_HAL_IsEnable(EWM_Type * base)
{
    return ((bool)EWM_BRD_CTRL_EWMEN(base));
}

/*!
 * @brief Enable/Disable EWM interrupt.
 * 
 * This function sets EWM enable/disable.
 *
 * @param base The EWM peripheral base address
 * @param enable Set EWM interrupt enable/disable
 */
static inline void EWM_HAL_SetIntCmd(EWM_Type * base, bool enable)
{
   EWM_BWR_CTRL_INTEN(base, enable);
}

/*!
 * @brief Set EWM compare low register value.
 * 
 * This function sets EWM compare low register value and defines the minimum cycles to service EWM,
 * when counter value is greater than or equal to ewm compare low register value, refresh EWM can be successful,
 * and this register is write once, one more write will cause bus fault.
 *
 * @param base The EWM peripheral base address
 * @param minServiceCycles The EWM compare low register value 
 */
static inline void EWM_HAL_SetCmpLowRegValue(EWM_Type * base, uint8_t minServiceCycles)
{
    EWM_WR_CMPL(base, minServiceCycles);
}

/*!
 * @brief Set EWM compare high register value.
 * 
 * This function sets EWM compare high register value and defines the maximum cycles to service EWM,
 * when counter value is less than or equal to ewm compare high register value, refresh EWM can be successful,
 * the compare high register value must be greater than compare low register value,
 * and this register is write once, one more write will cause bus fault.
 *
 * @param base The EWM peripheral base address
 * @param maxServiceCycles The EWM compare high register value 
 */
static inline void EWM_HAL_SetCmpHighRegValue(EWM_Type * base, uint8_t maxServiceCycles)
{
    EWM_WR_CMPH(base, maxServiceCycles);
}

/*!
 * @brief Service EWM.
 * 
 * This function reset EWM counter to zero and 
 * the period of writing the frist value and the second value should be within 15 bus cycles.
 *
 * @param base The EWM peripheral base address
*/
static inline void EWM_HAL_Refresh(EWM_Type * base)
{
    EWM_WR_SERV(base, (uint8_t)0xB4U);
    EWM_WR_SERV(base, (uint8_t)0x2CU);
}

/*!
 * @brief Config EWM control register.
 * 
 * This function configures EWM control register,
 * EWM enable bitfeild, EWM ASSIN bitfeild and EWM INPUT enable bitfeild are WRITE ONCE, one more write will cause bus fault.
 *
 * @param base The EWM peripheral base address
 * @param ewmConfigPtr config EWM CTRL register
 */
void EWM_HAL_SetConfig(EWM_Type * base, const ewm_config_t *ewmConfigPtr);

/*!
 * @brief Restores the EWM module to reset value.
 *
 * This function restores the EWM module to reset value.
 *
 * @param base The EWM peripheral base address
 */
void EWM_HAL_Init(EWM_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_EWM_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

