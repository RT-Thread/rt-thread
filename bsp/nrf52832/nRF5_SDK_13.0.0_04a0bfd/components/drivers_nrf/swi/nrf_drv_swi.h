/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/**@file
 *
 * @defgroup nrf_drv_swi SWI driver
 * @{
 * @ingroup  nrf_drivers
 *
 * @brief    Driver for software interrupts (SWI).
 * @details  The SWI driver allows the user to allocate SWIs and pass extra flags to interrupt handler functions.
 */

#ifndef NRF_DRV_SWI_H__
#define NRF_DRV_SWI_H__

#include <stdbool.h>
#include <stdint.h>
#include "sdk_config.h"
#include "app_util.h"
#include "app_util_platform.h"
#include "sdk_common.h"
#include "sdk_errors.h"
#include "nrf_peripherals.h"

#ifndef EGU_ENABLED
    #define EGU_ENABLED 0
#endif

#if NRF_MODULE_ENABLED(EGU)
#include "nrf_egu.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t nrf_swi_t;         ///< @brief SWI channel (unsigned integer).

/** @brief   SWI user flags (unsigned integer).
 *
 *  User flags are set during the SWI trigger and passed to the callback function as an argument.
 */
typedef uint16_t nrf_swi_flags_t;

/** @brief Unallocated channel value. */
#define NRF_SWI_UNALLOCATED ((nrf_swi_t) 0xFFFFFFFFuL)

/** @brief   SWI handler function.
 *
 *  Takes two arguments: SWI number (nrf_swi_t) and flags (nrf_swi_flags_t).
 */
typedef void (* nrf_swi_handler_t)(nrf_swi_t, nrf_swi_flags_t);

/**@brief Maximum numbers of SWIs. This number is fixed for a specific chip. */
#if NRF_MODULE_ENABLED(EGU)
#define SWI_MAX              EGU_COUNT
#else
#define SWI_MAX              SWI_COUNT
/**@brief Number of flags per SWI (fixed number). */
#define SWI_MAX_FLAGS        16
#endif

#ifdef SOFTDEVICE_PRESENT
    #if SWI_COUNT > 2
        #undef SWI_COUNT
        #define SWI_COUNT 2
    #endif
#else
    #ifdef SVCALL_AS_NORMAL_FUNCTION
    // Serialization is enabled.
        #if SWI_COUNT > 2
            #undef SWI_COUNT
            #define SWI_COUNT 2
        #endif
    #endif
#endif

#if NRF_MODULE_ENABLED(PWM_NRF52_ANOMALY_109_WORKAROUND)
    #if   (PWM_NRF52_ANOMALY_109_EGU_INSTANCE == 0)
        #define SWI_DISABLE0
    #elif (PWM_NRF52_ANOMALY_109_EGU_INSTANCE == 1)
        #define SWI_DISABLE1
    #elif (PWM_NRF52_ANOMALY_109_EGU_INSTANCE == 2)
        #define SWI_DISABLE2
    #elif (PWM_NRF52_ANOMALY_109_EGU_INSTANCE == 3)
        #define SWI_DISABLE3
    #elif (PWM_NRF52_ANOMALY_109_EGU_INSTANCE == 4)
        #define SWI_DISABLE4
    #elif (PWM_NRF52_ANOMALY_109_EGU_INSTANCE == 5)
        #define SWI_DISABLE5
    #endif
#endif

/**@brief Default SWI priority. */
#define SWI_DEFAULT_PRIORITY APP_IRQ_PRIORITY_LOWEST


/**@brief Function for initializing the SWI module.
 *
 * @retval     NRF_SUCCESS                           If the module was successfully initialized.
 * @retval     NRF_ERROR_MODULE_ALREADY_INITIALIZED  If the module has already been initialized.
 */
ret_code_t nrf_drv_swi_init(void);


/**@brief Function for uninitializing the SWI module.
 *
 * This function also disables all SWIs.
 */
void nrf_drv_swi_uninit(void);


/**@brief Function for allocating a first unused SWI instance and setting a handler.
 * @details The event handler function returns void and takes one uint32_t argument (SWI number).
 *
 * @param[out] p_swi         Pointer to the SWI that has been allocated.
 * @param[in]  event_handler Event handler function.
 *                           If NULL, no interrupt will be enabled (can be NULL only if the EGU driver is enabled).
 *                           For classic SWI, must be a valid handler pointer.
 * @param[in]  priority      Interrupt priority.
 *
 * @retval     NRF_SUCCESS      If the SWI was successfully allocated.
 * @retval     NRF_ERROR_NO_MEM If there is no available SWI to be used.
 */
ret_code_t nrf_drv_swi_alloc(nrf_swi_t * p_swi, nrf_swi_handler_t event_handler, uint32_t priority);


/**@brief Function for freeing a previously allocated SWI.
 *
 * @param[in,out]  p_swi     SWI to free. The value is changed to NRF_SWI_UNALLOCATED on success.
 */
void nrf_drv_swi_free(nrf_swi_t * p_swi);


/**@brief Function for triggering the SWI.
 *
 * @param[in]  swi           SWI to trigger.
 * @param[in]  flag_number   Number of user flag to trigger.
 */
void nrf_drv_swi_trigger(nrf_swi_t swi, uint8_t flag_number);


#if (EGU_ENABLED > 0) || defined(__SDK_DOXYGEN__)


/**@brief Function for returning the EGU trigger task address.
 *
 * @param[in]  swi           SWI instance.
 * @param[in]  channel       Number of the EGU channel.
 *
 * @returns EGU trigger task address.
 */
uint32_t nrf_drv_swi_task_trigger_address_get(nrf_swi_t swi, uint8_t channel);

/**@brief Function for returning the EGU triggered event address.
 *
 * @param[in]  swi           SWI instance.
 * @param[in]  channel       Number of the EGU channel.
 *
 * @returns EGU triggered event address.
 */
uint32_t nrf_drv_swi_event_triggered_address_get(nrf_swi_t swi, uint8_t channel);

#endif // NRF_MODULE_ENABLED(EGU)



#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_SWI_H__

/** @} */
