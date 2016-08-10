/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#ifndef __FSL_LPTMR_DRIVER_H__
#define __FSL_LPTMR_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_lptmr_hal.h"
#include "fsl_sim_hal.h"
#if FSL_FEATURE_SOC_LPTMR_COUNT

/*!
 * @addtogroup lptmr_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! @brief Table of base addresses for LPTMR instances. */
extern LPTMR_Type * const g_lptmrBase[];

/*! @brief Table to save LPTMR IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_lptmrIrqId[LPTMR_INSTANCE_COUNT];

/*!
 * @brief Data structure to initialize the LPTMR
 *
 * This structure is used when initializing the LPTMR during the LPTMR_DRV_Init function call.
 * @internal gui name="LPTMR configuration" id="lptmrCfg"
 */
typedef struct LptmrUserConfig {
    lptmr_timer_mode_t timerMode; /*!< Timer counter mode or pulse counter mode @internal gui name="Timer mode" */
    lptmr_pin_select_t pinSelect; /*!< LPTMR pulse input pin select @internal gui name="Pin select" */
    lptmr_pin_polarity_t pinPolarity; /*!< LPTMR pulse input pin polarity @internal gui name="Pin polarity" */
    bool freeRunningEnable; /*!< Free running configure. True means enable free running @internal gui name="Free running" */
    bool  prescalerEnable; /*!< Prescaler enable configure. True means enable prescaler @internal gui name="Prescaler" */
    clock_lptmr_src_t prescalerClockSource; /*!< LPTMR clock source @internal gui name="Prescaler clock source" */
    lptmr_prescaler_value_t prescalerValue; /*!< Prescaler value @internal gui name="Prescaler value" */
    bool isInterruptEnabled;  /*!< Timer interrupt 0-disable/1-enable @internal gui name="Interrupt" */
} lptmr_user_config_t;

/*!
 * @brief Defines a type of the user-defined callback function.
 */
typedef void (*lptmr_callback_t)(void);

/*!
 * @brief Internal driver state information.
 *
 * The contents of this structure are internal to the driver and should not be
 *  modified by users. Contents of the structure are subject to change in
 *  future releases.
 */
typedef struct LptmrState {
    lptmr_callback_t userCallbackFunc; /*!< Callback function that is executed in ISR. */
    uint32_t prescalerClockHz;
} lptmr_state_t;

/*! @brief Table to save pointers to context data. */
extern lptmr_state_t * g_lptmrStatePtr[LPTMR_INSTANCE_COUNT];

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPTMR Driver
 * @{
 */

/*!
 * @brief Initializes the LPTMR driver.
 *
 * This function initializes the LPTMR. The LPTMR can be initialized as a time counter or pulse counter,
 * which is determined by the timerMode in the lptmr_user_config_t. pinSelect and pinPolarity do not need to be
 * configured while working as a time counter.
 *
 * @param instance The LPTMR peripheral instance number.
 * @param userStatePtr The pointer to the structure of the context memory, see #lptmr_state_t.
 * @param userConfigPtr The pointer to the LPTMR user configure structure, see #lptmr_user_config_t.
 * @return kStatus_LPTMR_Success means succeed, otherwise means failed.
 */
lptmr_status_t LPTMR_DRV_Init(uint32_t instance, lptmr_state_t *userStatePtr, const lptmr_user_config_t* userConfigPtr);

/*!
 * @brief Deinitializes the LPTMR driver.
 *
 * This function  deinitializes the LPTMR. It disables the interrupt and turns off the LPTMR clock.
 *
 * @param instance The LPTMR peripheral instance number.
 * @return kStatus_LPTMR_Success means succeed, otherwise means failed.
 */
lptmr_status_t LPTMR_DRV_Deinit(uint32_t instance);

/*!
 * @brief Starts the LPTMR counter.
 *
 * This function starts the LPTMR counter. Ensure that all necessary
 * configurations are set before calling this function.
 *
 * @param instance The LPTMR peripheral instance number.
 * @return kStatus_LPTMR_Success means success. Otherwise, means failure.
 */
lptmr_status_t LPTMR_DRV_Start(uint32_t instance);

/*!
 * @brief Stops the LPTMR counter.
 *
 * This function stops the LPTMR counter.
 *
 * @param instance The LPTMR peripheral instance number.
 * @return kStatus_LPTMR_Success means success. Otherwise, means failure.
 */
lptmr_status_t LPTMR_DRV_Stop(uint32_t instance);

/*!
 * @brief Configures the LPTMR timer period in microseconds.
 *
 * This function configures the LPTMR time period while the LPTMR is working as a
 * time counter. After the time period in microseconds, the callback function is called.
 * This function cannot be called while the LPTMR is working as a pulse counter.
 * The value in microseconds (us) should be integer multiple of the clock source time slice. If the clock source
 * is 1 kHz, then both 2000 µs and 3000 µs are valid while 2500 µs gets the same result as the 2000 µs,
 * because 2500 µs cannot be generated in 1 kHz clock source.
 *
 * @param instance The LPTMR peripheral instance number.
 * @param us time period in microseconds.
 * @return kStatus_LPTMR_Success means success. Otherwise, means failure.
 */
lptmr_status_t LPTMR_DRV_SetTimerPeriodUs(uint32_t instance, uint32_t us);

 /*!
 * @brief Gets the current LPTMR time in microseconds.
 *
 * This function gets the current time while operating as a time counter.
 * This function cannot be called while operating as a pulse counter.
 *
 * @param instance The LPTMR peripheral instance number.
 * @return current time in microsecond unit.
 */
uint32_t LPTMR_DRV_GetCurrentTimeUs(uint32_t instance);

/*!
 * @brief Sets the pulse period value.
 *
 * This function configures the pulse period of the LPTMR while working as a
 * pulse counter. After the count of pulsePeriodValue pulse is captured, the callback function
 * is called.
 * This function cannot be called while operating as a time counter.
 *
 * @param instance The LPTMR peripheral instance number.
 * @param pulsePeriodCount pulse period value.
 * @return kStatus_LPTMR_Success means success. Otherwise, means failure.
 */
lptmr_status_t LPTMR_DRV_SetPulsePeriodCount(uint32_t instance, uint32_t pulsePeriodCount);

 /*!
 * @brief Gets the current pulse count.
 *
 * This function gets the current pulse count captured on the pulse input pin.
 * This function cannot be called while operating as a time counter.
 *
 * @param instance The LPTMR peripheral instance number.
 * @return pulse count captured on the pulse input pin.
 */
uint32_t LPTMR_DRV_GetCurrentPulseCount(uint32_t instance);

/*!
 * @brief Installs the user-defined callback in the LPTMR module.
 *
 * This function installs the user-defined callback in the LPTMR module.
 * When an LPTMR interrupt request is served, the callback is executed
 * inside the ISR.
 *
 * @param instance LPTMR instance ID.
 * @param userCallback User-defined callback function.
 * @return kStatus_LPTMR_Success means success. Otherwise, means failure.
 */
lptmr_status_t LPTMR_DRV_InstallCallback(uint32_t instance, lptmr_callback_t userCallback);

/*!
 * @brief Driver-defined ISR in the LPTMR module.
 *
 * This function is the driver-defined ISR in the LPTMR module.
 * It includes the process for interrupt mode defined by the driver. Currently, it
 * is called inside the system-defined ISR.
 *
 * @param instance LPTMR instance ID.
 */
void LPTMR_DRV_IRQHandler(uint32_t instance);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_LPTMR_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

