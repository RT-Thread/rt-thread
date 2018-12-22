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
/**@file
 * @addtogroup nrf_wdt WDT HAL and driver
 * @ingroup nrf_drivers
 * @brief Watchdog timer (WDT) APIs.
 * @details The WDT HAL provides basic APIs for accessing the registers of the watchdog timer.
 * The WDT driver provides APIs on a higher level.
 * @defgroup nrf_drv_wdt WDT driver
 * @{
 * @ingroup  nrf_wdt
 *
 * @brief    Driver for managing the watchdog timer (WDT).
 */

#ifndef NRF_DRV_WDT_H__
#define NRF_DRV_WDT_H__

#include <stdbool.h>
#include <stdint.h>
#include "sdk_errors.h"
#include "nrf_wdt.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Struct for WDT initialization. */
typedef struct
{
    nrf_wdt_behaviour_t    behaviour;          /**< WDT behaviour when CPU in sleep/halt mode. */
    uint32_t               reload_value;       /**< WDT reload value in ms. */
    uint8_t                interrupt_priority; /**< WDT interrupt priority */
} nrf_drv_wdt_config_t;

/**@brief WDT event handler function type. */
typedef void (*nrf_wdt_event_handler_t)(void);

/**@brief WDT channel id type. */
typedef nrf_wdt_rr_register_t nrf_drv_wdt_channel_id;

#define NRF_DRV_WDT_DEAFULT_CONFIG                                       \
    {                                                                    \
        .behaviour          = (nrf_wdt_behaviour_t)WDT_CONFIG_BEHAVIOUR, \
        .reload_value       = WDT_CONFIG_RELOAD_VALUE,                   \
        .interrupt_priority = WDT_CONFIG_IRQ_PRIORITY,                   \
    }
/**
 * @brief This function initializes watchdog.
 *
 * @param[in] p_config          Initial configuration. Default configuration used if NULL.
 * @param[in] wdt_event_handler specifies event handler provided by user.
 *
 * @note Function asserts if wdt_event_handler is NULL.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
ret_code_t nrf_drv_wdt_init(nrf_drv_wdt_config_t const * p_config,
                            nrf_wdt_event_handler_t     wdt_event_handler);

/**
 * @brief This function allocate watchdog channel.
 *
 * @note This function can not be called after nrf_drv_wdt_start(void).
 *
 * @param[out] p_channel_id      ID of granted channel.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
ret_code_t nrf_drv_wdt_channel_alloc(nrf_drv_wdt_channel_id * p_channel_id);

/**
 * @brief This function starts watchdog.
 *
 * @note After calling this function the watchdog is started, so the user needs to feed all allocated
 *       watchdog channels to avoid reset. At least one watchdog channel has to be allocated.
 */
void nrf_drv_wdt_enable(void);

/**
 * @brief This function feeds the watchdog.
 *
 * @details Function feeds all allocated watchdog channels.
 */
void nrf_drv_wdt_feed(void);

/**
 * @brief This function feeds the invidual watchdog channel.
 *
 * @param[in] channel_id      ID of watchdog channel.
 */
void nrf_drv_wdt_channel_feed(nrf_drv_wdt_channel_id channel_id);

/**@brief Function for returning a requested task address for the wdt driver module.
 *
 * @param[in]  task                One of the peripheral tasks.
 *
 * @retval     Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_wdt_ppi_task_addr(nrf_wdt_task_t task)
{
    return nrf_wdt_task_address_get(task);
}

/**@brief Function for returning a requested event address for the wdt driver module.
 *
 * @param[in]  event               One of the peripheral events.
 *
 * @retval     Event address
 */
__STATIC_INLINE uint32_t nrf_drv_wdt_ppi_event_addr(nrf_wdt_event_t event)
{
    return nrf_wdt_event_address_get(event);
}

#ifdef __cplusplus
}
#endif

#endif

/** @} */
