/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#ifndef _APP_BLE_GAP_SEC_KEYS_H
#define _APP_BLE_GAP_SEC_KEYS_H

 /**@file
 *
 * @defgroup app_ble_gap_sec_keys GAP Functions for managing memory for security keys in the application device.
 * @{
 * @ingroup  ser_app_s130_codecs
 *
 * @brief    GAP Application auxiliary functions for synchronizing the GAP security keys with the ones stored in the connectivity device.
 */

#include "ble_gap.h"
#include "ble_types.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief GAP connection - keyset mapping structure.
 *
 * @note  This structure is used to map keysets to connection instances and store them in a static table.
 */
typedef struct
{
  uint16_t               conn_handle;    /**< Connection handle.*/
  uint8_t                conn_active;    /**< Indication that keys for this connection are used by the SoftDevice. 0: keys used; 1: keys not used. */
  ble_gap_sec_keyset_t   keyset;         /**< Keyset structure, see @ref ble_gap_sec_keyset_t.*/
} ser_ble_gap_app_keyset_t;

/**@brief Allocates the instance in m_app_keys_table[] for storage of encryption keys.
 *
 * @param[in]     conn_handle         conn_handle
 * @param[out]    p_index             Pointer to the index of the allocated instance.
 *
 * @retval NRF_SUCCESS                Context allocated.
 * @retval NRF_ERROR_NO_MEM           No free instance available.
 */
uint32_t app_ble_gap_sec_context_create(uint16_t conn_handle, uint32_t *p_index);

/**@brief Release the instance identified by a connection handle.
 *
 * @param[in]     conn_handle         conn_handle
 *
 * @retval NRF_SUCCESS                Context released.
 * @retval NRF_ERROR_NOT_FOUND        Instance with conn_handle not found.
 */
uint32_t app_ble_gap_sec_context_destroy(uint16_t conn_handle);

/**@brief Finds index of instance identified by a connection handle in m_app_keys_table[].
 *
 * @param[in]     conn_handle         conn_handle
 *
 * @param[out]    p_index             Pointer to the index of the entry in the context table corresponding to the given conn_handle.
 *
 * @retval NRF_SUCCESS                Context found.
 * @retval NRF_ERROR_NOT_FOUND        Instance with conn_handle not found.
 */
uint32_t app_ble_gap_sec_context_find(uint16_t conn_handle, uint32_t *p_index);
/** @} */

#if NRF_SD_BLE_API_VERSION >= 6
/**
 * @brief Stores buffer for adv report data.
 *
 * @param p_data Pointer to the buffer.
 *
 * @return NRF_SUCCESS or error in case pointer is already set.
 */
uint32_t app_ble_gap_scan_data_set(ble_data_t const * p_data);

/**
 * @brief Returns pointer to the buffer for storing report data. Returns error if not paired with
 *        @ref app_ble_gap_scan_data_set call.
 *
 * @param[out] p_data Stored data.
 * @return NRF_SUCCESS or error in case pointer is already cleared.
 */
uint32_t app_ble_gap_scan_data_fetch_clear(ble_data_t * p_data);

/**
 * @brief Function for registering data pointers related with given adv_handle.
 *
 * @param adv_handle      Handle.
 * @param p_adv_data      Adv_data buffer.
 * @param p_scan_rsp_data Scan_rsp_data buffer.
 *
 * @return NRF_SUCCESS or error.
 *
 */
uint32_t app_ble_gap_adv_set_register(uint8_t adv_handle, uint8_t * p_adv_data, uint8_t * p_scan_rsp_data);


/**
 * @brief Function for unregistering given .
 *
 * @param[in]  adv_handle       Handle.
 * @param[out] pp_adv_data      Pointer to adv_data buffer associated with given adv_handle.
 * @param[out] pp_scan_rsp_data Pointer to adv_data buffer associated with given adv_handle.
 *
 * @return NRF_SUCCESS or error.
 *
 */
uint32_t app_ble_gap_adv_set_unregister(uint8_t adv_handle, uint8_t * * pp_adv_data, uint8_t **pp_scan_rsp_data);
#endif
#ifdef __cplusplus
}
#endif

#endif //_APP_BLE_GAP_SEC_KEYS_H
