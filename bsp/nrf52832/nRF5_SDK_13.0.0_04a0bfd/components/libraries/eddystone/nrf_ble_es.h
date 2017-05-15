/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#ifndef NRF_ES_H__
#define NRF_ES_H__

#include <stdint.h>
#include "ble.h"

/**
 * @file
 * @defgroup eddystone Eddystone library
 * @ingroup app_common
 * @{
 *
 * @brief   Library for Eddystone beacons. This library is used in the @ref ble_sdk_app_es.
 *
 * @note    The API documentation is provided for reference only. You should
 *          not modify this library, and you should not use any functions
 *          except for the main level functions defined in @c nrf_ble_es.h
 *          in different contexts.
 */

/** @brief Eddystone event types. */
typedef enum {
  NRF_BLE_ES_EVT_ADVERTISEMENT_SENT,        //!< A non-connectable Eddystone frame advertisement was sent.
  NRF_BLE_ES_EVT_CONNECTABLE_ADV_STARTED,   //!< Advertising in connectable mode was started.
}nrf_ble_es_evt_t;

/**@brief Eddystone event handler type. */
typedef void (*nrf_ble_es_evt_handler_t)(nrf_ble_es_evt_t evt);

/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of
 * interest to the Eddystone library. It must be called from the @ref
 * softdevice_handler callback for all BLE events that are received from the
 * SoftDevice.
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void nrf_ble_es_on_ble_evt(ble_evt_t * p_ble_evt);

/**@brief Function for putting the beacon in connectable mode.
 *
 * @details This function makes the beacon advertise connectable advertisements.
 *          If the beacon is in a connected state, the request is ignored.
 */
void nrf_ble_es_on_start_connectable_advertising(void);

/** @brief Function for initializing the Eddystone library.
 *
 * @param[in]   evt_handler Event handler to be called for handling BLE events.
 */
void nrf_ble_es_init(nrf_ble_es_evt_handler_t evt_handler);

/**
 * @}
 */

#endif
