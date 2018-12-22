/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_DRV_LPCOMP_H__
#define NRF_DRV_LPCOMP_H__

#include "nrf_lpcomp.h"
#include "sdk_errors.h"
#include "nrf_drv_common.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup nrf_lpcomp LPCOMP HAL and driver
 * @ingroup nrf_drivers
 * @brief Low Power Comparator (LPCOMP) APIs.
 * @details The LPCOMP HAL provides basic APIs for accessing the registers of Low Power Comparator.
 * The LPCOMP driver provides APIs on a higher level.
 *
 * @defgroup nrf_drv_lpcomp LPCOMP driver
 * @{
 * @ingroup nrf_lpcomp
 * @brief Low Power Comparator (LPCOMP) driver.
 */

/**@brief LPCOMP event handler function type.
 * @param[in] event  LPCOMP event.
 */
typedef void (* lpcomp_events_handler_t)(nrf_lpcomp_event_t event);

/**@brief LPCOMP configuration.
 */
typedef struct
{
    nrf_lpcomp_config_t    hal;                /**< LPCOMP HAL configuration. */
    nrf_lpcomp_input_t     input;              /**< Input to be monitored. */
    uint8_t                interrupt_priority; /**< LPCOMP interrupt priority. */
} nrf_drv_lpcomp_config_t;

/** @brief LPCOMP driver default configuration including the LPCOMP HAL configuration. */
#ifdef NRF52_SERIES
#define NRF_DRV_LPCOMP_DEFAULT_CONFIG                                                                                     \
    {                                                                                                                     \
        .hal                = {(nrf_lpcomp_ref_t)LPCOMP_CONFIG_REFERENCE , (nrf_lpcomp_detect_t)LPCOMP_CONFIG_DETECTION,  \
                               (nrf_lpcomp_hysteresis_t)LPCOMP_CONFIG_HYST},                                              \
        .input              = (nrf_lpcomp_input_t)LPCOMP_CONFIG_INPUT,                                                    \
        .interrupt_priority = LPCOMP_CONFIG_IRQ_PRIORITY                                                                  \
    }
#else
#define NRF_DRV_LPCOMP_DEFAULT_CONFIG                                                                                     \
    {                                                                                                                     \
        .hal                = {(nrf_lpcomp_ref_t)LPCOMP_CONFIG_REFERENCE , (nrf_lpcomp_detect_t)LPCOMP_CONFIG_DETECTION},  \
        .input              = (nrf_lpcomp_input_t)LPCOMP_CONFIG_INPUT,                                                    \
        .interrupt_priority = LPCOMP_CONFIG_IRQ_PRIORITY                                                                  \
    }
#endif

/**
 * @brief Function for initializing the LPCOMP driver.
 *
 * This function initializes the LPCOMP driver, but does not enable the peripheral or any interrupts.
 * To start the driver, call the function nrf_drv_lpcomp_enable() after initialization.
 *
 * If no configuration structure is provided, the driver is initialized with the default settings.
 *
 * @param[in] p_config              Initial configuration. If NULL, the default configuration is used.
 * @param[in] events_handler        Handler function.
 * @retval NRF_ERROR_INVALID_PARAM If the configuration is invalid.
 * @retval NRF_ERROR_INVALID_STATE If the driver has already been initialized.
 */
ret_code_t nrf_drv_lpcomp_init(const nrf_drv_lpcomp_config_t * p_config,
                               lpcomp_events_handler_t   events_handler);


/**
 *  @brief Function for uninitializing the LCOMP driver.
 *
 *  This function uninitializes the LPCOMP driver. The LPCOMP peripheral and
 *  its interrupts are disabled, and local variables are cleaned. After this call, you must
 *  initialize the driver again by calling nrf_drv_lpcomp_init() if you want to use it.
 *
 *  @sa nrf_drv_lpcomp_disable()
 *  @sa nrf_drv_lpcomp_init()
 */
void     nrf_drv_lpcomp_uninit(void);

/**@brief Function for enabling the LPCOMP peripheral and interrupts.
 *
 * Before calling this function, the driver must be initialized. This function
 * enables the LPCOMP peripheral and its interrupts.
 *
 * @sa nrf_drv_lpcomp_disable()
 */
void nrf_drv_lpcomp_enable(void);

/**@brief Function for disabling the LPCOMP peripheral.
 *
 * Before calling this function, the driver must be initialized. This function disables the LPCOMP
 * peripheral and its interrupts.
 *
 * @sa nrf_drv_lpcomp_enable()
 */
void nrf_drv_lpcomp_disable(void);

/**
 *@}
 **/


#ifdef __cplusplus
}
#endif

 #endif /* NRF_DRV_LPCOMP_H__ */
