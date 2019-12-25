/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_tps TX Power Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief TX Power Service module.
 *
 * @details This module implements the TX Power Service with the TX Power Level characteristic.
 *          During initialization it adds the TX Power Service and TX Power Level characteristic
 *          with the specified initial value to the BLE stack database.
 *
 *          It provides a function for letting the application update the TX Power Level
 *          characteristic.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_TPS_H__
#define BLE_TPS_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_tps instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_TPS_DEF(_name)                                                                          \
static ble_tps_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_TPS_BLE_OBSERVER_PRIO,                                                     \
                     ble_tps_on_ble_evt, &_name)


/**@brief TX Power Service init structure. This contains all options and data needed for
 *        initialization of the service. */
typedef struct
{
    int8_t          initial_tx_power_level;   /**< Initial value of the TX Power Level characteristic (in dBm). */
    security_req_t  tpl_rd_sec;               /**< Security requirement for reading TX Power Level characteristic. */
} ble_tps_init_t;

/**@brief TX Power Service structure. This contains various status information for the service. */
typedef struct
{
    uint16_t                  service_handle;           /**< Handle of TX Power Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t  tx_power_level_handles;   /**< Handles related to the TX Power Level characteristic. */
    uint16_t                  conn_handle;              /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
} ble_tps_t;


/**@brief Function for initializing the TX Power Service.
 *
 * @param[out]  p_hrs       TX Power Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_tps_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_tps_init(ble_tps_t * p_hrs, const ble_tps_init_t * p_tps_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the TX Power Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   TX Power Service structure.
 */
void ble_tps_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for setting the value of the TX Power Level characteristic.
 *
 * @param[in]   p_tps            TX Power Service structure.
 * @param[in]   tx_power_level   New TX Power Level (unit dBm, range -100 to 20).
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_tps_tx_power_level_set(ble_tps_t * p_tps, int8_t tx_power_level);


#ifdef __cplusplus
}
#endif

#endif // BLE_TPS_H__

/** @} */
